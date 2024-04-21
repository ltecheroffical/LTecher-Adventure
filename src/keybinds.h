#include <map>

#include <SDL3/SDL.h>


#ifndef KEYBINDS_H
#define KEYBINDS_H

typedef enum Keybind {
  PLAYER_UP,
  PLAYER_DOWN,
  PLAYER_LEFT,
  PLAYER_RIGHT
} Keybind;

class Keybinds {
public:
  static Keybinds& singleton() {
    static Keybinds instance;
    return instance;
  }

  /*
   * Gets the scancode of a keybind
   *
   * @param keybind The keybind
   * @param scancode The pointer to put the result into
   *
   * @returns True if the keybind exists or false if it doesn't
   */
  bool get(const Keybind keybind, SDL_Scancode *scancode) const {
    if (this->_keybinds.find(keybind) == this->_keybinds.end()) {
      return false;
    }
    *scancode = this->_keybinds.at(keybind);
    return true;
  }

  /*
   * Gets the scancode of a keybind
   *
   * @param keybind The keybind
   *
   * @returns SDL_SCANCODE_UNKNOWN if the keybind doesn't exist or SDL_Scancode
   */
  SDL_Scancode get_or_null(const Keybind keybind) const {
    SDL_Scancode scancode;
    if (this->get(keybind, &scancode)) {
      return scancode;
    }
    return SDL_SCANCODE_UNKNOWN;
  }

  /*
   * Binds a keybind to a scancode
   *
   * @param keybind The keybind
   * @param scancode The scancode
   *
   * @returns True if the keybind was bound or false if it wasn't
   */
  bool bind(const Keybind keybind, const SDL_Scancode scancode) {
    // Does it exist already?
    if (this->_keybinds.find(keybind) != this->_keybinds.end()) {
      // We can bind it
      this->_keybinds[keybind] = scancode;
    }
    // We can't bind it
    return false;
  }

  /*
   * Resets the keybinds to the default keybinds
   */
  void reset();

private:
  Keybinds();
  ~Keybinds() = default;

  std::map<Keybind, SDL_Scancode> _keybinds;
};
#endif
