#include "handlers.h"

 /**
* Funkcija koja omogucava unos imena igraca prilikom upisa u listu najboljih rezultata (slicno unosenju imena custom levela
* @param    rang    Celobrojna vrednost koja predstavlja trenutnu poziciju na koju treba da se upisu poeni igraca
*/
static void getPlayerName(int rang)
{
    int running=1, charCo=0;
    char tmp[256];
    SDL_Event event;
    strcpy(game->HSNames[rang], "_");
    sprintf(tmp, "%2d.  %10d: %s", rang+1, game->HSScores[rang], game->HSNames[rang]);
    editText(&texts[rang+4], tmp);
    while (running)
    {
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_KEYDOWN)
            {
                if ((event.key.keysym.sym >= SDLK_a && event.key.keysym.sym <= SDLK_z) ||
                         (event.key.keysym.sym >= SDLK_0 && event.key.keysym.sym <= SDLK_9))
                {
                    if (charCo < 50)
                    {
                        game->HSNames[rang][charCo++] = event.key.keysym.sym;
                        game->HSNames[rang][charCo] = 0;
                        sprintf(tmp, "%2d.  %10d: %s", rang+1, game->HSScores[rang], game->HSNames[rang]);
                        editText(&texts[rang+4], tmp);
                    }
                }
                else if (event.key.keysym.sym == SDLK_BACKSPACE)
                {
                    if (charCo > 0)
                    {
                        game->HSNames[rang][--charCo] = 0;
                        sprintf(tmp, "%2d.  %10d: %s", rang+1, game->HSScores[rang], game->HSNames[rang]);
                        editText(&texts[rang+4], tmp);
                    }
                }
                else if (event.key.keysym.sym == SDLK_RETURN && charCo > 0) running = 0;
            }
        }
        renderGame();
    }
}

/**
* Funkcija koja proverava da li ima neprijateljskih aviona
* - vraca 1 u slucaju da postoji makar jedan neprijatelj koji nije meta, a u suprotnom vraca 0
*/
static int enemyPlanes()
{
    enemyListNodePtr curr = game->enemies;
    while (curr)
    {
        if (curr->enemy->id < ENEMY_PLANE_TYPES)return 1;
        curr = curr->next;
    }
    return 0;
}

/**
* Funkcija koja radi update stanja igre u svakom frejmu (poziva hendlere za sve objekte u igrici, update-uje gui, spawnuje powerup, enemy-je, ispisuje HS ako je ispunjen uslov kraja igre)
* - u zavisnosti od podesene tezine stvaranje neprijatelja je cesce/redje
* - proverava trenutnu pozadinu kako bi se mete stvarale na razlicitim mestima u zavisnosti od pozadine (npr. na mapi sa vodom na vodi ce se stvoriti brod a na ostrvu tenk)
* - u slucaju unosenja odgovarajuće komande vraca vrednost 0 kako bi se igra pauzirala
*/
int gameItrationHandlerDefault()
{
    int i, j, nextHS;
    int spawn_frame_normal = game->difficulty == 1 ? 300 : game->difficulty == 2 ? 160 : 100;
    int spawn_frame_formation = game->difficulty == 1 ? 1000 : game->difficulty == 2 ? 500 : 300;
    int spawn_frame_boss = game->difficulty == 1 ? 2000 : game->difficulty == 2 ? 1500 : 800;
    char display_text[255], tmp[250], HStext[256];
    static int lastDrawnScore = -1, lastDrawnHealthP1 = -1, lastDrawnHealthP2 = -1, lastDrawnHS = -2;
    game->frames++;
    game->framesFromCont++;

    if (game->frames == 1) initPlayer();

    for (nextHS=0; nextHS < 10 && game->score < game->HSScores[nextHS]; nextHS++);
    nextHS--;
    if (nextHS == -1) sprintf(HStext, "New High Score!");
    else if (nextHS < 9) sprintf(HStext, "Next high score:  %2d.  %d", nextHS+1, game->HSScores[nextHS]);
    else sprintf(HStext, "Lowest high score: %d", game->HSScores[9]);
    if (lastDrawnScore != game->score ||
        lastDrawnHS != nextHS ||
        (game->players && game->players->player->health != lastDrawnHealthP1) ||
        (game->players && game->players->next && game->players->next->player->health != lastDrawnHealthP2))
    {
        lastDrawnScore = game->score;
        display_text[0] = 0;
        if (game->players)
        {
            sprintf(display_text, "%s   Score: %-10d Player1 health: %-5d    %-30s %s",
                    GAME_NAME, game->score, game->players->player->health, HStext,
                    game->players->player->handleIteration==playerIterationHandlerDemo?"Demo":
                        game->difficulty==1?"Difficulty: Easy":
                        game->difficulty==2?"Difficulty: Medium":"Difficulty: Hard");
            if (game->players->next)
                sprintf(display_text, " Player2 health: %5d", game->players->next->player->health);
        }
        editText(&texts[0], display_text);
    }

    if (game->framesFromCont == 1)
    {
        char counterText[] = "                    ";
        for (i=0; i<20; i++)
        {
            renderGame();
            SDL_Delay(50);
            counterText[i] = '#';
            editText(&texts[1], counterText);
        }
        editText(&texts[1], "");
    }
    //EnemySpawn
    if (game->game_mode!=1 || game->campaign_row<31)
    {
        if(!game->final_boss_active && game->game_mode == 1 && game->campaign_row==30)
        {
            game->final_boss_active = 1;
            initEnemy(640, -50, 4, 0);
        }
        else if(!game->final_boss_active && (game->game_mode !=1 || (game->game_mode ==1 && game->campaign_row!=30)))
        {
            if (game->frames % spawn_frame_normal == 0 && game->enemySpawnCounter<2)
            {
                int a=game->enemySpawnCounter %2;
                if(!game->boss_active/* && game->frames < 10000*/)
                {
                    initEnemy(-100,50,(game->frames % 480 == 0)*3*(1-a),0);
                    initEnemy(1380,50,(game->frames % 480 == 0)*3*a,1);
                }

                if(!game->boss_active && game->frames > 2000 /*&& game->frames <10000*/)
                {
                    initEnemy(550,-50,(game->frames % 480 == 0)*3*(1-a),2);
                    initEnemy(730,-50,(game->frames % 480 == 0)*3*a,3);
                }
            }
            if(!game->boss_active && game->frames % spawn_frame_boss == 0 )
            {
                game->boss_active = 1;
                initEnemy(640,-20,2,game->frames/spawn_frame_boss);
            }

            if(game->frames % spawn_frame_formation == 0)
            {
                int a = game->enemySpawnCounter % 3 -1;
                if(game->frames%(spawn_frame_formation*2)==0)
                {
                    initEnemy(440 + a*100,-60,1,4);
                    initEnemy(540 + a*100,-40,1,4);
                    initEnemy(640 + a*100,-20,1,4);
                    initEnemy(740 + a*100,-40,1,4);
                    initEnemy(840 + a*100,-60,1,4);
                }
                else if(game->frames % (spawn_frame_formation*3) == 0)
                {
                    initEnemy(140 + a*100,-60,1,4);
                    initEnemy(390 + a*100,-40,1,4);
                    initEnemy(640 + a*100,-20,1,4);
                    initEnemy(890 + a*100,-40,1,4);
                    initEnemy(1040+ a*100,-60,1,4);
                }
                else
                {
                    initEnemy(340 + a*100,-60,1,4);
                    initEnemy(490 + a*100,-40,1,4);
                    initEnemy(640 + a*100,-20,1,4);
                    initEnemy(790 + a*100,-40,1,4);
                    initEnemy(940 + a*100,-60,1,4);
                }

            }
        }

        //EnemySpawn

        //PowerUpSpawn
        if(game->frames % 1000 == 0)
            initPowerUp(rand()%WINDOWW,-10,rand()%2+1);
        //PowerUpSpawn
        if(game->background_offset == 0)
        {
            for (i=0; i<BACKGROUND_GRID_Y; i++)
            {
                switch (game->level_matrix[0][i])
                {
                case 0:
                    if (rand() % 9 == 0) initEnemy(i*WINDOWW/BACKGROUND_GRID_X+120+rand()%100-50, -WINDOWH/(BACKGROUND_GRID_Y-1)+rand()%100-50, 5, 1);
                    break;
                case 1: case 2:
                    if(rand() % 2 == 0) initEnemy(i*WINDOWW/BACKGROUND_GRID_X+120+rand()%100-50, -WINDOWH/(BACKGROUND_GRID_Y-1)+rand()%100-50, 5, 0);
                    break;
                case 3:
                    if(rand() % 10 == 0) initEnemy(i*WINDOWW/BACKGROUND_GRID_X+120+rand()%100-50, -WINDOWH/(BACKGROUND_GRID_Y-1)+rand()%100-50, 5, 0);
                    break;
                case 5: case 6: case 8:
                    if(rand() % 9 == 0) initEnemy(i*WINDOWW/BACKGROUND_GRID_X+120+rand()%100-50, -WINDOWH/(BACKGROUND_GRID_Y-1)+rand()%100-50, 5, 0);
                    break;
                }
            }
        }
    }

    if (!game->players || (game->game_mode == 1 && game->campaign_row > 30 && !enemyPlanes()))
    {
        if (game->players && (game->campaign_level_ind == lastCampaignLevel - 1))
        {
            FILE *out = fopen("res/saves/lastCampaignLevel.sav", "wb");
            lastCampaignLevel++;
            if (lastCampaignLevel == 4) lastCampaignLevel--;
            if (out)
            {
                maxLevelSavePtr maxLevelSave = malloc(sizeof(struct maxLevelSaveStruct));
                maxLevelSave->level = lastCampaignLevel;
                fwrite(maxLevelSave, sizeof(struct maxLevelSaveStruct), 1, out);
                free(maxLevelSave);
            }
            SDL_QueryTexture(levelClearTexture, NULL, NULL, &(gameOverRect.w), &(gameOverRect.h));
        }
        else SDL_QueryTexture(gameOverTexture, NULL, NULL, &(gameOverRect.w), &(gameOverRect.h));
        gameOverRect.x = (WINDOWW - gameOverRect.w) / 8;
        gameOverRect.y = (WINDOWH - gameOverRect.h) / 2;
        HSBackgroundRect.h = 370;
        HSBackgroundRect.w = 300;
        HSBackgroundRect.x = 720;
        HSBackgroundRect.y = 180;
        texts[3]->show = 1;
        for (i=4; i<14; i++)
        {
            sprintf(tmp, "%2d.  %10d  %s", i-3, game->HSScores[i-4], game->HSNames[i-4]);
            editText(&texts[i], tmp);
            texts[i]->show = 1;
        }
        renderGame();
        for (i=0; i<10; i++) if (game->HSScores[i] < game->score) break;
        for (j=9; j>i; j--) strcpy(game->HSNames[j], game->HSNames[j-1]), game->HSScores[j] = game->HSScores[j-1];
        if ((i < 10) && ((game->game_mode != 1) || game->players))
        {
            game->HSScores[i] = game->score;
            for (j=4; j<14; j++)
            {
                sprintf(tmp, "%2d.  %10d  %s", j-3, game->HSScores[j-4], game->HSNames[j-4]);
                editText(&texts[j], tmp);
                texts[j]->show = 1;
            }
            getPlayerName(i);
            saveHighScore();
        }
        else
        {
            SDL_Event event;
            int running = 1;
            while (running)
            {
                while (SDL_PollEvent(&event)) if (event.type == SDL_KEYDOWN) running = 0;
                SDL_Delay(10);
            }
        }
        freeGame();
        return 0;
    }
    if (events[SDLK_p] || events[SDLK_ESCAPE])
        return 0;
    return 1;
}

/**
* Funkcija koja na osnovu komandi sa tastature radi update pozicije igraca, stvara metkove ako su odgovarajuce komande unete i vodi racuna o trenutno aktivnim power-upovima
* @param    playerNode    Element liste igraca koji sadrzi podatke o trenutnom igracu
*/
int playerIterationHandlerDefault(playerListNodePtr playerNode)
{
    double dx=playerNode->player->speedActive ? 9 : 6, dy=playerNode->player->speedActive ? 6 : 4;
    playerPtr player = playerNode->player;
    player->counter++;
    if (player->health <= 0)
    {
        freePlayerNode(playerNode);
        return 0;
    }
    if (player->bulletCoolDown > 0) player->bulletCoolDown--;
    if (player->bombCoolDown > 0) player->bombCoolDown--;
    if ((events[SDLK_a] && events[SDLK_s]) || (events[SDLK_s] && events[SDLK_d]) ||
        (events[SDLK_d] && events[SDLK_w]) || (events[SDLK_w] && events[SDLK_a]))
    {
        dx /= sqrt(2);
        dy /= sqrt(2);
    }
    if (events[SDLK_SPACE] && player->bulletCoolDown == 0) // metak
    {
        player->bulletCoolDown = 10;
        initBullet(player->x_pos + player->position.w/2 -10, player->y_pos, 1, 1);
        initBullet(player->x_pos + player->position.w/2 +17, player->y_pos, 1, 1);
        if (audio) Mix_PlayChannel(-1, fire, 0);
    }
    if (events[SDLK_b] && player->bombCoolDown == 0) // bomba
    {
        player->bombCoolDown = 30;
        initBullet(player->x_pos + player->position.w/2 - 5, player->y_pos, 1, 2);
    }
    player->movement=0;
    if (events[SDLK_a]) player->x_pos -= dx, player->movement=-1;
    if (events[SDLK_s]) player->y_pos += dy;
    if (events[SDLK_d]) player->x_pos += dx, player->movement=+1;
    if (events[SDLK_w]) player->y_pos -= dy;
    if (player->x_pos < 0) player->x_pos = 0;
    if (player->x_pos > WINDOWW - player->position.w) player->x_pos = WINDOWW - player->position.w;
    if (player->y_pos - topStripRect.h < 0) player->y_pos = topStripRect.h;
    if (player->y_pos > WINDOWH - bottomStripRect.h - player->position.h) player->y_pos = WINDOWH - bottomStripRect.h - player->position.h;
    player->position.x = round(player->x_pos);
    player->position.y = round(player->y_pos);

    if (player->counter % 8 == 0)
    {
        initEffect(player->x_pos + player->position.w/2, player->y_pos+30, 1);
    }

    if(player->shieldActive > 0)
        player->shieldActive--;
    if(player->speedActive > 0)
        player->speedActive--;
    return 1;
}

/**
* Funkcija koja radi update igraca za demo igrice, sa predefinisamon vestackom inteligencijom, a poziva se u svakom frejmu
* - prvi prioritet: pozicioniranje ka meti
* - drugi prioritet: pozicioniranje prema powerUp-ovima
* - treci prioritet: unistavanje najblizeg neprijatelja
* @param    playerNode    Element liste igraca koji sadrzi podatke o trenutnom igracu
*/
int playerIterationHandlerDemo(playerListNodePtr playerNode)
{
    short bomb_target=0,pick_up_powerup=0;
    int dx=0;
    int dx_moving=playerNode->player->speedActive ? 9 : 6, dy=playerNode->player->speedActive ? 6 : 4;
    playerPtr player = playerNode->player;
    enemyListNodePtr pomEnemy = game->enemies,minEnemy=NULL;

    player->counter++;
    if (player->health <= 0)
    {
        freePlayerNode(playerNode);
        return 0;
    }
    if (player->bulletCoolDown > 0) player->bulletCoolDown--;
    if (player->bombCoolDown > 0) player->bombCoolDown--;

    if (player->bulletCoolDown == 0) // metak
    {
        player->bulletCoolDown = 10;
        initBullet(player->x_pos + player->position.w/2 -10, player->y_pos, 1, 1);
        initBullet(player->x_pos + player->position.w/2 +17, player->y_pos, 1, 1);
        if (audio) Mix_PlayChannel(-1, fire, 0);
    }
    while(pomEnemy)
    {
        int y_min=10000;
        if(pomEnemy->enemy->id ==5)
        {
            if((abs(playerNode->player->y_pos - pomEnemy->enemy->y_pos)< y_min) && pomEnemy->enemy->x_pos < WINDOWW)
            {
                bomb_target=1;
                y_min = abs(playerNode->player->y_pos - pomEnemy->enemy->y_pos);
                minEnemy = pomEnemy;
            }
        }
        pomEnemy = pomEnemy->next;
    }
    pomEnemy = minEnemy;
    if(!bomb_target && game->enemies!=NULL)
    {
        int y_min;
        enemyListNodePtr minEnemy;
        pomEnemy = game->enemies;
        minEnemy = pomEnemy;
        y_min=abs(playerNode->player->y_pos - pomEnemy->enemy->y_pos);
        while(pomEnemy)
        {
            if(abs(playerNode->player->y_pos - pomEnemy->enemy->y_pos)< y_min)
            {
                y_min = abs(playerNode->player->y_pos - pomEnemy->enemy->y_pos);
                minEnemy = pomEnemy;
            }
            pomEnemy=pomEnemy->next;
        }
        pomEnemy = minEnemy;
    }

    if(bomb_target && (playerNode->player->y_pos - pomEnemy->enemy->y_pos)<250 && (playerNode->player->y_pos - pomEnemy->enemy->y_pos)>0 && player->bombCoolDown == 0)
    {
        player->bombCoolDown = 30;
        initBullet(player->x_pos + player->position.w/2 - 5, player->y_pos, 1, 2);
    }

    if(!bomb_target && game->powerUps!=NULL)
        pick_up_powerup=1;

    if(!bomb_target && pick_up_powerup)
    {
        if(player->x_pos > game->powerUps->powerUp->x_pos) dx=-dx_moving,playerNode->player->movement=-1;
        else if(player->x_pos < game->powerUps->powerUp->x_pos) dx=dx_moving,playerNode->player->movement=1;
        else dx=0,playerNode->player->movement=0;
    }
    else if(pomEnemy!= NULL && abs(pomEnemy->enemy->x_pos - playerNode->player->x_pos)>5)
    {
        if(player->x_pos > pomEnemy->enemy->x_pos) dx=-dx_moving,playerNode->player->movement=-1;
        else if(player->x_pos < pomEnemy->enemy->x_pos) dx=dx_moving,playerNode->player->movement=1;
        else dx=0,playerNode->player->movement=0;
    }

    player->x_pos += dx;
    if (player->x_pos < 0) player->x_pos = 0;
    if (player->x_pos > WINDOWW - player->position.w) player->x_pos = WINDOWW - player->position.w;
    if (player->y_pos - topStripRect.h < 0) player->y_pos = topStripRect.h;
    if (player->y_pos > WINDOWH - bottomStripRect.h - player->position.h) player->y_pos = WINDOWH - bottomStripRect.h - player->position.h;
    player->position.x = round(player->x_pos);
    player->position.y = round(player->y_pos);

    if(player->shieldActive > 0)
        player->shieldActive--;
    if(player->speedActive > 0)
        player->speedActive--;
    return 1;
}

/**
* Funkcija koja radi update pojedinacnog default neprijatelja, a poziva se u svakom frejmu. U default neprijatelje spadaju obicni neprijatelji i neprijatelji u formaciji
* - obicni neprijatelji se krecu po 4 putanje u zavisnosti od njihovog path_id-a
* - neprijatelji u formaciji se krecu po zajednickoj putanji i path_id im je 4
* @param    enemyNode    Element liste neprijatelja koji sadrzi podatke o trenutnom neprijatelju
*/
int enemyIterationHandlerDefault(enemyListNodePtr enemyNode)
{
    double dx=0, dy=0;
    int cd_frame = game->difficulty == 1 ? 120 : game->difficulty == 2 ? 70 : 40;
    enemyPtr enemy = enemyNode->enemy;
    enemy->counter++;
    if (enemy->coolDown > 0) enemy->coolDown--;
    if(enemy->coolDown ==0)
    {
        initBullet(enemy->x_pos + enemy->position.w/2+5, enemy->y_pos+enemy->position.h-5, 0, 1);
        enemy->coolDown=cd_frame;
    }

    if(enemy->path_id == 0)
    {
        if (enemy->counter < 150) dx = 4,dy=1, enemy->texture_slot=enemy->id*3+2;
        else if (enemy->counter < 250) dy = 4,enemy->texture_slot=enemy->id*3+0;
        else if (enemy->counter < 350) dx = -4,dy=-1,enemy->texture_slot=enemy->id*3+1;
        else if (enemy->counter < 400) dy = -4,enemy->texture_slot=enemy->id*3+0;
        else if (enemy->counter < 450) dy = -4,dx=-2,enemy->texture_slot=enemy->id*3+1;
    }
    else if (enemy->path_id == 1)
    {
        if (enemy->counter < 150) dx = -4,dy=1,enemy->texture_slot=enemy->id*3+1;
        else if (enemy->counter < 250) dy = 4,enemy->texture_slot=enemy->id*3+0;
        else if (enemy->counter < 350) dx = 4,dy=-1,enemy->texture_slot=enemy->id*3+2;
        else if (enemy->counter < 400) dy = -4,enemy->texture_slot=enemy->id*3+0;
        else if (enemy->counter < 450) dy = -5,enemy->texture_slot=enemy->id*3+2;
    }
    else if (enemy->path_id == 2)
    {
        if (enemy->counter < 50) dy = 4,enemy->texture_slot=enemy->id*3+0;
        else if (enemy->counter < 150) dx = 4,dy=-1,enemy->texture_slot=enemy->id*3+2;
        else if (enemy->counter < 200) dy = 4,enemy->texture_slot=enemy->id*3+0;
        else if (enemy->counter < 400) dx = -4,dy=1,enemy->texture_slot=enemy->id*3+1;
        else if (enemy->counter < 450) dy = -5,dx=4,enemy->texture_slot=enemy->id*3+2;
    }
    else if (enemy->path_id == 3)
    {
        if (enemy->counter < 50) dy = 4,enemy->texture_slot=enemy->id*3+0;
        else if (enemy->counter < 150) dx = -4,dy=-1,enemy->texture_slot=enemy->id*3+1;
        else if (enemy->counter < 200) dy = 4,enemy->texture_slot=enemy->id*3+0;
        else if (enemy->counter < 400) dx = 4,dy=1,enemy->texture_slot=enemy->id*3+2;
        else if (enemy->counter < 450) dy = -5,dx=-4,enemy->texture_slot=enemy->id*3+1;
    }
    else if(enemy->path_id == 4)
    {
        if (enemy->counter < 50) dy = 2,dx=1,enemy->texture_slot=enemy->id*3+1;
        else if (enemy->counter < 150) dx = -2,enemy->texture_slot=enemy->id*3+1;
        else if (enemy->counter < 250) dx = -2,enemy->texture_slot=enemy->id*3+1;
        else if (enemy->counter < 350) dx = 2,dy=1,enemy->texture_slot=enemy->id*3+2;
        else if (enemy->counter < 450) dx = 2,dy=1,enemy->texture_slot=enemy->id*3+2;
    }

    enemy->x_pos += dx;
    enemy->y_pos += dy;
    enemy->position.x = round(enemy->x_pos);
    enemy->position.y = round(enemy->y_pos);

    if (enemy->counter == 450) enemy->counter = 0;
    if (enemy->counter > 400 && (enemy->x_pos<0 || enemy->y_pos< 0 || enemy->x_pos > WINDOWW || enemy->y_pos > WINDOWH))
        freeEnemyNode(enemyNode);
    return 1;
}

/**
* Funkcija koja radi update pojedinacnog follower neprijatelja (koji prati igraca i puca u njega), a poziva se u svakom frejmu
* - follower neprijatelj ima predefinisanu trajektoriju po y osi, a po x osi prati igraca i puca
* @param    enemyNode    Element liste neprijatelja koji sadrzi podatke o trenutnom neprijatelju
*/
int enemyIterationHandlerFollower(enemyListNodePtr enemyNode)
{
    double dx=0, dy=0;
    double playerx=0;
    int cd_frame = game->difficulty == 1 ? 60 : game->difficulty == 2 ? 35 : 20;
    if (game->players) playerx = game->players->player->x_pos;

    enemyPtr enemy = enemyNode->enemy;
    enemy->counter++;
    if (enemy->coolDown > 0) enemy->coolDown--;
    if(enemy->coolDown ==0)
    {
        initBullet(enemy->x_pos + enemy->position.w/2-12, enemy->y_pos+10, 0, 1);
        initBullet(enemy->x_pos + enemy->position.w/2+12, enemy->y_pos+10, 0, 1);
        enemy->coolDown=cd_frame;
    }

    if (enemy->counter < 150) dy=3;
    else if (enemy->counter < 300) dy=-2;
    else if (enemy->counter < 375) dy = 2;
    else if (enemy->counter < 450) dy = -2;

    if(abs(enemy->x_pos - playerx)>5)
    {
        if(enemy->x_pos>playerx) dx=-3,enemy->texture_slot=enemy->id*3+1;
        else if(enemy->x_pos<playerx) dx=3,enemy->texture_slot=enemy->id*3+2;
        else dx=0,enemy->texture_slot=enemy->id*3+0;
    }

    enemy->x_pos += dx;
    enemy->y_pos += dy;
    enemy->position.x = round(enemy->x_pos);
    enemy->position.y = round(enemy->y_pos);

    if (enemy->counter == 450) enemy->counter = 0;
    return 1;
}

/**
* Funkcija koja radi update pojedinacnog kamikaza neprijatelja (koji pokusava da udari u igraca), a poziva se u svakom frejmu
* -U zavisnosti od trenutne pozicije igraca na x i y osi, neprijatelj se pomera direktno ka igracu bez pucanja
* @param    enemyNode    Element liste neprijatelja koji sadrzi podatke o trenutnom neprijatelju
*/
int enemyIterationHandlerKamikaze(enemyListNodePtr enemyNode)
{
    double dx=0, dy=0;
    int speedx = game->difficulty == 1 ? 1.5 : game->difficulty == 2 ? 1.5 : 2.25;
    double playerx=0;
    double playery=0;
    if (game->players) playerx = game->players->player->x_pos;
    if (game->players) playery = game->players->player->y_pos;

    enemyPtr enemy = enemyNode->enemy;
    enemy->counter++;
    if(abs(enemy->x_pos - playerx)>5)
    {
        if(enemy->x_pos>playerx) dx=-3,enemy->texture_slot=enemy->id*3+1;
        else if(enemy->x_pos<playerx) dx=3,enemy->texture_slot=enemy->id*3+2;
        else dx=0,enemy->texture_slot=enemy->id*3+0;
    }
    if(abs(enemy->y_pos - playery)>2)
    {
        if(enemy->y_pos>playery) dy=-speedx;
        else if(enemy->y_pos<playery) dy=speedx;
        else dy=0;
    }
    enemy->x_pos += dx;
    enemy->y_pos += dy;
    enemy->position.x = round(enemy->x_pos);
    enemy->position.y = round(enemy->y_pos);

    if (enemy->counter == 450) enemy->counter = 0;
    return 1;
}

/**
* Funkcija koja radi update pojedinacnog boss neprijatelja, a poziva se u svakom frejmu
* - boss ima predefinisanu trajektoriju po y osi, a po x osi prati igraca
* - boss ima dve faze, normalnu u kojoj puca na svakih 75/50/25 frejmova, i hyper fazu u kojoj puca na svakih 10 frejmova i koja traje nekoliko sekundi (cooldown pucanja zavisi od tezine igre)
* @param    enemyNode    Element liste neprijatelja koji sadrzi podatke o trenutnom neprijatelju
*/
int enemyIterationHandlerBoss(enemyListNodePtr enemyNode)
{
    double dx=0, dy=0;
    double playerx=0;
    int cd_frame_shooting = game->difficulty == 1 ? 75 : game->difficulty == 2 ? 50 : 25;
    int mul=2;
    if (game->players) playerx = game->players->player->x_pos;
    enemyPtr enemy = enemyNode->enemy;
    enemy->counter++;
    if (enemy->coolDown > 0) enemy->coolDown--;
    if(enemy->coolDown <= 200)
        mul=4;
    if(enemy->coolDown %cd_frame_shooting == 0 || (mul==4 && enemy->coolDown %10 == 0))
    {
        initBullet(enemy->x_pos + enemy->position.w/2-70, enemy->y_pos+160, 0, 1);
        initBullet(enemy->x_pos + enemy->position.w/2, enemy->y_pos+160, 0, 1);
        initBullet(enemy->x_pos + enemy->position.w/2+70, enemy->y_pos+160, 0, 1);
    }

    if(enemy->coolDown == 0)
    {
        enemy->coolDown=500;
        mul=1;
    }

    if (enemy->counter < 150) dy=1.5;
    else if (enemy->counter < 300) dy=-1;
    else if (enemy->counter < 375) dy = 1;
    else if (enemy->counter < 450) dy = -2;

    if(abs(enemy->x_pos - playerx)>5)
    {
        if(enemy->x_pos>playerx) dx=-1*mul,enemy->texture_slot=enemy->id*3+1;
        else if(enemy->x_pos<playerx) dx=1*mul,enemy->texture_slot=enemy->id*3+2;
        else dx=0,enemy->texture_slot=enemy->id*3+0;
    }

    enemy->x_pos += dx;
    enemy->y_pos += dy;
    enemy->position.x = round(enemy->x_pos);
    enemy->position.y = round(enemy->y_pos);

    if (enemy->counter == 450) enemy->counter = 0;
    return 1;
}

/**
* Funkcija koja radi update pojedinacne mete na zemlji/u vodi, a poziva se u svakom frejmu
* - meta je fiksirana po x osi, a po y osi se pomera brzinom pomeranja y ose i tako stvara iluziju kretanja sa pozadinom
* - funkcija proverava da li je trenutna meta izasla sa ekrana (y koordinata joj je veca od visine prozora za igru)
* @param    enemyNode    Element liste neprijatelja koji sadrzi podatke o trenutnoj meti
*/
int enemyIterationHandlerGroundTarget(enemyListNodePtr enemyNode)
{
    enemyPtr enemy = enemyNode->enemy;

    if (game->game_mode!=1 || game->campaign_row < 31)
        enemy->y_pos += BACKGROUND_SPEED;
    enemy->position.y = round(enemy->y_pos);
    enemy->texture_slot=enemy->id*3+enemy->path_id;

    if (enemy->y_pos >= WINDOWH) freeEnemyNode(enemyNode);
    return 1;
}

/**
* Osnovno hendlovanje pozicije metka u svakom frejmu
* - metak se pomera ka gore ili dole u zavisnosti od objekta koji ga je ispalio
* - u slucaju da metak ispadne sa ekrana, memorija se oslobadja
* @param    bulletNode    Element liste metkova koji sadrzi podatke o trenutnom metku
*/
int bulletIterationHandlerBullet(bulletListNodePtr bulletNode)
{
    if (bulletNode->bullet->y_pos < topStripRect.h - bulletNode->bullet->position.h ||
        bulletNode->bullet->y_pos > WINDOWH - bottomStripRect.h ||
        bulletNode->bullet->x_pos < -bulletNode->bullet->position.w ||
        bulletNode->bullet->x_pos > WINDOWW) freeBulletNode(bulletNode);
    else
    {
        if(bulletNode->bullet->isPlayerOwned)
            bulletNode->bullet->y_pos-=10;
        else
            bulletNode->bullet->y_pos+=7;
        bulletNode->bullet->position.y = round(bulletNode->bullet->y_pos);
    }
    return 1;
}

/**
* Osnovno hendlovanje pozicije bombe u svakom frejmu
* - bomba se sama unistava posle nekoliko frejmove kako bi simulirala efekat "padanja" na zemlju
* @param    bulletNode    Element liste metkova koji sadrzi podatke o trenutnoj bombi
*/
int bulletIterationHandlerBomb(bulletListNodePtr bulletNode)
{
    bulletPtr bullet = bulletNode->bullet;
    bullet->y_pos -= bullet->counter / 20;
    bullet->position.y = round(bullet->y_pos);
    if (bullet->counter % 15 == 0)
    {
        bullet->position.w -= 2 * (60 - bullet->counter) / 20;
        bullet->position.h -= 2 * (60 - bullet->counter) / 10;
        bullet->position.y += 1 * (60 - bullet->counter) / 20;
        bullet->position.x += 1 * (60 - bullet->counter) / 20;
    }
    bullet->counter--;
    if (bullet->counter < 0){
        initEffect(bullet->x_pos + 10, bullet->y_pos - 20, 3);
        if (audio)
        {
            Mix_VolumeChunk(explosionSound, 35);
            Mix_PlayChannel(-1, explosionSound, 0);
        }
        freeBulletNode(bulletNode);
    }
    return 1;
}
/**
* Osnovno hendlovanje pozicije powerupa u svakom frejmu
* - powerUp se pomera ka dole brzinom pomeranja pozadine kako bi se simulirao efekat pracenja pozadine
* - u slucaju da y koordinata powerUp-a bude veca od visine prozora igre, powerUp se brise
* @param    powerUpNode    Element liste powerUp-ova koji sadrzi podatke o trenutnom powerUp-u
*/
int powerUpIterationHandler(powerUpListNodePtr powerUpNode)
{
    powerUpPtr powerUp = powerUpNode->powerUp;
    if (game->game_mode != 1 || game->campaign_row < 31)
        powerUp->y_pos += BACKGROUND_SPEED, powerUp->position.y = round(powerUp->y_pos);

    if (powerUp->y_pos >= WINDOWH) freePowerUpNode(powerUpNode);
    return 1;
}

/**
* Funkcija koja radi update pojedinacnog efekta dima iza aviona svakog frejma
* - efekat dima se smanjuje svaka cetiri frejma kako bi simulirao efekat "nestajanja"
* @param    effectNode    Element liste efekata koji sadrzi podatke o trenutnom efektu
*/
int effectIterationHandlerExhaust(effectListNodePtr effectNode)
{
    effectPtr effect = effectNode->effect;
    effect->counter++;
    if (effect->counter % 4 == 0)
    {
        effect->position.x += 2;
        effect->position.y += 2;
        effect->position.w -= 4;
        effect->position.h -= 4;
    }
    if (game->game_mode != 1 || game->campaign_row < 31)
        effect->position.y += 5;
    if (effect->counter == 20) freeEffectNode(effectNode);
    return 1;
}

/**
* Funkcija koja radi update pojedinacnog efekta eksplozije u vazduhu, u svakom frejmu
* - efekat eksplozije se smanjuje svaka tri frejma kako bi simulirao "nestanak"
* @param    effectNode    Element liste efekata koji sadrzi podatke o trenutnom efektu
*/
int effectIterationHandlerAirExplosion(effectListNodePtr effectNode)
{
    effectPtr effect = effectNode->effect;
    effect->counter++;
    if (effect->counter % 3 == 0)
    {
        effect->position.x += 2;
        effect->position.y += 2;
        effect->position.w -= 4;
        effect->position.h -= 4;
    }
    if (game->game_mode != 1 || game->campaign_row < 31)
        effect->position.y += 4;
    if (effect->counter == 40) freeEffectNode(effectNode);
    return 1;
}

/**
* Funkcija koja radi update pojedinacnog efekta eksplozije na zemlji, u svakom frejmu
* - efekat eksplozije se smanjuje svaka tri frejma kako bi simulirao "nestanak"
* @param    effectNode    Element liste efekata koji sadrzi podatke o trenutnom efektu
*/
int effectIterationHandlerLandExplosion(effectListNodePtr effectNode)
{
    effectPtr effect = effectNode->effect;
    effect->counter++;
    if (effect->counter % 3 == 0)
    {
        effect->position.x += 2;
        effect->position.y += 2;
        effect->position.w -= 4;
        effect->position.h -= 4;
    }
    if (game->game_mode != 1 || game->campaign_row < 31)
        effect->position.y += 2;
    if (effect->counter == 40) freeEffectNode(effectNode);
    return 1;
}

/**
* Funkcija koja radi update pojedinacnog efekta rupe na zemlji, u svakom frejmu
* - efekat rupe na zemlji se pomera po y osi brzinom pomeranja pozadine
* @param    effectNode    Element liste efekata koji sadrzi podatke o trenutnom efektu
*/
int effectIterationHandlerHole(effectListNodePtr effectNode)
{
    effectPtr effect = effectNode->effect;
    if (effect->counter % 3 == 0 && game->game_mode != 1 || game->campaign_row < 31)
        effect->position.y += BACKGROUND_SPEED;
    if (effect->position.y >WINDOWH) freeEffectNode(effectNode);
    return 1;
}

/**
* Funkcija koja radi update pojedinacnog efekta padanja aviona, u svakom frejmu
* - efekat padanja aviona se smanjuje u svakom frejmu kako bi se relano simuliralo rusenje aviona na zemlju/u vodu
* - efekat se pomera po y osi brzion pomreanja pozadine
* @param    effectNode    Element liste efekata koji sadrzi podatke o trenutnom efektu
*/
int effectIterationHandlerFallingPlane(effectListNodePtr effectNode)
{
    effectPtr effect = effectNode->effect;
    int koef = effect->position.w;
    effect->counter++;
    effect->position.y += BACKGROUND_SPEED+1;
    effect->position.x -= 1;

    effect->position.w -= (int)(2.0 * koef / 80);
    effect->position.h -= (int)(2.0 * koef / 80);
    effect->position.y += (int)(1.0 * koef / 80);
    effect->position.x += (int)(1.0 * koef / 80);
    if (effect->counter == 40)
    {
        initEffect(effect->position.x, effect->position.y, 3);
        freeEffectNode(effectNode);
    }
    return 1;
}

/**
* Funkcija koja radi update pojedinacnog efekta powerUp-a
* - efekat powerUp-a je vezan za igraca i pomera se zajedno sa igracem
* - ako je igrac unisten dok je efekat aktivan, efekat se takodje unistava
* @param    effectNode    Element liste efekata koji sadrzi podatke o trenutnom efektu
*/
int effectIterationHandlerPowerUp(effectListNodePtr effectNode)
{
    effectPtr effect = effectNode->effect;
    playerPtr player;
    if(game->players != NULL)
        player= game->players->player;
    else
        player = NULL;
    if(game->players==NULL || (effectNode->effect->id == 10 && player->shieldActive==0 ) || (effectNode->effect->id == 11 && player->speedActive==0 ))
        freeEffectNode(effectNode);
    else
    {
        if(player!=NULL)
        {
            effect->position.x=player->position.x;
            effect->position.y=player->position.y;
            effect->position.w=player->position.w;
            effect->position.h=player->position.h;
        }
    }
    if (effect->counter == 20) freeEffectNode(effectNode);
    return 1;
}
