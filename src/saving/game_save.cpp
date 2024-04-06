#include <algorithm>
#include <cstdint>
#include <iostream>
#include <vector>

#include <raylib.h>

#include <scene.h>
#include <app.h>

#include <components/health.h>

#include "game_save.h"

GameSave *GameSave::current_save = nullptr;

constexpr char header[7] = {
  'L',
  'T',
  'A',
  'S',
  'A',
  'V',
  'E'
};

GameSave::GameSave(char *file_path)
{
  if (GameSave::current_save != nullptr)
  {
    throw("There is already a save file open!");
  }

  this->save_file.open(file_path, std::ios::binary | std::ios::out | std::ios::in);

  if (!this->save_file.is_open())
  {
    // Try to open it in write only mode
    this->save_file.open(file_path, std::ios::binary | std::ios::out);
    
    if (!this->save_file.is_open())
    {
      // The save file cannot be written either way
      throw std::runtime_error("The save file cannot be opened!");
    }
  }
  else
  {
    // The save file exists already and no error occurred, load it
    data.assign(std::istreambuf_iterator<char>(this->save_file),
                std::istreambuf_iterator<char>());
  }
 
  GameSave::current_save = this;
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

  // Header
  this->data.insert(this->data.end(),
      reinterpret_cast<char*>((char*)&header),
      reinterpret_cast<char*>((char*)&header) + sizeof(header));


  // Metadata
  this->data.insert(this->data.end(),
      reinterpret_cast<char*>(&this->version),
      reinterpret_cast<char*>(&this->version) + sizeof(uint16_t));

  this->data.insert(this->data.end(),
      reinterpret_cast<char*>(&this->date_created),
      reinterpret_cast<char*>(&this->date_created) + sizeof(int));
  
  // Save Name
  uint8_t save_name_length = (uint8_t)this->save_name.length();
  char *save_name_c_str = (char *)this->save_name.c_str();

  this->data.insert(this->data.end(),
      reinterpret_cast<char*>(&save_name_length),
      reinterpret_cast<char*>(&save_name_length) + sizeof(uint8_t));

  this->data.insert(this->data.end(), save_name_c_str, save_name_c_str + save_name_length);
  
  // Screenshot
  int image_data_size = GetPixelDataSize(
      this->save_screenshot.width,
      this->save_screenshot.height,
      PIXELFORMAT_UNCOMPRESSED_R8G8B8A8);

  unsigned char *image_data_bytes = ExportImageToMemory(
    this->save_screenshot,
    ".png",
    &image_data_size);

  std::vector<char> image_data(image_data_bytes, image_data_bytes + image_data_size);

  int image_file_size = (int)image_data.size();
  this->data.insert(this->data.end(),
      reinterpret_cast<char*>(&image_file_size),
      reinterpret_cast<char*>(&image_file_size) + sizeof(int));
  
  this->data.insert(this->data.end(), image_data.begin(), image_data.end());


  // Player
  std::vector<char> player_data;
  for (int i = 0; i < this->players.size(); i++)
  {
    Player *player = this->players[i];
   
    Health *health = player->health_ptr();

    float health_value = health->get_health();
    float health_max = health->get_max();

    unsigned int player_size = 0;

    player_data.resize(player_data.size() + sizeof(unsigned int));

    // Player/Position
    player_size += sizeof(float);
    player_data.insert(player_data.end(),
        reinterpret_cast<char*>(&player->position.x),
        reinterpret_cast<char*>(&player->position.x) + sizeof(float));

    player_size += sizeof(float); 
    player_data.insert(player_data.end(),
        reinterpret_cast<char*>(&player->position.y),
        reinterpret_cast<char*>(&player->position.y) + sizeof(float));

    // Player/Health
    player_size += sizeof(float);
    player_data.insert(player_data.end(),
        reinterpret_cast<char*>(&health_value),
        reinterpret_cast<char*>(&health_value) + sizeof(float));


    player_size += sizeof(float);
    player_data.insert(player_data.end(),
        reinterpret_cast<char*>(&health_max),
        reinterpret_cast<char*>(&health_max) + sizeof(float));
    
    // Player/Size
    std::copy(reinterpret_cast<char*>(&player_size),
              reinterpret_cast<char*>(&player_size) + sizeof(unsigned int),
              player_data.end() - player_size - sizeof(unsigned int));
  }

  unsigned int player_data_size = (unsigned int)player_data.size();

  this->data.insert(this->data.end(),
      reinterpret_cast<char*>(&player_data_size),
      reinterpret_cast<char*>(&player_data_size) + sizeof(unsigned int));
  
  this->data.insert(this->data.end(), player_data.begin(), player_data.end());


  this->save_file.clear();
  this->save_file.write(this->data.data(), this->data.size());
  this->save_file.flush();

  this->on_save.emit();
}

void GameSave::load()
{
  // Increment each time a read happens with the size of the read
  int offset = 0;

  // Header Verification
#if PRODUCTION_BUILD == 0
  std::cout << "Checking save file header..." << std::endl;
  std::cout << "(left is in save and right is from expected header)" << std::endl;
#endif
  for (int i = 0; i < sizeof(header); i++)
  {
    std::cout << this->data[i] << " " << header[i] << " ";

    if (this->data[i] != header[i])
    {
#if PRODUCTION_BUILD == 0
      std::cout << "FAIL" << std::endl;
#endif
      throw std::runtime_error("The save file is corrupted! Header check failed!");
      return;
    }
#if PRODUCTION_BUILD == 0
    else
    {
      std::cout << "PASS" << std::endl;
    }
#endif

    offset += sizeof(char);
  }

#if PRODUCTION_BUILD == 0
  std::cout << "The save file header check was successful!" << std::endl;
#endif

  // Metadata
  std::copy(this->data.begin() + offset,
            this->data.begin() + offset + sizeof(uint16_t),
            reinterpret_cast<char*>(&this->version));
  offset += sizeof(uint16_t);

  std::copy(this->data.begin() + offset,
            this->data.begin() + offset + sizeof(int),
            reinterpret_cast<char*>(&this->date_created));
  offset += sizeof(int);

  // Save Name
  uint8_t save_name_length = 0;
  std::copy(this->data.begin() + offset,
            this->data.begin() + offset + sizeof(uint8_t),
            reinterpret_cast<char*>(&save_name_length));
  offset += sizeof(uint8_t);

  // Buffer overflow?
  if (offset + save_name_length > this->data.size())
  {
    throw std::runtime_error("The save file is corrupted! Save name is too large!");
  }

  this->save_name = std::string(
    this->data.begin() + offset,
    this->data.begin() + offset + save_name_length
  );
  offset += save_name_length;

  // Screenshot
  int image_file_size = 0;

  std::copy(this->data.begin() + offset,
            this->data.begin() + offset + sizeof(int),
            reinterpret_cast<char*>(&image_file_size));
  offset += sizeof(int);


  // Buffer overflow?
  if (offset + image_file_size > this->data.size())
  {
    throw std::runtime_error("The save file is corrupted! Image is too large!");
  }

  unsigned char *image_data = (unsigned char *)malloc(image_file_size);

  if (image_data == NULL)
  {
    throw std::runtime_error("Failed to allocate memory for image data!");
  }

  std::copy(this->data.begin() + offset,
            this->data.begin() + offset + image_file_size,
            image_data);
    
  offset += image_file_size;

  free(image_data);

  this->save_screenshot = LoadImageFromMemory(
    ".png",
    image_data,
    image_file_size
  );

  // Players
  unsigned int player_data_size = 0;
  std::copy(this->data.begin() + offset,
            this->data.begin() + offset + sizeof(unsigned int),
            reinterpret_cast<char*>(&player_data_size));
  offset += sizeof(unsigned int);

  // Buffer overflow?
  if (offset + player_data_size > this->data.size())
  {
    throw std::runtime_error("The save file is corrupted! Player data is too large!");
  }

  for (int i = 0; i < player_data_size; i++)
  {
    // Player
    // Use stripped down version of the player
    unsigned int player_size = 0;

    std::copy(this->data.begin() + offset,
              this->data.begin() + offset + sizeof(unsigned int),
              reinterpret_cast<char*>(&player_size));
    offset += sizeof(unsigned int);

    if (player_size == 0)
    {
      continue;
    }

    // Buffer overflow?
    if (offset + player_size > this->data.size())
    {
      throw std::runtime_error("The save file is corrupted! Player is too large!");
    }

    PlayerData player_data;

    // Player/Position
    std::copy(this->data.begin() + offset,
              this->data.begin() + offset + sizeof(float),
              reinterpret_cast<char*>(&player_data.position.x));
    offset += sizeof(float);

    std::copy(this->data.begin() + offset,
              this->data.begin() + offset + sizeof(float),
              reinterpret_cast<char*>(&player_data.position.y));
    offset += sizeof(float);

    // Player/Health
    std::copy(this->data.begin() + offset,
              this->data.begin() + offset + sizeof(float),
              reinterpret_cast<char*>(player_data.health.cur_health_ptr()));
    offset += sizeof(float);

    std::copy(this->data.begin() + offset,
              this->data.begin() + offset + sizeof(float),
              reinterpret_cast<char*>(player_data.health.max_health_ptr()));
    offset += sizeof(float);
  }
}
