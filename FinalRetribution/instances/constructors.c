#include "instances.h"

/**
* Funkcija koja inicijalizuje teksture za igru
* - učita teksture iz foldera sa resursima u niz tekstura koji se koristi za iscrtavanje objekata
*/
void initTextures()
{
    game->backgroundTiles = (SDL_Texture **) calloc(BACKGROUNDS_NUM,sizeof(SDL_Texture*));
    game->backgroundTiles[0]=IMG_LoadTexture(renderer, "res/images/background/tileable_water2.jpg");
    game->backgroundTiles[1]=IMG_LoadTexture(renderer, "res/images/background/island.jpg");
    game->backgroundTiles[2]=IMG_LoadTexture(renderer, "res/images/background/island2.jpg");
    game->backgroundTiles[3]=IMG_LoadTexture(renderer, "res/images/background/desert.jpg");
    game->backgroundTiles[4]=IMG_LoadTexture(renderer, "res/images/background/desert_palm.jpg");
    game->backgroundTiles[5]=IMG_LoadTexture(renderer, "res/images/background/grass.jpg");
    game->backgroundTiles[6]=IMG_LoadTexture(renderer, "res/images/background/grass_diagonal_road.png");
    game->backgroundTiles[7]=IMG_LoadTexture(renderer, "res/images/background/grass_crater_grass.png");
    game->backgroundTiles[8]=IMG_LoadTexture(renderer, "res/images/background/grass_swamp.png");

    game->enemy_sprites = (SDL_Texture **) calloc(3*ENEMY_NUM,sizeof(SDL_Texture*));
    game->enemy_sprites[0]=IMG_LoadTexture(renderer, "res/images/objTextures/enemy_top.png");
    game->enemy_sprites[1]=IMG_LoadTexture(renderer, "res/images/objTextures/enemy_left.png");
    game->enemy_sprites[2]=IMG_LoadTexture(renderer, "res/images/objTextures/enemy_right.png");
    game->enemy_sprites[3]=IMG_LoadTexture(renderer, "res/images/objTextures/stuka_top.png");
    game->enemy_sprites[4]=IMG_LoadTexture(renderer, "res/images/objTextures/stuka_left.png");
    game->enemy_sprites[5]=IMG_LoadTexture(renderer, "res/images/objTextures/stuka_right.png");
    game->enemy_sprites[6]=IMG_LoadTexture(renderer, "res/images/objTextures/boss_top.png");
    game->enemy_sprites[7]=IMG_LoadTexture(renderer, "res/images/objTextures/boss_left.png");
    game->enemy_sprites[8]=IMG_LoadTexture(renderer, "res/images/objTextures/boss_right.png");
    game->enemy_sprites[9]=IMG_LoadTexture(renderer, "res/images/objTextures/kamikaza_top.png");
    game->enemy_sprites[10]=IMG_LoadTexture(renderer, "res/images/objTextures/kamikaza_left.png");
    game->enemy_sprites[11]=IMG_LoadTexture(renderer, "res/images/objTextures/kamikaza_right.png");
    game->enemy_sprites[12]=IMG_LoadTexture(renderer, "res/images/objTextures/boss_top.png");
    game->enemy_sprites[13]=IMG_LoadTexture(renderer, "res/images/objTextures/boss_left.png");
    game->enemy_sprites[14]=IMG_LoadTexture(renderer, "res/images/objTextures/boss_right.png");
    game->enemy_sprites[15]=IMG_LoadTexture(renderer, "res/images/objTextures/tank.png");
    game->enemy_sprites[16]=IMG_LoadTexture(renderer, "res/images/objTextures/ship.png");

    game->explosion_texture = IMG_LoadTexture(renderer, "res/images/objTextures/explosion.png");
    game->bullet_texture = IMG_LoadTexture(renderer, "res/images/objTextures/bullet.png");
    game->bomb_texture = IMG_LoadTexture(renderer, "res/images/objTextures/bomb.png");
    game->fumes_texture = IMG_LoadTexture(renderer, "res/images/objTextures/f1.png");
    game->holeTexture = IMG_LoadTexture(renderer, "res/images/objTextures/hole.png");
    game->powerUpTexture = IMG_LoadTexture(renderer, "res/images/objTextures/powerUp.png");
    game->shieldTexture = IMG_LoadTexture(renderer, "res/images/objTextures/shield.png");
    game->speedTexture = IMG_LoadTexture(renderer, "res/images/objTextures/speed.png");

    game->playerTexture = IMG_LoadTexture(renderer, "res/images/objTextures/players/p0.png");
    game->playerTextureLeft = IMG_LoadTexture(renderer, "res/images/objTextures/players/left.png");
    game->playerTextureRight = IMG_LoadTexture(renderer, "res/images/objTextures/players/right.png");
    game->pauseTexture = NULL;
    game->pauseSurface = NULL;
}

/**
* Funkcija za inicijalizaciju strukture igre
* - inicijalna podešavanja broja objekata i raznih brojača
* - u zavisnosti od tipa igre koji se inicijalizuje otvara se određena HighScore tabela
* - zove se inicijalizacija tekstura i pozadine
* @param    game_mode    Indikator tipa igre koja se inicijalizuje (0:free game, 1:kampanja, 2:ucitavanje iz fajla)
* @param    difficulty    Indikator težine igre koja se inicijalizuje (0:demo igra, 1:lako, 2:normalno, 3:teško)
*/
void initGame(int game_mode,char * s,int difficulty)
{
    char HSFileName[51], tmp[256];
    int i;
    FILE *HSFile;
    game = malloc(sizeof(struct gameStruct));
    game->handleIteration = gameItrationHandlerDefault;
    game->players = NULL;
    game->enemies = NULL;
    game->effects = NULL;
    game->bullets = NULL;
    game->powerUps = NULL;
    game->playersCount = 0;
    game->enemiesCount = 0;
    game->effectsCount = 0;
    game->bulletsCount = 0;
    game->frames = 0;
    game->score = 0;
    game->game_mode = game_mode;
    game->difficulty = difficulty;
    game->boss_active = 0;
    game->final_boss_active=0;
    game->enemySpawnCounter=0;
    game->level_file = NULL;
    sprintf(HSFileName, "res/highscores/difficulty%d", difficulty);
    switch(game_mode)
    {
    case 0:
        strcat(HSFileName, "freeGameHighScoreTable.hst");
        break;
    case 1:
        sscanf(s,"%d %d", &game->campaign_level_ind, &game->campaign_row);
        sprintf(tmp, "%sCampaignLvl%dHighScoreTable.hst", HSFileName, game->campaign_level_ind);
        strcpy(HSFileName,tmp);
        break;
    case 2:
        strcat(HSFileName, s);
        strcat(HSFileName, ".hst");
        strcat(s, ".lvl");
        strcpy(tmp, "res/levels/");
        strcat(tmp, s);
        game->level_file = fopen(tmp, "r");
        if (game->level_file == NULL)
        {
            game->game_mode=0, printf("No such file! Fallback to free mod!");
            strcpy(HSFileName, "freeGameHighScoreTable.hst");
        }
         else
        {
            if(!feof(game->level_file))
                 fscanf(game->level_file,"%d",&game->level_default);
         }
        break;
    }

    strcpy(game->HSFileName, HSFileName);
    HSFile = fopen(HSFileName, "rb");
    if (HSFile)
    {
        HSFileMemberPtr HSentry = malloc(sizeof(struct HSFileMemberStruct));
        for (i=0; i<10; i++)
        {
            fread(HSentry, sizeof(struct HSFileMemberStruct), 1, HSFile);
            strcpy(game->HSNames[i], HSentry->name);
            game->HSScores[i] = HSentry->score;
        }
        free(HSentry);
        fclose(HSFile);
    }
    else
    {
        for (i=0; i<10; i++)
        {
            game->HSNames[i][0] = 0;
            game->HSScores[i] = 0;
        }
        saveHighScore();
    }

    game->framesFromCont = 0;
    game->background_offset = 0;

    initTextures();
    initLevelMatrix();
}

/**
* Funkcija za inicijalizaciju strukture za prikaz teksta
* @param    textTexture    Pokazivač na teksturu teksta koju treba iscrtati
* @param    x    X koordinata mesta na koje treba iscrtati teksturu
* @param    y    Y koordinata mesta na koje treba iscrtati teksturu
* @param    col1    Jačina crvene boje teksture RGBA formata
* @param    col2    Jačina zelene boje teksture RGBA formata
* @param    col3    Jačina plave boje teksture RGBA formata
* @param    col4    Jačina providnosti teksture RGBA formata
* @param    TTF_Font    Pokazivać na font koji će biti korišćen za iscrtavanje
* @param    str    Tekst koji treba iscrtati
*/
void initText(textPtr *textTexture, int x, int y, int col1, int col2, int col3, int col4, TTF_Font *font, char* str)
{
    *textTexture = malloc(sizeof(struct textStruct));
    (*textTexture)->color.r = col1;
    (*textTexture)->color.g = col2;
    (*textTexture)->color.b = col3;
    (*textTexture)->color.a = col4;
    (*textTexture)->font = font;
    (*textTexture)->rect.x = x;
    (*textTexture)->rect.y = y;
    (*textTexture)->show = 1;
    strcpy((*textTexture)->str, str);
    SDL_Surface *surf = TTF_RenderText_Blended((*textTexture)->font, (*textTexture)->str, (*textTexture)->color);
    (*textTexture)->texture = SDL_CreateTextureFromSurface(renderer, surf);
    SDL_FreeSurface(surf);
    // cuvanje visine i sirine teksta
    SDL_QueryTexture((*textTexture)->texture, NULL, NULL, &((*textTexture)->rect.w), &((*textTexture)->rect.h));
}

/**
* Funkcija za izmenu sadrzaja teksta i teksture strukture za prikaz teksta
* @param    textTexture    Pokazivač na teksturu teksta koju treba iscrtati
* @param    str    Tekst koji treba iscrtati
*/
void editText(textPtr *textTexture, char* str)
{
    strcpy((*textTexture)->str, str);
    SDL_DestroyTexture((*textTexture)->texture);
    SDL_Surface *surf = TTF_RenderText_Blended((*textTexture)->font, (*textTexture)->str, (*textTexture)->color);
    (*textTexture)->texture = SDL_CreateTextureFromSurface(renderer, surf);
    SDL_FreeSurface(surf);
    // cuvanje visine i sirine teksta
    SDL_QueryTexture((*textTexture)->texture, NULL, NULL, &((*textTexture)->rect.w), &((*textTexture)->rect.h));
}

/**
* Funkcija za inicijalizaciju strukture igraca i njeno dodavanje u listu igraca
* - struktura novog igraca se dodaje u dvostruko ulančanu listu svih igrača u okviru strukture igre
* - vrše se inicijalna podešavanja brojača strukture, pozicije i veličine objekta
*/
void initPlayer()
{
    playerListNodePtr newPlayerNode = malloc(sizeof(struct playerListNodeStruct));
    playerPtr newPlayer = newPlayerNode->player = malloc(sizeof(struct playerStruct));
    newPlayerNode->next = game->players;
    newPlayerNode->prev = NULL;
    if(game->players != NULL)
        game->players->prev = newPlayerNode;
    game->players = newPlayerNode;

    newPlayer->x_pos = WINDOWW/2 - 50;
    newPlayer->y_pos = WINDOWH - 150;
    newPlayer->position.x = round(newPlayer->x_pos);
    newPlayer->position.y = round(newPlayer->y_pos);;
    newPlayer->position.w = 89;
    newPlayer->position.h = 71;
    newPlayer->counter = 0;
    newPlayer->shieldActive = 0;
    newPlayer->speedActive = 0;
    newPlayer->bulletCoolDown = 30;
    newPlayer->bombCoolDown = 120;
    newPlayer->health = 300;
    if(game->difficulty == 0)
    {
        newPlayer->handleIteration = playerIterationHandlerDemo;
        game -> difficulty = 2;
    }
    else
        newPlayer->handleIteration = playerIterationHandlerDefault;

}

/**
* Funkcija za inicijalizaciju strukture neprijatelja i njeno dodavanje u dvostruko ulančanu listu neprijatelja
* - vrše se inicijalna podešavanja strukture neprijatelja, resetovanje brojača i setovanja parametara za iscrtavanje
* @param    x_pos   X koordinata mesta na koje treba postaviti neprijatelja pri inicijalizaciji
* @param    y_pos    Y koordinata mesta na koje treba postaviti neprijatelja pri inicijalizaciji
* @param    id    Identifikacioni broj tipa neprijatelja (0:obican, 1:avion sa više health-a, 2:boss follower, 3:kamikaza, 4:glavni boss, 5:meta)
* @param    path_id    Identifikacioni broj putanje po kojoj neprijatelj treba da se kreće
*/
void initEnemy(double x_pos, double y_pos,int id, int path_id)
{
    enemyListNodePtr newEnemyNode = malloc(sizeof(struct enemyListNodeStruct));
    enemyPtr newEnemy = newEnemyNode->enemy = malloc(sizeof(struct enemyStruct));
    newEnemyNode->next = game->enemies;
    newEnemyNode->prev = NULL;
    if(game->enemies != NULL)
        game->enemies->prev = newEnemyNode;
    game->enemies = newEnemyNode;

    newEnemy->x_pos = x_pos;
    newEnemy->y_pos = y_pos;
    newEnemy->position.x = round(newEnemy->x_pos);
    newEnemy->position.y = round(newEnemy->y_pos);;
    newEnemy->position.w = 60;
    newEnemy->position.h = 60;
    newEnemy->counter = 0;
    newEnemy->texture_slot = 0;
    newEnemy->coolDown = 70;
    newEnemy->id = id;
    newEnemy->path_id = path_id;
    switch(id)
    {
        case 0: // obican
            newEnemy->handleIteration = enemyIterationHandlerDefault;
            newEnemy->health = 10;
            newEnemy->score = 100;
            game->enemySpawnCounter+=1;
            // printf("Spawnovanih neprijatelja ima : %d",game->enemySpawnCounter);
            break;
        case 1: // stuka
            newEnemy->handleIteration = enemyIterationHandlerDefault;
            newEnemy->health = 20;
            newEnemy->score = 100;
            break;
        case 2: // boss follower
            newEnemy->handleIteration = enemyIterationHandlerFollower;
            newEnemy->health = sqrt(path_id)*180;
            newEnemy->score = 250;
            newEnemy->position.w = 100;
            newEnemy->position.h = 100;
            break;
        case 3: // kamikaze
            newEnemy->handleIteration = enemyIterationHandlerKamikaze;
            newEnemy->health = 20;
            newEnemy->score = 150;
            break;
        case 4: // glavni boss
            newEnemy->handleIteration = enemyIterationHandlerBoss;
            newEnemy->health = 1500;
            newEnemy->score = 1000;
            newEnemy->position.w = 200;
            newEnemy->position.h = 200;
            break;
        case 5: // meta na ostrvu ili u vodi
            newEnemy->handleIteration = enemyIterationHandlerGroundTarget;
            newEnemy->health = 1;
            newEnemy->score = 600;
            newEnemy->position.w = 40;
            newEnemy->position.h = 80;
            if (path_id==1)
            {
                newEnemy->position.h = 120;
                newEnemy->health = 11;
            }
            break;
    }
}

/**
* Funkcija za inicijalizaciju strukture metaka i njeno dodavanje u listu metaka
* - vrše se inicijalna podešavanja strukture metka, resetovanje brojača i setovanja parametara za iscrtavanje
* @param    x   X koordinata mesta na koje treba postaviti metak pri inicijalizaciji
* @param    y    Y koordinata mesta na koje treba postaviti metak pri inicijalizaciji
* @param    isPlayerOwned    Flag koji govori da li je metak ispaljen od strane igrača ili neprijatelja
* @param    type    Identifikacioni broj tipa metka (1:običan 2:bomba)
*/
void initBullet(double x, double y, short isPlayerOwned, int type)
{
    bulletListNodePtr newBulletNode = malloc(sizeof(struct bulletListNodeStruct));
    bulletPtr newBullet = newBulletNode->bullet = malloc(sizeof(struct bulletStruct));
    newBulletNode->next = game -> bullets;
    newBulletNode->prev = NULL;
    if (game->bullets!=NULL)
        game->bullets->prev = newBulletNode;
    game->bullets = newBulletNode;
    newBullet->id = type;

    switch (type)
    {
    case 1:
        newBullet->position.w = 3;
        newBullet->position.h = 15;
        newBullet->handleIteration = bulletIterationHandlerBullet;
        break;
    case 2:
        newBullet->position.w = 10;
        newBullet->position.h = 20;
        newBullet->handleIteration = bulletIterationHandlerBomb;
        break;
    }

    newBullet->x_pos = x - 5; //NO NO, hardkodovano, fuj to!
    newBullet->y_pos = y;
    newBullet->position.x = round(newBullet->x_pos);
    newBullet->position.y = round(newBullet->y_pos);
    newBullet->texturePosition.x = 1;
    newBullet->texturePosition.y = 42;
    newBullet->texturePosition.w = 10;
    newBullet->texturePosition.h = 10;
    newBullet->counter = 60;
    newBullet->isPlayerOwned = isPlayerOwned;
}

/**
* Funkcija za inicijalizaciju strukture efekta i njeno dodavanje u listu efekata
* - vrše se inicijalna podešavanja strukture efekta, resetovanje brojača i setovanja parametara za iscrtavanje
* @param    x   X koordinata mesta na koje treba postaviti efekat pri inicijalizaciji
* @param    y    Y koordinata mesta na koje treba postaviti efekat pri inicijalizaciji
* @param    type    Identifikacioni broj tipa efekta (1:dim 2:eksplozija u vazduhu, 3:eksplozija na zemlji, 4:rupa na zemlji, 5:pad običnog aviona, 6:pad štuke, 7:pad bossa followera, 8:pad kamikaza, 9:pad glavnog bossa, 10:štit, 11:brzina)
*/
void initEffect(double x, double y, int type)
{
    effectListNodePtr newEffectNode = malloc(sizeof(struct effectListNodeStruct));
    effectPtr newEffect = newEffectNode->effect = malloc(sizeof(struct effectStruct));
    newEffectNode->next = game->effects;
    newEffectNode->prev = NULL;
    if(game->effects != NULL)
        game->effects->prev =newEffectNode;
    game->effects = newEffectNode;
    switch (type)
    {
    case 1: // Efekat dima iz igracevog aviona
        newEffect->position.h = newEffect->position.w = 30;
        newEffect->handleIteration = effectIterationHandlerExhaust;
        break;
    case 2: // Efekat eksplozije neprijatelja
        newEffect->position.w = newEffect->position.h = 40;
        newEffect->handleIteration = effectIterationHandlerAirExplosion;
        break;
    case 3: // Efekat eksplozije na zemlji
        newEffect->position.w = newEffect->position.h = 45;
        newEffect->handleIteration = effectIterationHandlerLandExplosion;
        break;
    case 4: // rupa na zamlji
        newEffect->position.w = newEffect->position.h = 45;
        newEffect->handleIteration = effectIterationHandlerHole;
        break;
    case 5: // pad obicnog aviona
        newEffect->position.w = newEffect->position.h = 55;
        newEffect->handleIteration = effectIterationHandlerFallingPlane;
        break;
    case 6: // pad stuke
        newEffect->position.w = newEffect->position.h = 65;
        newEffect->handleIteration = effectIterationHandlerFallingPlane;
        break;
    case 7: // pad bosa 1
        newEffect->position.w = newEffect->position.h = 110;
        newEffect->handleIteration = effectIterationHandlerFallingPlane;
        break;
    case 8: // pad kamikaze
        newEffect->position.w = newEffect->position.h = 55;
        newEffect->handleIteration = effectIterationHandlerFallingPlane;
        break;
    case 9: // pad bosa 2
        newEffect->position.w = newEffect->position.h = 70;
        newEffect->handleIteration = effectIterationHandlerFallingPlane;
        break;
    case 10: // Efekat igracevog stita
        newEffect->position.h = newEffect->position.w = 40;
        newEffect->handleIteration = effectIterationHandlerPowerUp;
        break;
    /*case 11: // Efekat brzine
        newEffect->position.h = newEffect->position.w = 40;
        newEffect->handleIteration = effectIterationHandlerPowerUp;
        break;*/
    }
    newEffect->x_pos = x - newEffect->position.w/2;
    newEffect->y_pos = y - newEffect->position.h/2;
    newEffect->position.x = round(newEffect->x_pos);
    newEffect->position.y = round(newEffect->y_pos);
    newEffect->id = type;
    newEffect->counter = 0;
}
/**
* Funkcija za inicijalizaciju strukture powerUp-a i njeno dodavanje u listu efekata
* - vrše se inicijalna podešavanja strukture powerUp-a, resetovanje brojača i setovanja parametara za iscrtavanje
* @param    x   X koordinata mesta na koje treba postaviti powerUp pri inicijalizaciji
* @param    y    Y koordinata mesta na koje treba postaviti powerUp pri inicijalizaciji
* @param    type    Identifikacioni broj tipa powerUp-a (1:štit 2:brzina)
*/
void initPowerUp(double x, double y, int type)
{
    powerUpListNodePtr newPowerUpNode = malloc(sizeof(struct powerUpListNodeStruct));
    powerUpPtr newPowerUp = newPowerUpNode->powerUp = malloc(sizeof(struct powerUpStruct));
    newPowerUpNode->next = game->powerUps;
    newPowerUpNode->prev = NULL;
    if(game->powerUps != NULL)
        game->powerUps->prev =newPowerUpNode;
    game->powerUps = newPowerUpNode;
    newPowerUp->position.h = newPowerUp->position.w = 30;
    newPowerUp->handleIteration = powerUpIterationHandler;
    newPowerUp->x_pos = x - newPowerUp->position.w/2;
    newPowerUp->y_pos = y - newPowerUp->position.h/2;
    newPowerUp->position.x = round(newPowerUp->x_pos);
    newPowerUp->position.y = round(newPowerUp->y_pos);
    newPowerUp->id = type;
    newPowerUp->counter = 0;
}
/**
* Funkcija za inicijalizaciju matrice nivoa nulama
*/
void initLevelMatrix()
{
    int i,j;
    for (i=0; i<BACKGROUND_GRID_Y;i++)
        for (j=0; j<BACKGROUND_GRID_X;j++)
            game->level_matrix[i][j]=0;
}

/**
* Funkcija za snimanje trenutnog stanja tabele najboljih rezultata u fajl sacuvan u strukturi igre
*/
void saveHighScore()
{
    FILE *file = fopen(game->HSFileName, "wb");
    HSFileMemberPtr HSentry;
    int i;
    if (!file) return;
    HSentry = malloc(sizeof(struct HSFileMemberStruct));
    for (i=0; i<10; i++)
    {
        strcpy(HSentry->name, game->HSNames[i]);
        HSentry->score = game->HSScores[i];
        fwrite(HSentry, sizeof(struct HSFileMemberStruct), 1, file);
    }
    free(HSentry);
    fclose(file);
}
