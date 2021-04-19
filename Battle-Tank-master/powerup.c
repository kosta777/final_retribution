#include "tank.h"

void init_powerups(){
	powerup.life = 2;
	powerup.bomb = 0;
	powerup.star = 0;
	powerup.clock = 0;
	powerup.shovel = 0;
	powerup.shield = 0;
}

void update_powerups(char pw){
	PlaySound(TEXT("Sound\\powerup.wav"),NULL, SND_ASYNC);
	switch (pw){
	case 'l': powerup.life++;							break;
	case 'q': powerup.bomb = 1;							break;
	case 's': if(powerup.star<3) powerup.star++;		break;
	case 'a': powerup.clock = 1;						break;
	case 'y': powerup.shovel = 1;						break;
	case 'x': powerup.shield = 1;						break;
	}
}

int check_powerups(int y, int x, int a){
	int i;
	Powerup_list * temp;
	int flag[3]={ 0, 0 ,0};
	switch (a){
	case 1: 
		for (i = 0; i < 6; i++){
			if (matrix[y - y1b - 2][x - x1b - 1] == pUps[i]) {
				flag[0]=1;// negde da ubacimo brisanje powerupa.
			}
			else if ((matrix[y - y1b - 2][x - x1b - 1] == ' ') || (matrix[y - y1b - 2][x - x1b - 1] == 'g')) flag[0]=1;
			if	(matrix[y - y1b - 2][x - x1b] == pUps[i]){
				flag[1]=1; // negde da ubacimo brisanje powerupa.
			}
			else if ((matrix[y - y1b - 2][x - x1b] == ' ') || (matrix[y - y1b - 2][x - x1b] == 'g')) flag[1]=1;
			if	(matrix[y - y1b - 2][x - x1b + 1] == pUps[i]){
				flag[2]=1;// negde da ubacimo brisanje powerupa.
			}
			else if ((matrix[y - y1b - 2][x - x1b + 1] == ' ') || (matrix[y - y1b - 2][x - x1b + 1] == 'g')) flag[2]=1;
		} 
		for(i=0;i<=2; i++) if(flag[i]==0) return 0;
		for (i = 0; i < 6; i++){
			if (matrix[y - y1b - 2][x - x1b - 1] == pUps[i]) {
				if(lst->curr==lst->first) update_powerups(pUps[i]);
				temp=which_powerup(y-2,x-1);
				free_powerup(temp); 
				// negde da ubacimo brisanje powerupa.
			}

			if	(matrix[y - y1b - 2][x - x1b] == pUps[i]){
				if(lst->curr==lst->first) update_powerups(pUps[i]);
				temp=which_powerup(y-2,x);
				free_powerup(temp);
		 // negde da ubacimo brisanje powerupa.
			}

			if	(matrix[y - y1b - 2][x - x1b + 1] == pUps[i]){
				if(lst->curr==lst->first) update_powerups(pUps[i]);
				temp=which_powerup(y-2,x+1);
				free_powerup(temp); 
				// negde da ubacimo brisanje powerupa.
			}

		} 
		return 1;
	case 2:
		for (i = 0; i < 6; i++){
		if (matrix[y - y1b - 1][x - x1b - 2] == pUps[i]) {
				flag[0]=1;// negde da ubacimo brisanje powerupa.
			}
		else if ((matrix[y - y1b - 1][x - x1b - 2] == ' ') || (matrix[y - y1b - 1][x - x1b - 2] == 'g')) flag[0]=1;
			if	(matrix[y - y1b][x - x1b - 2] == pUps[i]){
				
				flag[1]=1; // negde da ubacimo brisanje powerupa.
			}
			else if ((matrix[y - y1b][x - x1b - 2] == ' ') || (matrix[y - y1b][x - x1b - 2] == 'g')) flag[1]=1;
			if	(matrix[y - y1b + 1][x - x1b - 2] == pUps[i]){
				flag[2]=1;// negde da ubacimo brisanje powerupa.
			}
			else if ((matrix[y - y1b + 1][x - x1b - 2] == ' ') || (matrix[y - y1b + 1][x - x1b - 2] == 'g')) flag[2]=1;
	}
	for(i=0;i<=2; i++) if(flag[i]==0) return 0;
	for (i = 0; i < 6; i++){
		if (matrix[y - y1b - 1][x - x1b - 2] == pUps[i]) {
				if(lst->curr==lst->first) update_powerups(pUps[i]);
				temp=which_powerup(y-1,x-2);
				free_powerup(temp); 
			}
			if	(matrix[y - y1b][x - x1b - 2] == pUps[i]){
				if(lst->curr==lst->first) update_powerups(pUps[i]);
				temp=which_powerup(y,x-2);
				free_powerup(temp);
			}
			if	(matrix[y - y1b + 1][x - x1b - 2] == pUps[i]){
				if(lst->curr==lst->first) update_powerups(pUps[i]);
				temp=which_powerup(y+1,x-2);
				free_powerup(temp);	
			}
	}
	return 1;
	case 3:
		for (i = 0; i < 6; i++){
		
			if (matrix[y - y1b - 1][x - x1b + 2] == pUps[i]) {
				flag[0]=1; // negde da ubacimo brisanje powerupa.
			}
		else if ((matrix[y - y1b - 1][x - x1b + 2] == ' ') || (matrix[y - y1b - 1][x - x1b + 2] == 'g')) flag[0]=1;
			
		if	(matrix[y - y1b][x - x1b + 2] == pUps[i]){
				flag[1]=1;// negde da ubacimo brisanje powerupa.
			}
			else if ((matrix[y - y1b][x - x1b + 2] == ' ') || (matrix[y - y1b][x - x1b + 2] == 'g')) flag[1]=1;
			
			if	(matrix[y - y1b + 1][x - x1b + 2] == pUps[i]){
				flag[2]=1; // negde da ubacimo brisanje powerupa.
			}
			else if ((matrix[y - y1b + 1][x - x1b + 2] == ' ') || (matrix[y - y1b + 1][x - x1b + 2] == 'g')) flag[2]=1;
	} 
		for(i=0;i<=2; i++) if(flag[i]==0) return 0;
			for (i = 0; i < 6; i++){
		
			if (matrix[y - y1b - 1][x - x1b + 2] == pUps[i]) {
				if(lst->curr==lst->first) update_powerups(pUps[i]);
				temp=which_powerup(y-1,x+2);
				free_powerup(temp); // negde da ubacimo brisanje powerupa.
			}
			if	(matrix[y - y1b][x - x1b + 2] == pUps[i]){
				if(lst->curr==lst->first) update_powerups(pUps[i]);
				temp=which_powerup(y,x+2);
				free_powerup(temp); // negde da ubacimo brisanje powerupa.
			}
			if	(matrix[y - y1b + 1][x - x1b + 2] == pUps[i]){
				if(lst->curr==lst->first) update_powerups(pUps[i]);
				temp=which_powerup(y+1,x+2);
				free_powerup(temp);
			}
	} 
	return 1;
	case 4:
		for (i = 0; i < 6; i++){
			if (matrix[y - y1b + 2][x - x1b - 1] == pUps[i]) {
				flag[0]=1;// negde da ubacimo brisanje powerupa.
			}
			else if ((matrix[y - y1b + 2][x - x1b - 1] == ' ') || (matrix[y - y1b + 2][x - x1b - 1] == 'g')) flag[0]=1;
			if	(matrix[y - y1b + 2][x - x1b] == pUps[i]){
				flag[1]=1;// negde da ubacimo brisanje powerupa.
			}
			else if ((matrix[y - y1b + 2][x - x1b] == ' ') || (matrix[y - y1b + 2][x - x1b] == 'g')) flag[1]=1;
			if	(matrix[y - y1b + 2][x - x1b + 1] == pUps[i]){
				flag[2]=1;// negde da ubacimo brisanje powerupa.
			}
			else if ((matrix[y - y1b + 2][x - x1b + 1] == ' ') || (matrix[y - y1b + 2][x - x1b + 1] == 'g')) flag[2]=1;
		}	 
		for(i=0;i<=2; i++) if(flag[i]==0) return 0;
		for (i = 0; i < 6; i++){
			if (matrix[y - y1b + 2][x - x1b - 1] == pUps[i]) {
				if(lst->curr==lst->first) update_powerups(pUps[i]);
				temp=which_powerup(y+2,x-1);
				free_powerup(temp);
			}
			if	(matrix[y - y1b + 2][x - x1b] == pUps[i]){
				if(lst->curr==lst->first) update_powerups(pUps[i]);
				temp=which_powerup(y+2,x);
				free_powerup(temp);
			}
			if	(matrix[y - y1b + 2][x - x1b + 1] == pUps[i]){
				if(lst->curr==lst->first) update_powerups(pUps[i]);
				temp=which_powerup(y+2,x+1);
				free_powerup(temp);
			}
		}	
		return 1;
	}
}

void execute_powerups(clock_t *pw_shield_start, clock_t *pw_clock_start, clock_t *pw_shovel_start, unsigned long int*random_pup_gen){
	int i, j, check, x, y;
	List *current,*temp;
	(*random_pup_gen)++;
	if (*random_pup_gen == 700000) *random_pup_gen = 0, rand_pup_gen();
	if (powerup.bomb){
		PlaySound(TEXT("Sound\\bomb.wav"),NULL, SND_ASYNC);
		for (current = lst->first->next; current != NULL; ){
			check=0;
			for (i = 0; i < 3; i++) // proverava da li je u travi.
				for (j = 0; j < 3; j++)
					if(current->tankAll.tank.visit_grass[i][j])
					{ check = 1; break; }
			if (!check){
				temp=current; 
				current=current->next;
				free_tank(temp);
			}// ako nije u travi brise ga.
			else current=current->next;
		}
		powerup.bomb = 0;
	}

	if (powerup.clock){ // if unutar delay-a za botove, ali to cu promeniti kad dodju normalni.
		if (powerup.clock == 1){
			*pw_clock_start = clock();
			powerup.clock = 2;
			for (current = lst->first->next; current != NULL; current = current->next)
			current->tankAll.tank.phase = 5;
		}
		if (((clock()-*pw_clock_start)*1000/CLOCKS_PER_SEC) >  PW_DURATION){
			for (current = lst->first->next; current != NULL; current = current->next)
				current->tankAll.tank.phase = 2;
			powerup.clock = 0;
		}	
	}

	if (powerup.shovel){
		if (powerup.shovel == 1){
			*pw_shovel_start = clock();
			x = 41;
			for (y = 62; y < 67; y++) print_wall(y, x);
			x = 49;
			for (y = 62; y < 67; y++) print_wall(y, x);
			y = 62;
			for (x = 41; x < 50; x++) print_wall(y, x);
			refresh();

			powerup.shovel = 2;
		}
		if (((clock() - *pw_shovel_start) * 1000 / CLOCKS_PER_SEC) > PW_DURATION * 2){ // konstanta! PW_DURATION
			x = 41;
			for (y = 62; y < 67; y++) print_head(y, x);
			x = 49;
			for (y = 62; y < 67; y++) print_head(y, x);
			y = 62;
			for (x = 41; x < 50; x++) print_head(y, x);
			refresh();
			powerup.shovel = 0;
		}
	
	}
	
	if (powerup.shield){ // imam if u funkciji collision: if (!((temp == lst->first) && powerup.shield)) free_tank(temp);
		if (powerup.shield == 1){
			*pw_shield_start = clock();
			powerup.shield = 2;
		}
		if (((clock()-*pw_shield_start)*1000/CLOCKS_PER_SEC) >  PW_DURATION){
			powerup.shield = 0;
		}
	}
}

int stars()
{
	switch(powerup.star){
	case 0: return 1;
	case 1: return 2;
	case 2: case 3: return 4;
	}
}

void alloc_powerup(chtype type, int y, int x)
{
	Powerup_list* novi;
	novi=(Powerup_list *) malloc (sizeof(Powerup_list));
	novi->next=NULL;
	if(Plst->first==NULL) Plst->first=novi;
	else Plst->last->next=novi;
	Plst->last=novi;
	novi->info.type=type;
	novi->info.position_y=y;
	novi->info.position_x=x;
}

void free_powerup(Powerup_list* curr)
{
	Powerup_list* temp=Plst->first, *prev = NULL;
	int i,j;
	while (temp != curr){
		prev = temp;
		temp = temp->next;
	}
	if (!prev) Plst->first = curr->next;
	else prev->next = curr->next;
	if (curr == Plst->last) Plst->last = prev;
	for (j = (curr->info.position_y - 1); j < (curr->info.position_y + 2); j++){
		for (i = (curr->info.position_x - 1); i < (curr->info.position_x + 2); i++){
			matrix[j - 2][i - 2] = ' ';
			print_blanko(j,i);
		}
	}
	free(curr);
}

Powerup_list * which_powerup(int y, int x){
	Powerup_list * temp=Plst->first;
	while(temp!=NULL){
		if ((y == temp->info.position_y || y == temp->info.position_y + 1 || y == temp->info.position_y - 1) && (x == temp->info.position_x|| x == temp->info.position_x + 1 || x == temp->info.position_x - 1)) return temp;
		temp=temp->next;
	}
}


void delete_powerup_list()
{
	Powerup_list * temp;
	while(Plst->first){
		temp=Plst->first;
		Plst->first=Plst->first->next;
		free(temp);
	}
}
