#include <string>
#include <stdexcept>

#ifndef APP_EXCEPTIONS
#define APP_EXCEPTIONS

namespace app::errors {
  class already_exists : public std::runtime_error {
  public:
    already_exists(std::string what) : std::runtime_error(what) {}
    already_exists() : std::runtime_error("App already exists") {}
  };

  class not_active : public std::runtime_error {
  public:
    not_active(std::string what) : std::runtime_error(what) {}
    not_active() : std::runtime_error("App not active") {}
  };
}
#endif
