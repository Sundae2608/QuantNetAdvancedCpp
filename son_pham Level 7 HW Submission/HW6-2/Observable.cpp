#include "Observable.h"

#include <algorithm>
#include <deque>
#include <functional>
#include <iostream>

template class Observable<std::deque>;

template <template <typename...> class Container>
int Observable<Container>::addObserver(std::function<void()> observer) {
  int observerId = nextObserverId++;
  observers.push_back(ObserverWrapper<Container<int>>(observer, observerId));
  std::cout << "Added observer with ID: " << observerId << std::endl;
  return observerId;
}

template <template <typename...> class Container>
void Observable<Container>::deleteObserver(int observerId) {
  auto it = std::find_if(
      observers.begin(), observers.end(),
      [observerId](const ObserverWrapper<Container<int>> &wrapper) {
        return wrapper.id == observerId;
      });
  if (it != observers.end()) {
    std::cout << "Deleted observer with ID: " << observerId << std::endl;
    observers.erase(it);
  }
}

template <template <typename...> class Container>
void Observable<Container>::notifyObservers() {
  for (const auto &wrapper : observers) {
    wrapper.observer();
  }
}