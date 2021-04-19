#include "tank.h"

void start_level(clock_t *start_lvl_time, int *l, int *br, unsigned long int *random_pup_gen, long int* random_element_gen){
	char lvlprint[31];
	char lvl_num[3];
	Levels tank_struct;
	*random_pup_gen = 0;
	*random_element_gen = 0;
	strcpy(lvlprint, "level");
	sprintf(lvl_num, "%d", *l + 1);
	strcat(lvlprint, lvl_num);
	strcat(lvlprint, ".lvl");
	strcpy(map_name, lvlprint);
	create_map(map_name,0);
	Sleep(3000);
	init_powerups();
	*start_lvl_time = clock();
	*br = 0;
	lst->first = NULL;
	lst->curr = NULL;
	lst->last = NULL;
	lst->n = 0;
	Plst->first = NULL;
	Plst->last = NULL;
	strcpy(map_name, "level");
	strcat(map_name, lvl_num);
	strcat(map_name, ".map");
	create_map(map_name,0);
	tank_struct.kind = -1;
	tank_struct.smart = 0;

	print_border_side_menu(2, x1m, 25, x2m, 3);       // bots left.
	print_bots_left();								  // saljes tezinu izabranu u podesavanjima( Easy-0 medium-1 hard-2) LVL(koji je nivo).  NOVO!
	print_border_side_menu(47, x1m + 20, 56, x2m, 4); // high score counter. // changed coordinates-Andrija // sve spusteno za 21
	print_border_side_menu(58, x1m, 67, x2m, 4);      // pw disclaimer.
	print_menu_pups(61);
	alloc_tank(0, tank_struct);
}

void fire_rate_assessment(int keyPressed){
	int j;
	if (stars() == 2){
		for (pridx = 0; pridx < 4; pridx = pridx + 2){
			if ((!(lst->first->tankAll.projectile[pridx].phase))) { action(keyPressed, &lst->first->tankAll); break; }
		}
	}
	else if (stars() == 4){
		for (j = 0; j < 4; j = j + 2)
			if ((!(lst->first->tankAll.projectile[j].phase)) && (!(lst->first->tankAll.projectile[j + 1].phase))){
				for (pridx = j; pridx < j + 2; pridx = pridx++) { action(keyPressed, &lst->first->tankAll); }
				break;
			}
	}
	else { pridx = 0; if ((!(lst->first->tankAll.projectile[pridx].phase))) action(keyPressed, &lst->first->tankAll); }
}

void execute_our_tank(unsigned short *mm, unsigned short *pp, int *phase, int *lastKey,clock_t start_lvl_time,int br, int decide){
	struct timeb vreme;
	int keyPressed;
	ftime(&vreme);
	keyPressed = getch();
	if (keyPressed != *lastKey){
		*phase = 1;
		*lastKey = keyPressed;
	}
	lst->curr = lst->first;
	if (keyPressed == ' '){
		fire_rate_assessment(keyPressed); // for different powerup stars.
	}
	else if( keyPressed == ESC){
		pause_game(decide,start_lvl_time,br);
	}
	else {
		if (*phase == 1){ action(keyPressed, &lst->first->tankAll); *mm = *pp = vreme.millitm; *phase = 2; }
		else{
			ftime(&vreme);
			*mm = vreme.millitm;
			if (delay_s(67, *mm, *pp, *phase)){
				action(keyPressed, &lst->first->tankAll);
				*mm = *pp = vreme.millitm;
			}
		}
	}
}

void execute_bots(int flag){
	int i;

	for (i = 0, lst->curr = lst->first; i < lst->n; i++, lst->curr = lst->curr->next){
		if (i != 0){
			pridx = 0; // vodi racuna da ne bi slao bilo koji pridx!
			switch (lst->curr->tankAll.tank.diff){   // ovo treba da se poveze da se pusti bot Ne znam gde da stavim
			case 1: easy_bot(); break;
			case 2: medium_bot(); break;
			case 3: hard_bot(); break;
			}
			if (lst->curr->tankAll.projectile[0].phase){
				projectile(lst->curr->tankAll.tank.position.y,
					lst->curr->tankAll.tank.position.x, lst->curr->tankAll.projectile[0].position.projectil_dir);
			}
			if (!strcmp(map_name, "gameover.map")) return;
		}
		else{
				if(!flag) {
					switch (lst->curr->tankAll.tank.diff){   // ovo treba da se poveze da se pusti bot Ne znam gde da stavim
				case 1: easy_bot(); break;
				case 2: medium_bot(); break;
				case 3: hard_bot_demo(); break;
				}
			}
			for (pridx = 0; pridx < 4; pridx++)
				if (lst->curr->tankAll.projectile[pridx].phase) {  projectile(lst->curr->tankAll.tank.position.y,
					lst->curr->tankAll.tank.position.x, lst->curr->tankAll.projectile[pridx].position.projectil_dir); }
			
		}
	}
}

void demo_mode(){
	Levels tank_struct;
	lst->first = NULL;
	lst->curr = NULL;
	lst->last = NULL;
	lst->n = 0;
	powerup.life=ULLONG_MAX;
	strcpy(map_name, "gohardorgohome.map");
	create_map(map_name, 0);
	tank_struct.kind = 0;
	tank_struct.smart = 3; // onaj koji glumi naseg bota je hard-bot
	alloc_tank(0, tank_struct);
	lst->curr=lst->first;  // ovo mora posle alokacije
	tank_struct.kind = 0;
	srand(time(NULL));
	tank_struct.smart = ( rand() % 3 ) + 1;
	alloc_tank(1,tank_struct);
}

void should_spawn_bot(clock_t *start_lvl_time, int *rez, int *br, int l){
	if (*br < botsInLevel[BOT_DIF][LVL] && (((*rez = free_place(0)) && (((clock() - *start_lvl_time) * 1000 / CLOCKS_PER_SEC)>LEVEL[BOT_DIF][LVL][*br].time * 1000)) || (lst->n == 1))){
		pridx = 0;
		alloc_tank(*rez, LEVEL[BOT_DIF][LVL][*br]); (*br)++;
	}
}

void link_levels(){
	LEVEL[0] = levelEasy;
	LEVEL[1] = levelMedium;
	LEVEL[2] = levelHard;
	levelEasy[0] = Level1_e;
	levelEasy[1] = Level2_e;
	levelEasy[2] = Level3_e;
	levelEasy[3] = Level4_e;
	levelEasy[4] = Level5_e;
	levelEasy[5] = Level6_e;
	levelEasy[6] = Level7_e;
	levelEasy[7] = Level8_e;
	levelEasy[8] = Level9_e;
	levelEasy[9] = Level10_e;
	levelMedium[0] = Level1_m;
	levelMedium[1] = Level2_m;
	levelMedium[2] = Level3_m;
	levelMedium[3] = Level4_m;
	levelMedium[4] = Level5_m;
	levelMedium[5] = Level6_m;
	levelMedium[6] = Level7_m;
	levelMedium[7] = Level8_m;
	levelMedium[8] = Level9_m;
	levelMedium[9] = Level10_m;
	levelHard[0] = Level1_h;
	levelHard[1] = Level2_h;
	levelHard[2] = Level3_h;
	levelHard[3] = Level4_h;
	levelHard[4] = Level5_h;
	levelHard[5] = Level6_h;
	levelHard[6] = Level7_h;
	levelHard[7] = Level8_h;
	levelHard[8] = Level9_h;
	levelHard[9] = Level10_h;

	botsInLevel[0] = Easy;
	botsInLevel[1] = Medium;
	botsInLevel[2] = Hard;
}
