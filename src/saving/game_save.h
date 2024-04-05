#include <raylib.h>

#include <fstream>
#include <string>
#include <vector>

#include <event.h>

#include <entities/player.h>

#pragma once

class GameSave
{
public:
  GameSave(char *file_path);
  ~GameSave();

  Event<> on_save;

  void save();
  void load();

  uint16_t version = 1;
  int date_created = time(NULL);

  std::string save_name;
  
  Image save_screenshot = LoadImageFromScreen();

  std::vector<Player*> players = Player::players;
  std::vector<PlayerData*> player_data;

  static GameSave *current_save;

private:
  std::fstream save_file;
  std::vector<char> data;
};
