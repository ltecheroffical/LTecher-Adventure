#include <raylib.h>
#include <scene.h>
#include <gui/screens/game_hud.h>

#pragma once
class GameScene : public Scene
{
private:
  GameHUD *screen = new GameHUD(this);

#if PRODUCTION_BUILD == 0
  Texture2D save_screenshot;
  bool show_screenshot = false;
#endif

public:
  GameScene() = default;
  ~GameScene() override = default;

  void on_load() override;
  void on_update(float delta) override;
  void on_render() override;
};
