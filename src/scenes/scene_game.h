#include <memory>

#include <framework/scene.h>

#include <entities/player/player.h>

#include <world/world.h>

#ifndef SCENE_GAME_H
#define SCENE_GAME_H

class SceneGame : public Scene {
public:
  SceneGame() = default;
  ~SceneGame() override = default;

  void init() override;

private:
  std::unique_ptr<World> _gameobject_world;
  std::unique_ptr<Player> _gameobject_player;
};

#endif
