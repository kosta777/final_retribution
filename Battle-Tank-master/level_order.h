#ifndef LEVEL_H_INCLUDED
#define LEVEL_H_INCLUDED
#include "tank.h"

#define baseY 61
#define baseX1 40
#define baseX2 50
#define spawn1Y1 4
#define spawn1Y2 6
#define spawn1X1 4
#define spawn1X2 6
#define spawn2X1 88
#define spawn2X2 90
#define spawn3X1 46
#define spawn3X2 48
#define bspawnY1 64	
#define bspawnY2 66
#define bspawnX1 37
#define bspawnX2 39

typedef struct Map
{
	char mapa[dimx][dimy];
}map;

typedef struct Score
{
	char name[100];
	long long int score;
	struct Score* next;
}score;

extern int Skor;
extern char lvl_matrix[dimx][dimy];
extern char lvl_meni[][dimx]; // stavke menija
extern char button[][dimx];
extern char buffer[100];

void init_matrix();
void print_matrix();

// save menu
void save_in_matrix(int yu, int xu, int yd, int xd, char k);

int check_if_legit(char buff[16]);

void name_it();

void save_it();

int save_map();
//==================================


// graphics 
void print_brick_lvl(int yu, int xu, int yd, int xd);
void print_grass_lvl(int yu, int xu, int yd, int xd);
void print_water_lvl(int yu, int xu, int yd, int xd);
void print_blanko_lvl(int yu, int xu, int yd, int xd);
void print_eraser(int yu, int xu, int yd, int xd);
void print_wall_lvl(int yu, int xu, int yd, int xd);
void print_head_lvl(int yu, int xu, int yd, int xd);
void print_blocked_areas();
//===============================

void what_to_print(int yu, int xu, int yd, int xd, char k);
//movement
int lvl_can_move(int yu, int xu, int yd, int xd, int num);

void move_up2x2(int yu, int xu, int yd, char xd);
void move_right2x2(int yu, int xu, int yd, int xd);
void move_down2x2(int yu, int xu, int yd, int xd);
void move_left2x2(int yu, int xu, int yd, int xd);
//=================

void menu_content();

int load_maps();

void size_resize(int *yu, int *xu, int *yd, int *xd);

void buttons();

void level_editor();
//Load_Maps
int print_a_page(char **book, int c_page, int limitdown, int limitup, int per_page);

void lmenu_up(char **book, int *mv, int limit, int *ind, int from);
void lmenu_down(char **book, int *mv, int limit, int *ind, int from);

int load_maps(int decide);
void load_matrix(char name[]);
//S===========

// UNDO/REDO
void PUSH_unredo(map** unredo, int* n_unredo);
void copy_matrix(map** unredo, int n_unredo);
void destroy_undo_redo(map** undo, map **redo, int n_redo, int n_undo);

void _undo_redo(map** pop, map** push, int* n_undo, int* n_redo);
int POP(map** unredo, int* n_unredo);
///=======

//highscores
int read_high_scores();
long long int RSA_D(double checksum);
unsigned long long int RSA_E(long long int sum);
FILE* create_scoreboard_n_check(FILE* hs, score* best);
int read_high_scores();
void destroy_scoreboard(score* best);
int show_scores(score* zurzeit, int j, score* cmp);
void new_high_score(long long int s);
//===========================


//rand gen
void rand_gen();
void rand_pup_gen();
//===============

int blocked_areas(int yu, int xu, int yd, int xd);
void print_blocked_areas();

#endif
