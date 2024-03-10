#include <cstdint>
#include <iostream>
#include <vector>

#include <raylib.h>

#include <scene.h>
#include <app.h>

#include "game_save.h"

GameSave *GameSave::current_save = nullptr;

GameSave::GameSave(char *file_path)
{
  this->save_file.open(file_path, std::ios::out | std::ios::binary);

  if (!this->save_file.is_open())
  {
    throw("Save could not be opened!");
  }

  if (this->current_save == nullptr)
  {
    this->current_save = this;
  }
  else
  {
    throw("Cannot load more than one save!");
  }
}

GameSave::~GameSave()
{
  if (this->current_save == this)
  {
    this->current_save = nullptr;
  }
  this->save_file.close();
}

void GameSave::save()
{
  this->data.clear();

  char *save_name_c_str = (char*)this->save_name.c_str();

  uint8_t save_name_length = (uint8_t)this->save_name.length();

  this->data.resize(this->data.size() + sizeof(uint8_t));
  char *save_name_length_bytes = reinterpret_cast<char*>(&save_name_length);
  std::copy(save_name_length_bytes,
            save_name_length_bytes + sizeof(uint8_t),
            this->data.end() - sizeof(uint8_t));
  
  this->data.resize(this->data.size() + save_name_length);
  std::copy(save_name_c_str,
            save_name_c_str + save_name_length,
            this->data.end() - save_name_length);
  
  App::render_objects(Scene::get_current_scene()->get_children());
  Image screenshot = LoadImageFromScreen();
  int image_file_size = 0;
  
  int image_data_size = GetPixelDataSize(
      screenshot.width,
      screenshot.height,
      PIXELFORMAT_UNCOMPRESSED_R8G8B8A8);

  unsigned char *image_data_bytes = ExportImageToMemory(
    screenshot,
    ".png",
    &image_data_size);
  
  std::vector<char> image_data(image_data_bytes, image_data_bytes + image_data_size);

  int file_size = (int)image_data.size();
  this->data.resize(this->data.size() + sizeof(int));
  
  char *image_size_bytes = reinterpret_cast<char*>(&file_size);
  std::copy(image_size_bytes,
             image_size_bytes + sizeof(int),
            this->data.end() - sizeof(int));
  
  this->data.resize(this->data.size() + file_size);
  std::copy(image_data.begin(),
            image_data.end(),
            this->data.end() - file_size);

  this->save_file.clear();
  for (int i = 0; i < this->data.size(); i++)
  {
    this->save_file << this->data[i];
  }
  this->save_file.flush();
}
