#include "tank.h"

void init_colors(){
	start_color();
	init_pair(1, COLOR_WHITE, COLOR_BLACK);
	init_pair(2, COLOR_GREEN, COLOR_BLACK);
	init_pair(3, COLOR_YELLOW, COLOR_RED);
	init_pair(4, COLOR_WHITE, COLOR_YELLOW);
	init_pair(5, COLOR_BLACK, COLOR_YELLOW);
	init_pair(6, COLOR_BLACK, COLOR_BLACK);
	init_pair(7, COLOR_RED, COLOR_RED);
	init_pair(8, COLOR_YELLOW, COLOR_BLACK);
	init_pair(9, COLOR_RED, COLOR_YELLOW);
	init_pair(10, COLOR_WHITE, COLOR_BLUE);
	init_pair(11, COLOR_YELLOW, COLOR_BLUE);
	init_pair(12, COLOR_CYAN, COLOR_BLUE);
	init_pair(13, COLOR_WHITE, COLOR_WHITE);
	init_pair(14, COLOR_BLUE, COLOR_BLUE);
	init_pair(15, COLOR_RED, COLOR_BLACK);
	init_pair(16, COLOR_MAGENTA, COLOR_BLACK);
	init_pair(17, COLOR_GREEN, COLOR_YELLOW);
	init_pair(18, COLOR_YELLOW, COLOR_BLACK);
	init_pair(19, COLOR_CYAN, COLOR_BLACK);
	init_pair(20, COLOR_BLUE, COLOR_BLACK);
	init_pair(21, COLOR_RED, COLOR_GREEN);
}

void init_curses(){
	initscr();
	init_colors();
	cbreak();
	noecho();
	keypad(stdscr, TRUE);
	curs_set(0);
	resize_term(70, 150);
}

void print_brick(int y, int x){
	attron(COLOR_PAIR(3));
	mvaddch(y, x, ACS_PLUS);
	attroff(A_BOLD);
	matrix[y - y1b][x - x1b] = 'b';
}

void print_grass(int y, int x){
	attron(COLOR_PAIR(2));
	mvaddch(y, x, ACS_BOARD);
	matrix[y - y1b][x - x1b] = 'g';
}

void print_water(int y, int x){
	attron(COLOR_PAIR(12));
	mvaddch(y, x, ACS_BOARD);
	matrix[y - y1b][x - x1b] = 'w';
}

void print_wall(int y, int x){
	attron(COLOR_PAIR(13));
	mvaddch(y, x, ACS_PLUS | A_BOLD);
	matrix[y - y1b][x - x1b] = 'c';
}

void print_blanko(int y, int x){
	attron(COLOR_PAIR(6));
	mvaddch(y, x, ' ');
	matrix[y - y1b][x - x1b] = ' ';
}

void print_red(int y, int x)
{
	attron(COLOR_PAIR(7));
	mvaddch(y, x, ACS_BOARD);
	matrix[y - y1b][x - x1b] = 'h';
}

void print_blue(int y, int x)
{
	attron(COLOR_PAIR(14));
	mvaddch(y, x, ACS_BOARD);
	matrix[y - y1b][x - x1b] = 'h';
}

void print_white(int y, int x)
{
	attron(COLOR_PAIR(13));
	mvaddch(y, x, ACS_BOARD);
	matrix[y - y1b][x - x1b] = 'h';
}

void print_head(int y, int x)
{
	attron(COLOR_PAIR(6));
	mvaddch(y, x, ACS_BOARD | A_BOLD);
	matrix[y - y1b][x - x1b] = 'h';
}



void print_tank(int y, int x, TankDesign *tank_type, int *position)
{
	if (matrix[y - 1 - y1b][x - 1 - x1b] == 'g') lst->curr->tankAll.tank.visit_grass[0][0] = 1;
	else{
		attron(COLOR_PAIR(tank_type[position[0]].paint));
		mvaddch(y - 1, x - 1, tank_type[position[0]].ch);
	}
	matrix[y - 1 - y1b][x - 1 - x1b] = 't';

	if (matrix[y - 1 - y1b][x - x1b] == 'g') lst->curr->tankAll.tank.visit_grass[0][1] = 1;
	else{
		attron(COLOR_PAIR(tank_type[position[1]].paint));
		mvaddch(y - 1, x, tank_type[position[1]].ch);
	}
	matrix[y - 1 - y1b][x - x1b] = 't';

	if (matrix[y - 1 - y1b][x + 1 - x1b] == 'g') lst->curr->tankAll.tank.visit_grass[0][2] = 1;
	else{
		attron(COLOR_PAIR(tank_type[position[2]].paint));
		mvaddch(y - 1, x + 1, tank_type[position[2]].ch);
	}
	matrix[y - 1 - y1b][x + 1 - x1b] = 't';

	if (matrix[y - y1b][x - 1 - x1b] == 'g') lst->curr->tankAll.tank.visit_grass[1][0] = 1;
	else{
		attron(COLOR_PAIR(tank_type[position[3]].paint));
		mvaddch(y, x - 1, tank_type[position[3]].ch);
	}
	matrix[y - y1b][x - 1 - x1b] = 't';

	if (matrix[y - y1b][x - x1b] == 'g') lst->curr->tankAll.tank.visit_grass[1][1] = 1;
	else{
		attron(COLOR_PAIR(tank_type[position[4]].paint));
		mvaddch(y, x, tank_type[position[4]].ch);
	}
	matrix[y - y1b][x - x1b] = 't';

	if (matrix[y - y1b][x + 1 - x1b] == 'g') lst->curr->tankAll.tank.visit_grass[1][2] = 1;
	else{
		attron(COLOR_PAIR(tank_type[position[5]].paint));
		mvaddch(y, x + 1, tank_type[position[5]].ch);
	}
	matrix[y - y1b][x + 1 - x1b] = 't';

	if (matrix[y + 1 - y1b][x - 1 - x1b] == 'g') lst->curr->tankAll.tank.visit_grass[2][0] = 1;
	else{
		attron(COLOR_PAIR(tank_type[position[6]].paint));
		mvaddch(y + 1, x - 1, tank_type[position[6]].ch);
	}
	matrix[y + 1 - y1b][x - 1 - x1b] = 't';

	if (matrix[y + 1 - y1b][x - x1b] == 'g') lst->curr->tankAll.tank.visit_grass[2][1] = 1;
	else{
		attron(COLOR_PAIR(tank_type[position[7]].paint));
		mvaddch(y + 1, x, tank_type[position[7]].ch);
	}
	matrix[y + 1 - y1b][x - x1b] = 't';

	if (matrix[y + 1 - y1b][x + 1 - x1b] == 'g') lst->curr->tankAll.tank.visit_grass[2][2] = 1;
	else{
		attron(COLOR_PAIR(tank_type[position[8]].paint));
		mvaddch(y + 1, x + 1, tank_type[position[8]].ch);
	}
	matrix[y + 1 - y1b][x + 1 - x1b] = 't';


	refresh();
}

void create_tank(int barrel, TankAll current)
{
	switch (barrel)
	{
	case 1: print_tank(current.tank.position.y, current.tank.position.x, current.tank.tankDesign_v, top);
		break;
	case 2: print_tank(current.tank.position.y, current.tank.position.x, current.tank.tankDesign_h, left);
		break;
	case 3: print_tank(current.tank.position.y, current.tank.position.x, current.tank.tankDesign_h, right);
		break;
	case 4: print_tank(current.tank.position.y, current.tank.position.x, current.tank.tankDesign_v, bottom);
		break;
	}
}

void delete_tank(int y, int x){

	if (!lst->curr->tankAll.tank.visit_grass[0][0]) print_blanko(y - 1, x - 1); //ako je blanko, to znaci da je u visitu 0!print_blanko(y - 1, x - 1);
	else{
		print_grass(y - 1, x - 1);
		lst->curr->tankAll.tank.visit_grass[0][0] = 0;
	}

	if (!lst->curr->tankAll.tank.visit_grass[0][1]) print_blanko(y - 1, x);
	else{
		print_grass(y - 1, x);
		lst->curr->tankAll.tank.visit_grass[0][1] = 0;
	}

	if (!lst->curr->tankAll.tank.visit_grass[0][2]) print_blanko(y - 1, x + 1);
	else{
		print_grass(y - 1, x + 1);
		lst->curr->tankAll.tank.visit_grass[0][2] = 0;
	}

	if (!lst->curr->tankAll.tank.visit_grass[1][0]) print_blanko(y, x - 1);
	else{
		print_grass(y, x - 1);
		lst->curr->tankAll.tank.visit_grass[1][0] = 0;
	}

	if (!lst->curr->tankAll.tank.visit_grass[1][1]) print_blanko(y, x);
	else{
		print_grass(y, x);
		lst->curr->tankAll.tank.visit_grass[1][1] = 0;
	}

	if (!lst->curr->tankAll.tank.visit_grass[1][2]) print_blanko(y, x + 1);
	else{
		print_grass(y, x + 1);
		lst->curr->tankAll.tank.visit_grass[1][2] = 0;
	}

	if (!lst->curr->tankAll.tank.visit_grass[2][0]) print_blanko(y + 1, x - 1);
	else{
		print_grass(y + 1, x - 1);
		lst->curr->tankAll.tank.visit_grass[2][0] = 0;
	}

	if (!lst->curr->tankAll.tank.visit_grass[2][1]) print_blanko(y + 1, x);
	else{
		print_grass(y + 1, x);
		lst->curr->tankAll.tank.visit_grass[2][1] = 0;
	}

	if (!lst->curr->tankAll.tank.visit_grass[2][2]) print_blanko(y + 1, x + 1);
	else{
		print_grass(y + 1, x + 1);
		lst->curr->tankAll.tank.visit_grass[2][2] = 0;
	}

	refresh();
}

void delete_projectile(int y, int x, char last_object)
{
	if (last_object == 'w') print_water(y, x); // umesto if-a moze print object da se pozove on je sam po sebi case
	else if (last_object == ' ') print_blanko(y, x);
}

void print_projectile(int y, int x, char object)
{
	if (object == 'w')  attron(COLOR_PAIR(11)); // ako naidje na vodu
	else if (object == ' ')  attron(COLOR_PAIR(8));
	mvaddch(y, x, ACS_BULLET | A_BOLD);
	matrix[y - y1b][x - x1b] = '*';
}

void print_object(int y, int x, int c){
	switch (c)
	{
	case 'b': print_brick(y, x);   break;
	case 'w': print_water(y, x);   break;
	case 'g': print_grass(y, x);   break;
	case 'c': print_wall(y, x);    break;
	case '1': print_red(y, x);     break;
	case '2': print_blue(y, x);    break;
	case '3': print_white(y, x);   break;
	case 'h': print_head(y, x);    break;
	default:  print_blanko(y, x);  break;
	}
}

void print_border()
{
	int i;
	attron(COLOR_PAIR(10)); // dodaj atribut za boju
	mvaddch(y1b, x1b, ACS_ULCORNER);
	mvaddch(y2b, x1b, ACS_LLCORNER);
	mvaddch(y1b, x2b, ACS_URCORNER);
	mvaddch(y2b, x2b, ACS_LRCORNER);

	matrix[0][0] = 'e';
	matrix[dimx][0] = 'e';
	matrix[0][dimy] = 'e';
	matrix[dimx][dimy] = 'e';
	for (i = y1b + 1; i<y2b; i++)
	{
		mvaddch(i, x1b, ACS_VLINE);
		mvaddch(i, x2b, ACS_VLINE);

		matrix[i - y1b - 1][0] = 'e';
		matrix[i - y1b][dimy] = 'e';
	}

	for (i = x1b + 1; i<x2b; i++)
	{
		mvaddch(y1b, i, ACS_HLINE);
		mvaddch(y2b, i, ACS_HLINE);

		matrix[0][i - 3] = 'e';
		matrix[dimx][i - 3] = 'e';
	}
	refresh();
}

void create_map(char *map_name, int load){
	FILE *map;
	char temp[100];
	int y = y1b + 1, x = x1b + 1;
	int i, j;
	switch(load){
	case 0: strcpy(temp,"Levels\\"); strcat(temp,map_name); break;
	case 1: strcpy(temp,"Saved Games\\"); strcat(temp,map_name); break;
	case 2: strcpy(temp,"Saved Maps\\"); strcat(temp,map_name); break;
	}
	map = fopen(temp, "rb");
	print_border();  //okvir
	for (i = y; i<y2b; i++){
		fread(matrix[i - y1b] + x - x1b, sizeof(char), 89, map);
	}
	for (i = y - 2; i < y2b - 2; i++)
		for (j = x - x1b; j<x2b - 2; j++){
			what_to_print(i + 2, j + 2, i + 2, j + 2, matrix[i][j]);
			if (matrix[i][j] == '.') matrix[i][j] = ' ';
		}
	fclose(map);
	refresh();
}

void print_powerup(int y, int x, chtype pup, char kind){
	// koordinate powerupa, karakter za stampanje, vrsta powerupa.
	int A;
	switch (kind){
	case 'l': A = 20; break;
	case 'q': A = 15; break;
	case 's': A = 2;  break;
	case 'a': A = 16; break;
	case 'y': A = 18; break;
	case 'x': A = 19; break;
	}
	attron(COLOR_PAIR(A) | A_BOLD);
	mvaddch(y - 1, x, ACS_DIAMOND);
	mvaddch(y, x, pup);
	attroff(COLOR_PAIR(A) | A_BOLD);
	attron(COLOR_PAIR(1) | A_BOLD);
	mvaddch(y - 1, x - 1, ACS_ULCORNER);
	mvaddch(y - 1, x + 1, ACS_URCORNER);
	mvaddch(y, x - 1, ACS_VLINE);
	mvaddch(y, x + 1, ACS_VLINE);
	mvaddch(y + 1, x - 1, ACS_LLCORNER);
	mvaddch(y + 1, x, ACS_HLINE);
	mvaddch(y + 1, x + 1, ACS_LRCORNER);
	attroff(COLOR_PAIR(1) | A_BOLD);
}

void print_menu_pups(int y)
{
	print_powerup(y, 105, ACS_BLOCK, 'x');
	print_powerup(y, 112, ACS_PLUS, 'l');
	print_powerup(y, 119, 187, 's');
	print_powerup(y, 126, 164, 'q');
	print_powerup(y, 133, 162, 'a');
	print_powerup(y, 140, ACS_DARROW, 'y');
	attron(COLOR_PAIR(15) | A_BOLD);
	mvaddstr(y + 2, 103, "Shield");
	mvaddstr(y + 2, 111, "Life");
	mvaddstr(y + 2, 118, "Star");
	mvaddstr(y + 2, 125, "Bomb");
	mvaddstr(y + 2, 131, "Clock");
	mvaddstr(y + 2, 138, "Shovel");
	mvaddstr(y + 4, 119, "Power-ups");
	attroff(COLOR_PAIR(15) | A_BOLD);
	/*
	pup-list

	162 - clock
	164 - bomba
	ACS_BLOCK - stit
	ACS_PLUS - zivot
	187 - zvezda
	ACS_DARROW- lopata
	*/

}



void print_commands()
{
	attron(COLOR_PAIR(10));
	mvprintw(48, 117, " CONTROLS : ");
	attroff(COLOR_PAIR(10));

	mvaddch(54, 122, ACS_UARROW);
	mvaddch(55, 120, ACS_LARROW);
	mvaddch(55, 124, ACS_RARROW);
	mvaddch(56, 122, ACS_DARROW);

	mvaddstr(52, 119, "MOVE UP");
	mvaddstr(55, 110, "MOVE LEFT");
	mvaddstr(55, 126, "MOVE RIGHT");
	mvaddstr(58, 118, "MOVE DOWN");
	attron(COLOR_PAIR(1) | A_REVERSE);
	mvaddstr(62, 112, "        SPACE        ");
	attroff(COLOR_PAIR(1) | A_REVERSE);
	mvaddstr(64, 120, "SHOOT");
	refresh();
}

void print_border_menu(int y1, int x1, int y2, int x2)
{
	int i;
	attron(COLOR_PAIR(10)); // dodaj atribut za boju
	mvaddch(y1, x1, ACS_ULCORNER);
	mvaddch(y2, x1, ACS_LLCORNER);
	mvaddch(y1, x2, ACS_URCORNER);
	mvaddch(y2, x2, ACS_LRCORNER);
	for (i = y1 + 1; i<y2; i++)
	{
		mvaddch(i, x1, ACS_VLINE);
		mvaddch(i, x2, ACS_VLINE);
	}

	for (i = x1 + 1; i<x2; i++)
	{
		mvaddch(y1, i, ACS_HLINE);
		mvaddch(y2, i, ACS_HLINE);
	}
	refresh();
	attroff(COLOR_PAIR(10));
}  
// granice/okvir mape/menija
//======================================================================= odavde pa do dole.

void print_border_side_menu(int y1, int x1, int y2, int x2, int C)
{
	int i;
	attron(COLOR_PAIR(C)); // dodaj atribut za boju
	mvaddch(y1, x1, ACS_ULCORNER);
	mvaddch(y2, x1, ACS_LLCORNER);
	mvaddch(y1, x2, ACS_URCORNER);
	mvaddch(y2, x2, ACS_LRCORNER);
	for (i = y1 + 1; i<y2; i++)
	{
		mvaddch(i, x1, ACS_PLUS);
		mvaddch(i, x2, ACS_PLUS);
	}

	for (i = x1 + 1; i<x2; i++)
	{
		mvaddch(y1, i, ACS_PLUS);
		mvaddch(y2, i, ACS_PLUS);
	}
	refresh();
	attroff(COLOR_PAIR(C));
}  // granice/okvir mape/menija

void show_number(int y, int x, int numI[5][3], chtype C){
	int i, j;

	for (i = 0; i < 5; i++){
		for (j = 0; j < 3; j++){

			if (numI[i][j]) {
				attron(COLOR_PAIR(10));
				mvaddch(y + i, x + j, C);
				attroff(COLOR_PAIR(10));
			}
			else{
				attron(COLOR_PAIR(1));
				mvaddch(y + i, x + j, ' ');
				attroff(COLOR_PAIR(1));
			}
		}
	}
}

void print_tank_status(int y, int x, TankDesign *tank_type, int *position, int A){

	switch (A){
	case 0: attron(COLOR_PAIR(1) | A_BOLD); mvaddch(y + 3, x, 'N'); attroff(COLOR_PAIR(1) | A_BOLD); break;
	case 1: attron(COLOR_PAIR(1) | A_BOLD); mvaddch(y + 3, x, 'S'); attroff(COLOR_PAIR(1) | A_BOLD); break;
	}

	attron(COLOR_PAIR(tank_type[position[0]].paint));
	mvaddch(y - 1, x - 1, tank_type[position[0]].ch);

	attron(COLOR_PAIR(tank_type[position[1]].paint));
	mvaddch(y - 1, x, tank_type[position[1]].ch);

	attron(COLOR_PAIR(tank_type[position[2]].paint));
	mvaddch(y - 1, x + 1, tank_type[position[2]].ch);

	attron(COLOR_PAIR(tank_type[position[3]].paint));
	mvaddch(y, x - 1, tank_type[position[3]].ch);

	attron(COLOR_PAIR(tank_type[position[4]].paint));
	mvaddch(y, x, tank_type[position[4]].ch);

	attron(COLOR_PAIR(tank_type[position[5]].paint));
	mvaddch(y, x + 1, tank_type[position[5]].ch);

	attron(COLOR_PAIR(tank_type[position[6]].paint));
	mvaddch(y + 1, x - 1, tank_type[position[6]].ch);

	attron(COLOR_PAIR(tank_type[position[7]].paint));
	mvaddch(y + 1, x, tank_type[position[7]].ch);

	attron(COLOR_PAIR(tank_type[position[8]].paint));
	mvaddch(y + 1, x + 1, tank_type[position[8]].ch);

	refresh();
}

void delete_bots_left(){
	int i, j, y, x;
	int xCord[] = { 105, 112, 119, 126, 133, 140 };
	int yCord[] = { 5, 12, 19 };

	if (M == -1) { M = 5; N--; }
	y = yCord[N] - 1; x = xCord[M] - 1;
	attron(COLOR_PAIR(1));
	mvaddch(y + 4, x + 1, ' ');
	for (i = y; i < y + 3; i++)
		for (j = x; j < x + 3; j++)
			mvaddch(i, j, ' ');
	attroff(COLOR_PAIR(1));
	refresh();
	M--;
}

void print_bots_left(){  // BOT_DIF - easy(0), medium(1), hard(2) LVL - koji nivo.
	int i, j, bot, n, m;
	TankDesign *style;
	int xCord[] = { 105, 112, 119, 126, 133, 140 };
	int yCord[] = { 5, 12, 19 };

	bot = botsInLevel[BOT_DIF][LVL];
	for (i = 0; i < 3; i++){
		for (j = 0; j < 6; j++){
			bot--;
			switch (LEVEL[BOT_DIF][LVL][bot].smart) {
			case 1:	style = normal_tank_v; break;
			case 2: style = brat_tank_v; break;
			case 3: style = special_tank_v; break;
			default: style = normal_tank_v;
			}

			if (bot >= 0)
				print_tank_status(yCord[i], xCord[j], style, top, LEVEL[BOT_DIF][LVL][bot].kind);
		}
	}
	N = botsInLevel[BOT_DIF][LVL] / 6; M = botsInLevel[BOT_DIF][LVL] % 6 - 1;
}

void print_number(int y, int x, int number){
	int num1[][3] = { { 0, 0, 1 }, { 0, 1, 1 }, { 1, 0, 1 }, { 0, 0, 1 }, { 0, 0, 1 } };
	int num2[][3] = { { 1, 1, 1 }, { 0, 0, 1 }, { 1, 1, 1 }, { 1, 0, 0 }, { 1, 1, 1 } };
	int num3[][3] = { { 1, 1, 1 }, { 0, 0, 1 }, { 1, 1, 1 }, { 0, 0, 1 }, { 1, 1, 1 } };
	int num4[][3] = { { 1, 0, 1 }, { 1, 0, 1 }, { 1, 1, 1 }, { 0, 0, 1 }, { 0, 0, 1 } };
	int num5[][3] = { { 1, 1, 1 }, { 1, 0, 0 }, { 1, 1, 1 }, { 0, 0, 1 }, { 1, 1, 1 } };
	int num6[][3] = { { 1, 1, 1 }, { 1, 0, 0 }, { 1, 1, 1 }, { 1, 0, 1 }, { 1, 1, 1 } };
	int num7[][3] = { { 1, 1, 1 }, { 1, 0, 1 }, { 0, 0, 1 }, { 0, 0, 1 }, { 0, 0, 1 } };
	int num8[][3] = { { 1, 1, 1 }, { 1, 0, 1 }, { 1, 1, 1 }, { 1, 0, 1 }, { 1, 1, 1 } };
	int num9[][3] = { { 1, 1, 1 }, { 1, 0, 1 }, { 1, 1, 1 }, { 0, 0, 1 }, { 1, 1, 1 } };
	int num0[][3] = { { 1, 1, 1 }, { 1, 0, 1 }, { 1, 0, 1 }, { 1, 0, 1 }, { 1, 1, 1 } };

	chtype C = ACS_BLOCK; // OVDE BRZO MENJAMO ISPIS BROJEVA.

	switch (number){
	case 1: show_number(y, x, num1, C);	break;
	case 2: show_number(y, x, num2, C);	break;
	case 3: show_number(y, x, num3, C);	break;
	case 4: show_number(y, x, num4, C);	break;
	case 5: show_number(y, x, num5, C);	break;
	case 6: show_number(y, x, num6, C);	break;
	case 7: show_number(y, x, num7, C);	break;
	case 8: show_number(y, x, num8, C);	break;
	case 9: show_number(y, x, num9, C);	break;
	case 0: show_number(y, x, num0, C);	break;
	}
	refresh();

}

void counter_spec(int y, int x){
	int i;
	for (i = 0; i < 10; i++){
		print_number(y, x, i);
		refresh();
		Sleep(1000);
	}
}

void print_high_score(){
	int I, II, III, IV;

	if (HIGH_SCORE < 10){
		I = HIGH_SCORE;
		print_number(49, 138, I);
	}

	else if (HIGH_SCORE >= 10 && HIGH_SCORE < 100){
		II = HIGH_SCORE / 10;
		I = HIGH_SCORE % 10;

		print_number(49, 138, I);
		print_number(49, 134, II);
	}
	else if (HIGH_SCORE >= 100 && HIGH_SCORE < 1000){
		III = HIGH_SCORE / 100;
		II = (HIGH_SCORE % 100) / 10;
		I = (HIGH_SCORE % 100) % 10;

		print_number(49, 138, I);
		print_number(49, 134, II);
		print_number(49, 130, III);
	}
	else if (HIGH_SCORE >= 1000 && HIGH_SCORE < 10000){
		IV = HIGH_SCORE / 1000;
		III = (HIGH_SCORE % 1000) / 100;
		II = ((HIGH_SCORE % 1000) % 100) / 10;
		I = ((HIGH_SCORE % 1000) % 100) % 10;

		print_number(49, 138, I);
		print_number(49, 134, II);
		print_number(49, 130, III);
		print_number(49, 126, IV);
	}
	else if (HIGH_SCORE >= 10000){
		IV = 9;
		III = 9;
		II = 9;
		I = 9;

		print_number(49, 138, I);
		print_number(49, 134, II);
		print_number(49, 130, III);
		print_number(49, 126, IV);
	}
}
