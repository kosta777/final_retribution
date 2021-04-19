#include "tank.h"


void rand_gen()
{
	int i;
	int k, l;
	int h, w, pos; // h => height; w =>width; pos =>random element to print
	char possibility[2] = { 'b', 'c' };
	int percentage[10] = { 1, 1 };
 	for (i = 0; i < 10; i++)
	{	
		pos = percentage[(rand() % (9  + 1))];
		h = (rand() % ((dimx + 1) - 4 + 1)) + 4;
		w = (rand() % ((dimy + 1) - 4 + 1)) + 2;
		if ((matrix[h - 2][w - 2] == ' ') && (matrix[h - 2][w - 2] != 'g')) // if he found a blank spot in the matrix, he will print a random character
		{
			what_to_print(h, w, h, w, possibility[pos]);
			matrix[h - 2][w - 2] = possibility[pos];
			for (l = w - 1; l	< (w + 2); l++) // random element will expand up to 3x3 size(if possible)
			{
				if ((matrix[h - 3][l - 2] == ' ') && (!blocked_areas(h - 1, l, h - 1, l))) what_to_print(h - 1, l, h - 1, l, possibility[pos]), matrix[h - 3][l - 2] = possibility[pos];
				if ((matrix[h - 2][l - 2] == ' ') && (!blocked_areas(h, l, h, l))) what_to_print(h, l, h, l, possibility[pos]), matrix[h - 2][l - 2] = possibility[pos];
				if ((matrix[h - 1][l - 2] == ' ')&&(!blocked_areas(h+1,l,h+1,l))) what_to_print(h + 1, l, h+1, l, possibility[pos]), matrix[h - 1][l - 2] = possibility[pos];

			}
			return;
		}
	}

}

int check_if_free(int y, int x)
{
	int i, j, rvl = 1;
	for (i = (y - 1); i < (y + 2); i++)
		for (j = (x - 1); j < (x + 2); j++)
			if ((matrix[i - 2][j - 2] != ' ') || (blocked_areas(i,j,i,j))) return 0;
	return rvl;
}

void rand_pup_gen()
{
	/*life - l  ACS_PLUS
		bomb - q  164
		star - s  187
		clock - a  162
		shovel - y  ACS_DARROW
		shield - x  ACS_BLOCK
		*/
	int i, j;
	int k, l;
	int h, w, pos;
	chtype possibility[6] = { ACS_BLOCK, ACS_PLUS, 187, 164, 162, ACS_DARROW };

	for (i = 0; i < 10; i++)
	{
		h = (rand() % ((dimx + 1) - 4 + 1)) + 4;
		w = (rand() % ((dimy + 1) - 2 + 1)) + 2;
		pos = (rand() % ((5 + 1)));	
		if (check_if_free(h, w))
		{
			alloc_powerup(pUps[pos], h, w);
			print_powerup(h, w, possibility[pos], pUps[pos]);
			for (j = h -1 ; j <(h + 2); j++)
				for (i = w -1 ; i < (w + 2); i++)
					matrix[j - 2][i - 2] = pUps[pos];
			return;
		}
	}
}
