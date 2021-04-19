#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>

#define NUMBER_OF_TEXTURES 2

#define audio 1
#ifndef WIN32
#define audio 0
#endif // WIN32

SDL_Renderer* renderer;
SDL_Window *window;

SDL_Texture **textureArr;

Mix_Music *bgSound;
Mix_Chunk *clickSound;

TTF_Font *font;

typedef struct effectStruct
{
    int counter, x;
} *effectPtr;
effectPtr pomEffect, effects[3];

int randCol()
{
    return rand() % 255 + 0;
}

void init()
{
    srand(time(NULL));
    IMG_Init(IMG_INIT_PNG);
    SDL_Init(SDL_INIT_VIDEO);

    window = SDL_CreateWindow("SDL2 & Code::Blocks", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 600, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);
     if (window == NULL) {
        printf("SDL_SetVideoMode failed: %s\n", SDL_GetError());
        exit(1); /* Unrecoverable error */
    }
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    SDL_SetRenderDrawColor(renderer, randCol(), randCol(), randCol(), 255);
    if (audio)
    {
        SDL_Init(SDL_INIT_AUDIO);
        Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
        bgSound = Mix_LoadMUS("In the jungle city PSG.mp3");
        clickSound = Mix_LoadWAV("button-7.wav");
    }
    TTF_Init();
    font = TTF_OpenFont("Lionelofparis.ttf", 20);

    effects[0] = NULL;
    effects[1] = NULL;
    effects[2] = NULL;
}

void loadTextures(char* name)
{
    textureArr = calloc(NUMBER_OF_TEXTURES, sizeof(void*));
    textureArr[0] = IMG_LoadTexture(renderer, name);
    textureArr[1] = IMG_LoadTexture(renderer, "effect.png");
}

void drawSprite(int x, int y, SDL_Texture *texture, int scale)
{
    SDL_Rect rect;
    rect.x = x + scale;
    rect.y = y + scale;
    SDL_QueryTexture(texture, NULL, NULL, &rect.w, &rect.h);
    rect.w -= 2*scale;
    rect.h -= 2*scale;
    SDL_RenderCopy(renderer, texture, NULL, &rect);
}

void kill()
{
    int i;
    for (i=0; i<NUMBER_OF_TEXTURES; i++) SDL_DestroyTexture(textureArr[i]);
    IMG_Quit();
    if (audio)
    {
        Mix_FreeMusic(bgSound);
        Mix_FreeChunk(clickSound);
        Mix_CloseAudio();
    }

    TTF_CloseFont(font);

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    SDL_Quit();

    free(textureArr);

    if (effects[0]) free(effects[0]);
    if (effects[1]) free(effects[1]);
    if (effects[2]) free(effects[2]);
}

int main(int argc, char** argv)
{
    char a[5000];
    char typedTex[100] = "";
    Uint32 old_time = 0, old_time1 = 0, new_time;
    SDL_Event event;
    int dispFps = 0, fps = 0, x=100, dx=0, running = 1, ticks = SDL_GetTicks();
    init();
    loadTextures("pic1.png");

    if (audio)
    {
        Mix_PlayMusic(bgSound, -1);
        Mix_VolumeMusic(90);
        Mix_VolumeChunk(clickSound, 40);
    }
    while (running)
    {
        // Check for various events (keyboard, mouse, touch, close)
        if (ticks + 50 < SDL_GetTicks())
        {
            while (SDL_PollEvent(&event))
            {
                if (event.type == SDL_KEYDOWN)
                {
                    switch (event.key.keysym.sym)
                    {
                    case SDLK_q: case SDLK_ESCAPE:
                        running = 0;
                        break;
                    case SDLK_a:
                        if (audio) Mix_PlayChannel(-1, clickSound, 0);
                        dx = -4;
                        break;
                    case SDLK_d:
                        if (audio) Mix_PlayChannel(-1, clickSound, 0);
                        dx = 4;
                        break;
                    case SDLK_s:
                        if (audio) Mix_PlayChannel(-1, clickSound, 0);
                        dx = 0;
                        break;
                    case SDLK_x:
                        if (audio) Mix_VolumeMusic(Mix_VolumeMusic(-1) - 5), Mix_VolumeChunk(clickSound, Mix_VolumeChunk(clickSound, -1) - 5);
                        break;
                    case SDLK_c:
                        if (audio) Mix_VolumeMusic(Mix_VolumeMusic(-1) + 5), Mix_VolumeChunk(clickSound, Mix_VolumeChunk(clickSound, -1) + 5);
                        break;
                    case SDLK_y:
                        if (strlen(typedTex) < 99) sprintf(typedTex, "%s%c", typedTex, 'Y');
                        break;
                    case SDLK_BACKSPACE:
                       if (strlen(typedTex) > 0) typedTex[strlen(typedTex)-1] = '\0';
                        break;
                    default:
                        break;
                    }
                }
                else if (event.type == SDL_QUIT)
                {
                    running = 1;
                }
            }
            ticks = SDL_GetTicks();
        }

        x += dx;
        if (x < 0) x = 0;
        if (x > 780) x = 780;
	    // Clear buffer
	    SDL_RenderClear(renderer);

        // Draw here ...
        SDL_Color color = { 255, 255, 255, 255 };
        //strncpy(a, "", sizeof(a));
        //a[0]='\0';


        sprintf(a, "SDL Demo, commands: A S D, volume X C, fps: %4d Type Y and backspace: %s", dispFps, typedTex);

        SDL_Surface *surf = TTF_RenderText_Blended(font, a, color);
        SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surf);
        SDL_FreeSurface(surf);
        drawSprite(0, 0, texture, 0);
        SDL_DestroyTexture(texture);

        if (effects[0]) drawSprite(effects[0]->x, 300, textureArr[1], effects[0]->counter*2);
        if (effects[1]) drawSprite(effects[1]->x, 300, textureArr[1], effects[1]->counter*2);
        if (effects[2]) drawSprite(effects[2]->x, 300, textureArr[1], effects[2]->counter*2);
        drawSprite(x, 300, textureArr[0], 0);

	    // Switch buffers
	    SDL_RenderPresent(renderer);

	    new_time = SDL_GetTicks();
	    if (new_time - old_time > 1000)
        {
            SDL_SetRenderDrawColor(renderer, randCol(), randCol(), randCol(), 255);
            old_time = new_time;
            dispFps = fps;
            fps = 0;
        }
        if (new_time - old_time1 > 100)
        {
            old_time1 = new_time;
            if (effects[0]) if (++effects[0]->counter == 3) {free(effects[0]); effects[0] = NULL;};
            if (effects[1]) if (++effects[1]->counter == 3) {free(effects[1]); effects[1] = NULL;};
            if (effects[2]) if (++effects[2]->counter == 3) {free(effects[2]); effects[2] = NULL;};
            if (!effects[0]) pomEffect = effects[0] = malloc(sizeof(struct effectStruct));
            else if (!effects[1]) pomEffect = effects[1] = malloc(sizeof(struct effectStruct));
            else pomEffect = effects[2] = malloc(sizeof(struct effectStruct));
            pomEffect->counter = 0;
            pomEffect->x = x;
        }

        fps++;

    }
    kill();
    return 0;
}
