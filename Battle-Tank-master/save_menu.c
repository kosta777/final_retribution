#include "tank.h"

char buffer[100];

void save_in_matrix(int yu, int xu, int yd, int xd, char k){
	int i, j;
	if (k == 'e') k = '.';
	for (i = yu; i <= yd; i++)
		for (j = xd; j <= xu; j++)
			lvl_matrix[i - 3][j - 3] = k;
} // cuva  element koji je korisnik sacuvao na mapi

int check_if_legit(char buff[16]){
	int i = 0;
	while (buff[i] != '\0')
	{
		if ((!isalpha(buff[i++])) && (!isalnum(buff[i - 1]))) 
		{
			mvprintw(10, 102, " Only letters & numbers allowed ! >.< ");
			refresh();  Sleep(1125);
			mvprintw(10, 102, "                                      ");
			return 1;
		}
	}
	refresh();
	return 0;
}

void name_it(){
	mvprintw(10, 102, " Give your map a  name :) ");
	refresh();
	Sleep(750);
	mvprintw(10, 102, "                            ");
	refresh();
}

void save_it(){
	FILE *file;
	int i, j;
	char temp[100];
	strcpy(temp,"Saved Maps\\");
	strcat(temp,buffer);
	file = fopen(temp, "wb");
//	for (j = 0; j < 65; fprintf(file, "/\n"), j++)
	//	for (i = 0; i < 90; fprintf(file, "%c", lvl_matrix[j][i]), i++);
	for (i = 0; i < dimx; )
		fwrite(lvl_matrix[i++], sizeof(char), dimy-1, file);
	fclose(file);
}

int save_map(){
	int i = 0, j = 115, tru = 1;
	char Key;
	int x1 = 100, y1 = 2, x2 = 145, y2 = 17, min = 115, max = 130, mv = 8, ind1 = 4;
	FILE  *saved_maps;
	buffer[0] = '\0';

	print_border_side_menu(y1, x1, y2, x2, 3);// IZMENA
	mvprintw(y1 + 1, x1 + 15, " S A V E  M A P  A S");
	mvprintw(y1 + 6, x1 + 2, " Map Name :  _______________");
	mvprintw(y1 + 13, x1 + 2, "ESC : Return to main menu ");
	attron(COLOR_WHITE | A_REVERSE);
	mvprintw(y1 + 11, x1 + 1, " Max. 15 characters(letters & num allowed!)");
	attroff(COLOR_WHITE | A_REVERSE);
	refresh();

	//===================Naming the map====================

	while (tru)
	{

		switch (Key = getch()){
		case KEY_UP: case KEY_DOWN: case KEY_LEFT: case KEY_RIGHT:  break;

		case ENTER:if (buffer[0] == '\0') name_it(); else  tru = check_if_legit(buffer); break; // checks if the name is correctly inputted

		default: if (j < max) 
		{ buffer[i++] = Key; buffer[i] = '\0'; mvaddch(y1 + 6, j++, Key); 
		}; refresh(); break;

		case BACKSPACE: if (j > min) 
		{ 
			buffer[--i] = '\0'; mvaddch(y1 + 6, --j, '_'); 
		}; refresh(); break;

		case ESC: delete_menu(y1, x1, y2, x2); return 1; break;


		}
	}

	//==================================================

	buffer[i] = '.'; buffer[i + 1] = 'm'; buffer[i + 2] = 'a'; buffer[i + 3] = 'p'; buffer[i + 4] = '\0'; // adds .dat extension
	save_it();


	if (!(saved_maps = fopen("Saved Maps\\saved_maps.txt", "r+"))) saved_maps = fopen("Saved Maps\\saved_maps.txt", "w"); // if saved_maps doesn't exist, then create new file
	i = 0;
	while ((Key = fgetc(saved_maps)) != EOF){   // does this map already exist in the file?
		while (Key == buffer[i]) 
		{
			Key = fgetc(saved_maps);
			i++;
		}
		if (i == strlen(buffer)) break; else i = 0;
	}

	if (i == strlen(buffer)) fclose(saved_maps); else // if it does->do nothing, if it doesn't, then save it in the file;
	{
		fprintf(saved_maps, "%s\n", buffer);
		fclose(saved_maps);
	}

	delete_menu(y1, x1, y2, x2);
	print_border_menu(y1, x1, y2, x2);
	mvprintw(y1 + 4, x1 + 2, " Continue with editting this map?");
	attron(COLOR_PAIR(8));
	mvprintw(y1 + 6, x1 + 18, " Yes ");
	attroff(COLOR_PAIR(8));
	mvprintw(y1 + 8, x1 + 18, " No ");
	refresh();
	while (1){
		switch (getch()){
		case KEY_UP: menu_up(&mv, y1 + 6, &ind1, x1 + 18, 0); break;
		case KEY_DOWN: menu_down(&mv, y1 + 8, &ind1, x1 + 18, 0); break;
		case ENTER: if (mv == 8)
		{
			delete_menu(y1, x1, y2, x2); return 0;
		}
					else
					{
						delete_menu(y1, x1, y2, x2); return 1;
					}
					break;
		}
	}
}
