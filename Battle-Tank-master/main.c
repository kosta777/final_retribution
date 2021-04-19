#include "tank.h"


void main(){ // Da sredimo main kasnije.
	int i, rez;
	int br, phase = 1, lastKey = 5;
	long int random_element_gen;
	unsigned long int random_pup_gen;
	unsigned short mm = 0, pp = 0;
	char lvlprint[31];
	char lvl_num[3];
	clock_t start_lvl_time, pw_shield_start, pw_clock_start, pw_shovel_start;
	Plst = (Poweruplst*)malloc(sizeof(Poweruplst));
	Plst->first = Plst->last = NULL;
	lst = (Lst*)malloc(sizeof(Lst));
	init_curses();
	link_levels();
	while (1){
		demo_mode();
		refresh(); 
		main_menu(1);
		for (LVL = 0 ; LVL<10; LVL++){ // Begin.
			if(!GAME_LOADED)  start_level(&start_lvl_time, &LVL, &br, &random_pup_gen, &random_element_gen);
			else{
				start_lvl_time=clock()-level_info.time;
				LVL=level_info.Lvl;
				br=level_info.Br;
				HIGH_SCORE=level_info.high_score;
				random_pup_gen = 0;
				random_element_gen = 0;
			}
			attron(COLOR_PAIR(1));
			mvaddstr(68,40,"ESC TO PAUSE");
			attroff(COLOR_PAIR(1));
			while (1){
				time_now();
				print_high_score();
				random_element_gen++;
				if (random_element_gen == 300000) random_element_gen = 0, rand_gen();
				execute_powerups(&pw_shield_start, &pw_clock_start, &pw_shovel_start, &random_pup_gen);
				should_spawn_bot(&start_lvl_time, &rez, &br, LVL);
				if (_kbhit())
					execute_our_tank(&mm, &pp, &phase, &lastKey, start_lvl_time, br, 1);
				execute_bots(1);
				if (!strcmp(map_name,"gohardorgohome.map")) break; // ako se vratim iz custom game-a
				if ((!powerup.life) || (!strcmp(map_name, "gameover.map"))){
					create_map(map_name, 0);
					Sleep(2000);
					break;
				}
				if (lst->n == 1 && br >= botsInLevel[BOT_DIF][LVL]) { print_high_score(); Sleep(2000); free_tank(lst->first); break; }
			}
			delete_tank_list();
			delete_powerup_list();
			if(GAME_LOADED) GAME_LOADED=0;
			if (!strcmp(map_name, "gameover.map") ||  (!strcmp(map_name, "gohardorgohome.map")) ) break;
		}
		if(LVL==10){
			strcpy(map_name,"win.map");
			create_map(map_name, 0);
			Sleep(2500);
		}
		if(! (!strcmp(map_name, "gohardorgohome.map"))) new_high_score(HIGH_SCORE);
		HIGH_SCORE=0;
		clear();
		//delete_menu(2, x1m, 25, x2m);
		//delete_menu(27, x1m + 20, 36, x2m);
		//delete_menu(58, x1m, 67, x2m);
	}
	free(lst);
	free(Plst);
	endwin();
}

