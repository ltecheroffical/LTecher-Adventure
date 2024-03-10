#include <scene.h>
#include <gui/screens/game_hud.h>

#pragma once
class GameScene : public Scene
{
private:
  GameHUD *screen = new GameHUD(this);

public:
  GameScene() = default;
  ~GameScene() override = default;

  void on_load() override;
  void on_update(float delta) override;
  void on_render() override;
};
