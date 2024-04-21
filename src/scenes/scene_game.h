#include <framework/scene.h>

#ifndef SCENE_GAME_H
#define SCENE_GAME_H

class SceneGame : public Scene {
public:
  SceneGame();
  ~SceneGame();

protected:
  void init() override;
};

#endif
