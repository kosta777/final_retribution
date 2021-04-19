#include "savingGame.h"

/**
* Funkcija koja snima igru u fajl
* - u posebnom zaglavlju se čuva broj različitih objekata, kako bi datoteka kasnije bila korektno pročitana
* @param    gamePath    putanja do fajla u koji treba snimiti igru
*/
void saveGame(char *gamePath)
{
    FILE *outFile = fopen(gamePath, "wb");
    enemyListNodePtr enemy = game->enemies;
    bulletListNodePtr bullet = game->bullets;
    effectListNodePtr effect = game->effects;
    powerUpListNodePtr powerUp = game->powerUps;
    saveHeaderPtr saveHeader;
    if (!outFile)
    {
        printf("Error while saving game!\n");
        return;
    }
    // kreiranje i snimanje save headera koji sadrzi broj instanci svih struktura
    saveHeader = malloc(sizeof(struct saveHeaderStruct));
    saveHeader->bulletNum = saveHeader->effectNum = saveHeader->enemyNum = saveHeader->powerUpNum = 0;
    while (enemy) saveHeader->enemyNum++, enemy = enemy->next;
    while (bullet) saveHeader->bulletNum++, bullet = bullet->next;
    while (effect) saveHeader->effectNum++, effect = effect->next;
    while (powerUp) saveHeader->powerUpNum++, powerUp = powerUp->next;
    fwrite(saveHeader, sizeof(struct saveHeaderStruct), 1, outFile);
    // snimanje igre
    fwrite(game, sizeof(struct gameStruct), 1, outFile);
    // snimanje playera
    fwrite(game->players->player, sizeof(struct playerStruct), 1, outFile);
    // snimanje neprijatelja
    for (enemy = game->enemies; enemy; enemy = enemy->next)
        fwrite(enemy->enemy, sizeof(struct enemyStruct), 1, outFile);
    // snimanje metkova
    for (bullet = game->bullets; bullet; bullet = bullet->next)
        fwrite(bullet->bullet, sizeof(struct bulletStruct), 1, outFile);
    // snimanje efekata
    for (effect = game->effects; effect; effect = effect->next)
        fwrite(effect->effect, sizeof(struct effectStruct), 1, outFile);
    // snimanje powerupova
    for (powerUp = game->powerUps; powerUp; powerUp = powerUp->next)
        fwrite(powerUp->powerUp, sizeof(struct powerUpStruct), 1, outFile);
    free(saveHeader);
    printf("Game saved\n");
    fclose(outFile);
}

/**
* Funkcija koja ucitava igru iz fajla
* @param    gamePath    putanja do fajla iz koga treba učitati igru
*/
void loadGame(char *gamePath)
{
    enemyListNodePtr currEnemy=NULL, newEnemy;
    bulletListNodePtr currBullet=NULL, newBullet;
    effectListNodePtr currEffect=NULL, newEffect;
    powerUpListNodePtr currPowerUp=NULL, newPowerUp;
    FILE *inFile = fopen(gamePath, "rb");
    int i;
    saveHeaderPtr saveHeader;
    if (!inFile)
    {
        printf("Error while loading the game!\n");
        return;
    }
    if (game) freeGame();
    // ucitavanje hedera
    saveHeader = malloc(sizeof(struct saveHeaderStruct));
    fread(saveHeader, sizeof(struct saveHeaderStruct), 1, inFile);
    // ucitavanje igre
    game = malloc(sizeof(struct gameStruct));
    fread(game, sizeof(struct gameStruct), 1, inFile);
    game->players = game->bullets = game->effects = game->powerUps = NULL;
    // ucitavanje igraca
    game->players = malloc(sizeof(struct playerListNodeStruct));
    game->players->player = malloc(sizeof(struct playerStruct));
    fread(game->players->player, sizeof(struct playerStruct), 1, inFile);
    game->players->next = game->players->prev = NULL;
    // ucitavanje neprijatelja
    for (i=0; i<saveHeader->enemyNum; i++)
    {
        newEnemy = malloc(sizeof(struct enemyListNodeStruct));
        newEnemy->enemy = malloc(sizeof(struct enemyStruct));
        fread(newEnemy->enemy, sizeof(struct enemyStruct), 1, inFile);
        newEnemy->next = NULL;
        newEnemy->prev = currEnemy;
        if (currEnemy) currEnemy->next = newEnemy, currEnemy = newEnemy;
        else game->enemies = currEnemy = newEnemy;
    }
    // ucitavanje metkova
    for (i=0; i<saveHeader->bulletNum; i++)
    {
        newBullet = malloc(sizeof(struct bulletListNodeStruct));
        newBullet->bullet = malloc(sizeof(struct bulletStruct));
        fread(newBullet->bullet, sizeof(struct bulletStruct), 1, inFile);
        newBullet->next = NULL;
        newBullet->prev = currBullet;
        if (currBullet) currBullet->next = newBullet, currBullet = newBullet;
        else game->bullets = currBullet = newBullet;
    }
    // ucitavanje efekata
    for (i=0; i<saveHeader->effectNum; i++)
    {
        newEffect = malloc(sizeof(struct effectListNodeStruct));
        newEffect->effect = malloc(sizeof(struct effectStruct));
        fread(newEffect->effect, sizeof(struct effectStruct), 1, inFile);
        newEffect->next = NULL;
        newEffect->prev = currEffect;
        if (currEffect) currEffect->next = newEffect, currEffect = newEffect;
        else game->effects = currEffect = newEffect;
    }
    // ucitavanje powerupova
    for (i=0; i<saveHeader->powerUpNum; i++)
    {
        newPowerUp = malloc(sizeof(struct powerUpListNodeStruct));
        newPowerUp->powerUp = malloc(sizeof(struct powerUpStruct));
        fread(newPowerUp->powerUp, sizeof(struct powerUpStruct), 1, inFile);
        newPowerUp->next = NULL;
        newPowerUp->prev = currPowerUp;
        if (currPowerUp) currPowerUp->next = newPowerUp, currPowerUp = newPowerUp;
        else game->powerUps = currPowerUp = newPowerUp;
    }

    initTextures();

    free(saveHeader);
    printf("Game loaded\n");
    fclose(inFile);
}
