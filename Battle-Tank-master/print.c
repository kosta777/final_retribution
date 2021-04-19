#include "tank.h"

void print_brick_lvl(int yu, int xu, int yd, int xd){
	int i;
	attron(COLOR_PAIR(3));
	for (; yu <= yd; yu++){
		for (i = xd; i <= xu; ++i)
			mvaddch(yu, i, ACS_PLUS);
	}
	attroff( COLOR_PAIR(3));
}

void print_grass_lvl(int yu, int xu, int yd, int xd){
	int i;
	attron(COLOR_PAIR(2));
	for (; yu <= yd; yu++){
		for (i = xd; i <= xu; ++i)
			mvaddch(yu, i, ACS_BOARD);
	}
	attroff(COLOR_PAIR(2));
}

void print_water_lvl(int yu, int xu, int yd, int xd){
	int i;
	attron(COLOR_PAIR(12));
	for (; yu <= yd; yu++){
		for (i = xd; i <= xu; ++i)
			mvaddch(yu, i, ACS_BOARD);
	}
	attroff(COLOR_PAIR(12));
}

void print_blanko_lvl(int yu, int xu, int yd, int xd){
	int i;
	attron(COLOR_PAIR(6));
	for (; yu <= yd; yu++){
		for (i = xd; i <= xu; ++i)
			mvaddch(yu, i, ' ');
	}
	attroff(COLOR_PAIR(6));
}

void print_wall_lvl(int yu, int xu, int yd, int xd)
{
	int i;
	attron(COLOR_PAIR(13) | A_BOLD);
	for (; yu <= yd; yu++){
		for (i = xd; i <= xu; ++i)
			mvaddch(yu, i, ACS_PLUS);
	}
	attroff(COLOR_PAIR(13) | A_BOLD);
}

void print_eraser(int yu, int xu, int yd, int xd){
	int i;
	attron(COLOR_WHITE | A_REVERSE);
	for (; yu <= yd; yu++)
	{
		for (i = xd; i <= xu; ++i)
			mvaddch(yu, i, ' ');
	}
	attroff(COLOR_WHITE | A_REVERSE);
	refresh();
}

void print_red_lvl(int yu, int xu,int yd, int xd)
{
	int i;
	attron(COLOR_PAIR(7));
	for (; yu <= yd; yu++)
	{
		for (i = xd; i <= xu; ++i)
			mvaddch(yu, i, ACS_BOARD);
	}
	attroff(COLOR_PAIR(7));
	//matrix[y - y1b][x - x1b] = 'h';
}

void print_blue_lvl(int yu, int xu, int yd, int xd)
{
		int i;
	attron(COLOR_PAIR(14));
	for (; yu <= yd; yu++)
	{
		for (i = xd; i <= xu; ++i)
			mvaddch(yu, i, ACS_BOARD);
	}
	attroff(COLOR_PAIR(14));
//	matrix[y - y1b][x - x1b] = 'h';
}

void print_white_lvl(int yu, int xu, int yd, int xd)
{
	int i;
	attron(COLOR_PAIR(13));
	for (; yu <= yd; yu++)
	{
		for (i = xd; i <= xu; ++i)
			mvaddch(yu, i, ACS_BOARD);
	}
	attroff(COLOR_PAIR(13));
	//matrix[y - y1b][x - x1b] = 'h';
}

void print_head_lvl(int yu, int xu, int yd, int xd)
{
	int i;
	attron(COLOR_PAIR(6));
	for (; yu <= yd; yu++)
	{
		for (i = xd; i <= xu; ++i)
			mvaddch(yu, i, ACS_BOARD | A_BOLD);
		attroff(COLOR_PAIR(6));
	}
}

void what_to_print(int yu, int xu, int yd, int xd, char k)
{ // decides what's going to be shown on the map
	switch (k){
	case 'b': print_brick_lvl(yu, xu, yd, xd );	break;
	case 'w': print_water_lvl(yu, xu, yd, xd );	break;
	case 'g': print_grass_lvl(yu, xu, yd, xd );	break;
	case '.': print_blanko_lvl(yu, xu, yd, xd); break;
	case 'c': print_wall_lvl(yu, xu, yd, xd  );	break;
	case '1': print_red_lvl(yu, xu, yd, xd   );	break;
	case '2': print_blue_lvl(yu, xu, yd, xd  );	break;
	case '3': print_white_lvl(yu, xu, yd, xd );	break;
	case 'h': print_head_lvl(yu, xu, yd, xd  );	break;
	default:  print_eraser(yu, xu, yd, xd    );	break;
	}
}

void print_blocked_areas()
{
	what_to_print(bspawnY1, bspawnX2, bspawnY2, bspawnX1, '2');
	what_to_print(spawn1Y1, spawn1X2, spawn1Y2, spawn1X1, '2');
	what_to_print(spawn1Y1, spawn2X2, spawn1Y2, spawn2X1, '2');
	what_to_print(spawn1Y1, spawn3X2, spawn1Y2, spawn3X1, '2');
}

void print_matrix(){
	int i, j;
	for (i = 3; i < (dimx + 2); i++)
		for (j = 3; j < (dimy + 2); j++){
		what_to_print(i, j, i, j, lvl_matrix[i-3][j-3]);
		}
	print_blocked_areas();
	refresh();
}
