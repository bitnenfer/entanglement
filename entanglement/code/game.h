#ifndef _GAME_H_
#define _GAME_H_

#define STATE_0 0

struct state
{
    void(*fp_create)();
    void(*fp_update)(float32_t);
    void(*fp_render)();
    void(*fp_destroy)();
};

typedef struct state state_t;

void game_swap_state(state_t* p_next_state);

#endif // !_GAME_H_
