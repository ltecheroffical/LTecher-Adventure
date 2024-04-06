#include <fstream>

#include "os_info.h"

const char *OS::get_name()
{
#if defined(__APPLE__)
  #if defined(__MACH__)
    #define PLATFORM (char*)"MacOS"
  #else
    #define PLATFORM (char*)"iOS"
  #endif
#elif defined(WIN32)
  #ifdef _WIN64
    #define PLATFORM (char*)"Win64"
  #else
    #define PLATFORM (char*)"Win32"
  #endif
#elif defined(__linux__)
  #define PLATFORM (char*)"Linux"
#else
  #define PLATFORM (char*)"UNKNOWN"
#endif

  return PLATFORM;
}

const char *OS::get_version()
{
#ifdef __MACH__
  // macOS
  std::ifstream file("/System/Library/CoreServices/SystemVersion.plist");

  std::string line;
  std::string version;
  while (std::getline(file, line)) {
    if (line.find("<key>ProductVersion</key>") != std::string::npos) {
      std::getline(file, line);
      size_t start = line.find("<string>") + 8;
      size_t end = line.find("</string>");
      version = line.substr(start, end - start);
      break;
    }
  }
  #define OS_VERSION version
#elif __linux__
  // Linux
  std::ifstream file("/etc/os-release");
  std::string line;
  std::string version;
  while (std::getline(file, line)) {
    if (line.find("VERSION_ID=") != std::string::npos) {
      version = line.substr(line.find("=") + 1);
      // Remove quotes if present
      version.erase(std::remove(version.begin(), version.end(), '\"'), version.end());
      break;
    }
  }
  #define OS_VERSION version
#else
  #define OS_VERSION "" 
#endif
  
#ifdef WIN32
  return OS_VERSION;
#else
  const char *os_ver = OS_VERSION.c_str();
  return os_ver;
#endif
}
