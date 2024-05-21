#include <vector>
#include <string>

#include <entities/player/player.h>
#include <save/data/player_data.h>

#ifndef GAME_SAVE_H
#define GAME_SAVE_H

class GameSave {
public:
  GameSave() = default;
  ~GameSave() = default;

  inline static const short SAVE_VERSION = 1;

  /*
   * Saves the save file
   *
   * @return true if the save was successful
   */
  bool save(std::string save_file);
  /*
   * Loads the save file
   *
   * @return true if the load was successful
   */
  bool load(char *buffer, size_t length);

  /*
   * Adds a player to the save
   *
   * @param player The player to add
   */
  void add_player(Player *player);


  // Sets if players of the save cannot be revived
  bool flag_one_life = false;
  
  // Sets if the save is modded
  bool flag_modded = false;

  // Sets if the save is server side
  bool flag_server_save = false;

private:
  std::string _save_file;

  std::vector<Player*> _players;
  std::vector<PlayerData> _saved_players;
};
#endif
