#include <iostream>
#include <fstream>
#include <chrono>

#include <cstdint>

#include <util/hash.h>

#include "game_save.h"


const uint16_t HEADER = 0x91ef;


const char FLAG_ONE_LIFE     = 1;
const char FLAG_MODDED       = 2;
const char FLAG_SERVER_SAVE  = 4;


bool GameSave::save(std::string save_path) {
  std::vector<char> data;

  data.insert(data.begin(), (const char*)&HEADER, (const char*)&HEADER + sizeof(HEADER));
  
  data.insert(
    data.end(),
    (const char*)&SAVE_VERSION,
    (const char*)&SAVE_VERSION + sizeof(unsigned short));

  char flags = 0;

  if (this->flag_one_life) {
    flags |= FLAG_ONE_LIFE;
  }
  if (this->flag_modded) {
    flags |= FLAG_MODDED;
  }
  if (this->flag_server_save) {
    flags |= FLAG_SERVER_SAVE;
  }

  data.insert(data.end(), &flags, &flags + 1);

  long long last_save = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());

  data.insert(
    data.end(),
    (const char*)&last_save,
    (const char*)&last_save + sizeof(unsigned long long));

  unsigned int player_count = this->_players.size();
  data.insert(
    data.end(),
    (const char*)&player_count,
    (const char*)&player_count + sizeof(unsigned int));

  
  for ([[maybe_unused]] auto player : this->_players) {
    PlayerData player_data;


    player_data.name[0] = 'T';
    player_data.name[1] = 'E';
    player_data.name[2] = 'S';
    player_data.name[3] = 'T';
    player_data.name[4] = '\0';

    player_data.health = 69;
    player_data.max_health = 420;

    player_data.x = player->position.x;
    player_data.y = player->position.y;

    data.insert(
      data.end(),
      (const char*)&player_data,
      (const char*)&player_data + sizeof(PlayerData));
  }


  std::ofstream save_file(save_path);
  if (!save_file.is_open()) {
    return false;
  }
  
  save_file.write(data.data(), data.size());
  return true;
}

bool GameSave::load(char *data, size_t size) {
  long long offset = 0;

  uint16_t file_header = 0;
  std::memcpy(&file_header, data + offset, sizeof(file_header));
  offset += sizeof(HEADER);

  if (std::memcmp(&HEADER, &file_header, sizeof(file_header)) != 0) {
#if PRODUCTION_BUILD == 0
    std::cout << "Bad header" << std::endl;
#endif
    return false;
  }

  unsigned short save_version;
  if (size < offset + sizeof(save_version)) {
    return false;
  }

  std::memcpy(&save_version, data + offset, sizeof(save_version));
  offset += sizeof(save_version);
  
  if (save_version != SAVE_VERSION) {
#if PRODUCTION_BUILD == 0
    std::cout << "Bad save version" << std::endl;
#endif
    return false;
  }

  char flags;
  if (size < offset + sizeof(flags)) {
    return false;
  }
  std::memcpy(&flags, data + offset, sizeof(flags));
  offset += sizeof(flags);

  if (flags & FLAG_ONE_LIFE) {
    this->flag_one_life = true;
  }
  if (flags & FLAG_MODDED) {
    this->flag_modded = true;
  }
  if (flags & FLAG_SERVER_SAVE) {
    this->flag_server_save = true;
  }

  unsigned long long last_save;
  if (size < offset + sizeof(last_save)) {

    return false;
  }
  std::memcpy(&last_save, data + offset, sizeof(last_save));
  offset += sizeof(last_save);

  unsigned int player_count;
  if (size < offset + sizeof(player_count)) {
    return false;
  }
  std::memcpy(&player_count, data + offset, sizeof(player_count));
  offset += sizeof(player_count);

  if (size < offset + player_count * sizeof(PlayerData)) {
    return false;
  }

  for (unsigned int i = 0; i < player_count; i++) {
    PlayerData player_data;
    std::memcpy(&player_data, data + offset, sizeof(player_data));
    offset += sizeof(player_data);
    this->_saved_players.push_back(player_data);
  }

  return true;
}

void GameSave::add_player(Player *player) {
  // Do we have this player?
  if (std::ranges::find(this->_players, player) == this->_players.end()) {
    // Now do we have it in the saved players?
    auto it = this->_saved_players.begin();
    while (it != this->_saved_players.end()) {
      if (std::memcmp(&it->name, &player->name, sizeof(player->name)) == 0) {
        // Populate the player data
        player->position.x = it->x;
        player->position.y = it->y;
        break;
      }
      it++;
    }
    this->_players.push_back(player);
  }
}
