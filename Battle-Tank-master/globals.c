#include "tank.h"

Lst *lst;

char meni[][dimx] = { " New Game ", " Load Game ", " Settings ", " Map Editor ", " Play Custom map", " High Scores ", " Exit ", " -> EASY ", " -> MEDIUM ", " -> HARD " };

char map_name[50] = "dobraje.map";

char matrix[dimx + 1][dimy + 1];                         // velicina mape

char element = 'b';

Powerups powerup;

Poweruplst* Plst;

char pUps[6] = { 'x', 'l', 's', 'q', 'a', 'y' };

int pridx;

int top[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8 };
int left[] = { 2, 5, 8, 1, 4, 7, 0, 3, 6 };
int right[] = { 6, 3, 0, 7, 4, 1, 8, 5, 2 };
int bottom[] = { 8, 7, 6, 5, 4, 3, 2, 1, 0 };

int HIGH_SCORE=0;  

int BOT_DIF = 0, LVL;

int M, N;

int GAME_LOADED=0;

Loaded_level_info level_info;

TankDesign special_tank_v[] = { { ACS_VLINE | A_BOLD, 1 }, { ACS_VLINE | A_BOLD, 1 }, { ACS_VLINE | A_BOLD, 1 },
{ ACS_VLINE | A_BOLD, 1 }, { ACS_BULLET | A_BOLD | A_ALTCHARSET, 4 }, { ACS_VLINE | A_BOLD, 1 },
{ ACS_DIAMOND | A_BOLD, 4 }, { ACS_HLINE | A_BOLD, 4 }, { ACS_DIAMOND | A_BOLD, 4 } };

TankDesign special_tank_h[] = { { ACS_HLINE | A_BOLD, 1 }, { ACS_HLINE | A_BOLD, 1 }, { ACS_HLINE | A_BOLD, 1 },
{ ACS_HLINE | A_BOLD, 1 }, { ACS_BULLET | A_BOLD | A_ALTCHARSET, 4 }, { ACS_HLINE | A_BOLD, 1 },
{ ACS_DIAMOND | A_BOLD, 4 }, { ACS_VLINE | A_BOLD, 4 }, { ACS_DIAMOND | A_BOLD, 4 } };

TankDesign normal_tank_v[] = { { ' ', 1 }, { ACS_VLINE | A_BOLD, 1 }, { ' ', 1 }, { ACS_PLUS | A_BOLD, 18 },
{ ACS_CKBOARD | A_BOLD, 2 }, { ACS_PLUS | A_BOLD, 18 }, { ACS_PLUS | A_BOLD, 18 },
{ ACS_BLOCK, 2 }, { ACS_PLUS | A_BOLD, 18 } };

TankDesign normal_tank_h[] = { { ' ', 1 }, { ACS_HLINE | A_BOLD, 1 }, { ' ', 1 },
{ ACS_PLUS | A_BOLD, 18 }, { ACS_CKBOARD | A_BOLD, 2 }, { ACS_PLUS | A_BOLD, 18 },
{ ACS_PLUS | A_BOLD, 18 }, { ACS_BLOCK, 2 }, { ACS_PLUS | A_BOLD, 18 } };

TankDesign brat_tank_v[] = { { ACS_BOARD, 8 }, { ACS_VLINE | A_BOLD, 1 }, { ACS_BOARD, 8 },
{ ACS_VLINE | A_BOLD, 18 }, { ACS_CKBOARD, 2 }, { ACS_VLINE | A_BOLD, 18 },
{ ACS_BOARD, 8 }, { ACS_HLINE | A_BOLD, 18 }, { ACS_BOARD, 8 } };

TankDesign brat_tank_h[] = { { ACS_BOARD, 8 }, { ACS_HLINE | A_BOLD, 1 }, { ACS_BOARD, 8 },
{ ACS_HLINE | A_BOLD, 18 }, { ACS_CKBOARD, 2 }, { ACS_HLINE | A_BOLD, 18 },
{ ACS_BOARD, 8 }, { ACS_VLINE | A_BOLD, 18 }, { ACS_BOARD, 8 } };

TankDesign novi_tank_v[]    = { { ACS_VLINE | A_BOLD, 15  }, { ACS_VLINE | A_BOLD, 15 }, { ACS_VLINE | A_BOLD, 15 }, 
{ACS_BOARD, 8 }, { ACS_VLINE | A_BOLD, 15}, { ACS_BOARD, 8  }, 
{ ACS_BOARD, 8 }, { ACS_DIAMOND | A_BOLD, 21  }, { ACS_BOARD, 8 } };

TankDesign novi_tank_h[]    = { { ACS_HLINE | A_BOLD, 15   }, { ACS_HLINE | A_BOLD, 15 }, { ACS_HLINE | A_BOLD, 15  },
{ ACS_BOARD, 8}, { ACS_HLINE | A_BOLD, 15}, { ACS_BOARD, 8 }, 
{ ACS_BOARD, 8 }, { ACS_DIAMOND | A_BOLD, 21  }, { ACS_BOARD, 8 } };