#include <functional>
#include <future>
#include <iostream>

// Function categories
template <typename T> using FactoryFunction = std::function<T()>;
template <typename T> using ComputeFunction = std::function<T(const T &)>;
template <typename T> using DispatchFunction = std::function<void(T &)>;

// Class with Input-Processing-Output
template <typename T> class TmpProcessor {
private:
  FactoryFunction<T> _factory;
  ComputeFunction<T> _compute;
  DispatchFunction<T> _dispatch;

public:
  TmpProcessor(const FactoryFunction<T> &factory,
               const ComputeFunction<T> &compute,
               const DispatchFunction<T> &dispatch)
      : _factory(factory), _compute(compute), _dispatch(dispatch) {}

  // The template method pattern
  virtual void algorithm() final {
    T val = _factory();
    T val2 = _compute(val);
    _dispatch(val2);
  }
};

int main41() {
  // Example factory, compute, and dispatch functions
  FactoryFunction<int> factory = []() { return 10; };
  ComputeFunction<int> compute = [](const int &val) { return val * 2; };
  DispatchFunction<int> dispatch = [](int &val) {
    std::cout << "Result: " << val << std::endl;
  };

  // Create TmpProcessor instance
  TmpProcessor<int> processor(factory, compute, dispatch);

  // Run the algorithm
  processor.algorithm();
}