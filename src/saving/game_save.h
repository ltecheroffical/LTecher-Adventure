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

  /*
   * Emitted when the save file is loaded
   */
  Event<> on_load;
  /*
   * Emitted when the save file is saved
   */
  Event<> on_save;

  /*
   * Saves the game to the save file
   */
  void save();
  /*
   * Loads the game from the save file
   */
  void load();


  /*
   * The version of the save file
   */
  uint16_t version = 1;
  /*
   * The date the save file was created
   */
  int date_created = time(NULL);

  /*
   * The name of the save
   */
  std::string save_name;
  
  /*
   * The preview of the save file's content
   */
  Image save_screenshot = LoadImageFromScreen();

  /*
   * The players in the save file, this value is only for saving
   */
  std::vector<Player*> players = Player::players;
  /*
   * Populated when the save file is loaded
   */
  std::vector<PlayerData*> player_data;

  /*
   * The current save file
   */
  static GameSave *current_save;

private:
  std::fstream save_file;
  std::vector<char> data;
};
