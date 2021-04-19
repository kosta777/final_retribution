#include "tank.h"

void load_matrix(char name[]){
	FILE *file;
	int i = 0, j = 0;
	char key,temp[100];
	strcpy(temp,"Saved Maps\\");
	strcat(temp,name);
	if (!(file = fopen(temp, "rb")))
	{
		init_matrix();
		return;
	}
	/*while ((key = fgetc(file)) != EOF)
		{
		if (key == '/') i++;
		if (key == '\n') { j = 0; continue; }
		lvl_matrix[i][j++] = key;
		}	
		*/
	while (fread(lvl_matrix[i++], sizeof(char), dimy-1, file) != 0);
	fclose(file);
	
}

void free_book(char** book)
{
	int i = 0;
	while (book[i])
	{
		free(book[i++]);
	}
}

int print_a_page(char **book, int c_page, int limitdown, int limitup, int per_page)
{
	int i, j = limitup;
	char name[100];
	for (i = (c_page - 1)*per_page; book[i] != NULL; i++)
	{
		strcpy(name,book[i]);
		name[strlen(name)-4]='\0';
		mvprintw(j, 113, "%s", name);
		j += 2;
		if (j == limitdown) break;
	}
	mvprintw(38, 117, "         ");
	mvprintw(38, 117, "PAGE %d", c_page);
	strcpy(name,book[(c_page-1)*per_page]);
	name[strlen(name)-4]='\0';
	attron(COLOR_PAIR(8)| A_BOLD);
	mvprintw(8, 113, "%s", name);
	attroff(COLOR_PAIR(8)| A_BOLD);
	refresh();
	return j;
}

void lmenu_up(char **book, int *mv, int limit, int *ind, int from)
{
	int i;
	char name[100];
	if (*mv == limit) return;
	strcpy(name,book[--(*ind)]);
	name[strlen(name)-4]='\0';
	*mv = *mv - 2;
	attron(COLOR_PAIR(8)| A_BOLD);
	mvprintw(*mv, from, "%s  ", name);
	attroff(COLOR_PAIR(8)| A_BOLD);
	strcpy(name,book[*ind + 1]);
	name[strlen(name)-4]='\0';
	mvprintw(*mv + 2, from, "%s  ", name);
	refresh();

}

void lmenu_down(char **book, int *mv, int limit, int *ind, int from)
{
	int i;
	char name[100];
	if (*mv == limit) return;
	*mv = *mv + 2;
	strcpy(name,book[++(*ind)]);
	name[strlen(name)-4]='\0';
	attron(COLOR_PAIR(8)| A_BOLD);
	mvprintw(*mv, from, "%s  ", name);
	attroff(COLOR_PAIR(8)| A_BOLD);
	strcpy(name, book[*ind - 1]);
	name[strlen(name)-4]='\0';
	mvprintw(*mv - 2, from, "%s  ",name);
	refresh();
} // kretanje po meniju

int load_maps(int decide){
	char **book = (char**)calloc(1, sizeof(char*));
	FILE *saved_maps,*saved_games; 
	int pages, num = 0, per_page = 10, c_page = 1;
	int x1 = 100, y1 = 2, x2 = 145, y2 = 45;
	int limitup = 8, limitdown = 28, mv = 8, i = 0, j = 6;
	int from = 113;
	switch(decide){
		case 0 :case 1:	if (!(saved_maps = fopen("Saved Maps\\saved_maps.txt", "r"))) return 1;   break;  //ne zaboravi break, if the file doesn't exist, return
		case 2: if (!(saved_maps = fopen("Saved Games\\saved_games.txt", "r"))) return 1; break;
	}
	while (!feof(saved_maps)) // inserts every map name into an array
	{
		book[num] = (char*)calloc(20, sizeof(char));
		fscanf(saved_maps, "%s", book[num++]);
		if (book[num - 1][0] == '\0') { num--; book[num] = NULL; continue; };
		book = (char**)realloc(book, (num + 1)*sizeof(char*));
		book[num] = NULL;
	}
	if (num == 0) {
		free_book(book);  //delete array
		return 1;
	}// if there aren't any saved maps, return


	fclose(saved_maps);
	pages = (num - 1) / per_page + 1;
	print_border_menu(y1, x1, y2, x2);
	if(decide==2) mvprintw(4, 115, "L O A D   G A M E");
	else mvprintw(4, 115, "L O A D   M A P");
	mvprintw(42, 102, "ARROW LEFT/RIGHT : navigate through pages");
	mvprintw(44, 102, "ARROW UP/RIGHT : navigate through files");
	refresh();

	while (1)
	{
		j = print_a_page(book, c_page, limitdown, limitup, per_page) - 2;
		while (1){
			switch (getch()){
			case KEY_UP: PlaySound(TEXT("Sound\\Menu_move.wav"),NULL, SND_ASYNC); lmenu_up(book, &mv, limitup, &i, from); break;
			case KEY_DOWN: PlaySound(TEXT("Sound\\Menu_move.wav"),NULL, SND_ASYNC); lmenu_down(book, &mv, j, &i, from); break;
			case KEY_LEFT:PlaySound(TEXT("Sound\\Menu_move.wav"),NULL, SND_ASYNC); if (c_page > 1) 
			{
				delete_menu(5, 101, 38, 144); j = print_a_page(book, --c_page, limitdown, limitup, per_page) - 2; mv = 8; i = (c_page - 1)*per_page;
			} break;
			case KEY_RIGHT: PlaySound(TEXT("Sound\\Menu_move.wav"),NULL, SND_ASYNC); if (c_page < pages) {
				delete_menu(5, 101, 38, 144);  j = print_a_page(book, ++c_page, limitdown, limitup, per_page) - 2; mv = 8; i = (c_page - 1)*per_page;
			} break;
			case ENTER: PlaySound(TEXT("Sound\\select.wav"),NULL, SND_ASYNC); if (decide==1) { strcpy(buffer, book[i]); load_matrix(book[i]); print_matrix(); free_book(book);  delete_menu(y1, x1, y2, x2); return 0; }
						else if (!decide) { clear(); strcpy(map_name,book[i]); custom_map(map_name); free_book(book); delete_menu(y1, x1, y2, x2);  return 1; }
						else if(decide==2){
							load_game(book[i]);
							delete_menu(y1, x1, y2, x2);
							return 0;
						}
				break;
			case ESC: delete_menu(y1, x1, y2, x2); return 1; break;
			}
		}
	}
}
