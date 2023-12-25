#ifndef OBSERVABLE_H
#define OBSERVABLE_H

#include <functional>
#include <list>

class Observer; // Forward declaration

class Observable {
public:
  virtual ~Observable() = default; // Add a virtual destructor
  void addObserver(std::function<void(Observable *)> observer);
  void deleteObservers();
  void notifyObservers();

private:
  std::list<std::function<void(Observable *)>> observers;
};

#endif // OBSERVABLE_H