#include <fstream>
#include <chrono>

#include <save/data/player_data.h>

#include <util/hash.h>

#include "game_save.h"


const char HEADER[4] = {'L', 'T', 'S', 'A'};


const uint8_t FLAG_ONE_LIFE     = 1;
const uint8_t FLAG_MODDED       = 2;
const uint8_t FLAG_SERVER_SAVE  = 4;


GameSave::GameSave(std::string save_file) : _save_file(save_file) {

}

bool GameSave::save() {
  std::vector<char> data;

  data.insert(data.begin(), HEADER, HEADER + sizeof(HEADER));
  
  data.insert(
    data.end(),
    reinterpret_cast<const char*>(&SAVE_VERSION),
    reinterpret_cast<const char*>(&SAVE_VERSION) + sizeof(uint16_t));

  uint8_t flags = 0;

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

  uint64_t save_time = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());

  data.insert(
    data.end(),
    reinterpret_cast<const char*>(&save_time),
    reinterpret_cast<const char*>(&save_time) + sizeof(uint64_t));

  uint32_t player_count = this->_players.size();
  data.insert(
    data.end(),
    reinterpret_cast<const char*>(&player_count),
    reinterpret_cast<const char*>(&player_count) + sizeof(uint32_t));

  
  for ([[maybe_unused]] auto player : this->_players) {
    PlayerData player_data;


    player_data.name[0] = 'T';
    player_data.name[1] = 'E';
    player_data.name[2] = 'S';
    player_data.name[3] = 'T';
    player_data.name[4] = '\0';

    player_data.health = 69;
    player_data.max_health = 420;

    player_data.x = 53.92f;
    player_data.y = 127.045f;

    data.insert(
      data.end(),
      reinterpret_cast<const char*>(&player_data),
      reinterpret_cast<const char*>(&player_data) + sizeof(PlayerData));
  }


  std::ofstream save_file(_save_file);
  if (!save_file.is_open()) {
    return false;
  }
  
  save_file.write(data.data(), data.size());
  return true;
}

bool GameSave::load() {
  return true;
}

void GameSave::add_player(Player *player) {
  // Do we have this player?
  if (std::ranges::find(this->_players, player) == this->_players.end()) {
    this->_players.push_back(player);
  }
}
