#include <format>
#include <iostream>

#include <app.h>

constexpr auto help_message() {
  return "Usage {} [--title-info] [--no-max-fps] [--help]\n"
         "\n"
         "Options:\n"
         "  --no-max-fps  Disable FPS limiter\n"
         "  --title-info  Shows game info in the window title\n"
         "\n"
         "  --help, -h    Show this help message\n";
}

int main(int argc, char** argv) {
  uint32_t flags = 0;

  if (argc > 0) {
    for (int i = 1; i < argc; i++) {
      std::string arg = argv[i];

      if (arg == "--help" || arg == "-h") {
        std::cout << std::format(help_message(), argv[0]) << std::endl;
        return 0;
      } else if (arg == "--no-max-fps") {
        flags += (uint32_t)AppFlags::APP_FLAG_NO_FPS_LIMIT;
      } else if (arg == "--title-info") {
        flags += (uint32_t)AppFlags::APP_FLAG_TITLE_INFO;
      } else {
        std::cout << "Unknown argument: " << arg << std::endl;

        std::cout << std::format(help_message(), argv[0]) << std::endl;
        return 1;
      }
    }
  }

  App app;
  app.set_flags(flags);
  return app.run();
}
