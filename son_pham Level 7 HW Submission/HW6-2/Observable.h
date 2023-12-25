#ifndef OBSERVABLE_H
#define OBSERVABLE_H

#include <deque>
#include <functional>

template <template <typename...> class Container> class Observable {
public:
  int addObserver(std::function<void()> observer);
  void deleteObserver(int observerId);
  void notifyObservers();

private:
  template <typename T> class ObserverWrapper {
  public:
    ObserverWrapper(std::function<void()> observer, int id)
        : observer(observer), id(id) {}

    std::function<void()> observer;
    int id;
  };

  Container<ObserverWrapper<int>> observers;
  int counterValue = 0;
  int nextObserverId = 1;
};

#endif // OBSERVABLE_H