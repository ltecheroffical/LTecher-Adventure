#include <csignal>
#include <fstream>
#include <cstddef>
#include <iostream>

#include <save/game_save.h>

char *crash_data;
unsigned short crash_data_size;

void segfault_handler(int sig) {
  std::cout << "Segmentation fault caught!" << std::endl;

  std::ofstream crash_file("crash_data.bin", std::ios::out | std::ios::binary);

  crash_file.write(crash_data, crash_data_size);

  crash_file.close();
  std::cout << "The data has been written to crash_data.bin" << std::endl;
  exit(1);
}

int main() {
  // Register segfault signal
  signal(SIGSEGV, segfault_handler);

  GameSave save;
  
  std::ifstream urandom("/dev/urandom", std::ios::in | std::ios::binary);

  long long start = time(NULL);
  while (time(NULL) - start < 15) {
    unsigned char size = 0;
    char *data;

    urandom.read((char*)&size, sizeof(size));
    size = size;

    data = new char[size];
    urandom.read(data, size);

    // Make sure header is correct by copying the correct header
    if (size >= sizeof(uint16_t)) {
      const uint16_t HEADER = 0x91ef;
      memcpy(data, &HEADER, sizeof(HEADER));
    }

    crash_data = data;
    crash_data_size = size;

    save.load(data, size);
    delete data;
  }
  return 0;
}
