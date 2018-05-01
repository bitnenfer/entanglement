#ifndef _INIT_SCENE_H_
#define _INIT_SCENE_H_

#include "../game.h"
#include "../types.h"

extern void InitSceneCreate();
extern void InitSceneUpdate(float32_t delta);
extern void InitSceneRender();
extern void InitSceneDestroy();

state_t gInitScene = { &InitSceneCreate, &InitSceneUpdate, &InitSceneRender, &InitSceneDestroy };

#endif // !_INIT_SCENE_H_
