#pragma once

#include <functional>
#include <vector>

template<typename... Args>
class Event {
public:
  using Callback = std::function<void(Args...)>;

  void subscribe(Callback callback) {
      callbacks.push_back(callback);
  }

  void emit(Args... args) {
      for (auto& callback : callbacks) {
          callback(args...);
      }
  }

private:
  std::vector<Callback> callbacks;
};
