#include "tank.h"

Levels Level1_e[] = { { 0, 1, 1 }, { 0, 2, 2 }, { 0, 3, 1 }, { 0, 5, 1 }, { 0, 6, 1 }, { 0, 8, 1 } };
Levels Level2_e[] = { { 0, 1, 1 }, { 1, 3, 2 }, { 0, 4, 1 }, { 0, 6, 2 }, { 0, 8, 1 }, { 0, 12, 1 }, { 1, 15, 1 } };
Levels Level3_e[] = { { 0, 1, 1 }, { 0, 2, 1 }, { 1, 3, 1 }, { 0, 5, 1 }, { 1, 10, 1 }, { 1, 10, 1 }, { 1, 10, 2 } };
Levels Level4_e[] = { { 1, 1, 2 }, { 0, 4, 1 }, { 0, 4, 2 }, { 1, 10, 1 }, { 1, 10, 1 }, { 1, 10, 2 }, { 1, 14, 2 }, { 1, 18, 1 } };
Levels Level5_e[] = { { 1, 2, 2 }, { 0, 4, 2 }, { 1, 5, 1 }, { 0, 7, 1 }, { 1, 10, 1 }, { 0, 15, 2 }, { 0, 15, 2 }, { 1, 15, 2 } };
Levels Level6_e[] = { { 0, 1, 2 }, { 0, 1, 1 }, { 0, 2, 2 }, { 1, 3, 1 }, { 1, 4, 2 }, { 1, 5, 1 }, { 1, 6, 1 }, { 1, 7, 1 }, { 1, 8, 3 } };
Levels Level7_e[] = { { 0, 1, 2 }, { 0, 3, 2 }, { 0, 5, 2 }, { 1, 7, 2 }, { 1, 10, 1 }, { 1, 10, 1 }, { 1, 12, 1 }, { 1, 12, 3 }, { 1, 14, 3 }, { 1, 15, 2 } };
Levels Level8_e[] = { { 1, 1, 1 }, { 1, 2, 2 }, { 1, 5, 2 }, { 1, 8, 1 }, { 1, 10, 3 }, { 1, 12, 1 }, { 1, 12, 2 }, { 1, 16, 3 }, { 1, 16, 2 }, { 1, 18, 3 }, { 1, 20, 3 } };
Levels Level9_e[] = { { 0, 1, 1 }, { 0, 2, 1 }, { 1, 3, 3 }, { 0, 4, 1 }, { 0, 5, 1 }, { 0, 5, 1 }, { 1, 6, 2 }, { 1, 7, 2 }, { 0, 11, 3 }, { 0, 11, 2 }, { 1, 12, 2 }, { 1, 14, 3 } };
Levels Level10_e[] = { { 0, 1, 1 }, { 0, 2, 1 }, { 1, 3, 2 }, { 1, 3, 1 }, { 1, 4, 1 }, { 0, 8, 3 }, { 1, 8, 1 }, { 1, 15, 2 }, { 1, 10, 2 }, { 1, 12, 1 }, { 1, 12, 3 }, { 1, 15, 1 }, { 1, 18, 3 }, { 1, 20, 2 } };/*U ovom nivou je kao za kraj easy nivoa namesten najtezi tenkic*/

Levels Level1_m[] = { { 0, 1, 1 }, { 0, 4, 1 }, { 0, 7, 2 }, { 0, 8, 2 }, { 0, 10, 1 }, { 1, 11, 2 } };/*Na mediumu ako sam negde stavim tenkic easy on ce biti specijalan sigurno!!!*/
Levels Level2_m[] = { { 0, 1, 2 }, { 0, 3, 2 }, { 0, 5, 1 }, { 1, 7, 2 }, { 1, 7, 2 }, { 0, 12, 2 }, { 0, 15, 2 }, { 0, 16, 3 } };
Levels Level3_m[] = { { 0, 1, 2 }, { 0, 5, 2 }, { 1, 7, 2 }, { 0, 10, 1 }, { 1, 12, 3 }, { 1, 20, 2 }, { 1, 20, 3 }, { 1, 20, 3 } };/*Otprilike ovde ce da se pojavi specijalan tenkic tezine hard pa shodno tome ce ostali tenkici biti obicni mediumi*/
Levels Level4_m[] = { { 1, 1, 3 }, { 1, 5, 1 }, { 1, 7, 1 }, { 1, 11, 2 }, { 1, 15, 1 }, { 0, 23, 1 }, { 1, 23, 2 }, { 1, 24, 1 }, { 1, 24, 3 } };/*Ovde svi specijalni*/
Levels Level5_m[] = { { 1, 1, 2 }, { 0, 2, 3 }, { 0, 5, 2 }, { 1, 10, 3 }, { 1, 15, 2 }, { 0, 16, 3 }, { 1, 17, 2 }, { 1, 18, 2 }, { 1, 19, 2 }, { 1, 20, 2 } };
Levels Level6_m[] = { { 1, 1, 2 }, { 1, 5, 2 }, { 0, 10, 1 }, { 0, 12, 1 }, { 1, 15, 1 }, { 1, 25, 2 }, { 1, 25, 3 }, { 1, 36, 3 }, { 1, 26, 2 }, { 1, 28, 2 }, { 1, 28, 3 }, { 1, 30, 3 } };
Levels Level7_m[] = { { 1, 1, 2 }, { 0, 2, 1 }, { 1, 3, 2 }, { 1, 4, 3 }, { 1, 5, 1 }, { 1, 6, 2 }, { 1, 7, 1 }, { 1, 8, 3}, { 1, 9, 2 }, { 1, 10, 3 }, { 1, 11, 2 }, { 1, 12, 3 } };
Levels Level8_m[] = { { 1, 1, 3 }, { 1, 3, 2 }, { 1, 5, 2 }, { 1, 7, 1 }, { 0, 15, 2 }, { 0, 17, 3 }, { 0, 19, 2 }, { 0, 21, 3 }, { 1, 23, 1 }, { 1, 30, 2 } , { 1, 32, 2 }, { 1, 34, 3 }};
Levels Level9_m[] = { { 1, 1, 2 }, { 1, 4, 2 }, { 1, 5, 2 }, { 1, 7, 2}, { 1, 10, 2}, { 1, 14, 2 }, { 1, 16, 2 }, { 1, 22, 3 }, { 1, 22, 3 }, { 1, 24, 2 }, { 1, 26, 3 }, { 1, 27, 3 }, { 1, 27, 3 }, { 1, 14, 3 } };/*Uvertira pred 10-ti nivo medium nivoa*/
Levels Level10_m[] = { { 1, 1, 1 }, { 1, 3, 1 }, { 1, 5, 2 }, { 1, 9, 2 }, { 0, 12, 3 }, { 1, 14, 3 }, { 1, 18, 2 }, { 1, 22, 2 }, { 1, 24, 3 }, { 1, 26, 3 }, { 1, 26, 2 }, { 1, 27, 2 }, { 1, 27, 3 }, { 1, 29, 3 }, { 1, 29, 3 } };/*Zurka ludnica*/

Levels Level1_h[] = { { 0, 2, 1 }, { 1, 5, 3 }, { 0, 7, 2 }, { 1, 10, 3 }, { 1, 5, 2 }, { 1, 6, 1 }, { 0, 8, 1 } };/*Ako ovde bude bilo mediuma bice samo special,easy izbacujem*/
Levels Level2_h[] = { { 0, 1, 1 }, { 1, 3, 2 }, { 1, 4, 3 }, { 1, 10, 2 }, { 0, 14, 2 }, { 0, 17, 2 }, { 1, 25, 3 }, { 0, 30, 2 }, { 0, 35, 2 }, { 1, 40, 3 } };
Levels Level3_h[] = { { 1, 2, 3 }, { 1, 4, 2 }, { 1, 5, 3 }, { 1, 6, 3 }, { 1, 10, 2 }, { 1, 11, 3 }, { 1, 15, 3 }, { 0, 30, 2 }, { 0, 35, 2 }, { 1, 40, 3 }, { 1, 40, 3 } };
Levels Level4_h[] = { { 0, 2, 3 }, { 0, 2, 2 }, { 1, 3, 2 }, { 1, 7, 2 }, { 1, 10, 3 }, { 0, 13, 3 }, { 1, 20, 2 }, { 0, 21, 2 }, { 0, 27, 2 }, { 1, 35, 3 }, { 0, 36, 2 }, { 0, 37, 2 }, { 0, 40, 3 }, { 1, 41, 3 } };
Levels Level5_h[] = { { 1, 1, 2 }, { 0, 6, 2 }, { 1, 8, 1 }, { 0, 9, 3 }, { 0, 11, 3 }, { 0, 13, 3 }, { 0, 15, 3 }, { 0, 17, 1 }, { 0, 20, 3 }, { 1, 23, 3 }, { 1, 27, 2 }, { 0, 27, 3 }, { 1, 29, 2 }};
Levels Level6_h[] = { { 0, 1, 3 }, { 1, 4, 2 }, { 1, 9, 3 }, { 1, 9, 3 }, { 1, 11, 3 }, { 0, 11, 1 }, { 0, 14, 3 }, { 0, 19, 3 }, { 1, 21, 2 }, { 1, 25, 2 }, { 1, 30, 2 }, { 1, 40, 2 } };
Levels Level7_h[] = { { 1, 1, 2 }, { 1, 4, 2 }, { 1, 5, 1 }, { 1, 6, 3 }, { 0, 8, 3 }, { 1, 10, 2 }, { 1, 13, 3 }, { 1, 15, 2 }, { 1, 17, 2 }, { 1, 20, 2 }, { 1, 21, 2 }, { 1, 24, 2 }, { 1, 30, 3 } };
Levels Level8_h[] = { { 1, 1, 3 }, { 1, 6, 2 }, { 1, 8, 1 }, { 1, 10, 3 }, { 1, 13, 1 }, { 1, 15, 2 }, { 1, 30, 3 }, { 1, 35, 3 }, { 0, 37, 3 }, { 1, 40, 3 }, { 1, 42, 2 } };
Levels Level9_h[] = { { 1, 2, 3 }, { 1, 4, 3 }, { 1, 7, 3 }, { 1, 14, 3 }, { 1, 16, 3 }, { 1, 20, 3 }, { 1, 22, 3 }, { 1, 25, 3 }, { 1, 35, 3 }, { 1, 45, 3 } };
Levels Level10_h[] = { { 1, 1, 1 }, { 1, 2, 1 }, { 1, 3, 2 }, { 1, 4, 3 }, { 1, 5, 2 }, { 1, 6, 2 }, { 1, 10, 3 }, { 1, 17, 2 }, { 1, 20, 3 }, { 1, 30, 3 }, { 1, 34, 3 }, { 1, 40, 3 }, { 1, 40, 3 }, { 1, 42, 3 }, { 1, 44, 3 }, { 1, 44, 3 }, { 1, 46, 3 } };

int Easy[10] = { 6, 7, 7, 8, 8, 9, 11, 12, 13, 14 };
int Medium[10] = { 6, 8, 8, 9, 10, 12, 12, 12, 14, 15 };
int Hard[10] = { 7, 10, 11, 14, 13, 12, 13, 11, 10, 17 };

int *botsInLevel[3];
Levels *levelEasy[10];
Levels *levelMedium[10];
Levels *levelHard[10];

Levels **LEVEL[3];