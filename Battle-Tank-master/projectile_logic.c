#include "tank.h"

void projectile(int y, int x, int projectil_dir){
	// Global: Coordinates of projectile, var for delay, phase of projectile, last object for projectile[pridx].
	struct timeb vreme;
	ftime(&vreme);
	if (lst->curr->tankAll.projectile[pridx].phase == 1) // prvo postavljanje checka na 1, samo taj put ulazi u petlju
	{
		switch (projectil_dir){       //definisanje pocetnog mesta na kome je cevka
		case 1:  lst->curr->tankAll.projectile[pridx].position.y = y - 1;   lst->curr->tankAll.projectile[pridx].position.x = x;      break;
		case 2:	 lst->curr->tankAll.projectile[pridx].position.y = y;       lst->curr->tankAll.projectile[pridx].position.x = x - 1;  break;
		case 3:	 lst->curr->tankAll.projectile[pridx].position.y = y;       lst->curr->tankAll.projectile[pridx].position.x = x + 1;  break;
		case 4:  lst->curr->tankAll.projectile[pridx].position.y = y + 1;   lst->curr->tankAll.projectile[pridx].position.x = x;      break;
		}
		lst->curr->tankAll.projectile[pridx].pp = lst->curr->tankAll.projectile[pridx].mm = vreme.millitm;
	}
	else lst->curr->tankAll.projectile[pridx].mm = vreme.millitm;
	if (delay_s(40, lst->curr->tankAll.projectile[pridx].mm, lst->curr->tankAll.projectile[pridx].pp, lst->curr->tankAll.projectile[pridx].phase)) { //u prvoj inicijalizaciji last object saljemo bez inicijalizacije jer ga ne koristimo
		lst->curr->tankAll.projectile[pridx].last_object = move_projectile(projectil_dir);
		if (lst->curr->tankAll.projectile[pridx].phase == 1) if (lst->curr->tankAll.projectile[pridx].last_object != 't') {
			lst->curr->tankAll.projectile[pridx].phase = 2;// u prvom pozivu check ce preci u 2->stanje leta
		}
		ftime(&vreme);
		lst->curr->tankAll.projectile[pridx].pp = lst->curr->tankAll.projectile[pridx].mm = vreme.millitm;
	}
}

char move_projectile(int projectil_dir) //vraca nam poslednji objekat na putu u slucaju da treba da ga vratimo posle prolaska metka.
/*Global: - delete_projectile: Coordinates of projectile, last object
- can_fly: Coordinates of projectile
- print_projectile: Coordinates of projectile
- collision: Coordinates of projectile
phase of projectile*/
{
	barrier object;
	if (lst->curr->tankAll.projectile[pridx].phase == 2){
		delete_projectile(lst->curr->tankAll.projectile[pridx].position.y, lst->curr->tankAll.projectile[pridx].position.x, lst->curr->tankAll.projectile[pridx].last_object);
		refresh();
	}
	//if (lst->curr->tankAll.projectile[pridx].phase == 1) lst->curr->tankAll.projectile[pridx].phase = 2; //ako je metak bio u letu brisi ga

	switch (projectil_dir){ //switch za stranu u koju metak treba da leti.

	case 1:
		object = can_fly(lst->curr->tankAll.projectile[pridx].position.y - 1, lst->curr->tankAll.projectile[pridx].position.x);
		switch (object.flag)  // switch za povratnu vrednost can_fly, 1 naisao na prazno polje, 0 nestaje metak ostale vrednosti metak leti ali se ne printa(trava)
		{
		case 1: print_projectile(--lst->curr->tankAll.projectile[pridx].position.y, lst->curr->tankAll.projectile[pridx].position.x, object.obs); break;
		case 0: collision(lst->curr->tankAll.projectile[pridx].position.y - 1, lst->curr->tankAll.projectile[pridx].position.x, projectil_dir, object.obs);
			lst->curr->tankAll.projectile[pridx].phase = 0; break;
		case 2: --lst->curr->tankAll.projectile[pridx].position.y; break; //ako naidje na travu samo pomeri metak ali ga ne ispisuj!
		}
		return object.obs;
		break;

	case 2:
		object = can_fly(lst->curr->tankAll.projectile[pridx].position.y, lst->curr->tankAll.projectile[pridx].position.x - 1);
		switch (object.flag)
		{
		case 1: print_projectile(lst->curr->tankAll.projectile[pridx].position.y, --lst->curr->tankAll.projectile[pridx].position.x, object.obs); break;
		case 0: collision(lst->curr->tankAll.projectile[pridx].position.y, lst->curr->tankAll.projectile[pridx].position.x - 1, projectil_dir, object.obs);
			lst->curr->tankAll.projectile[pridx].phase = 0; break;
		case 2: --lst->curr->tankAll.projectile[pridx].position.x; break;
		}
		return object.obs;
		break;
	case 3:
		object = can_fly(lst->curr->tankAll.projectile[pridx].position.y, lst->curr->tankAll.projectile[pridx].position.x + 1);
		switch (object.flag)
		{
		case 1: print_projectile(lst->curr->tankAll.projectile[pridx].position.y, ++lst->curr->tankAll.projectile[pridx].position.x, object.obs); break;
		case 0: collision(lst->curr->tankAll.projectile[pridx].position.y, lst->curr->tankAll.projectile[pridx].position.x + 1, projectil_dir, object.obs);
			lst->curr->tankAll.projectile[pridx].phase = 0; break;
		case 2: ++lst->curr->tankAll.projectile[pridx].position.x;  break;
		}
		return object.obs;
		break;

	case 4:
		object = can_fly(lst->curr->tankAll.projectile[pridx].position.y + 1, lst->curr->tankAll.projectile[pridx].position.x);
		switch (object.flag)
		{
		case 1: print_projectile(++lst->curr->tankAll.projectile[pridx].position.y, lst->curr->tankAll.projectile[pridx].position.x, object.obs); break;
		case 0: collision(lst->curr->tankAll.projectile[pridx].position.y + 1, lst->curr->tankAll.projectile[pridx].position.x, projectil_dir, object.obs);
			lst->curr->tankAll.projectile[pridx].phase = 0; break;
		case 2: ++lst->curr->tankAll.projectile[pridx].position.y; break;
		}
		return object.obs;
		break;
	}
	refresh();
	object.obs=' ';
	return object.obs;
}

barrier can_fly(int y, int x)
{
	barrier ret;
	List * temp;
	int i;//return
	ret.obs = matrix[y - y1b][x - x1b];
	switch (ret.obs){
	case ' ': case 'w':
		ret.flag = 1;
		break;
	case 'g':
		ret.flag = 2;
		break;
	case 'b': case 'e': case 'c': case 't': case 'x': case 'h': case 'l': case 's': case 'q': case 'a': case 'y':
		ret.flag = 0;
		break;
	case '*':
		temp = NULL;
		for (i = 0; i<4; i++) { if (lst->first->tankAll.projectile[i].phase == 2) if ((y == lst->first->tankAll.projectile[i].position.y) && (x == lst->first->tankAll.projectile[i].position.x)) temp = lst->first; }
		if (temp == lst->first && lst->first == lst->curr){
			ret.obs = 't';
			ret.flag = 3;
			break;      //brute force
		}
		else
			ret.flag = 0;
		break;
	}
	return ret;
	// I jos za tenkove, projektile i ostale stvari.
}

void collision(int y, int x, int projectil_dir, char object){ // saljes mi koordinate udara.
	List *temp,*currcopy;
	Powerup_list * pom;
	int pridxcopy, i, j;
	switch (object){
	case 'b':
		switch (projectil_dir){
		case 1://up 
			if (matrix[y - y1b][x - x1b - 1] == 'b' && (matrix[y - y1b + 1][x - x1b - 1] != 'b')) print_blanko(y, x - 1);
			if (matrix[y - y1b][x - x1b] == 'b') print_blanko(y, x);
			if (matrix[y - y1b][x - x1b + 1] == 'b' && (matrix[y - y1b + 1][x - x1b + 1] != 'b')) print_blanko(y, x + 1);
			break;
		case 2: // left.
			if ((matrix[y - y1b - 1][x - x1b] == 'b') && (matrix[y - y1b - 1][x - x1b + 1] != 'b')) print_blanko(y - 1, x);
			if (matrix[y - y1b][x - x1b] == 'b') print_blanko(y, x);
			if ((matrix[y - y1b + 1][x - x1b] == 'b') && (matrix[y - y1b + 1][x - x1b + 1] != 'b'))print_blanko(y + 1, x);
			break;
		case 3: //right.
			if ((matrix[y - y1b - 1][x - x1b] == 'b') && (matrix[y - y1b - 1][x - x1b - 1] != 'b')) print_blanko(y - 1, x);
			if (matrix[y - y1b][x - x1b] == 'b') print_blanko(y, x);
			if ((matrix[y - y1b + 1][x - x1b] == 'b') && (matrix[y - y1b + 1][x - x1b - 1] != 'b')) print_blanko(y + 1, x);
			break;
		case 4:
			if ((matrix[y - y1b][x - x1b - 1] == 'b') && (matrix[y - y1b - 1][x - x1b - 1] != 'b')) print_blanko(y, x - 1);
			if (matrix[y - y1b][x - x1b] == 'b') print_blanko(y, x);
			if (matrix[y - y1b][x - x1b + 1] == 'b' && (matrix[y - y1b - 1][x - x1b + 1] != 'b')) print_blanko(y, x + 1);
			break;
		}
		
	
		break;
	case 't':
		temp = which_tank(y, x);
		if ((lst->curr != lst->first) && (temp != lst->first)) break; // friendly-fire
		if (temp == lst->first){
			if (powerup.shield){
				break;
			}
			currcopy=lst->curr;
			lst->curr=lst->first;
			if (powerup.life>1){
				PlaySound(TEXT("Sound\\Unistenje_tenka.wav"), NULL, SND_ASYNC);
				delete_tank(lst->first->tankAll.tank.position.y, lst->first->tankAll.tank.position.x);
				lst->curr=currcopy;
				lst->first->tankAll.tank.position.y = 65;// Pocetne koordinate za nas tenk, zameniti sa konstantama.
				lst->first->tankAll.tank.position.x = 24;
				lst->first->tankAll.tank.position.last_move = 1;
				lst->first->tankAll.tank.position.barrel = 1;
				for(i=0;i<3;i++)
					for(j=0;j<3;j++) 
						lst->first->tankAll.tank.visit_grass[i][j]=0;
				for (i = 0; i<4; i++) {
					if (lst->first->tankAll.projectile[i].phase == 2){
						delete_projectile(lst->first->tankAll.projectile[i].position.y, lst->first->tankAll.projectile[i].position.x, lst->first->tankAll.projectile[i].last_object);
					}
					lst->first->tankAll.projectile[i].phase = 0;
					lst->first->tankAll.projectile[i].last_object = ' ';
				}
				create_tank(1, lst->first->tankAll);
				powerup.life--;
			}
			else{
				PlaySound(TEXT("Sound\\Unistenje_tenka.wav"), NULL, SND_ASYNC);
				delete_tank(lst->first->tankAll.tank.position.y, lst->first->tankAll.tank.position.x);
				lst->curr=currcopy;
				strcpy(map_name, "gameover.map");
				powerup.life--;
				break;
			}
		}
		else free_tank(temp);
		PlaySound(TEXT("Sound\\Unistenje_tenka.wav"), NULL, SND_ASYNC);
		break;
	case 'x': case 'l': case 's': case 'q': case 'a': case 'y':
		pom = which_powerup(y, x);
		free_powerup(pom);
		break;
	case 'c':
		if (lst->curr->tankAll.tank.type == 1 || (lst->curr==lst->first && powerup.star==3)){
			switch (projectil_dir){
			case 1://up 
				if (matrix[y - y1b][x - x1b - 1] == 'c' && (matrix[y - y1b + 1][x - x1b - 1] != 'c')) print_blanko(y, x - 1);
				if (matrix[y - y1b][x - x1b] == 'c') print_blanko(y, x);
				if (matrix[y - y1b][x - x1b + 1] == 'c' && (matrix[y - y1b + 1][x - x1b + 1] != 'c')) print_blanko(y, x + 1);
				break;
			case 2: // left.
				if ((matrix[y - y1b - 1][x - x1b] == 'c') && (matrix[y - y1b - 1][x - x1b + 1] != 'c')) print_blanko(y - 1, x);
				if (matrix[y - y1b][x - x1b] == 'c') print_blanko(y, x);
				if ((matrix[y - y1b + 1][x - x1b] == 'c') && (matrix[y - y1b + 1][x - x1b + 1] != 'c'))print_blanko(y + 1, x);
				break;
			case 3: //right.
				if ((matrix[y - y1b - 1][x - x1b] == 'c') && (matrix[y - y1b - 1][x - x1b - 1] != 'c')) print_blanko(y - 1, x);
				if (matrix[y - y1b][x - x1b] == 'c') print_blanko(y, x);
				if ((matrix[y - y1b + 1][x - x1b] == 'c') && (matrix[y - y1b + 1][x - x1b - 1] != 'c')) print_blanko(y + 1, x);
				break;
			case 4:
				if ((matrix[y - y1b][x - x1b - 1] == 'c') && (matrix[y - y1b - 1][x - x1b - 1] != 'c')) print_blanko(y, x - 1);
				if (matrix[y - y1b][x - x1b] == 'c') print_blanko(y, x);
				if (matrix[y - y1b][x - x1b + 1] == 'c' && (matrix[y - y1b - 1][x - x1b + 1] != 'c')) print_blanko(y, x + 1);
				break;
			}
		}
		break; // za beton, kada budemo imali strukturu.
	case '*':
		pridxcopy = pridx;
		temp = which_projectile(y, x);
		if (lst->curr != temp){
			delete_projectile(temp->tankAll.projectile[pridx].position.y, temp->tankAll.projectile[pridx].position.x, temp->tankAll.projectile[pridx].last_object);
			temp->tankAll.projectile[pridx].phase = 0;
		}// za metak o metak, gledamo razlicite strane i gledamo da li se sudaraju, pazimo na mimoilazenje.
		pridx = pridxcopy;
		break;

	case 'h':
		PlaySound(TEXT("Sound\\Unistenje_tenka.wav"), NULL, SND_ASYNC);
		create_map("gameover.map", 0);
		if(!(!strcmp("gohardorgohome.map",map_name))) Sleep(2300);
		strcpy(map_name, "gameover.map");
		break;
	}

}

List* which_tank(int y, int x){
	List *temp = lst->first;
	int i;
	while (temp){
		if ((y == temp->tankAll.tank.position.y || y == temp->tankAll.tank.position.y + 1 || y == temp->tankAll.tank.position.y - 1) && (x == temp->tankAll.tank.position.x || x == temp->tankAll.tank.position.x + 1 || x == temp->tankAll.tank.position.x - 1)) return temp;
		temp = temp->next;
	}
}

List * which_projectile(int y, int x){
	List *temp = lst->first;
	while (temp){
		if (temp != lst->curr){
			if (temp == lst->first){ for (pridx = 0; pridx<4; pridx++) if (temp->tankAll.projectile[pridx].phase == 2) if ((y == temp->tankAll.projectile[pridx].position.y) && (x == temp->tankAll.projectile[pridx].position.x)) return temp; }
			else { pridx = 0;  if (temp->tankAll.projectile[pridx].phase == 2)  if ((y == temp->tankAll.projectile[0].position.y) && (x == temp->tankAll.projectile[0].position.x)) return temp; }
		}
		temp = temp->next;
	}
}
