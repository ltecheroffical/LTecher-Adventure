#include <raylib.h>
#include <scene.h>
#include <gui/screens/game_hud.h>

#pragma once
class GameScene : public Scene
{
private:
  /*
   * The HUD is the screen that shows the information
   */
  GameHUD *screen = new GameHUD(this);

#ifndef REMOVE_IMGUI
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
