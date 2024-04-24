#include <SDL3/SDL.h>


#ifndef FRAMEWORK_IMAGE_H
#define FRAMEWORK_IMAGE_H

typedef struct SDL_ImageData {
  SDL_Texture *texture;
  int width;
  int height;
} SDL_Image;
#endif
