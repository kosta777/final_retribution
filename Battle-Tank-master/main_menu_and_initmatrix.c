#include "tank.h"

char lvl_matrix[dimx][dimy];

char lvl_meni[][dimx] = { " Create New Map ", " Load Map ", " Save Map As", " Exit ", " Yes ", " No ", "Continue", "Return to Main Menu", "Save Game" };
char button[][dimx] = { " R : Turn resizing on/off ", " W : Change element to water ", " B : Change element to brick", " G : Change element to grass ",
" C : Change element to Concrete ", " E : Eraser", " Z : Undo", " X : Redo", " SPACE : Save element on map  ", " ESC : Return to menu " };

void init_matrix(){
 int i, j;
 for (i = 0; i < 65; i++)
  for (j = 0; j < 90; j++){
   lvl_matrix[i][j] = '.';
  }
 save_in_matrix(61, 50, 61, 40, 'b');
 for (i = 62; i < dimx + 2; i++)
 {
  save_in_matrix(i, 50, i, 40, 'b');
  save_in_matrix(i, 49, i, 41, 'h');
 }
 save_in_matrix(63, 48, 63, 42, '1');
 save_in_matrix(64, 48, 64, 42, '2');
 save_in_matrix(65, 48, 65, 42, '3');
}

void buttons(){
 int y1 = 47, y2 = 67;
 int x1 = 95, i = 0, x2 = 120;
 for (; y1 <= y2; y1 += 2)
  mvprintw(y1, x1, button[i++]);
}


int option_selected(int mv, int mainm){ // mainm ako smo u glavnom meniju
	switch (mv){
	case 7:      if (mainm) { HIGH_SCORE=0; return 0; }                                                                  else { init_matrix(); print_matrix(); buffer[0] = '\0'; element = 'b'; return 0; } break;
	case 9:      if (mainm) { delete_menu(y1c, x1c, y2c, x2c); return load_maps(2); }	                else   load_maps(1);  break;
	case 11:	 if (mainm)	{ bot_settings(); delete_menu(y1m, x1m, y2m, x2m); return 1;}	           else   return save_map();
	case 13:	 if (mainm)	{ level_editor(); print_border_menu(y1c, x1c, y2c, x2c); print_commands(); create_map(map_name, 0); return 1; }  else return 0;	 
	case 15:     if (mainm) { delete_menu(y1c, x1c, y2c, x2c); load_maps(0); return 1;} 					
	case 17:	 if (mainm) { read_high_scores(); return 1; }                                                        break;													
	case 19:	 if (mainm) { system("cls"); exit(0); }	                                                      break; 
	}

} //  koji blok je izabran



void bot_settings(){
	int limitup=11,limitdown=15,mv=11,i=7;
	print_border_menu(y1m, x1m, y2m, x2m);
	attron(COLOR_PAIR(10));
		mvprintw(4, 111, " SET GAME DIFFICULTY : ");
	attroff(COLOR_PAIR(10));
	attron(COLOR_PAIR(8)|A_BOLD);
	mvprintw(11, 117, " -> EASY ");
	attroff(COLOR_PAIR(8)|A_BOLD);
	mvprintw(13, 117, " -> MEDIUM");
	mvprintw(15, 117, " -> HARD  ");
	while(1){
		switch(getch()){
		    case KEY_UP : PlaySound(TEXT("Sound\\Menu_move.wav"),NULL, SND_ASYNC); menu_up(&mv,limitup,&i,117,1); break;
			case KEY_DOWN : PlaySound(TEXT("Sound\\Menu_move.wav"),NULL, SND_ASYNC); menu_down(&mv,limitdown,&i,117,1); break;
			case ENTER : 
				PlaySound(TEXT("Sound\\select.wav"),NULL, SND_ASYNC);
				if(mv==11) BOT_DIF=0;
						 else if (mv==13) BOT_DIF=1;
						 else if(mv==15) BOT_DIF=2; 
			case ESC :   return;
		}
	}
	
}

void menu_content(int mainm){
	int i, j;
	if (mainm){
		attron(COLOR_PAIR(10) | A_BOLD);
		mvprintw(4, 117, " M E N U : ");
		attroff(COLOR_PAIR(10)| A_BOLD);
		attron(COLOR_PAIR(8)|A_BOLD);
		mvprintw(7, 117, meni[0]);
		attroff(COLOR_PAIR(8)|A_BOLD);
		mvprintw(9, 117, meni[1]);
		mvprintw(11, 117, meni[2]);
		mvprintw(13, 117, meni[3]);
		mvprintw(15, 117, meni[4]);
		mvprintw(17, 117, meni[5]);
		mvprintw(19, 117, meni[6]);
	}
	else{
		mvprintw(4, 117, " LEVEL EDITOR : ");
		attron(COLOR_PAIR(8)|A_BOLD);
		mvprintw(7, 117, lvl_meni[0]);
		attroff(COLOR_PAIR(8)|A_BOLD);
		mvprintw(9, 117, lvl_meni[1]);
		mvprintw(11, 117, lvl_meni[2]);
		mvprintw(13, 117, lvl_meni[3]);
	}
	refresh();
} // sadrzaj menija

void delete_menu(int y1, int x1, int y2, int x2){
	int i, j;
	attron(COLOR_PAIR(1));
	for (j = y1; j <= y2; j++)
		for (i = x1; i <= x2; i++)
			mvaddch(j, i, ' ');
	attroff(COLOR_PAIR(1));
	refresh();
} // brise meni

void pause_menu_content(int decide)
{
 attron(COLOR_PAIR(10) | A_BOLD );
 mvprintw(30, 118, "PAUSE");
 attroff(COLOR_PAIR(10)| A_BOLD);
 attron(COLOR_PAIR(8)|A_BOLD);
 mvprintw(33, 113, "Continue");
 attroff(COLOR_PAIR(8)|A_BOLD);
 mvprintw(35, 113, "Return to Main Menu");
 if(decide) mvprintw(37, 113, "Save Game");
 refresh();
}

void pause_game(int decide,clock_t start_lvl_time, int br)
{
 int y1 = 28, x1 = x1m, y2 = 45, x2 = x2m, mv = 33;
 int limitup = 33, limitdown = 37, tru = 1, ind = 6;
 clock_t time_diff;
 time_diff=clock()-start_lvl_time;
 print_border_menu(y1, x1, y2, x2);
 if(!decide) limitdown=35;
 pause_menu_content(decide);
 while (tru)
 {
  switch (getch())
  {
  case KEY_UP: PlaySound(TEXT("Sound\\Menu_move.wav"),NULL, SND_ASYNC); menu_up(&mv, limitup, &ind, 113, 0);       break;
  case KEY_DOWN: PlaySound(TEXT("Sound\\Menu_move.wav"),NULL, SND_ASYNC); menu_down(&mv, limitdown, &ind, 113, 0); break;
  case ESC: PlaySound(TEXT("Sound\\select.wav"),NULL, SND_ASYNC); delete_menu(y1, x1, y2, x2);  return; break;
  case ENTER: 
	  PlaySound(TEXT("Sound\\select.wav"),NULL, SND_ASYNC);
	  switch (mv){
		  case 33:	 delete_menu(y1, x1, y2, x2);																             return;
		  case 35:   delete_tank_list();   delete_powerup_list();     strcpy(map_name, "gohardorgohome.map"); return;    // else strcpy(map_name, "gameover.map");                return;                                                                    break;
		  case 37:   save_game(time_diff, br);  print_border_menu(y1, x1, y2, x2); mv=33; ind=6 ;pause_menu_content(decide);  break;
	  } break;
  }
 }
}

int main_menu(int mainm){
	int  xu, xd, yd, mv = 7, ind = 0, tru = 1, limitup = 7, limitdown, i, b;
	clock_t demo_time=clock();
	if (mainm){
		print_border_side_menu(y1c - 11, x1c, y2c - 23, x2c, 3); // pw disclaimer izmenio!
		print_menu_pups(38); // Izmenio!
		print_border_side_menu(y1c, x1c, y2c, x2c, 3);
		print_commands();
	}
	if (!mainm) limitdown = 13;
	else limitdown = 19;
	print_border_side_menu(y1m, x1m, y2m, x2m, 3);
	menu_content(mainm);
	PlaySound(TEXT("Sound\\Music.wav"),NULL, SND_ASYNC );
	while (tru){
		if (_kbhit()){
			switch (getch()){
			case KEY_UP: PlaySound(TEXT("Sound\\Menu_move.wav"),NULL, SND_ASYNC); menu_up(&mv, limitup, &ind, 117, mainm);		 break;
			case KEY_DOWN:  PlaySound(TEXT("Sound\\Menu_move.wav"),NULL, SND_ASYNC); menu_down(&mv, limitdown, &ind, 117, mainm);  break;
			case ENTER:
				PlaySound(TEXT("Sound\\select.wav"),NULL, SND_ASYNC);
				delete_menu(y1c - 11, x1c, y2c - 23, x2c); // vidi jos
				delete_menu(y1m, x1m, y2m, x2m);  
				if (tru = option_selected(mv, mainm)){
					print_border_side_menu(y1m, x1m, y2m, x2m, 3);
					menu_content(mainm);
					PlaySound(TEXT("Sound\\Music.wav"),NULL, SND_ASYNC );
					if(mainm){
						print_border_side_menu(y1c - 11, x1c, y2c - 23, x2c, 3);
						print_menu_pups(38); 
						print_border_side_menu(y1c, x1c, y2c, x2c, 3);
						print_commands();
					}
					mv = limitup;
					ind = 0;
				}
				else{
					delete_menu(y1c, x1c, y2c, x2c);
					if(GAME_LOADED){
						print_border_side_menu(2, x1m, 25, x2m, 3); // bots left.
						print_bots_left(); // saljes tezinu izabranu u podesavanjima( Easy-0 medium-1 hard-2) LVL(koji je nivo).  NOVO!
						print_border_side_menu(47, x1m + 20, 56, x2m, 4);// high score counter. // changed coordinates-Andrija // sve spusteno za 21
						print_border_side_menu(58, x1m, 67, x2m, 4); // pw disclaimer.
						print_menu_pups(61);
					}
					else if(mainm) delete_tank_list();
					if (mainm)
					 {
						return 0;
					}
					else
					{
						if (mv == limitup) return 1; //za Create new map
						else if ((mv == 11) || (mv ==9)) return 1;
						return 0;
					}
				}
			}
		}
		if (mainm){
			for (b=0; b<2; b++) spawn_bot_demo(&demo_time);
			execute_bots(0);
		    time_now();
			if ((!strcmp(map_name, "gameover.map"))){
				create_map(map_name, 0);
				Sleep(430);
				delete_tank_list();
				demo_mode();
			}
		}
		//demo mod za bota
	}
}

void spawn_bot_demo(clock_t* demo_time){
	int rez;
	Levels tank_struct;
	tank_struct.kind=0;
	srand(time(NULL));
	tank_struct.smart=( rand() % 3 ) + 1;
	if (lst->n < 7 && (((rez = free_place(0)) && (((clock() - *demo_time) * 1000 / CLOCKS_PER_SEC)>3000)) || (lst->n == 2))){
		alloc_tank(rez, tank_struct);
		*demo_time=clock();
	}
}



void level_editor(){
 int yu = 32, xd = 32, yd = 32, xu = 32; // yu  y up ;  yd  y down; xu  x up; xd  x down     [yu]|    [xd]...[xu] |           //             [yd]|    [xd]...[xu] |
 int i, j, tru = 1; // i,j pomocne promenljive;tru promenljiva koja prekida kretanje bloka po mapi; dify i difx vracaju visinu i sirinu bloka koji 
 //treba da  se pojavi na mapi;
 int n_undo, n_redo;
 map* undo, *redo;
 buffer[0] = '\0';
 init_matrix();
 clear();
 element = 'b';
	print_border_menu(2, 2, dimx+2, dimy+2); // IZMENA // screen dimensions
 while (1){
  if (!main_menu(0)) { delete_menu(55, 95, 67, 120); delete_menu(47, 95, 67, 130); return; } // enter the menu
  tru = 1;
  n_undo = n_redo = 0;
  undo = (map*)calloc(1, sizeof(map));
  redo = (map*)calloc(1, sizeof(map));
  buttons();
  yd = yu = 32;
  xd = xu = 32;
  what_to_print(yu, xu, yd, xd, element);
  while (tru){
    
   switch (getch()){ // kretanje po mapi i cuvanje elementa na mapi// biranje elementa//menjanje dimenzija elementa
   case KEY_UP:    if (lvl_can_move(yu, xu, yd, xd, 1))  move_up2x2(yu--, xu, yd--, xd);        break;
   case KEY_DOWN:   if (lvl_can_move(yu, xu, yd, xd, 2))  move_down2x2(yu++, xu, yd++, xd);       break;
   case KEY_LEFT: if (lvl_can_move(yu, xu, yd, xd, 3))  move_left2x2(yu, xu--, yd, xd--);       break;
   case KEY_RIGHT:if (lvl_can_move(yu, xu, yd, xd, 4))  move_right2x2(yu, xu++, yd, xd++);       break;
   case ' ': PlaySound(TEXT("Sound\\select.wav"),NULL, SND_ASYNC); PUSH_unredo(&undo, &n_undo);  save_in_matrix(yu, xu, yd, xd, element);         break;                 break;
   case ESC: PlaySound(TEXT("Sound\\select.wav"),NULL, SND_ASYNC); tru = 0;                         break;
   case 'R': case 'r': size_resize(&yu, &xu, &yd, &xd);                break;
   case 'B': case 'b': print_brick_lvl(yu, xu, yd, xd); element = 'b';             break;
   case 'G': case 'g': print_grass_lvl(yu, xu, yd, xd); element = 'g';             break;
   case 'W': case 'w': print_water_lvl(yu, xu, yd, xd); element = 'w';             break;
   case 'C': case 'c': print_wall_lvl(yu, xu, yd, xd); element = 'c';             break;
   case 'E': case'e':  element = 'e';  print_eraser(yu, xu, yd, xd);             break;
   case 'S': case 's': if (buffer[0] != '\0') save_it(); else  if(save_map()) tru = 0;         break;
   case 'z':case 'Z': _undo_redo(&undo, &redo, &n_undo, &n_redo);  what_to_print(yu, xu, yd, xd, element);   break;
   case 'x': case 'X': _undo_redo(&redo, &undo, &n_redo, &n_undo);  what_to_print(yu, xu, yd, xd, element);   break;
   }
  }
  destroy_undo_redo(&undo, &redo, n_redo, n_undo);
  delete_menu(47, 95, 67, 130);
 }
}
