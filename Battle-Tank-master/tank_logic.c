#include "tank.h"

int free_place(int place){ //place=0 ispitaj sva mesta
	int i, j, k, flag;
	spawn_place splace[3] = { { 4, 20 }, { 4, 56 }, { 4, 72 } };
	if (place == 0){
		for (k = 0; k<3; k++){
			flag = 0;
			for (i = splace[k].y - 1; i <= splace[k].y + 1; i++){
				for (j = splace[k].x - 1; j <= splace[k].x + 1; j++){
					if (matrix[i - y1b][j - x1b] != ' ')
					{
						flag = 1;
						break;
					}
				}
				if (flag) break;
			}
			if (!flag) return k + 1;
		}
		return 0;
	}
	else{
		for (i = splace[place - 1].y - 1; i <= splace[place - 1].y + 1; i++){
			for (j = splace[place - 1].x - 1; j <= splace[place - 1].x + 1; j++){
				if (matrix[i - y1b][j - x1b] != ' ')
				{
					return 0;
				}
			}
		}
		return place;
	}
}

void alloc_tank(int place, Levels tank_struct){ //place=0 za nas tenk
	List *novi;
	int rez;
	spawn_place splace[3] = { { 5, 5 }, { 5, 47 }, { 5, 89 } };
	int i, j;
	novi = (List*)malloc(sizeof(List));
	novi->next = NULL;
	lst->n++;
	if (lst->first == NULL) lst->first = novi;
	else lst->last->next = novi;

	if (place == 0){
		lst->first->tankAll.tank.position.y = 65;// Pocetne koordinate za nas tenk, zameniti sa konstantama.
		lst->first->tankAll.tank.position.x = 38;
		lst->first->tankAll.tank.position.last_move = 1;
		lst->first->tankAll.tank.position.barrel = 1;
		lst->first->tankAll.tank.tankDesign_v = novi_tank_v;
		lst->first->tankAll.tank.tankDesign_h = novi_tank_h;
		lst->first->tankAll.projectile = (Projectile*)malloc(4 * sizeof(Projectile));
		for (i = 1; i<4; i++) { novi->tankAll.projectile[i].phase = 0; novi->tankAll.projectile[i].last_object = ' '; }
	}
	else{
		if (!(rez = free_place(lst->n % 3 + 1)))
		{
			novi->tankAll.tank.position.y = splace[place - 1].y; novi->tankAll.tank.position.x = splace[place - 1].x;
		}
		else { novi->tankAll.tank.position.y = splace[rez - 1].y; novi->tankAll.tank.position.x = splace[rez - 1].x; }
		novi->tankAll.projectile = (Projectile *)malloc(sizeof(Projectile));
		switch (tank_struct.smart){
		case 1:  novi->tankAll.tank.tankDesign_v = normal_tank_v; novi->tankAll.tank.tankDesign_h = normal_tank_h; break;
		case 2:  novi->tankAll.tank.tankDesign_v = brat_tank_v; novi->tankAll.tank.tankDesign_h = brat_tank_h; break;
		case 3:  novi->tankAll.tank.tankDesign_v = special_tank_v; novi->tankAll.tank.tankDesign_h = special_tank_h; break;
		}
		novi->tankAll.tank.position.last_move = 4;
		novi->tankAll.tank.position.barrel = 4;

		if(!(!strcmp(map_name,"gohardorgohome.map"))) delete_bots_left(); // ako se igra demo ne brisi meni
	}
	novi->tankAll.tank.type = tank_struct.kind;
	novi->tankAll.tank.diff = tank_struct.smart;
	lst->last = novi;
	novi->tankAll.tank.phase = 2;
	novi->tankAll.projectile[0].phase = 0;
	novi->tankAll.projectile[0].last_object = ' ';



	for (i = 0; i<3; i++)
		for (j = 0; j<3; j++) novi->tankAll.tank.visit_grass[i][j] = 0;
	create_tank(novi->tankAll.tank.position.barrel, novi->tankAll);

}

void inc_highScore(List *curr){  // !
	switch (curr->tankAll.tank.diff){
	case 1: HIGH_SCORE += 100; break;
	case 2: HIGH_SCORE += 200; break;
	case 3: HIGH_SCORE += 300; break;
	}
	switch (curr->tankAll.tank.type){
	case 0: break;
	case 1: HIGH_SCORE += 75; break;
	}
}

void free_tank(List *curr){
	chtype possibility[6] = { ACS_BLOCK, ACS_PLUS, 187, 164, 162, ACS_DARROW };
	int pos, j, i;
	List *temp = lst->first, *prev = NULL, *lstcurrcopy;
	inc_highScore(curr); // !
	if(!(!strcmp(map_name,"gohardorgohome.map"))) delete_bots_left();
	while (temp && temp != curr){
		prev = temp;
		temp = temp->next;
	}
	if (!prev) lst->first = curr->next;
	else prev->next = curr->next;
	if (curr == lst->last) lst->last = prev;
	lstcurrcopy = lst->curr; // da ne brise travu jer globalnim lst->curr brisemo a taj lst->curr je nas tenk, curr je tenk koji se brise
	lst->curr = curr;
	if (lst->curr->tankAll.projectile[pridx].phase == 2){
		delete_projectile(lst->curr->tankAll.projectile[pridx].position.y, lst->curr->tankAll.projectile[pridx].position.x, lst->curr->tankAll.projectile[pridx].last_object);
		lst->curr->tankAll.projectile[pridx].phase = 0;
		free(lst->curr->tankAll.projectile);
	}
	delete_tank(curr->tankAll.tank.position.y, curr->tankAll.tank.position.x);
	lst->curr = lstcurrcopy;
	if (curr->tankAll.tank.type == 1){ // ako je tenk specijalan
		srand(time(NULL));
		pos = rand() % ((5 + 1));
		alloc_powerup(pUps[pos], curr->tankAll.tank.position.y, curr->tankAll.tank.position.x);
		print_powerup(curr->tankAll.tank.position.y, curr->tankAll.tank.position.x, possibility[pos], pUps[pos]);
		for (j = curr->tankAll.tank.position.y - 1 ; j < (curr->tankAll.tank.position.y + 2); j++)
			for (i = curr->tankAll.tank.position.x - 1; i < (curr->tankAll.tank.position.x + 2); i++)
				matrix[j - y1b][i - x1b] = pUps[pos];
	}
	free(curr);
	lst->n--;
}

void action(int keyPressed, TankAll *current){
	switch (keyPressed)
	{
	case KEY_UP: case 1:  current->tank.position.last_move = 1;
		if (can_move(current->tank.position.y, current->tank.position.x, 1))
			move_tank(--current->tank.position.y, current->tank.position.x, KEY_UP);
		else { delete_tank(current->tank.position.y, current->tank.position.x);  create_tank(1, *current); } refresh(); break;

	case KEY_LEFT: case 2: current->tank.position.last_move = 2;
		if (can_move(current->tank.position.y, current->tank.position.x, 2))
			move_tank(current->tank.position.y, --current->tank.position.x, KEY_LEFT);
		else { delete_tank(current->tank.position.y, current->tank.position.x);  create_tank(2, *current); } refresh(); break;

	case KEY_RIGHT: case 3: current->tank.position.last_move = 3;
		if (can_move(current->tank.position.y, current->tank.position.x, 3))
			move_tank(current->tank.position.y, ++current->tank.position.x, KEY_RIGHT);
		else { delete_tank(current->tank.position.y, current->tank.position.x);  create_tank(3, *current); } refresh(); break;

	case KEY_DOWN: case 4:  current->tank.position.last_move = 4;
		if (can_move(current->tank.position.y, current->tank.position.x, 4))
			move_tank(++current->tank.position.y, current->tank.position.x, KEY_DOWN);
		else { delete_tank(current->tank.position.y, current->tank.position.x);  create_tank(4, *current); } refresh(); break;

	case ' ':
		PlaySound(TEXT("Sound\\Pucanje.wav"),NULL, SND_ASYNC);
		current->projectile[pridx].last_object = 't ';
		current->projectile[pridx].position.projectil_dir = current->tank.position.last_move;
		current->projectile[pridx].phase = 1;
		break;
	}
}

int can_move(int y, int x, int barrel) { // novo. Ubacio sam proveru powerupova. 
	switch (barrel)
	{
	case 1:
		if (((matrix[y - y1b - 2][x - x1b - 1] == ' ') || (matrix[y - y1b - 2][x - x1b - 1] == 'g') || (matrix[y - y1b - 2][x - x1b - 1] == '*')) &&
			((matrix[y - y1b - 2][x - x1b] == ' ') || (matrix[y - y1b - 2][x - x1b] == 'g') || (matrix[y - y1b - 2][x - x1b] == '*')) &&
			((matrix[y - y1b - 2][x - x1b + 1] == ' ') || (matrix[y - y1b - 2][x - x1b + 1] == 'g') || (matrix[y - y1b - 2][x - x1b + 1] == '*'))) return 1;
		else if (check_powerups(y, x, barrel))	return 1;
		else return 0;

	case 2:
		if (((matrix[y - y1b - 1][x - x1b - 2] == ' ') || (matrix[y - y1b - 1][x - x1b - 2] == 'g') || (matrix[y - y1b - 1][x - x1b - 2] == '*')) &&
			((matrix[y - y1b][x - x1b - 2] == ' ') || (matrix[y - y1b][x - x1b - 2] == 'g') || (matrix[y - y1b][x - x1b - 2] == '*')) &&
			((matrix[y - y1b + 1][x - x1b - 2] == ' ') || (matrix[y - y1b + 1][x - x1b - 2] == 'g') || (matrix[y - y1b + 1][x - x1b - 2] == '*'))) return 1;
		else if (check_powerups(y, x, barrel))	return 1;
		else return 0;
	case 3:
		if (((matrix[y - y1b - 1][x - x1b + 2] == ' ') || (matrix[y - y1b - 1][x - x1b + 2] == 'g') || (matrix[y - y1b - 1][x - x1b + 2] == '*')) &&
			((matrix[y - y1b][x - x1b + 2] == ' ') || (matrix[y - y1b][x - x1b + 2] == 'g') || (matrix[y - y1b][x - x1b + 2] == '*')) &&
			((matrix[y - y1b + 1][x - x1b + 2] == ' ') || (matrix[y - y1b + 1][x - x1b + 2] == 'g') || (matrix[y - y1b + 1][x - x1b + 2] == '*'))) return 1;
		else if (check_powerups(y, x, barrel))	return 1;
		else return 0;

	case 4:
		if (((matrix[y - y1b + 2][x - x1b - 1] == ' ') || (matrix[y - y1b + 2][x - x1b - 1] == 'g') || (matrix[y - y1b + 2][x - x1b - 1] == '*')) &&
			((matrix[y - y1b + 2][x - x1b] == ' ') || (matrix[y - y1b + 2][x - x1b] == 'g') || (matrix[y - y1b + 2][x - x1b] == '*')) &&
			((matrix[y - y1b + 2][x - x1b + 1] == ' ') || (matrix[y - y1b + 2][x - x1b + 1] == 'g') || (matrix[y - y1b + 2][x - x1b + 1] == '*'))) return 1;
		else if (check_powerups(y, x, barrel))	return 1;
		else return 0;
	}
}

void move_tank(int y, int x, int mov){
	switch (mov){
	case KEY_UP:    delete_tank(y + 1, x);  create_tank(1, lst->curr->tankAll);  break;
	case KEY_LEFT:  delete_tank(y, x + 1);  create_tank(2, lst->curr->tankAll);  break;
	case KEY_RIGHT: delete_tank(y, x - 1);  create_tank(3, lst->curr->tankAll);  break;
	case KEY_DOWN:  delete_tank(y - 1, x);  create_tank(4, lst->curr->tankAll);  break;
	}
}

void delete_tank_list(){
	List *temp;
	while (lst->first)
	{
		temp = lst->first;
		lst->first = lst->first->next;
		free(temp->tankAll.projectile);
		free(temp);
	}
	lst->last = lst->curr = NULL;
	lst->n = 0;
}
