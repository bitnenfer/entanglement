#ifndef _INIT_SCENE_H_
#define _INIT_SCENE_H_

#include "../game.h"
#include "../types.h"

extern void TamagotchiSceneCreate();
extern void TamagotchiSceneUpdate(float32_t delta);
extern void TamagotchiSceneRender();
extern void TamagotchiSceneDestroy();

state_t gInitScene = { &TamagotchiSceneCreate, &TamagotchiSceneUpdate, &TamagotchiSceneRender, &TamagotchiSceneDestroy };

#endif // !_INIT_SCENE_H_
