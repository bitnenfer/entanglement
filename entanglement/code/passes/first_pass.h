#ifndef  _FIRST_PASS_H_
#define _FIRST_PASS_H_

#include "../types.h"
#include "../game.h"


void first_pass_create();
void first_pass_update(float32_t delat);
void first_pass_render();
void first_pass_destroy();

state_t gFirstPassState = { &first_pass_create, &first_pass_update, &first_pass_render, &first_pass_destroy };

#endif // ! _FIRST_PASS_H_
