#include "collisions.h"
#define MIN(X, Y) (((X) < (Y)) ? (X) : (Y))


/**
* Funkcija za detekciju kolizije izmedju objekata na ekranu
* - igrač       - neprijatelj
* - igrač       - metak
* - neprijatelj - metak
* - igrač       - pojačanje
*/
void detectCollisions()
{
    enemyListNodePtr currEnemy = game->enemies, nextEnemy;
    playerListNodePtr currPlayer = game->players, nextPlayer;
    bulletListNodePtr currBullet = game->bullets, nextBullet;
    powerUpListNodePtr currPowerUp = game->powerUps,nextPowerUp;
    while(currPlayer)
    {
        nextPlayer = currPlayer->next;
        currEnemy = game->enemies;
        while (currEnemy)
        {
            nextEnemy = currEnemy->next;
            if(currEnemy->enemy->id < ENEMY_PLANE_TYPES && detectPlayerEnemyCollision(currPlayer->player, currEnemy->enemy))
            {
                initEffect(currEnemy->enemy->x_pos+15, currEnemy->enemy->y_pos+15, 2);
                if(currPlayer->player->shieldActive==0)
                {
                    if (currEnemy->enemy->id == 3) currPlayer->player->health -= 40;
                    else currPlayer->player->health -= 20;
                }
                game->score = (int)(0.97 * game->score);
                if(currEnemy->enemy->id == 2) // AKO JE BOSS
                    game->boss_active = 0;
                if (currEnemy->enemy->id < ENEMY_PLANE_TYPES)
                        initEffect(currEnemy->enemy->position.x + currEnemy->enemy->position.w/2,
                                   currEnemy->enemy->position.y + currEnemy->enemy->position.h/2,
                                   currEnemy->enemy->id+5);
                if(currEnemy->enemy->id != 4) freeEnemyNode(currEnemy);
                if (audio)
                {
                    Mix_VolumeChunk(explosionSound, 30);
                    Mix_PlayChannel(-1, explosionSound, 0);
                }
            }
            currEnemy = nextEnemy;
        }
        currPlayer = nextPlayer;
    }

    currPlayer = game->players;
    while(currPlayer)
    {
        nextPlayer = currPlayer->next;
        currBullet = game->bullets;
        while (currBullet)
        {
            nextBullet = currBullet->next;
            if(!currBullet->bullet->isPlayerOwned && detectBulletPlayerCollision(currBullet->bullet,currPlayer->player))
            {
                initEffect(currPlayer->player->x_pos+15, currPlayer->player->y_pos+15, 2);
                if(currPlayer->player->shieldActive==0)
                    currPlayer->player->health -= 10;
                freeBulletNode(currBullet);
                if (audio)
                {
                    Mix_VolumeChunk(explosionSound, 30);
                    Mix_PlayChannel(-1, explosionSound, 0);
                }
                break;
            }
            currBullet = nextBullet;
        }
        currPlayer = nextPlayer;
    }

    currEnemy = game->enemies;
    while (currEnemy)
    {
        nextEnemy = currEnemy->next;
        currBullet = game->bullets;
        while (currBullet)
        {
            nextBullet = currBullet->next;
            if(currBullet->bullet->isPlayerOwned && detectBulletEnemyCollision(currBullet->bullet,currEnemy->enemy))
            {
                float koef=1;
                switch (currEnemy->enemy->id)
                {
                case 0: case 1: case 3: koef = 1; break;
                case 2: koef = 2; break;
                case 4: koef = 6; break;
                case 5: koef = 4; break;
                }
                initEffect(currEnemy->enemy->x_pos+currEnemy->enemy->position.w/2-3*koef,
                               currEnemy->enemy->y_pos+currEnemy->enemy->position.h/2-4*koef,
                               currBullet->bullet->id+1);
                initEffect(currEnemy->enemy->x_pos+currEnemy->enemy->position.w/2-1*koef,
                           currEnemy->enemy->y_pos+currEnemy->enemy->position.h/2-1*koef,
                           currBullet->bullet->id+1);
                initEffect(currEnemy->enemy->x_pos+currEnemy->enemy->position.w/2+4*koef,
                           currEnemy->enemy->y_pos+currEnemy->enemy->position.h/2+3*koef,
                           currBullet->bullet->id+1);
                if (currBullet->bullet->id == 2)
                {
                    if (!currEnemy->enemy->path_id)
                        initEffect(currEnemy->enemy->position.x+currEnemy->enemy->position.w/2,
                                   currEnemy->enemy->position.y+currEnemy->enemy->position.h/2, 4);
                    game->players->player->health += 10;
                    if (audio)
                    {
                        Mix_VolumeChunk(explosionSound, 50);
                        Mix_PlayChannel(-1, explosionSound, 0);
                    }
                }
                freeBulletNode(currBullet);
                currEnemy->enemy->health -= 10;
                if(currEnemy->enemy->health <= 0)
                {
                    game->score+=currEnemy->enemy->score;
                    if(currEnemy->enemy->id == 2)           //Ako je boss
                        game->boss_active = 0;
                    if (currEnemy->enemy->id < ENEMY_PLANE_TYPES)
                        initEffect(currEnemy->enemy->position.x + currEnemy->enemy->position.w/2,
                                   currEnemy->enemy->position.y + currEnemy->enemy->position.h/2,
                                   currEnemy->enemy->id+5);
                    if (currEnemy->enemy->id < ENEMY_PLANE_TYPES && audio)
                    {
                        Mix_VolumeChunk(explosionSound, 25);
                        Mix_PlayChannel(-1, explosionSound, 0);
                    }
                    freeEnemyNode(currEnemy);
                }
                break;
            }
            currBullet = nextBullet;
        }
        currEnemy = nextEnemy;
    }

    currPlayer = game->players;
    while(currPlayer)
    {
        nextPlayer = currPlayer->next;
        currPowerUp = game->powerUps;
        while (currPowerUp)
        {
            nextPowerUp = currPowerUp->next;
            if(detectPowerUpPlayerCollision(currPowerUp->powerUp,currPlayer->player))
            {
                switch(currPowerUp->powerUp->id)
                {
                    case 1:
                        currPlayer->player->shieldActive = 400;
                        initEffect(currPlayer->player->x_pos + (currPlayer->player->position.w/2),currPlayer->player->y_pos + (currPlayer->player->position.h/2),10);
                        break;
                    case 2:
                        currPlayer->player->speedActive = 350;
                        // initEffect(currPlayer->player->x_pos + (currPlayer->player->position.w/2),currPlayer->player->y_pos + (currPlayer->player->position.h/2),11);
                        break;
                }
                freePowerUpNode(currPowerUp);
                break;
            }
            currPowerUp = nextPowerUp;
        }
        currPlayer = nextPlayer;
    }
}

/**
* Funkcija za proveru i hendlovanje sudara igraca i protivnika
*/
int detectPlayerEnemyCollision(playerPtr player,enemyPtr enemy)
{
    int dx, dy, distance;
    int playerRadius, enemyRadius;
    playerRadius = MIN(player->position.w/2, player->position.h/2);
    enemyRadius = MIN(enemy->position.w/2, enemy->position.h/2);
    dx = player->position.x + player->position.w/2 - enemy->position.x - enemy->position.w/2;
    dy = player->position.y + player->position.h/2 - enemy->position.y - enemy->position.h/2;
    distance = sqrt(dx*dx + dy*dy);
    return distance < playerRadius + enemyRadius;
}

/**
* Funkcija za proveru i hendlovanje sudara metka i protivnika
*/
int detectBulletEnemyCollision(bulletPtr bullet, enemyPtr enemy)
{
    int dx, dy, BR=10; // bomb range
    float bulletRadius, enemyRadius, distance;
    switch (bullet->id)
    {
    case 1:
        if (enemy->id > 4 ) return 0;
        bulletRadius = MIN(bullet->position.w/2, bullet->position.h/2);
        enemyRadius = MIN(enemy->position.w/2, enemy->position.h/2);
        if (bullet->id == 2) enemyRadius *= 10;
        dx = bullet->position.x + bullet->position.w/2 - enemy->position.x - enemy->position.w/2;
        dy = bullet->position.y + bullet->position.h/2 - enemy->position.y - enemy->position.h/2;
        distance = sqrt(dx*dx + dy*dy);
        return distance < bulletRadius + enemyRadius;
        break;
    case 2:
        if (enemy->id < 5 || bullet->counter > 0) return 0;
        if (enemy->position.x - BR > bullet->position.x + bullet->position.w) return 0;
        if (enemy->position.y - BR > bullet->position.y + bullet->position.h) return 0;
        if (enemy->position.x + enemy->position.w + BR < bullet->position.x) return 0;
        if (enemy->position.y + enemy->position.h + BR < bullet->position.y) return 0;
        return 1;
        break;
    }
    return 0;
}

/**
* Funkcija za proveru i hendlovanje sudara metka i igraca
*/
int detectBulletPlayerCollision(bulletPtr bullet, playerPtr player)
{
    int dx, dy, distance;
    int bulletRadius, playerRadius;
    bulletRadius = MIN(bullet->position.w/2, bullet->position.h/2);
    playerRadius = MIN(player->position.w/2, player->position.h/2);
    dx = bullet->position.x + bullet->position.w/2 - player->position.x - player->position.w/2;
    dy = bullet->position.y + bullet->position.h/2 - player->position.y - player->position.h/2;
    distance = sqrt(dx*dx + dy*dy);
    return distance < bulletRadius + playerRadius;
}

/**
* Funkcija za proveru i hendlovanje kolizije izmedju powerUp-a i igraca
*/
int detectPowerUpPlayerCollision(powerUpPtr powerUp, playerPtr player)
{
    int dx, dy, distance;
    int powerUpRadius, playerRadius;
    powerUpRadius = MIN(powerUp->position.w/2, powerUp->position.h/2);
    playerRadius = MIN(player->position.w/2, player->position.h/2);
    dx = powerUp->position.x + powerUp->position.w/2 - player->position.x - player->position.w/2;
    dy = powerUp->position.y + powerUp->position.h/2 - player->position.y - player->position.h/2;
    distance = sqrt(dx*dx + dy*dy);
    return distance < powerUpRadius + playerRadius;
}

/**
* Funkcija za proveru i hendlovanje kolizije izmedju powerUp-a i neprijatelja
*/
int detectPowerUpEnemyCollision(powerUpPtr powerUp, enemyPtr enemy)
{
    int dx, dy, distance;
    int powerUpRadius, playerRadius;
    powerUpRadius = MIN(powerUp->position.w/2, powerUp->position.h/2);
    playerRadius = MIN(enemy->position.w/2, enemy->position.h/2);
    dx = powerUp->position.x + powerUp->position.w/2 - enemy->position.x - enemy->position.w/2;
    dy = powerUp->position.y + powerUp->position.h/2 - enemy->position.y - enemy->position.h/2;
    distance = sqrt(dx*dx + dy*dy);
    return distance < powerUpRadius + playerRadius;
}
