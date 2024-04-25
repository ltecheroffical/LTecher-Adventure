#include <iostream>

#include <app.h>

const char help_message[] = "Usage %s [--no-max-fps] [--help]\n"
                            "\n"
                            "Options:\n"
                            "  --no-max-fps  Disable FPS limiter\n"
                            "  --help, -h    Show this help message\n";

int main(int argc, char** argv) {
  int flags = 0;

  if (argc > 0) {
    for (int i = 1; i < argc; i++) {
      std::string arg = argv[i];

      if (arg == "--help" || arg == "-h") {
        char *help_formatted = new char[1024];
        snprintf(help_formatted, 1024, help_message, argv[0]);
        std::cout << help_formatted << std::endl;
        delete[] help_formatted;
        return 0;
      } else if (arg == "--no-max-fps") {
        flags |= APP_FLAGS_NO_FPS_LIMIT;
      } else {
        std::cout << "Unknown argument: " << arg << std::endl;

        char *help_formatted = new char[1024];
        snprintf(help_formatted, 1024, help_message, argv[0]);
        std::cout << help_formatted << std::endl;
        delete[] help_formatted;
        return 1;
      }
    }
  }

  App app;
  app.set_flags(flags);
  return app.run();
}
