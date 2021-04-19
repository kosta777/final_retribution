#include "tank.h"




int blocked_areas(int yu, int xu, int yd, int xd)
{
	int i;
	for (; yu <= yd; yu++)
		for (i = xd; i <= xu; i++)
		{
		if ((yu >= baseY) && ((i >= baseX1) && (i <= baseX2))) return 1;
		else
			if (((yu >= spawn1Y1) && (yu <= spawn1Y2)) && ((i >= spawn1X1) && (i <= spawn1X2))) return 1;
			else
				if (((yu >= spawn1Y1) && (yu <= spawn1Y2)) && ((i >= spawn2X1) && (i <= spawn2X2))) return 1;
				else
					if (((yu >= spawn1Y1) && (yu <= spawn1Y2)) && ((i >= spawn3X1) && (i <= spawn3X2))) return 1;
					else
						if (((yu >= bspawnY1) && (yu <= bspawnY2)) && ((i >= bspawnX1) && (i <= bspawnX2))) return 1;

		}
	return 0;
}
int lvl_can_move(int yu, int xu, int yd, int xd, int num){
	switch (num){
	case 1: if (((yu - 1) == 2)||(blocked_areas(yu-1,xu,yd-1,xd))) return 0; else return 1; break; // up
	case 2: if (((yd + 1) == (dimx + 2)) || blocked_areas(yu+1,xu,yd+1,xd)) return 0; else return 1; break; // down
	case 3: if (((xd - 1) == 2)|| (blocked_areas(yu,xu-1,yd,xd-1))) return 0; else return 1; break; //left
	case 4: if (((xu + 1) == (dimy + 2))||(blocked_areas(yu,xu+1,yd,xd+1))) return 0; else return 1; break; // right
	}
}  // ispituje mogucnost kretanje u zadatom smeru(zidovi mape ogranicavaju kretanje)

void move_up2x2(int yu, int xu, int yd, int xd){
	int i, j;
	for (j = yd, i = xd; i <= xu; i++)
		what_to_print(j, i, j, i, lvl_matrix[j - 3][i - 3]);
	for (j = yu - 1, i = xd; i <= xu; i++)
		what_to_print(j, i, j, i, element);
	refresh();

}

void move_right2x2(int yu, int xu, int yd, int xd){
	int i, j;

	for (j = yu, i = xd; j <= yd; j++){
		what_to_print(j, i, j, i, lvl_matrix[j - 3][i - 3]);
	}
	for (j = yu, i = xu + 1; j <= yd; j++)
		what_to_print(j, i, j, i, element);
	refresh();
}

void move_down2x2(int yu, int xu, int yd, int xd)
{
	int i, j;
	for (j = yu, i = xd; i <= xu; i++){
		what_to_print(j, i, j, i, lvl_matrix[j - 3][i - 3]);
	}
	for (j = yd + 1, i = xd; i <= xu; i++){
		what_to_print(j, i, j, i, element);
	}
	refresh();
}

void move_left2x2(int yu, int xu, int yd, int xd)
{
	int i, j;
	for (i = xu, j = yu; j <= yd; j++)
		what_to_print(j, i, j, i, lvl_matrix[j - 3][i - 3]);
	for (i = xd - 1, j = yu; j <= yd; j++)
		what_to_print(j, i, j, i, element);
	refresh();
}

void expand_y(int *yu, int xu, int *yd, int xd)
{
	int i, j;
	if ((*yd - *yu) == 16) return;
	--(*yu); ++(*yd);
	for (j = *yu, i = xd; i <= xu; i++){
		what_to_print(j, i, j, i, element);
		what_to_print(*yd, i, *yd, i, element);
	}
	refresh();
} // uvecaj po visni

void reduce_y(int *yu, int xu, int *yd, int xd)
{
	int i, j;
	if (*yu == *yd) return;
	attron(COLOR_BLACK);
	for (i = *yu, j = xd; j <= xu; j++){
		what_to_print(*yu, j, *yu, j, lvl_matrix[i - 3][j - 3]);
		what_to_print(*yd, j, *yd, j, lvl_matrix[*yd - 3][j - 3]);
	}
	(*yu)++;
	(*yd)--;
	attroff(COLOR_BLACK);
	refresh();
}  // smanji po visini

void reduce_x(int yu, int *xu, int yd, int *xd)
{
	int i;
	if (*xd == *xu) return;
	attron(COLOR_BLACK);
	for (i = yu; i <= yd; i++){
		what_to_print(i, *xd, i, *xd, lvl_matrix[i - 3][*xd - 3]);
		what_to_print(i, *xu, i, *xu, lvl_matrix[i - 3][*xu - 3]);
	}
	++(*xd);
	--(*xu);
	attroff(COLOR_BLACK);
	refresh();
}  // smanji po duzini

void expand_x(int yu, int *xu, int yd, int *xd){
	int i;
	if ((*xu - *xd) == 16) return;
	++(*xu); --(*xd);
	for (i = yu; i <= yd; i++){
		what_to_print(i, *xu, i, *xu, element);
		what_to_print(i, *xd, i, *xd, element);
	}
	refresh();
} // uvecaj po duzini

void menu_up(int *mv, int limit, int *ind, int from, int mainm){
	int i;
	if (*mv == limit) return;
	*mv = *mv - 2;
	attron(COLOR_PAIR(8)| A_BOLD);
	if(mainm) mvprintw(*mv, from, meni[--(*ind)]); //koji meni printa
	else mvprintw(*mv, from, lvl_meni[--(*ind)]);
	attroff(COLOR_PAIR(8)| A_BOLD);
	if(mainm) mvprintw(*mv + 2, from, meni[*ind + 1]);
	else mvprintw(*mv + 2, from, lvl_meni[*ind + 1]);
	refresh();
} // kretanje po meniju

void menu_down(int *mv, int limit, int *ind, int from, int mainm){
	int i;
	if (*mv == limit) return;
	*mv = *mv + 2;
	attron(COLOR_PAIR(8)| A_BOLD);
	if(mainm) mvprintw(*mv, from, meni[++(*ind)]);
	else mvprintw(*mv, from, lvl_meni[++(*ind)]);
	attroff(COLOR_PAIR(8)| A_BOLD);
	if(mainm) mvprintw(*mv - 2, from, meni[*ind - 1]);
	else mvprintw(*mv - 2, from, lvl_meni[*ind - 1]);
	refresh();
} // kretanje po meniju

void size_resize(int *yu, int *xu, int *yd, int *xd){
	while (1){
		switch (getch()){
		case KEY_UP: if (lvl_can_move(*yu, *xu, *yd, *xd, 1) && lvl_can_move(*yu, *xu, *yd, *xd, 2)) expand_y(yu, *xu, yd, *xd);   break;
		case KEY_DOWN: reduce_y(yu, *xu, yd, *xd); break;
		case KEY_LEFT: reduce_x(*yu, xu, *yd, xd); break;
		case KEY_RIGHT: if (lvl_can_move(*yu, *xu, *yd, *xd, 3) && lvl_can_move(*yu, *xu, *yd, *xd, 4)) expand_x(*yu, xu, *yd, xd); break;
		case 'r': case 'R': return; break;
		}
	}
}

void destroy_undo_redo(map** undo, map **redo, int n_redo, int n_undo){
	if ((!redo[0]) && (!undo[0])) return;
	free(redo[0]);
	free(undo[0]);
}


void copy_matrix(map** unredo, int n_unredo){
	int i, j;
	for (i = 0; i < 65; i++)
		for (j = 0; j < 90; j++){
		unredo[0][n_unredo].mapa[i][j] = lvl_matrix[i][j];
		}
}

void PUSH_unredo(map** unredo, int* n_unredo){
	int max = 30, i;
	if (!unredo[0]) return;
	if (*n_unredo == max) {
		for (i = 0; i <= (*n_unredo - 2); i++) unredo[0][i] = unredo[0][i + 1];
		--*n_unredo;
	}

	copy_matrix(unredo, *n_unredo);
	++*n_unredo;
	unredo[0] = (map*)realloc(unredo[0], (*n_unredo + 1)*sizeof(map));
}

int POP(map** unredo, int* n_unredo){
	int i = 0, j = 0;
	if (*n_unredo == 0) return 0;
	--(*n_unredo);
	unredo[0] = (map*)realloc(unredo[0], (*n_unredo + 2)*sizeof(map));
	return 1;
}


void _undo_redo(map** pop, map** push, int* n_pop, int* n_push){
	int i, j;
	if (!POP(pop, n_pop)) return;
	PUSH_unredo(push, n_push);
	for (i = 0; i < 65; i++)
		for (j = 0; j < 90; j++)
			lvl_matrix[i][j] = pop[0][*n_pop].mapa[i][j];
	print_matrix();

}