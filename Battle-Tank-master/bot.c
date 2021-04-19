#include "tank.h"
int array_bot_barrel[] = { 2, 4, 3, 4, 2, 3, 4 }, s = 0, x1;

//dimy = 40 - 50
//dimx = 61 - 66
void move_bot_barrel()
{
 int a, b, c, d;
 a = !can_move(lst->curr->tankAll.tank.position.y, lst->curr->tankAll.tank.position.x, 1);
 b = !can_move(lst->curr->tankAll.tank.position.y, lst->curr->tankAll.tank.position.x, 2);
 c = !can_move(lst->curr->tankAll.tank.position.y, lst->curr->tankAll.tank.position.x, 3);
 d = !can_move(lst->curr->tankAll.tank.position.y, lst->curr->tankAll.tank.position.x, 4);
 if (a && b && c)
  lst->curr->tankAll.tank.position.barrel = 4;
 else if (a && b && d)
  lst->curr->tankAll.tank.position.barrel = 3;
 else if (a && c && d)
  lst->curr->tankAll.tank.position.barrel = 2;
 else if (b && c && d)
  lst->curr->tankAll.tank.position.barrel = 1;
}

	int hit_tank(int y, int x)
{
	int b = lst->first->tankAll.tank.position.y-y1b;
	int a = lst->first->tankAll.tank.position.x-x1b;
	if (((y == (b - 1)) && (x == (a - 1))) || ((y == b - 1) && (x == a)) || ((y == (b - 1)) && (x == (a + 1))) ||
		((y == b) && (x == (a - 1))) || ((y == b) && (x == (a + 1))) || 
		((y == (b + 1)) && (x == (a-1))) || ((y == (b+1)) && (x == a)) || ((y == (b + 1)) && (x == (a + 1))))
		return 1;
	return 0;
}

void shoot()
{
	int i = 0;
	if (!lst->curr->tankAll.projectile[0].phase)
	{
		switch (lst->curr->tankAll.tank.position.barrel)
		{
		case 1:
			while ((matrix[lst->curr->tankAll.tank.position.y - y1b - 2 - i][lst->curr->tankAll.tank.position.x - x1b]==' ') ||
				(matrix[lst->curr->tankAll.tank.position.y - y1b - 2 - i][lst->curr->tankAll.tank.position.x - x1b] == 'g') ||
				(matrix[lst->curr->tankAll.tank.position.y - y1b - 2 - i][lst->curr->tankAll.tank.position.x - x1b] == 'w'))
				i++;

			if  ((matrix[lst->curr->tankAll.tank.position.y - y1b - 2 - i][lst->curr->tankAll.tank.position.x - x1b] == 'b') ||
				(matrix[lst->curr->tankAll.tank.position.y - y1b - 2 - i][lst->curr->tankAll.tank.position.x - x1b] == 'h') ||

				((matrix[lst->curr->tankAll.tank.position.y - y1b - 2 - i][lst->curr->tankAll.tank.position.x - x1b] == '*') &&
				((lst->curr->tankAll.tank.position.y - y1b - 2 - i) == lst->first->tankAll.projectile[0].position.y) &&
				((lst->curr->tankAll.tank.position.x - x1b) == lst->first->tankAll.projectile[0].position.x)) ||
			
				((matrix[lst->curr->tankAll.tank.position.y - y1b - 2 - i][lst->curr->tankAll.tank.position.x - x1b]=='t') &&
				((hit_tank(lst->curr->tankAll.tank.position.y - y1b - 2 - i, lst->curr->tankAll.tank.position.x - x1b)))))
					lst->curr->tankAll.projectile[0].phase = 1;
			break;
		case 2:
			while ((matrix[lst->curr->tankAll.tank.position.y - y1b][lst->curr->tankAll.tank.position.x - x1b - 2 - i] == ' ') ||
				(matrix[lst->curr->tankAll.tank.position.y - y1b][lst->curr->tankAll.tank.position.x - x1b - 2 - i] == 'g') ||
				(matrix[lst->curr->tankAll.tank.position.y - y1b][lst->curr->tankAll.tank.position.x - x1b - 2 - i] == 'w'))
				i++;

			if  ((matrix[lst->curr->tankAll.tank.position.y - y1b][lst->curr->tankAll.tank.position.x - x1b - 2 - i] == 'b') ||
				(matrix[lst->curr->tankAll.tank.position.y - y1b - 2 - i][lst->curr->tankAll.tank.position.x - x1b] == 'h') ||

				((matrix[lst->curr->tankAll.tank.position.y - y1b][lst->curr->tankAll.tank.position.x - x1b - 2 - i] == '*') &&
				((lst->curr->tankAll.tank.position.y - y1b) == lst->first->tankAll.projectile[0].position.y) &&
				((lst->curr->tankAll.tank.position.x - x1b - 2 - i) == lst->first->tankAll.projectile[0].position.x)) ||

				((matrix[lst->curr->tankAll.tank.position.y - y1b][lst->curr->tankAll.tank.position.x - x1b - 2 - i] == 't') &&
				(hit_tank(lst->curr->tankAll.tank.position.y - y1b, lst->curr->tankAll.tank.position.x - x1b - 2 - i))))
				lst->curr->tankAll.projectile[0].phase = 1;
			break;
		case 3:
			while ((matrix[lst->curr->tankAll.tank.position.y - y1b][lst->curr->tankAll.tank.position.x - x1b + 2 + i] == ' ') ||
				(matrix[lst->curr->tankAll.tank.position.y - y1b][lst->curr->tankAll.tank.position.x - x1b + 2 + i] == 'g') ||
				(matrix[lst->curr->tankAll.tank.position.y - y1b][lst->curr->tankAll.tank.position.x - x1b + 2 + i] == 'w'))
				i++;

			if ((matrix[lst->curr->tankAll.tank.position.y - y1b][lst->curr->tankAll.tank.position.x - x1b + 2 + i] == 'b') ||
				(matrix[lst->curr->tankAll.tank.position.y - y1b - 2 - i][lst->curr->tankAll.tank.position.x - x1b] == 'h') ||

				((matrix[lst->curr->tankAll.tank.position.y - y1b][lst->curr->tankAll.tank.position.x - x1b + 2 + i] == '*') &&
				((lst->curr->tankAll.tank.position.y - y1b) == lst->first->tankAll.projectile[0].position.y) &&
				((lst->curr->tankAll.tank.position.x - x1b + 2 + i) == lst->first->tankAll.projectile[0].position.x)) ||

				((matrix[lst->curr->tankAll.tank.position.y - y1b][lst->curr->tankAll.tank.position.x - x1b + 2 + i] == 't') &&
				(hit_tank(lst->curr->tankAll.tank.position.y - y1b, lst->curr->tankAll.tank.position.x - x1b + 2 + i))))
				lst->curr->tankAll.projectile[0].phase = 1;
			break;
		case 4:
			while ((matrix[lst->curr->tankAll.tank.position.y - y1b + 2 + i][lst->curr->tankAll.tank.position.x - x1b] == ' ') ||
				(matrix[lst->curr->tankAll.tank.position.y - y1b + 2 + i][lst->curr->tankAll.tank.position.x - x1b] == 'g') ||
				(matrix[lst->curr->tankAll.tank.position.y - y1b + 2 + i][lst->curr->tankAll.tank.position.x - x1b] == 'w'))
				i++;

			if ((matrix[lst->curr->tankAll.tank.position.y - y1b + 2 + i][lst->curr->tankAll.tank.position.x - x1b] == 'b') ||
				(matrix[lst->curr->tankAll.tank.position.y - y1b - 2 - i][lst->curr->tankAll.tank.position.x - x1b] == 'h') ||

				((matrix[lst->curr->tankAll.tank.position.y - y1b + 2 + i][lst->curr->tankAll.tank.position.x - x1b] == '*') &&
				((lst->curr->tankAll.tank.position.y - y1b + 2 + i) == lst->first->tankAll.projectile[0].position.y) &&
				((lst->curr->tankAll.tank.position.x - x1b) == lst->first->tankAll.projectile[0].position.x)) ||

				((matrix[lst->curr->tankAll.tank.position.y - y1b + 2 + i][lst->curr->tankAll.tank.position.x - x1b] == 't') &&
				((hit_tank(lst->curr->tankAll.tank.position.y - y1b + 2 + i, lst->curr->tankAll.tank.position.x - x1b)))))
				lst->curr->tankAll.projectile[0].phase = 1;
			break;
		}
	}
}

void find_bullet()
{
	int i = 0;
	while ((matrix[lst->curr->tankAll.tank.position.y - y1b - 2 - i][lst->curr->tankAll.tank.position.x - x1b] == ' ') ||
		(matrix[lst->curr->tankAll.tank.position.y - y1b - 2 - i][lst->curr->tankAll.tank.position.x - x1b] == 'g') ||
		(matrix[lst->curr->tankAll.tank.position.y - y1b - 2 - i][lst->curr->tankAll.tank.position.x - x1b] == 'w'))
		i++;

	if (((matrix[lst->curr->tankAll.tank.position.y - y1b - 2 - i][lst->curr->tankAll.tank.position.x - x1b] == '*') &&
		((lst->curr->tankAll.tank.position.y - y1b - 2 - i) == lst->first->tankAll.projectile[0].position.y) &&
		((lst->curr->tankAll.tank.position.x - x1b) == lst->first->tankAll.projectile[0].position.x)) ||
		(matrix[lst->curr->tankAll.tank.position.y - y1b - 2 - i][lst->curr->tankAll.tank.position.x - x1b] == 'h') ||
		(hit_tank(lst->curr->tankAll.tank.position.y - y1b - 2 - i, lst->curr->tankAll.tank.position.x - x1b)))
	{
		lst->curr->tankAll.tank.position.barrel = 1;
		lst->curr->tankAll.projectile[0].phase = 1;
		lst->curr->tankAll.projectile[0].position.projectil_dir = lst->curr->tankAll.tank.position.barrel;
		return;
	}
	i = 0;
	while ((matrix[lst->curr->tankAll.tank.position.y - y1b][lst->curr->tankAll.tank.position.x - x1b - 2 - i] == ' ') ||
		(matrix[lst->curr->tankAll.tank.position.y - y1b][lst->curr->tankAll.tank.position.x - x1b - 2 - i] == 'g') ||
		(matrix[lst->curr->tankAll.tank.position.y - y1b][lst->curr->tankAll.tank.position.x - x1b - 2 - i] == 'w'))
		i++;

	if (((matrix[lst->curr->tankAll.tank.position.y - y1b][lst->curr->tankAll.tank.position.x - x1b - 2 - i] == '*') &&
		((lst->curr->tankAll.tank.position.y - y1b) == lst->first->tankAll.projectile[0].position.y) &&
		((lst->curr->tankAll.tank.position.x - x1b - 2 - i) == lst->first->tankAll.projectile[0].position.x)) ||
		(matrix[lst->curr->tankAll.tank.position.y - y1b][lst->curr->tankAll.tank.position.x - x1b - 2 - i] == 'h') ||
		(hit_tank(lst->curr->tankAll.tank.position.y - y1b, lst->curr->tankAll.tank.position.x - x1b - 2 - i)))
	{
		lst->curr->tankAll.tank.position.barrel = 2;
		lst->curr->tankAll.projectile[0].phase = 1;
		lst->curr->tankAll.projectile[0].position.projectil_dir = lst->curr->tankAll.tank.position.barrel;
		return;
	}
	i = 0;
	while ((matrix[lst->curr->tankAll.tank.position.y - y1b][lst->curr->tankAll.tank.position.x - x1b + 2 + i] == ' ') ||
		(matrix[lst->curr->tankAll.tank.position.y - y1b][lst->curr->tankAll.tank.position.x - x1b + 2 + i] == 'g') ||
		(matrix[lst->curr->tankAll.tank.position.y - y1b][lst->curr->tankAll.tank.position.x - x1b + 2 + i] == 'w'))
		i++;
	if (((matrix[lst->curr->tankAll.tank.position.y - y1b][lst->curr->tankAll.tank.position.x - x1b + 2 + i] == '*') &&
		((lst->curr->tankAll.tank.position.y - y1b) == lst->first->tankAll.projectile[0].position.y) &&
		((lst->curr->tankAll.tank.position.x - x1b + 2 + i) == lst->first->tankAll.projectile[0].position.x)) ||
		(matrix[lst->curr->tankAll.tank.position.y - y1b][lst->curr->tankAll.tank.position.x - x1b + 2 + i] == 'h') ||
		(hit_tank(lst->curr->tankAll.tank.position.y - y1b, lst->curr->tankAll.tank.position.x - x1b + 2 + i)))
	{
		lst->curr->tankAll.tank.position.barrel = 3;
		lst->curr->tankAll.projectile[0].phase = 1;
		lst->curr->tankAll.projectile[0].position.projectil_dir = lst->curr->tankAll.tank.position.barrel;
		return;
	}
	i = 0;
	while ((matrix[lst->curr->tankAll.tank.position.y - y1b + 2 + i][lst->curr->tankAll.tank.position.x - x1b] == ' ') ||
		(matrix[lst->curr->tankAll.tank.position.y - y1b + 2 + i][lst->curr->tankAll.tank.position.x - x1b] == 'g') ||
		(matrix[lst->curr->tankAll.tank.position.y - y1b + 2 + i][lst->curr->tankAll.tank.position.x - x1b] == 'w'))
		i++;

	if (((matrix[lst->curr->tankAll.tank.position.y - y1b + 2 + i][lst->curr->tankAll.tank.position.x - x1b] == '*') &&
		((lst->curr->tankAll.tank.position.y - y1b + 2 + i) == lst->first->tankAll.projectile[0].position.y) &&
		((lst->curr->tankAll.tank.position.x - x1b) == lst->first->tankAll.projectile[0].position.x)) ||
		(matrix[lst->curr->tankAll.tank.position.y - y1b + 2 + i][lst->curr->tankAll.tank.position.x - x1b] == 'h') ||
		(hit_tank(lst->curr->tankAll.tank.position.y - y1b + 2 + i, lst->curr->tankAll.tank.position.x - x1b)))
	{
		lst->curr->tankAll.tank.position.barrel = 4;
		lst->curr->tankAll.projectile[0].phase = 1;
		lst->curr->tankAll.projectile[0].position.projectil_dir = lst->curr->tankAll.tank.position.barrel;
		return;
	}
}

void medium_bot()
{
	struct timeb vreme;	
	clock_t x;
	int flag=0;
	ftime(&vreme);
	if (lst->curr->tankAll.tank.phase == 2)
	{
		lst->curr->tankAll.tank.counter1 = 0;
		lst->curr->tankAll.tank.time = clock();
	}
	//if (delay_s(890, x = vreme1.millitm, lst->curr->tankAll.tank.pp1, lst->curr->tankAll.tank.phase)) 
	if (lst->curr->tankAll.tank.counter1 < 5)
	{
		easy_bot();
		if ((((x = clock()) - lst->curr->tankAll.tank.time) / CLOCKS_PER_SEC) > 3)
		{
			lst->curr->tankAll.tank.counter1++;
			lst->curr->tankAll.tank.time = x;
		}
	}
	else
	{
		if (lst->curr->tankAll.tank.counter1++ == 1)
		{
		//	lst->curr->tankAll.tank.start = lst->curr->tankAll.tank.end = vreme.millitm;
			lst->curr->tankAll.tank.counter = 1;
			//lst->curr->tankAll.tank.pp = lst->curr->tankAll.tank.mm = vreme.millitm;

		}
		//lst->curr->tankAll.tank.end = vreme.millitm;
		
		move_bot_barrel();
		if ((((x = clock()) - lst->curr->tankAll.tank.time) / CLOCKS_PER_SEC) > 2)
		{
			 shoot();
			lst->curr->tankAll.tank.time = x;
		}
		else if ((!(s = can_move(lst->curr->tankAll.tank.position.y, lst->curr->tankAll.tank.position.x, lst->curr->tankAll.tank.position.barrel)) ||
			(delay_s(rand() % 250 + 749, lst->curr->tankAll.tank.end, lst->curr->tankAll.tank.start, lst->curr->tankAll.tank.phase))))
		{
	  	if (s)
			{
				lst->curr->tankAll.tank.counter += 1;
				lst->curr->tankAll.tank.counter %= 6;
			}
			if ((!(lst->curr->tankAll.tank.counter)) || (!s))
			{
				lst->curr->tankAll.tank.counter = 1;
				srand(time(NULL));
				x1 = rand() % 9;
				if (array_bot_barrel[x1] == lst->curr->tankAll.tank.position.barrel)
				{
					x1++;
					x1 %= 9;
				}
				if (lst->curr->tankAll.tank.time != x)
					lst->curr->tankAll.tank.position.barrel = array_bot_barrel[x1]; // Ovde neka budu dodele vrednosti generatora za sve tezine.
			}
			//lst->curr->tankAll.tank.start = vreme.millitm;
			
		}

		lst->curr->tankAll.tank.mm = vreme.millitm;
		if (delay_s(100, lst->curr->tankAll.tank.mm, lst->curr->tankAll.tank.pp, lst->curr->tankAll.tank.phase))
			{
				action(lst->curr->tankAll.tank.position.barrel, &lst->curr->tankAll);
				ftime(&vreme);
				lst->curr->tankAll.tank.pp = vreme.millitm;
				if (!lst->curr->tankAll.projectile[0].phase)
				{
					if (!(lst->curr->tankAll.projectile[0].counter))
					{
						if(!flag) lst->curr->tankAll.projectile[0].phase = 1;
					}
					lst->curr->tankAll.projectile[0].counter++;
					lst->curr->tankAll.projectile[0].counter %= 5;
					lst->curr->tankAll.projectile[0].position.projectil_dir = lst->curr->tankAll.tank.position.last_move;
				}
			}
		}
}


void easy_bot()
{ // Mislim da bi bilo dobro da se fja zove bot, a da se tezina razlikuje u generatorima koje ces implementirati dole.
	// koristi matricu da bi odredio puteve, nemoj ubacivati kodove u vec postojece fje da bi odredio put.
	int array_bot_barrel[] = {2, 4, 3, 4, 2, 4, 3, 1, 4 }, x, s = 0,i, flag=0;
	struct timeb vreme;
	if(lst->curr== lst->first)
	{
		for(i=0;i<10;i++){
			if(array_bot_barrel[i]==4) array_bot_barrel[i]=1;
			else if(array_bot_barrel[i]==1) array_bot_barrel[i]=4;
		}
	}
	ftime(&vreme);
	if (lst->curr->tankAll.tank.phase == 2)
	{
		lst->curr->tankAll.tank.pp = lst->curr->tankAll.tank.mm = vreme.millitm;
		lst->curr->tankAll.tank.phase = 0;
		lst->curr->tankAll.tank.start = lst->curr->tankAll.tank.end = vreme.millitm;
		lst->curr->tankAll.tank.counter = 1;
		lst->curr->tankAll.projectile[0].counter = 0;
	}
	lst->curr->tankAll.tank.mm = lst->curr->tankAll.tank.end = vreme.millitm;
	srand(time(NULL));
	if ((!(s = can_move(lst->curr->tankAll.tank.position.y, lst->curr->tankAll.tank.position.x, lst->curr->tankAll.tank.position.barrel)) || 
		(delay_s(rand()%250+749, lst->curr->tankAll.tank.end, lst->curr->tankAll.tank.start, lst->curr->tankAll.tank.phase))))
	{
		if (s)
		{
			lst->curr->tankAll.tank.counter += 1;
			lst->curr->tankAll.tank.counter %= 6;
		}
		if ((!(lst->curr->tankAll.tank.counter)) || (!s))
		{
			lst->curr->tankAll.tank.counter = 1;
			srand(time(NULL));
			if ((x = (rand() % 9)), array_bot_barrel[x] == lst->curr->tankAll.tank.position.barrel)
			{
				x++;
				x %= 9;
			}
			lst->curr->tankAll.tank.position.barrel = array_bot_barrel[x]; // Ovde neka budu dodele vrednosti generatora za sve tezine.
		}
		if (lst->curr->tankAll.tank.position.barrel == 1)
		{
			lst->curr->tankAll.tank.counter =3;
		}
		lst->curr->tankAll.tank.start = vreme.millitm;

	}
	if(lst->first==lst->curr){
					switch(lst->first->tankAll.tank.position.barrel){
				case 2:
					if(lst->first->tankAll.tank.position.y>=baseY   &&  lst->first->tankAll.tank.position.x>=baseX2) flag=1; break;
				case 3:
					if(lst->first->tankAll.tank.position.y>=baseY   &&  lst->first->tankAll.tank.position.x<=baseX1) flag=1; break;
				case 4:
					if(lst->first->tankAll.tank.position.x<=baseX2  &&  lst->first->tankAll.tank.position.x>=baseX1) flag=1; break;
					}
			}

	if (delay_s(100, lst->curr->tankAll.tank.mm, lst->curr->tankAll.tank.pp, lst->curr->tankAll.tank.phase))
	{
	if (lst->curr->tankAll.tank.phase != 5)
		action(lst->curr->tankAll.tank.position.barrel, &lst->curr->tankAll);
		ftime(&vreme);
		lst->curr->tankAll.tank.pp = lst->curr->tankAll.tank.mm = vreme.millitm;
	if (!lst->curr->tankAll.projectile[0].phase)
		{
		if (!(lst->curr->tankAll.projectile[0].counter))
		{
			if(!flag) lst->curr->tankAll.projectile[0].phase = 1;
		}
		lst->curr->tankAll.projectile[0].counter++;
		lst->curr->tankAll.projectile[0].counter %= 5;
		lst->curr->tankAll.projectile[0].position.projectil_dir = lst->curr->tankAll.tank.position.last_move;
		}
	}
}
