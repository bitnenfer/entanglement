#ifndef _GAME_H_
#define _GAME_H_

#define STATE_0 0

struct state
{
    void(*fpCreate)();
    void(*fpUpdate)(float32_t);
    void(*fpRender)();
    void(*fpDestroy)();
};

typedef struct state state_t;

extern void ldGameSwapState(state_t* pNextState);

#endif // !_GAME_H_
