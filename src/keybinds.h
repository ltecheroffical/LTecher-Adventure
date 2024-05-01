#include <map>

#include <SDL3/SDL.h>


#ifndef KEYBINDS_H
#define KEYBINDS_H

using Keybind = enum class Keybind {
  PLAYER_UP,
  PLAYER_DOWN,
  PLAYER_LEFT,
  PLAYER_RIGHT
};

class Keybinds {
public:
  static Keybinds& singleton() { 
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
    if (!this->_keybinds.contains(keybind)) {
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
    if (SDL_Scancode scancode; this->get(keybind, &scancode)) {
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
    if (this->_keybinds.contains(keybind)) {
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

  static Keybinds instance;

  std::map<Keybind, SDL_Scancode> _keybinds;
};
#endif
