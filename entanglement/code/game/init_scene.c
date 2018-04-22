#include "init_scene.h"


enum tamagotchi_anim_state
{
    TAM_IDLE,
    TAM_WALK_LEFT,
    TAM_WALK_RIGHT
};

typedef struct tamagotchi_char
{
    vec2_t pos;
    float32_t timer;
    float32_t tileX;
    float32_t flipX;
    float32_t targetX;
    int32_t frame;
    enum tamagotchi_anim_state state;
    int32_t head;
    int32_t eye;
    int32_t mouth;

} tamagotchi_char_t;

typedef struct tamagotchi_state
{
    float32_t age;
    float32_t hunger;
    float32_t health;
    float32_t happy;

} tamagotchi_state_t;

tamagotchi_char_t mainChar;
tamagotchi_state_t mainState;

const float32_t animDelays[] = {
    15.0f,
    25.0f,
    40.0f,
    100.0f
};

float32_t currentAnimDelay = 15.0f;

void InitTamagotchiChar()
{
    tamagotchi_char_t tamaChar = {
        .pos = { LD_CONFIG_GAME_WIDTH / 2, LD_CONFIG_GAME_HEIGHT / 2 },
        .timer = 0.0f,
        .tileX = 0.0f,
        .flipX = 1.0f,
        .frame = 0,
        .state = TAM_IDLE,
        .head = 0,
        .eye = 0,
        .mouth = 0,
        .targetX = LD_CONFIG_GAME_WIDTH / 2 + 10
    };
    tamagotchi_state_t tamaState = {
        .age = 0.0f,
        .hunger = 0.0f,
        .health = 0.0f,
        .happy = 0.0f
    };

    mainChar = tamaChar;
    mainState = tamaState;

    mainChar.head = rand() % 4;
    mainChar.eye = rand() % 4;
    mainChar.mouth = rand() % 4;

}

void UpdateTamagotchiChar(float32_t delta)
{
    mainChar.timer += delta;

    /* Handle Input */
    {
        if (ldIsKeyHit(KEY_LEFT))
        {
            mainChar.state = TAM_WALK_LEFT;
        }
        else if (ldIsKeyHit(KEY_RIGHT))
        {
            mainChar.state = TAM_WALK_RIGHT;
        }
        else if (ldIsKeyHit(KEY_DOWN))
        {
            mainChar.state = TAM_IDLE;
        }
    }

    /* Handle States */
    {
        switch (mainChar.state)
        {
        case TAM_IDLE:
        {
            mainChar.frame = 0;
            mainChar.tileX = 0.0f;
            if (mainChar.timer > currentAnimDelay)
            {
                #define GET_RAND ((rand() % 100) * 2 - 100)

                currentAnimDelay = animDelays[rand() % 4];
                
                if (GET_RAND < 0)
                {
                    if (GET_RAND < 0)
                    {
                        mainChar.targetX = LD_CONFIG_GAME_WIDTH / 2 - 20;
                        mainChar.state = TAM_WALK_LEFT;
                    }
                    else
                    {
                        mainChar.targetX = LD_CONFIG_GAME_WIDTH / 2 + 20;
                        mainChar.state = TAM_WALK_RIGHT;
                    }
                }
                else
                {
                    if (GET_RAND < 0)
                    {
                        mainChar.targetX = LD_CONFIG_GAME_WIDTH / 2;

                        if (mainChar.targetX < mainChar.pos.x)
                        {
                            mainChar.state = TAM_WALK_LEFT;
                        }
                        else
                        {
                            mainChar.state = TAM_WALK_RIGHT;
                        }
                    }
                }

                #undef GET_RAND
                mainChar.timer = 0;
            }
            break;
        }
        case TAM_WALK_LEFT:
        {
            if (mainChar.timer > 1.0f)
            {
                mainChar.frame = 1 + ((mainChar.frame + 1) % 5);
                mainChar.tileX = (float32_t)(mainChar.frame * 24);
                mainChar.timer = 0;
            }
            mainChar.flipX = 1.0f;
            if (mainChar.pos.x > mainChar.targetX)
            {
                mainChar.pos.x -= 1.0f;
            }
            else
            {
                mainChar.state = TAM_IDLE;
            }
            break;
        }
        case TAM_WALK_RIGHT:
        {
            if (mainChar.timer > 1.0f)
            {
                mainChar.frame = 1 + ((mainChar.frame + 1) % 5);
                mainChar.tileX = (float32_t)(mainChar.frame * 24);
                mainChar.timer = 0;
            }
            mainChar.flipX = -1.0f;
            if (mainChar.pos.x < mainChar.targetX)
            {
                mainChar.pos.x += 1.0f;
            }
            else
            {
                mainChar.state = TAM_IDLE;
            }
            break;
        }
        }
    }
}
void RenderTamagotchiChar()
{
    ldGfxCanvasPushMatrix();
    {
        ldGfxCanvasTranslate(mainChar.pos.x, mainChar.pos.y);
        ldGfxCanvasScale(mainChar.flipX, 1.0f);
        ldGfxCanvasDrawImageFrame(&tamaBodyImage, -12, -32, mainChar.tileX, 0, 24, 32);
        ldGfxCanvasDrawImage(&tamaHeadParts[mainChar.head], -12, -32);
        ldGfxCanvasDrawImage(&tamaEyeParts[mainChar.eye], -12, -32);
        ldGfxCanvasDrawImage(&tamaMouthParts[mainChar.mouth], -12, -32);
    }
    ldGfxCanvasPopMatrix();
}

void TamagotchiSceneCreate()
{
    glClearColor(227.0f /255.0f, 244.0f /255.0f, 212.0f /255.0f, 1);

    InitTamagotchiChar();
    ldGfxCanvasSetMaskColor(
        115.0f / 255.0f,
        140.0f / 255.0f,
        95.0f / 255.0f
    );
}
void TamagotchiSceneUpdate(float32_t delta)
{
    if (ldIsKeyHit(KEY_SPACE))
    {
        ldGameSwapState(&gInitScene);
    }
    UpdateTamagotchiChar(delta);
}
void TamagotchiSceneRender()
{
    glClear(GL_COLOR_BUFFER_BIT);
    ldGfxCanvasPushMatrix();
    {
        ldGfxCanvasScale(LD_CONFIG_SCALE, LD_CONFIG_SCALE);
        ldGfxCanvasPushMatrix();
        {
            ldGfxCanvasSetAlpha(0.1f);
            ldGfxCanvasTranslate(2, 2);
            ldGfxCanvasDrawImage(&bgImage, 0, 0);
            RenderTamagotchiChar();
        }
        ldGfxCanvasPopMatrix();

        ldGfxCanvasSetAlpha(1.0f);
        ldGfxCanvasDrawImage(&bgImage, 0, 0);
        RenderTamagotchiChar();
    }
    ldGfxCanvasPopMatrix();
    ldGfxCanvasFlush();
}
void TamagotchiSceneDestroy()
{

}
