#include <fstream>
#include <plugin.h>
#include <vector>

#pragma once

class GameSave : public Plugin
{
public:
  GameSave() = default;
  ~GameSave() = default;

  void on_update(float delta) override;
  void on_game_start() override;

private:
  std::fstream save_file;
  std::vector<char> data;
};
