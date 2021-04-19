#include "menu.h"

/**
* Funkcija za inicijalizaciju menija:
* - inicijalizacija tekstualnih struktura
* - inicijalizacija tekstura za pozadinu
* - postavljanje parametara za selektore
*/
static void initMenu()
{
    int i;
    char tmpTxt[255];
    for (i=0; i<256; i++) events[i] = 0;
    strcpy(tmpTxt, "Continue game");
    if (!game) strcat(tmpTxt, " (no game started)");
    initText(&textTextures[0], 150, 320, 200, 200, 200, 255, font, tmpTxt);
    strcpy(tmpTxt, "Campaign");
    initText(&textTextures[1], 150, 370, 200, 200, 200, 255, font, tmpTxt);
    strcpy(tmpTxt, "New endurance game (Medium)");
    initText(&textTextures[2], 150, 420, 200, 200, 200, 255, font, tmpTxt);
    strcpy(tmpTxt, "Save game");
    if (!game) strcat(tmpTxt, " (no game started)");
    if (game && game->game_mode == 2) strcat(tmpTxt, " (can't save this game mod)");
    initText(&textTextures[3], 150, 470, 200, 200, 200, 255, font, tmpTxt);
    strcpy(tmpTxt, "Load saved game");
    initText(&textTextures[4], 150, 520, 200, 200, 200, 255, font, tmpTxt);
    strcpy(tmpTxt, "Load custom level (Medium)");
    initText(&textTextures[5], 150, 570, 200, 200, 200, 255, font, tmpTxt);
    strcpy(tmpTxt, "Exit");
    initText(&textTextures[6], 150, 620, 200, 200, 200, 255, font, tmpTxt);
    sprintf(tmpTxt, "Continue campaign (lvl: %d)", lastCampaignLevel);
    initText(&textTextures[7], 570, 250, 3, 3, 3, 255, font, tmpTxt); textTextures[7]->show = 0;
    strcpy(tmpTxt, "level 1: Battle of Baguio");
    initText(&textTextures[8], 570, 300, 3, 3, 3, 255, font, tmpTxt); textTextures[8]->show = 0;
    strcpy(tmpTxt, "level 2: Battle of Medenine"); i = (lastCampaignLevel<2?100:3);
    initText(&textTextures[9], 570, 350, i, i, i, 255, font, tmpTxt); textTextures[9]->show = 0;
    strcpy(tmpTxt, "Level 3: Operation Overlord"); i = (lastCampaignLevel<3?100:3);
    initText(&textTextures[10], 570, 400, i, i, i, 255, font, tmpTxt); textTextures[10]->show = 0;
    strcpy(tmpTxt, "Level name: ");
    initText(&textTextures[11], 540, 550, 3, 3, 3, 255, font, tmpTxt); textTextures[11]->show = 0;
    initText(&textTextures[12], 950, 200, 255, 255, 255, 255, font, "High scores:"); textTextures[12]->show = game;
    for (i=0; i<10; i++)
    {
        if (game) sprintf(tmpTxt, "%2d.  %10d  %s", i+1, game->HSScores[i], game->HSNames[i]);
        else strcpy(tmpTxt, "_");
        initText(&textTextures[i+13], 900, 230+30*i, 255, 255, 255, 255, font, tmpTxt);
        textTextures[i+13]->show = game;
    }
    initText(&textTextures[23], 1050, 600, 255, 255, 255, 255, font, "For tips, press F1 !");
    backgroundTexture = IMG_LoadTexture(renderer, "res/images/background/mainmenu.png");
    backgroundOverlay = IMG_LoadTexture(renderer, "res/images/background/overlayMenu.png");
    selectorTexture = IMG_LoadTexture(renderer, "res/images/objTextures/b1.png");
    metalFrameTexture = IMG_LoadTexture(renderer, "res/images/background/metal_frame.jpg");
    logoTexture = IMG_LoadTexture(renderer, "res/images/background/logo.png");
    helpTexture = IMG_LoadTexture(renderer, "res/images/background/help.png");
    helpRect.x = helpRect.y = helpRect.w = helpRect.h = 0;
    difficulty = 2;
    selectorPos = 1;
    selectorRect.h = selectorRect.w = 20;
    selectorRect.x = 110;
    selectorRect.y = 320;
    metalFrameRect.h = metalFrameRect.w = metalFrameRect.x = metalFrameRect.y = 0;
    mainMetalFrameRect.h = 370;
    mainMetalFrameRect.w = 380;
    mainMetalFrameRect.x = 85;
    mainMetalFrameRect.y = 290;
    helpTipRect.h = 42;
    helpTipRect.w = 190;
    helpTipRect.x = 1030;
    helpTipRect.y = 590;
    selector2Rect.h = selector2Rect.w = selector2Rect.x = selector2Rect.y = 0;
    logoRect.h = 180, logoRect.w = 360, logoRect.x = 50, logoRect.y = 90;
    if (!game) selectorPos = 2, selectorRect.y = 370;
    if (audio)
    {
        menuMusic = Mix_LoadMUS("res/sound/menuMusic.mp3");
        Mix_PlayMusic(menuMusic, -1);
        Mix_VolumeMusic(9);
    }
}

/**
* Funkcija za deinicijalizaciju menija
* - deinicijalizacija svih tekstura
*/
static void killMenu()
{
    int i;
    if (audio) Mix_PauseMusic();
    SDL_DestroyTexture(backgroundTexture);
    SDL_DestroyTexture(backgroundOverlay);
    SDL_DestroyTexture(selectorTexture);
    SDL_DestroyTexture(metalFrameTexture);
    SDL_DestroyTexture(logoTexture);
    for (i=0; i<TEXT_TEXTURE_NUM; i++) freeText(&textTextures[i]);
}

/**
* Funkcija koja iscrtava meni
* - prepoznavanje izmena koje treba da budu napravljene na teksturama sa tekstom
*/
static void renderMenu()
{
    int i;
    static int lastDifficulty=2;
    if (difficulty != lastDifficulty)
    {
        char temp[50], diff[10];
        sprintf(diff, "%s", difficulty==0?"Demo": difficulty==1?"Easy": difficulty==2?"Medium":"Hard");
        sprintf(temp, "New endurance game (%s)", diff);
        editText(&textTextures[2], temp);
        sprintf(temp, "Load custom level (%s)", diff);
        editText(&textTextures[5], temp);
        lastDifficulty = difficulty;
    }
    SDL_RenderClear(renderer);
    if (game && game->pauseTexture) SDL_RenderCopy(renderer, game->pauseTexture, NULL, &backgroundRect);
    else SDL_RenderCopy(renderer, backgroundTexture, NULL, &backgroundRect);
    if (!game)
    {
        SDL_RenderCopy(renderer, backgroundOverlay, NULL, &mainMetalFrameRect);
        SDL_RenderCopy(renderer, backgroundOverlay, NULL, &helpTipRect);
    }
    else SDL_RenderCopy(renderer, backgroundOverlay, NULL, &backgroundRect);
    SDL_RenderCopy(renderer, metalFrameTexture, NULL, &metalFrameRect);
    SDL_RenderCopy(renderer, selectorTexture, NULL, &selectorRect);
    SDL_RenderCopy(renderer, selectorTexture, NULL, &selector2Rect);
    for (i=0; i<TEXT_TEXTURE_NUM; i++) drawText(textTextures[i]);
    SDL_RenderCopy(renderer, logoTexture, NULL, &logoRect);
    SDL_RenderCopy(renderer, helpTexture, NULL, &helpRect);
    SDL_RenderPresent(renderer);
}

/**
* Funkcija koja prikazuje podmeni za odabir željenog dela kampanje
* - na početku funkcije se uključuje prkazivanje podmenija
* - omogućava odabiranje željene opcije podešavanjem slelektoora
* - pri izlasku prekida ispisivanje podmenija
*/
int selectCampaignLevel()
{
    int running=1, i;
    SDL_Event event;
    metalFrameRect.x = 500;
    metalFrameRect.y = 220;
    metalFrameRect.w = 400;
    metalFrameRect.h = 240;
    selector2Pos = 1;
    selector2Rect.x = 535;
    selector2Rect.y = 250;
    for (i=7; i<11; i++) textTextures[i]->show = 1;
    selector2Rect.w = selector2Rect.h = 20;
    while (running)
    {
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_KEYDOWN)
            {
                switch (event.key.keysym.sym)
                {
                case SDLK_s: case SDLK_DOWN:
                    selector2Pos += 1;
                    selector2Rect.y += 50;
                    if (selector2Pos == 5) selector2Pos = 1, selector2Rect.y = 250;
                    if (selector2Pos - 1 > lastCampaignLevel) selector2Pos = 1, selector2Rect.y = 250;
                    break;
                case SDLK_w: case SDLK_UP:
                    selector2Pos -= 1;
                    selector2Rect.y -= 50;
                    if (selector2Pos == 0) selector2Pos = 4, selector2Rect.y = 400;
                    if (selector2Pos - 1 > lastCampaignLevel) selector2Pos = lastCampaignLevel + 1, selector2Rect.y = 250 + lastCampaignLevel*50;
                    break;
                case SDLK_a: case SDLK_ESCAPE: case SDLK_LEFT:
                    running = 0;
                    selector2Pos = 0;
                    break;
                case SDLK_RETURN:
                    running = 0;
                    break;
                }
            }
        }
        renderMenu();
    }
    metalFrameRect.h = metalFrameRect.w = metalFrameRect.x = metalFrameRect.y = 0;
    selector2Rect.h = selector2Rect.w = selector2Rect.x = selector2Rect.y = 0;
    for (i=7; i<11; i++) textTextures[i]->show = 0;
    return selector2Pos;
}

/**
* Funkcija koja omogucava unos imena dodatnog nivoa
* - učitavanje imena svih fajlova sa opisima nivoa u niz
* - korišćenjem dugmeta TAB moguce je iterirati kroz učitani niz
* @param    fileName    Niz kararaktera u koji se upisuje uneto ime
*/
void getLevelFileName(char *fileName)
{
    int running=1, charCo=0, levelFiles=0, levelFileInd=-1;
    char strTmp[256] = "(TAB) Level name: ", levelFileNames[256][256];
    SDL_Event event;
    DIR *dir;
    struct dirent *ent;
    if ((dir = opendir ("res/levels/")) != NULL) {
        while ((ent = readdir (dir)) != NULL)
        {
            if(strlen(ent->d_name) > 4 && !strcmp(ent->d_name + strlen(ent->d_name) - 4, ".lvl"))
            {
                strcpy(levelFileNames[levelFiles], ent->d_name);
                levelFileNames[levelFiles][strlen(levelFileNames[levelFiles])-4] = 0;
                levelFiles++;
            }

        }
        closedir (dir);
    }
    fileName[0] = 0;
    editText(&textTextures[11], strTmp);
    metalFrameRect.x = 500;
    metalFrameRect.y = 540;
    metalFrameRect.w = 550;
    metalFrameRect.h = 45;
    textTextures[11]->show = 1;
    while (running)
    {
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_KEYDOWN)
            {
                if (event.key.keysym.sym == SDLK_ESCAPE || event.key.keysym.sym == SDLK_LEFT)
                {
                    running = 0;
                    fileName[0] = 0;
                }
                else if ((event.key.keysym.sym >= SDLK_a && event.key.keysym.sym <= SDLK_z) ||
                         (event.key.keysym.sym >= SDLK_0 && event.key.keysym.sym <= SDLK_9))
                {
                    if (charCo < 25)
                    {
                        fileName[charCo++] = event.key.keysym.sym;
                        fileName[charCo] = 0;
                        sprintf(strTmp, "(TAB) Level name: %s", fileName);
                        editText(&textTextures[11], strTmp);
                    }
                }
                else if (event.key.keysym.sym == SDLK_BACKSPACE)
                {
                    if (charCo > 0)
                    {
                        fileName[--charCo] = 0;
                        sprintf(strTmp, "(TAB) Level name: %s", fileName);
                        editText(&textTextures[11], strTmp);
                    }
                }
                else if (event.key.keysym.sym == SDLK_TAB)
                {
                    if (levelFiles)
                    {
                        levelFileInd = (levelFileInd + 1) % levelFiles;
                        charCo = strlen(levelFileNames[levelFileInd]);
                        strcpy(fileName, levelFileNames[levelFileInd]);
                        sprintf(strTmp, "(TAB) Level name: %s", fileName);
                        editText(&textTextures[11], strTmp);
                    }
                }
                else if (event.key.keysym.sym == SDLK_RETURN) running = 0;
            }
        }
        renderMenu();
    }
    metalFrameRect.h = metalFrameRect.w = metalFrameRect.x = metalFrameRect.y = 0;
    textTextures[11]->show = 0;
}

/**
* Funkcija koja omogucava unos imena snimljene igre
* - ucitavanje imena svih fajlova sa opisima nivoa u niz
* - korišćenjem dugmeta TAB moguce je iterirati kroz učitani niz
* @param    fileName    Niz kararaktera u koji se upisuje uneto ime
*/
void getSavedGameName(char *fileName)
{
    int running=1, charCo=0, levelFiles=0, levelFileInd=-1;
    char strTmp[256] = "(TAB) Game name: ", levelFileNames[256][256];
    SDL_Event event;
    DIR *dir;
    struct dirent *ent;
    if ((dir = opendir ("res/saves/")) != NULL) {
        while ((ent = readdir (dir)) != NULL)
        {
            if(strlen(ent->d_name) > 4 && !strcmp(ent->d_name + strlen(ent->d_name) - 4, ".gsa"))
            {
                strcpy(levelFileNames[levelFiles], ent->d_name);
                levelFileNames[levelFiles][strlen(levelFileNames[levelFiles])-4] = 0;
                levelFiles++;
            }

        }
        closedir (dir);
    }
    fileName[0] = 0;
    editText(&textTextures[11], strTmp);
    metalFrameRect.x = 500;
    metalFrameRect.y = 540;
    metalFrameRect.w = 550;
    metalFrameRect.h = 45;
    textTextures[11]->show = 1;
    while (running)
    {
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_KEYDOWN)
            {
                if (event.key.keysym.sym == SDLK_ESCAPE || event.key.keysym.sym == SDLK_LEFT)
                {
                    running = 0;
                    fileName[0] = 0;
                }
                else if ((event.key.keysym.sym >= SDLK_a && event.key.keysym.sym <= SDLK_z) ||
                         (event.key.keysym.sym >= SDLK_0 && event.key.keysym.sym <= SDLK_9))
                {
                    if (charCo < 25)
                    {
                        fileName[charCo++] = event.key.keysym.sym;
                        fileName[charCo] = 0;
                        sprintf(strTmp, "(TAB) Game name: %s", fileName);
                        editText(&textTextures[11], strTmp);
                    }
                }
                else if (event.key.keysym.sym == SDLK_BACKSPACE)
                {
                    if (charCo > 0)
                    {
                        fileName[--charCo] = 0;
                        sprintf(strTmp, "(TAB) Game name: %s", fileName);
                        editText(&textTextures[11], strTmp);
                    }
                }
                else if (event.key.keysym.sym == SDLK_TAB)
                {
                    if (levelFiles)
                    {
                        levelFileInd = (levelFileInd + 1) % levelFiles;
                        charCo = strlen(levelFileNames[levelFileInd]);
                        strcpy(fileName, levelFileNames[levelFileInd]);
                        sprintf(strTmp, "(TAB) Game name: %s", fileName);
                        editText(&textTextures[11], strTmp);
                    }
                }
                else if (event.key.keysym.sym == SDLK_RETURN) running = 0;
            }
        }
        renderMenu();
    }
    metalFrameRect.h = metalFrameRect.w = metalFrameRect.x = metalFrameRect.y = 0;
    textTextures[11]->show = 0;
}

/**
* Funkcija za hendlovanje dogadjaja (eventa) u meniju
* - odabiranje željene opcije selektorom
* - komande: W, A, S, D, strelice, razmak, enter i dugme escape
* - vraća 1 ako je potrebno ostati u meniju, ili 0 ukoliko je potrebno izaći iz menija
* @param    ret    Broj koji označava da li je nakon zatvaranja menija sa povratnom vrednošću 0, potrebno pokrenuti igru ili ugasiti program
*/
static int handleMenuEvents(int *ret)
{
    char temp[255];
    if (events[SDLK_0]) difficulty = 0;
    if (events[SDLK_1]) difficulty = 1;
    if (events[SDLK_2]) difficulty = 2;
    if (events[SDLK_3]) difficulty = 3;
    if (events[SDLK_m])
    {
        int running = 1;
        SDL_QueryTexture(helpTexture, NULL, NULL, &(helpRect.w), &(helpRect.h));
        helpRect.w /= 2;
        helpRect.h /= 2;
        helpRect.x = (WINDOWW - helpRect.w) / 2;
        helpRect.y = (WINDOWH - helpRect.h) / 2;
        SDL_Event event;
        while (running)
        {
            while (SDL_PollEvent(&event))
            {
                if (event.type == SDL_KEYDOWN) running = 0;
                renderMenu();
            }
        }
        helpRect.x = helpRect.y = helpRect.w = helpRect.h = 0;
    }
    if (events[SDLK_w])
    {
        switch (selectorPos)
        {
        case 1: // nastavi igru
            selectorPos = 7;
            selectorRect.y = 620;
            break;
        case 2: // kampanja
            if (game) selectorPos = 1, selectorRect.y = 320;
            else selectorPos = 7, selectorRect.y = 620;
            break;
        case 3: // slobodna igra
            selectorPos = 2;
            selectorRect.y = 370;
            break;
        case 4: // snimi
            selectorPos = 3;
            selectorRect.y = 420;
            break;
        case 5: // ucitaj igru
            if (game && game->game_mode != 2) selectorPos = 4, selectorRect.y = 470;
            else selectorPos = 3, selectorRect.y = 420;
            break;
        case 6: // ucitaj nivo iz fajla
            selectorPos = 5;
            selectorRect.y = 520;
            break;
        case 7: // izlazak
            selectorPos = 6;
            selectorRect.y = 570;
            break;
        }
    }
    if (events[SDLK_s])
    {
        switch (selectorPos)
        {
        case 1: // nastavi igru
            selectorPos = 2;
            selectorRect.y = 370;
            break;
        case 2: // kampanja
            selectorPos = 3;
            selectorRect.y = 420;
            break;
        case 3: // slobodna igra
            if (game && game->game_mode != 2) selectorPos = 4, selectorRect.y = 470;
            else selectorPos = 5, selectorRect.y = 520;
            break;
        case 4: // snimi
            selectorPos = 5;
            selectorRect.y = 520;
            break;
        case 5: // ucitaj igru
            selectorPos = 6;
            selectorRect.y = 570;
            break;
        case 6: // ucitaj nivo iz fajla
            selectorPos = 7;
            selectorRect.y = 620;
            break;
        case 7: // izlazak
            if (game) selectorPos = 1, selectorRect.y = 320;
            else selectorPos = 2, selectorRect.y = 370;
            break;
        }
    }
    if (selectorPos == 1 && events[SDLK_RETURN]) // nastavak igre
    {
        return 0;
    }
    if (selectorPos == 2 && (events[SDLK_RETURN] || events[SDLK_d])) // ulazak u meni za odabir nivoa
    {
        switch (selectCampaignLevel())
        {
        case 1:
            sprintf(temp, "%d %d", lastCampaignLevel - 1, 0);// (campaign_row>4?campaign_row-4:0));
            if (game) freeGame();
            initGame(1, temp, lastCampaignLevel); // nastaviti kampanju
            return 0;
            break;
        case 2:
            if (game) freeGame();
             initGame(1, "0 0", 1); // pokrenuti prvi nivo u kampanji
            return 0;
            break;
        case 3:
            if (game) freeGame();
            initGame(1, "1 0", 2);// pokrenuti drugi nivo u kampanji (ako je otkljucan)
            return 0;
            break;
        case 4:
            if (game) freeGame();
            initGame(1, "2 0", 3); // restartovati kampanju i zapoceti prvi nivo
            return 0;
            break;
        }
    }
    if (selectorPos == 3 && events[SDLK_RETURN]) // slobodna igra
    {
        if (game) freeGame();
        // printf("game init: %d\n", difficulty);
        initGame(0, " ", difficulty); // random igra
        return 0;
    }
    if (selectorPos == 4 && (events[SDLK_RETURN] || events[SDLK_d])) // snimanje
    {
        char gameName[50], filePath[256];
        getSavedGameName(gameName);
        if (gameName[0] != 0)
        {
            sprintf(filePath, "res/saves/%s.gsa", gameName);
            saveGame(filePath);
            sprintf(filePath, "res/saves/%s.bmp", gameName);
            SDL_SaveBMP(game->pauseSurface, filePath);
        }
    }
    if (selectorPos == 5 && (events[SDLK_RETURN] || events[SDLK_d])) // ucitaj igru
    {
        char gameName[50], filePath[256];
        FILE *inFile;
        getSavedGameName(gameName);
        if (gameName[0] != 0)
        {
            sprintf(filePath, "res/saves/%s.gsa", gameName);
            if ((inFile = fopen(filePath, "rb")))
            {
                if (game) freeGame();
                loadGame(filePath);
                sprintf(filePath, "res/saves/%s.bmp", gameName);
                game->pauseSurface = SDL_LoadBMP(filePath);
                game->pauseTexture = SDL_CreateTextureFromSurface(renderer, game->pauseSurface);
                editText(&textTextures[0], "Continue game");
                selectorPos = 1, selectorRect.y = 320;
            }
            else printf("Saved game with name \"%s\" does not exist.\n", gameName);
        }
    }
    if (selectorPos == 6 && (events[SDLK_RETURN] || events[SDLK_d])) // ucitavanje nivoa iz fajla
    {
        char fileName[256];
        getLevelFileName(fileName);
        if (fileName[0] != 0)
        {
            char tmp[256];
            FILE *checkFile;
            strcpy(tmp, "res/levels/");
            strcat(tmp, fileName);
            strcat(tmp, ".lvl");
            checkFile = fopen(tmp, "r");
            // printf("Ime nivoa: %s\n", fileName);
            if (checkFile) // ako postoji fajl
            {
                fclose(checkFile);
                if (game) freeGame();
                initGame(2, fileName, difficulty); // proslediti parametre koji oznacavaju random igru
                return 0;
            }
        }
    }
    if (selectorPos == 7 && events[SDLK_RETURN]) // izlazak iz igrice
    {
        *ret = 0;
        freeGame();
        return 0;
    }
    return 1;
}

/**
* Funkcija sa glavnom petljom menija
* - prepoznaje dogadjaje i ažurira niz events
* - poziva funkciju handleMenuEvents koja upravlja menijem
* - vraca 1 ukoliko je potrebno pokrenuti igru, ili 0 ukoliko je potrebno izaći iz prorama
*/
int showMenu()
{
    SDL_Event event;
    int running = 1, ret = 1;
    initMenu();
    while (running)
    {
        events[SDLK_w] = events[SDLK_s] = events[SDLK_d] = events[SDLK_RETURN] = 0;
        events[SDLK_1] = events[SDLK_2] = events[SDLK_3] = events[SDLK_0] = 0;
        events[SDLK_m] = 0;
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_KEYDOWN)
            {
                switch (event.key.keysym.sym)
                {
                case SDLK_s: case SDLK_w: case SDLK_d: case SDLK_RETURN:
                case SDLK_0: case SDLK_1: case SDLK_2: case SDLK_3: case SDLK_4:
                case SDLK_5: case SDLK_6: case SDLK_7: case SDLK_8: case SDLK_9:
                    events[event.key.keysym.sym] = 1;
                    break;
                case SDLK_UP:
                    events[SDLK_w] = 1;
                    break;
                case SDLK_DOWN:
                    events[SDLK_s] = 1;
                    break;
                case SDLK_RIGHT:
                    events[SDLK_d] = 1;
                    break;
                case SDLK_F1:
                    events[SDLK_m] = 1; // indeks slova m je iskoriscen za event za help
                    break;
                }
            }
            if (event.type == SDL_KEYUP)
            {
                switch (event.key.keysym.sym){}
            }
        }
        running = handleMenuEvents(&ret);
        renderMenu();
    }
    killMenu();
    return ret;
}
