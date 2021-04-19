#include "tank.h"

void save_game(clock_t time_diff, int br){
	int i = 0, j = 122, tru = 1;
	char matrix_copy[dimx + 1][dimy + 1]; 
	char Key, name[100], temp[100],prefix[14], tempcat[100];
	int y1 = 28, x1 = x1m, y2 = 45, x2 = x2m, min = 122, max = 137, flag;
	int y = y1b + 1, x = x1b + 1;
	FILE  *saved_games, *map, *tank, *pup;
	Loaded_level_info info;
	List* currtank;
	Powerup_list * currpup;
	name[0] = '\0';
	delete_menu(y1, x1, y2, x2);
	print_border_menu(y1, x1, y2, x2);// IZMENA
	mvprintw(30,  110, " S A V E  G A M E  A S");
	mvprintw(33,  108, " Game Name :  _______________");
	mvprintw(39, 108, "ESC : Return to pause menu ");
	attron(COLOR_WHITE | A_REVERSE);
	mvprintw(37, 102, " Max. 15 characters(letters & num allowed!)");
	attroff(COLOR_WHITE | A_REVERSE);
	refresh();

	//===================Naming the game====================

	while (tru)
	{

		switch (Key = getch()){
		case KEY_UP: case KEY_DOWN: case KEY_LEFT: case KEY_RIGHT:  break;

		case ENTER: PlaySound(TEXT("Sound\\select.wav"),NULL, SND_ASYNC); if (name[0] == '\0')  name_it();  else  tru = check_if_legit(name); break; // checks if the name is correctly inputted

		default: if (j < max) 
		{ name[i++] = Key; name[i] = '\0'; mvaddch(33, j++, Key); 
		}; refresh(); break;

		case BACKSPACE: if (j > min) 
		{ 
			name[--i] = '\0'; mvaddch(33, --j, '_'); 
		}; refresh(); break;

		case ESC: PlaySound(TEXT("Sound\\select.wav"),NULL, SND_ASYNC);  delete_menu(y1, x1, y2, x2); return; break;


		}
	}
	delete_menu(y1, x1, y2, x2);
	refresh();
	strcat(name,".svg");
	if (!(saved_games = fopen("Saved Games\\saved_games.txt", "r+"))) saved_games = fopen("Saved Games\\saved_games.txt", "w");

	flag=0;
	while (fscanf(saved_games,"%s",temp) != EOF){   // does this map already exist in the file?
		if(!strcmp(name,temp)) { flag=1; break; }
	}
	if(!flag){
		fclose(saved_games);
		saved_games = fopen("Saved Games\\saved_games.txt", "a");
		fprintf(saved_games,"%s\n",name);
	}

	strcpy(prefix,"Saved Games\\");
	//mapa
	strcpy(tempcat,prefix);
	strcat(tempcat,name);
	strcpy(name,tempcat);
	map=fopen(name,"wb");
	//tenkovi
	strcpy(name + strlen(name) - 4,".tnk");
	tank=fopen(name,"wb");
	//power-upovi
	strcpy(name + strlen(name) - 4,".pup");
	pup=fopen(name,"wb");

	info.Lvl=LVL;
	info.Br=br;
	info.time=time_diff;
	info.high_score=HIGH_SCORE;
	//matrica
	for (i = y; i < y2b; i++){
		for (j = x; j<x2b; j++){
			if (matrix[i-y1b][j-x1b] == ' ' || matrix[i-y1b][j-x1b] == '*' || matrix[i-y1b][j-x1b] == 't' || matrix[i-y1b][j-x1b] == 'x' || matrix[i-y1b][j-x1b] == 'l' ||matrix[i-y1b][j-x1b] == 's' ||  matrix[i-y1b][j-x1b] == 'q'||  matrix[i-y1b][j-x1b] == 'a'|| matrix[i-y1b][j-x1b] == 'y' ) 
				matrix_copy[i-y1b][j-x1b]= '.';
			else matrix_copy[i-y1b][j-x1b]=matrix[i-y1b][j-x1b];
		}
		
	}
	for (i = y; i<y2b; i++){
		fwrite(matrix_copy[i - y1b] + x - x1b, sizeof(char), 89, map);
	}

	//sve o tenkovima i nivou
	fwrite(&info, sizeof(Loaded_level_info), 1, tank);
	for(currtank=lst->first; currtank; currtank = currtank->next){
		fwrite(&currtank->tankAll,sizeof(Tank), 1, tank);
	}

	//sve o powerupovima
	for(i=0;i<6;i++){
	switch(i){
	case 0 :	fwrite(&powerup.life,   sizeof(int), 1, pup);  break;
	case 1 :	fwrite(&powerup.bomb,   sizeof(int), 1, pup);  break;
	case 2 :	fwrite(&powerup.star,   sizeof(int), 1, pup);  break;
	case 3 :	fwrite(&powerup.clock,  sizeof(int), 1, pup);  break;
	case 4 :	fwrite(&powerup.shovel, sizeof(int), 1, pup);  break;
	case 5 :	fwrite(&powerup.shield, sizeof(int), 1, pup);  break;
		}
	}
	for(currpup=Plst->first; currpup; currpup = currpup->next){
		fwrite(&currpup->info, sizeof(Powerup_info), 1, tank);
	}
	//

	fclose(map);
	fclose(tank);
	fclose(pup);
	fclose(saved_games);
}

void load_game(char * game_name){
  FILE* tank_list, *pup_list;
  int i, savedpup;
  char tank_dat[100],pup_dat[100],prefix[14],tempcat[100];

  strcpy(prefix,"Saved Games\\");

  strcpy(map_name,game_name);

  create_map(map_name,1);

  strcpy(tank_dat, game_name);
  strcpy(tank_dat + strlen(tank_dat) - 4,".tnk");
  strcpy(pup_dat, game_name);
  strcpy(pup_dat + strlen(pup_dat) - 4,".pup");

  strcpy(tempcat,prefix);
  strcat(tempcat,tank_dat);
  strcpy(tank_dat,tempcat);

  tank_list=fopen(tank_dat,"rb");

  strcpy(tempcat,prefix);
  strcat(tempcat,pup_dat);
  strcpy(pup_dat,tempcat);
  
  pup_list=fopen(pup_dat,"rb");

  fread(&level_info, sizeof(Loaded_level_info), 1, tank_list);
  restaurate_tank_list(tank_list);

  for(i=0;i<6;i++){
	fread(&savedpup, sizeof(int), 1, pup_list);
	switch(i){
	case 0 :	powerup.life = savedpup;   break;
	case 1 :	powerup.bomb = savedpup;   break;
	case 2 :	powerup.star = savedpup;   break;
	case 3 :	powerup.clock = savedpup;  break;
	case 4 :	powerup.shovel = savedpup; break;
	case 5 :	powerup.shield = savedpup; break;
	}
  }
  restaurate_powerup_list(pup_list);

  restaurate_tanks_on_map();
  restaurate_powerups_on_map();
  
  GAME_LOADED=1;
  
  fclose(tank_list);
  fclose(pup_list);
}

void restaurate_tanks_on_map(){
	List *temp=lst->first;
	while(temp){
		create_tank(temp->tankAll.tank.position.barrel,temp->tankAll);
		temp=temp->next;
	}
}

void restaurate_powerups_on_map(){
	chtype pup_characters[6] = { ACS_BLOCK, ACS_PLUS, 187, 164, 162, ACS_DARROW };
	Powerup_list *temp=Plst->first;
	int i,j,k;
	while(temp){
		for(k=0;k<6;k++) if(pUps[k]==temp->info.type) break;
		print_powerup(temp->info.position_y,temp->info.position_x, pup_characters[k],temp->info.type);
		for (j = (temp->info.position_y - 1); j < (temp->info.position_y + 2); j++)
				for (i = (temp->info.position_x - 1); i < (temp->info.position_x + 2); i++)
					matrix[j - 2][i - 2] = temp->info.type;
		temp=temp->next;
	}
}

void restaurate_tank_list(FILE *tank_list){
	Tank currtank;
	List *novi;
	int i;
	lst->n=0;
	lst->first=lst->curr=lst->last=NULL;
	while(fread(&currtank,sizeof(Tank),1,tank_list)==1){
		novi=(List*) malloc ( sizeof(List));
		novi->next=NULL;
		novi->tankAll.tank=currtank;
		if(lst->last==NULL) { 
			lst->first=novi; novi->tankAll.projectile = (Projectile*)malloc(4 * sizeof(Projectile));
			for (i = 0; i<4; i++){ 
				novi->tankAll.projectile[i].phase = 0; 
				novi->tankAll.projectile[i].last_object = ' ';
			}
			lst->first->tankAll.tank.tankDesign_v = novi_tank_v;
			lst->first->tankAll.tank.tankDesign_h = novi_tank_h;
		}
		else { 
			lst->last->next=novi; novi->tankAll.projectile = (Projectile*)malloc(sizeof(Projectile));
			novi->tankAll.projectile[0].phase=0; novi->tankAll.projectile[0].last_object = ' ';
			switch (novi->tankAll.tank.diff){
				case 1:  novi->tankAll.tank.tankDesign_v = normal_tank_v; novi->tankAll.tank.tankDesign_h = normal_tank_h; break;
				case 2:  novi->tankAll.tank.tankDesign_v = brat_tank_v; novi->tankAll.tank.tankDesign_h = brat_tank_h; break;
				case 3:  novi->tankAll.tank.tankDesign_v = special_tank_v; novi->tankAll.tank.tankDesign_h = special_tank_h; break;
				}
		}
		lst->last=novi;
		lst->n++;
	}
}

void restaurate_powerup_list(FILE *pup_list){
	Powerup_info currpup;
	Powerup_list * novi;
	Plst->first=Plst->last=NULL;
	while(fread(&currpup,sizeof(TankAll),1,pup_list)==1){
		novi=(Powerup_list*) malloc (sizeof(Powerup_list));
		novi->next=NULL;
		novi->info=currpup;
		if(lst->last==NULL) Plst->first=novi;
		else Plst->last->next=novi;
		Plst->last=novi;
	}
}
