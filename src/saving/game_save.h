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

  std::string save_name;

  int date_created = time(NULL);
  
  Image save_screenshot = LoadImageFromScreen();

  std::vector<Player*> players = Player::players;

  static GameSave *current_save;

private:
  std::fstream save_file;
  std::vector<char> data;
};
