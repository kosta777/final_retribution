#include "game.h"

/**
* Funkcija koja iscrtava frejm igre
* - objekti se iscrtavaju po redosledu: efekti, neprijatelji, metci, pojačanja i igrač
*/
void renderGame()
{
    int i;
    SDL_RenderClear(renderer);
    drawBackground();
    drawEffects();
    drawEnemies();
    drawBullets();
    drawPowerUps();
    drawPlayers();
    SDL_RenderCopy(renderer, backgroundTexture, NULL, &topStripRect);
    SDL_RenderCopy(renderer, backgroundTexture, NULL, &bottomStripRect);
    if (game && game->players) SDL_RenderCopy(renderer, levelClearTexture, NULL, &gameOverRect);
    else SDL_RenderCopy(renderer, gameOverTexture, NULL, &gameOverRect);
    SDL_RenderCopy(renderer, HSBackgroundTexture, NULL, &HSBackgroundRect);
    for (i=0; i<TEXTS_NUM; i++) drawText(texts[i]);
    SDL_RenderPresent(renderer);
}

/**
* Funkcija za inicijalizaciju igre
* - učitava sve teksture potrebne za prikazivanje igre
* - resetuje game->framesFromCont na nulu, sto oznacava da je igra bila prekinuta, a sada se nastavlja
*/
static void initGameFunction()
{
    int i;
    char textPom[256];
    for (i=0; i<256; i++) events[i] = 0;
    backgroundTexture = IMG_LoadTexture(renderer, "res/images/background/Strip.png");
    gameOverTexture = IMG_LoadTexture(renderer, "res/images/background/gameOver.png");
    levelClearTexture = IMG_LoadTexture(renderer, "res/images/background/levelClear.png");
    HSBackgroundTexture = IMG_LoadTexture(renderer, "res/images/background/overlayMenu.png");
    gameOverRect.h = gameOverRect.w = gameOverRect.x = gameOverRect.y = 0;
    HSBackgroundRect.h = HSBackgroundRect.w = HSBackgroundRect.x = HSBackgroundRect.y = 0;
    sprintf(textPom, "%s   Score: 0", GAME_NAME);
    initText(&texts[0], 20, 15, 156, 156, 156, 255, font, textPom);
    initText(&texts[1], WINDOWW/3, WINDOWH/2, 156, 156, 156, 255, font, "|____________________|");
    initText(&texts[2], 20, WINDOWH - 36, 156, 156, 156, 255, font, "Commands: ESC - pause | SPACE - shooting | B - drop bomb | wasd, arrows - movement");
    initText(&texts[3], 800, 200, 156, 156, 156, 255, font, "High scores:"); texts[3]->show = 0;
    initText(&texts[4], 750, 230, 156, 156, 156, 255, font, "1");
    initText(&texts[5], 750, 260, 156, 156, 156, 255, font, "2");
    initText(&texts[6], 750, 290, 156, 156, 156, 255, font, "3");
    initText(&texts[7], 750, 320, 156, 156, 156, 255, font, "4");
    initText(&texts[8], 750, 350, 156, 156, 156, 255, font, "5");
    initText(&texts[9], 750, 380, 156, 156, 156, 255, font, "6");
    initText(&texts[10], 750, 410, 156, 156, 156, 255, font, "7");
    initText(&texts[11], 750, 440, 156, 156, 156, 255, font, "8");
    initText(&texts[12], 750, 470, 156, 156, 156, 255, font, "9");
    initText(&texts[13], 750, 500, 156, 156, 156, 255, font, "10");
    initText(&texts[14], 750, 540, 156, 156, 156, 255, font, "Name: ");
    for (i=3; i<15; i++) texts[i]->show = 0;
    game->framesFromCont = 0;
    if (audio)
    {
        Mix_PlayMusic(bgSound, -1);
        Mix_VolumeMusic(9);
    }
}

/**
* Funkcija koja pauzira igru i otvara meni
* - čuva sliku ekrana u trenutku pauziranja, koja se prikazuje kao pozadina u meniju
*/
static void pauseGame()
{
    int i;
    if (audio) Mix_PauseMusic();
    SDL_DestroyTexture(backgroundTexture);
    SDL_DestroyTexture(gameOverTexture);
    SDL_DestroyTexture(levelClearTexture);
    for (i=0; i<TEXTS_NUM; i++) freeText(&texts[i]);
    if (game)
    {
        if (game->pauseTexture) SDL_DestroyTexture(game->pauseTexture);
        game->pauseSurface = SDL_CreateRGBSurface(0, WINDOWW, WINDOWH, 32, 0x00ff0000, 0x0000ff00, 0x000000ff, 0xff000000);
        SDL_RenderReadPixels(renderer, NULL, SDL_PIXELFORMAT_ARGB8888, game->pauseSurface->pixels, game->pauseSurface->pitch);
        game->pauseTexture = SDL_CreateTextureFromSurface(renderer, game->pauseSurface);
    }
}

/**
* Funkcija koja poziva handleIteration funkciju za svakog igrača na ekranu
*/
static void updatePlayers()
{
    playerListNodePtr curr = game->players, next;
    while (curr)
    {
        next = curr->next;
        curr->player->handleIteration(curr);
        curr = next;
    }
}

/**
* Funkcija koja poziva handleIteration funkciju za svakog neprijatelja na ekranu
*/
static void updateEnemies()
{
    enemyListNodePtr curr = game->enemies, next;
    while (curr)
    {
        next = curr->next;
        curr->enemy->handleIteration(curr);
        curr = next;
    }
}

/**
* Funkcija koja poziva handleIteration funkciju za svaki metaka (i bombu) na ekranu
*/
static void updateBullets()
{
    bulletListNodePtr curr = game->bullets, next;
    while (curr)
    {
        next = curr->next;
        curr->bullet->handleIteration(curr);
        curr = next;
    }
}

/**
* Funkcija koja poziva handleIteration funkciju za svako pojačanje na ekranu
*/
static void updatePowerUps()
{
    powerUpListNodePtr curr = game->powerUps, next;
    while (curr)
    {
        // printf("Updating power ups");
        next = curr->next;
        curr->powerUp->handleIteration(curr);
        curr = next;
    }
}

/**
* Funkcija koja poziva handleIteration funkciju za svaki efekat na ekranu
*/
void updateEffects()
{
    effectListNodePtr curr = game->effects, next;
    while (curr)
    {
        next = curr->next;
        curr->effect->handleIteration(curr);
        curr = next;
    }
}

/**
* Zamenjuje dva reda backgrounda u matrici ucitanog nivoa (po indeksima)
*/
void swap_tile_rows(int a, int b)
{
    int i,c;
    for (i = 0; i < BACKGROUND_GRID_X; i++)
        c = game -> level_matrix[a][i], game -> level_matrix[a][i] = game -> level_matrix[b][i], game -> level_matrix[b][i] = c;

}

/**
* Ucitava sledeci red indeksa tileova za nivo iz fajla u prvi red matrice
*/
int * background_load_row()
{
    int i;
    int * ret = (int *) calloc(BACKGROUND_GRID_X,sizeof(int));
    for (i=0; i<BACKGROUND_GRID_X;i++)
        if(!feof(game->level_file))
                fscanf(game->level_file,"%d",&ret[i]), ret[i]%=BACKGROUNDS_NUM;
            else
                ret[i] = game->level_default;
    return ret;
}

/**
* Ucitava sledeci red indeksa tileova iz kampanje
*/
int * background_campaign()
{
    int i;
    int * ret = (int *) calloc(BACKGROUND_GRID_X,sizeof(int));
    for (i=0; i<BACKGROUND_GRID_X;i++)
        if (game->campaign_row<30) ret[i] = campaign_background[game->campaign_level_ind][game->campaign_row][i];
        else ret[i] = 0;
    game->campaign_row++;
    return ret;
}

/**
* Generise random novi red indeksa tileova
*/
int * background_random()
{
    int i, old, oldset=rand()%2+1;
    int * ret = (int *) calloc(BACKGROUND_GRID_X,sizeof(int));
    for (i=0; i<BACKGROUND_GRID_X;i++)
        old = ret[i] = ((rand() % 5 == 0) && !old && !game->level_matrix[0][i]) * (2-(oldset/2)), oldset = (old>0)?old:oldset;
    return ret;
}

/**
* Ubacuje novi red tileova u nivo (paziti na deklaracije u game.h)
*/
void background_swap(int * row)
{
    int i;
    for (i=0; i<BACKGROUND_GRID_Y-1;i++) // pomeri sve redove za jedan dole i onda
        swap_tile_rows(i,0);
    for (i=0; i<BACKGROUND_GRID_X;i++) // ubaci novi tile na vrh
        game->level_matrix[0][i] = row[i];
    free(row);
}

/**
* U svakom frejmu poziva funkcije koje updateuju pozadinu
*/
void doBackgroundJob()
{
    if (game->game_mode==1 && game->campaign_row==31) return;
    if (game->background_offset < BACKGROUND_TILE_SIZE) game->background_offset += BACKGROUND_SPEED;
    else
    {
        switch (game->game_mode)
        {
            case 0: background_swap(background_random()); break; // free mode
            case 1: background_swap(background_campaign()); break; // campaign
            case 2: background_swap(background_load_row());break; //custom level
            default: break;
        }

        game->background_offset=0;

    }
}

/**
* Funkcija sa glavnom petljom igre
* - prepoznaje dogadjaje i cuva ih u nizu events
* - redom poziva funkc˝ije za ažuriranje: igrača, neprijatelja, efekata, metaka i pojačanja
* - poziva funkciju koja detektuje i hendluje sudate objekata
* - poziva funkciju koja ažurira generalno stanje igre
* - poziva funkciju koja iscrtava stanje igre na ekran
* - održava ujednačen broj frejmova po sekundi
*/
void runGame()
{
    SDL_Event event;
    Uint32 fps=0, fps_clock, speedcap=8;
    int running=1, i;
    if (!game || game->frames == 0)
    {
        for (i=0;i<BACKGROUND_GRID_Y;i++)
            game->background_offset=BACKGROUND_TILE_SIZE,doBackgroundJob(); // inicijalno puni matricu
    }
    initGameFunction();
    fps_clock = SDL_GetTicks();
    while (running)
    {
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_KEYDOWN)
            {
                switch (event.key.keysym.sym)
                {
                case SDLK_p: case SDLK_a: case SDLK_s: case SDLK_d: case SDLK_w: case SDLK_SPACE: case SDLK_ESCAPE: case SDLK_b:
                    events[event.key.keysym.sym] = 1;
                    break;
                case SDLK_UP:
                    events[SDLK_w] = 1;
                    break;
                case SDLK_DOWN:
                    events[SDLK_s] = 1;
                    break;
                case SDLK_LEFT:
                    events[SDLK_a] = 1;
                    break;
                case SDLK_RIGHT:
                    events[SDLK_d] = 1;
                    break;
                }
            }
            if (event.type == SDL_KEYUP)
            {
                switch (event.key.keysym.sym)
                {
                case SDLK_a: case SDLK_s: case SDLK_d: case SDLK_w: case SDLK_SPACE: case SDLK_b:
                    events[event.key.keysym.sym] = 0;
                    break;
                case SDLK_UP:
                    events[SDLK_w] = 0;
                    break;
                case SDLK_DOWN:
                    events[SDLK_s] = 0;
                    break;
                case SDLK_LEFT:
                    events[SDLK_a] = 0;
                    break;
                case SDLK_RIGHT:
                    events[SDLK_d] = 0;
                    break;
                }
            }
            if (event.type == SDL_WINDOW_MINIMIZED)
            {
                events[SDLK_p] = 1;
            }
        }

        updatePlayers();
        updateEnemies();
        updateEffects();
        updateBullets();
        updatePowerUps();
        detectCollisions();

        renderGame();

        if (SDL_GetTicks() - fps_clock > 250)
        {
            // printf("%d\n",fps*4); ispis fps-a
            if (fps > FPS_INTENDED / 4) speedcap++;
            else if (fps < FPS_INTENDED / 4) speedcap--;
            speedcap = (speedcap<1000)?speedcap:0;
            fps = 0;
            fps_clock = SDL_GetTicks();
        }
        SDL_Delay(speedcap);
        fps++;

        doBackgroundJob();
        running = game->handleIteration();
    }
    pauseGame();
    return;
}
