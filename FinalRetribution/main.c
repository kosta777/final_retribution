#include "main.h"

/**
* Funkcija za inicijalizaciju igre
*/
void initProgram()
{
    FILE *inFile;
    // inicijalizacija random gerator
    srand(time(NULL));
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");
    // inicijalizacija SDL2 i struktura winow i renderer
    SDL_Init(SDL_INIT_VIDEO);
    if (!(window = SDL_CreateWindow(GAME_NAME, SDL_WINDOWPOS_UNDEFINED,
                                    SDL_WINDOWPOS_UNDEFINED, WINDOWW, WINDOWH,
                                    SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL)))
    {
        printf("SDL_CreateWindow error: %s\n", SDL_GetError());
        exit(1);
    }
    if (!(renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED |
                                        SDL_RENDERER_PRESENTVSYNC)))
    {
        printf("SDL_CreateRenderer error: %s\n", SDL_GetError());
        exit(1);
    }
    backgroundRect.h = WINDOWH, backgroundRect.w = WINDOWW, backgroundRect.x = backgroundRect.y = 0;
    topStripRect.h = 50, topStripRect.w = WINDOWW, topStripRect.x = topStripRect.y = 0;
    bottomStripRect.h = 50, bottomStripRect.w = WINDOWW, bottomStripRect.x = 0, bottomStripRect.y = WINDOWH - bottomStripRect.h;

    // inicijalizacija SDL2 image za ucitavanje PNG slika
    IMG_Init(IMG_INIT_PNG);

    // inicijalizacija SDL2 ttf za koriscenje fontova
    TTF_Init();
    font = TTF_OpenFont("res/fonts/army.ttf", 20);

    // inicijalizacija zvuka (samo za windows masine)
    audio = initAudio;
    if (audio)
    {
        if (SDL_Init(SDL_INIT_AUDIO) < 0 || Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) == -1)
        {
            printf("Mix_OpenAudio error: %s\n", SDL_GetError());
            audio = 0;
        }
        else
        {
            bgSound = Mix_LoadMUS("res/sound/idle.mp3");
            fire = Mix_LoadWAV("res/sound/shoot.wav");
            Mix_VolumeChunk(fire, 4);
            explosionSound = Mix_LoadWAV("res/sound/explosion.wav");
        }
    }

    if ((inFile = fopen("res/saves/lastCampaignLevel.sav", "rb")))
    {
        maxLevelSavePtr maxLevelSave = malloc(sizeof(struct maxLevelSaveStruct));
        fread(maxLevelSave, sizeof(struct maxLevelSaveStruct), 1, inFile);
        fclose(inFile);
        lastCampaignLevel = maxLevelSave->level;
        free(maxLevelSave);
    }
    else
    {
        lastCampaignLevel = 1;
        printf("Error while trying to load your progress.\n");
    }
    game = NULL;
}

/**
* Funkcija za deinicijalizaciju igre
*/
void killGame()
{
    // deinicijalizacija igre
    free(game);

    // deinicijalizacija SDL2 ttf
    TTF_CloseFont(font);
    TTF_Quit();

    // deinicijalizacija SDL2 imgage
    IMG_Quit();

    // deinicijalizacija zvukova
    if (audio)
    {
        Mix_FreeMusic(bgSound);
        Mix_FreeChunk(fire);
        Mix_FreeChunk(explosionSound);
        Mix_CloseAudio();
    }

    // deinicijalizacija SDL2 i struktura renderer i window
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

/**
* Glavna funkcija koja vrti meni i igru
*/
int main(int argc, char *argv[])
{
    int running = 1;
    // inicijalizacija igre
    initProgram();

    running = showMenu();
    while (running)
    {
        // procedura za izvrsavanje igre
        runGame();
        // procedura za prikazivanje menija
        running = showMenu();
    }
    // deinicijalizacija igre
    killGame();
    return 0;
}
