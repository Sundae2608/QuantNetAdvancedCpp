#include <iostream>
#include <functional>
#include <future>
#include <chrono>
#include <thread>

// Function categories
namespace {

template <typename T>
using FactoryFunction = std::function<T()>;
template <typename T>
using ComputeFunction = std::function<T(const T&)>;
template <typename T, typename U>
using ComputeFunction2 = std::function<T(const U&, const U&)>;
using DispatchFunction = std::function<void(int&)>;

// Class with Input-Processing-Output
template <typename T>
class TmpProcessor
{
private:
    FactoryFunction<T> _factory;
    ComputeFunction<T> _f1;
    ComputeFunction<T> _f2;
    ComputeFunction<T> _f3;
    ComputeFunction2<T, T> _f4;
    DispatchFunction _dispatch;

public:
    TmpProcessor(const FactoryFunction<T>& factory, const ComputeFunction<T>& f1,
                 const ComputeFunction<T>& f2, const ComputeFunction<T>& f3,
                 const ComputeFunction2<T, T>& f4, const DispatchFunction& dispatch)
        : _factory(factory), _f1(f1), _f2(f2), _f3(f3), _f4(f4), _dispatch(dispatch) {}

    // The template method pattern
    void algorithm()
    {
        T a = _factory();
        T b = _f1(a);
        T c = _f2(a);
        T d = _f3(c);
        T f = _f4(b, d);
        _dispatch(f);
    }

  // The exercise ask for two versions of TmpProcessor. However
  // I decided to just write the parallel version inside
  // the processor for convenience.
  void algorithmParallel() {
    T a = _factory();

    // Launch all tasks using std::async and get futures
    std::future<T> futureF1 = std::async(std::launch::async, _f1, a);
    std::future<T> futureF2 = std::async(std::launch::async, _f2, a);
    std::future<T> futureF3 = std::async(std::launch::async, _f3, futureF2.get());
    std::future<T> futureF4 = std::async(std::launch::async, _f4, futureF1.get(), futureF3.get());

    T f = futureF4.get();
    _dispatch(f);
}
};

}

int main()
{
    FactoryFunction<int> factory = []() { return 5; };
    ComputeFunction<int> f1 = [](const int& a) { std::this_thread::sleep_for(std::chrono::seconds(1)); return a + 1; };
    ComputeFunction<int> f2 = [](const int& a) { std::this_thread::sleep_for(std::chrono::seconds(2)); return a * 2; };
    ComputeFunction<int> f3 = [](const int& c) { std::this_thread::sleep_for(std::chrono::seconds(1)); return c + 3; };
    ComputeFunction2<int, int> f4 = [](const int& b, const int& d) { std::this_thread::sleep_for(std::chrono::seconds(2)); return b * d; };
    DispatchFunction dispatch = [](int& f) { std::cout << "Result: " << f << std::endl; };

    TmpProcessor<int> processor(factory, f1, f2, f3, f4, dispatch);

    // Sequential processing with timing
    auto startTimeSeq = std::chrono::high_resolution_clock::now();
    processor.algorithm();
    auto endTimeSeq = std::chrono::high_resolution_clock::now();
    auto durationSeq = std::chrono::duration_cast<std::chrono::milliseconds>(endTimeSeq - startTimeSeq);
    std::cout << "Sequential processing time: " << durationSeq.count() << " ms" << std::endl;

    auto startTimePar = std::chrono::high_resolution_clock::now();
    processor.algorithmParallel();
    auto endTimePar = std::chrono::high_resolution_clock::now();
    auto durationPar = std::chrono::duration_cast<std::chrono::milliseconds>(endTimePar - startTimePar);
    std::cout << "Parallel processing time: " << durationPar.count() << " ms" << std::endl;

  // The output prints
  // Result: 78
  // Sequential processing time: 6001 ms
  // Result: 78
  // Parallel processing time: 5000 ms
    return 0;
}