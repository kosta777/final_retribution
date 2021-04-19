#include "tank.h"
int array_bot_barrel1[] = { 2, 4, 3, 4, 2, 3, 4 }, x1;
int array_bot_barrel2[] = { 2, 1, 3, 1, 2, 3, 1 };

int position_in_box(Box box)
{
	int bot_x = lst->curr->tankAll.tank.position.x - x1b;
	int bot_y = lst->curr->tankAll.tank.position.y - y1b;
	int pl_x = lst->first->tankAll.tank.position.x - x1b;
	int pl_y = lst->first->tankAll.tank.position.y - y1b;

	if ((bot_x<box.min_x) || (bot_x>box.max_x) || (bot_y<box.min_y) || (bot_y>box.max_y))
		return 0; // nije u kutiji
	else if ((bot_x == pl_x) || (bot_y == pl_y))
		return 5;
	else if ((bot_x < pl_x) && (bot_y < pl_y))
		return 1; // kada se bot nalazi gore levo od tenka u kutiji
	else if ((bot_x > pl_x) && (bot_y < pl_y))
		return 2; // bot se nalazi gore desno od tenka
	else if ((bot_x < pl_x) && (bot_y>pl_y))
		return 3; // bot je dole levo
	else if ((bot_x > pl_x) && (bot_y > pl_y))
		return 4; // bot je dole desno 
		 // ako se nalazi u vrsti ili koloni sa botom

}

int position_in_b_box(Box box)
{
	int bot_x = lst->curr->tankAll.tank.position.x - x1b;
	int bot_y = lst->curr->tankAll.tank.position.y - y1b;
	if ((bot_x<box.min_x) || (bot_x>box.max_x) || (bot_y < box.min_y))
		return 0;
	else if ((bot_x <= (baseX2 - 1)) && (bot_x >= baseX1 + 1))
		return 1;
	else if ((bot_y >= baseY + 1) && (bot_x < baseX1))
		return 2;
	else if ((bot_y >= (baseY + 1)) && (bot_x > baseX1))
		return 3;
	else if ((bot_y < baseY) && (bot_x < baseX1))
		return 4;
	else if ((bot_y<baseY + 1) && (bot_x>baseX2))
		return 5;
}

Box base_box(Box box)
{
	int i,j;
	box.min_x = 0;
	box.min_y = 0;
	box.max_x = 0;
	box.max_y = 66;
	
	for (j = baseY - 1; j > 0; j--)
	{
		for (i = 0; i < dimx - 1; i++)
		{
			if (matrix[j][i] == 'c')
			{
				box.min_y = j + 1;
				break;
			}
		}
		if (box.min_y)
			break;
	}
	for (i = baseX1 - 1; i > 0; i--)
	{
		for (j = box.max_y - 1; j > box.min_y; j--)
		{
			if (matrix[j][i] == 'c')
			{
				box.min_x = i + 1;
				break;
			}
		}
		if (box.min_x)
			break;
	}
	for (i = baseX2 + 1; i < dimx - 1; i++)
	{
		for (j = box.max_y - 1; j > box.min_y; j--)
		{
			if (matrix[j][i] == 'c')
			{
				box.max_x = i - 1;
				break;
			}
		}
		if (box.max_x)
			break;
	}
	return box;
}

Box get_box(Box box)
{
	int i, j;
	int x = lst->first->tankAll.tank.position.x - x1b;
	int y = lst->first->tankAll.tank.position.y - y1b;

	for (i = x - 2; i > 0; i--)
	{
		for (j = 1; j < dimy - 1; j++)
		{
			if (matrix[j][i] == 'c')
			{
				box.min_x = i + 1;
				break;
			}
		}
		if (box.min_x != 0)
			break;
	}

	for (j = y - 2; j > 0; j--)
	{
		for (i = box.min_x; i < dimx - 1; i++)
		{
			if (matrix[j][i] == 'c')
			{
				box.min_y = j + 1;
				break;
			}
		}
		if (box.min_y != 0)
		{
			break;
		}
	}

	for (i = x + 2; i < dimx - 1; i++)
	{
		for (j = box.min_y; j < dimy - 1; j++)
		{
			if (matrix[j][i] == 'c')
			{
				box.max_x = i - 1;
				break;
			}
		}
		if (box.max_x != 0)
			break;
	}

	for (j = y + 2; j < dimy - 1; j++)
	{
		for (i = box.min_x; i <= box.max_x; i++)
		{
			if (matrix[j][i] == 'c')
			{
				box.max_y = j - 1;
				break;
			}
		}
		if (box.max_y != 0)
			break;
	}
	return box;
}

int barricades(int choice) // ako je 1 onda se gleda broj cigala kad se fiksira x koordinata a 2 kad je fiksirana y koordinata, 3 i 4 za spec. tenk
{
	int bot_x = lst->curr->tankAll.tank.position.x - x1b;
	int bot_y = lst->curr->tankAll.tank.position.y - y1b;
	int pl_x = lst->first->tankAll.tank.position.x - x1b;
	int pl_y = lst->first->tankAll.tank.position.y - y1b;
	int sum = 0, i;
	if ((choice == 1) || (choice ==3))
	{
		if (bot_y > pl_y)
		{
			for (i = pl_y - 2; i > bot_y; i--)
			{
				if (matrix[i][pl_x] == 'b')
					sum++;
				if ((matrix[i][pl_x] == 'c') && (choice == 3))
					sum++;
			}
			return sum;
		}
		else
		{
			for (i = pl_y + 2; i < bot_y; i++)
			{
				if (matrix[i][pl_x] == 'b')
					sum++;
				if ((matrix[i][pl_x] == 'c') && (choice == 3))
					sum++;
			}
			return sum;
		}
	}
	else if ((choice == 2) || (choice ==4))
	{
		if (bot_x>pl_x)
		{
			for (i = pl_x + 2; i < bot_x; i++)
			{
				if (matrix[pl_y][i] == 'b')
					sum++;
				if ((choice == 4) && (matrix[pl_y][i] == 'c'))
					sum++;
			}
			return sum;
		}
		else
		{
			for (i = pl_x - 2; i > bot_x; i--)
			{
				if (matrix[pl_y][i] == 'b')
					sum++;
				if ((choice == 4) && (matrix[pl_y][i] == 'c'))
					sum++;
			}
			return sum;
		}
	}
}

void get_direction(int position)
{
	int bot_x = lst->curr->tankAll.tank.position.x - x1b;
	int bot_y = lst->curr->tankAll.tank.position.y - y1b;
	int pl_x = lst->first->tankAll.tank.position.x - x1b;
	int pl_y = lst->first->tankAll.tank.position.y - y1b;
	int left, right, up, down;
	down = ((matrix[bot_y + 2][bot_x - 1] == 'w') || (matrix[bot_y + 2][bot_x] == 'w') || (matrix[bot_y + 2][bot_x + 1] == 'w'));
	up = ((matrix[bot_y - 2][bot_x - 1] == 'w') || (matrix[bot_y - 2][bot_x] == 'w') || (matrix[bot_y - 2][bot_x + 1] == 'w'));
	right = ((matrix[bot_y - 1][bot_x + 2] == 'w') || (matrix[bot_y][bot_x + 2] == 'w') || (matrix[bot_y + 1][bot_x + 2] == 'w'));
	left = ((matrix[bot_y - 1][bot_x - 2] == 'w') || (matrix[bot_y][bot_x - 2] == 'w') || (matrix[bot_y + 1][bot_x - 2] == 'w'));
	switch (position)
	{
	case 1:
		if (down)
		{
			lst->curr->tankAll.tank.position.barrel = 3;
			return;
		}
		else if (right)
		{
			lst->curr->tankAll.tank.position.barrel = 4;
			return;
		}
	case 2:
		if (down)
		{
			lst->curr->tankAll.tank.position.barrel = 2;
			return;
		}
		else if (left)
		{
			lst->curr->tankAll.tank.position.barrel = 4;
			return;
		}
	case 3:
		if (up)
		{
			lst->curr->tankAll.tank.position.barrel = 3;
			return;
		}
		else if (right)
		{
			lst->curr->tankAll.tank.position.barrel = 1;
			return;
		}
	case 4:
		if (left)
		{
			lst->curr->tankAll.tank.position.barrel = 1;
			return;
		}
		else if (up)
		{
			lst->curr->tankAll.tank.position.barrel = 2;
			return;
		}
	}
	if (lst->curr->tankAll.tank.type==0)
	{
		if ((abs(bot_x - pl_x) + barricades(1)) >= (abs(bot_y - pl_y) + barricades(2)))
		{
			switch (position)
			{
			case 1: case 2: lst->curr->tankAll.tank.position.barrel = 4; break;
			case 3: case 4: lst->curr->tankAll.tank.position.barrel = 1; break;
			}
		}
		else
		{
			switch (position)
			{
			case 1: case 3: lst->curr->tankAll.tank.position.barrel = 3; break;
			case 2: case 4: lst->curr->tankAll.tank.position.barrel = 2; break;
			}
		}
	}
	else
	{
		if ((abs(bot_x - pl_x) + barricades(3)) >= (abs(bot_y - pl_y) + barricades(4)))
		{
			switch (position)
			{
			case 1: case 2: lst->curr->tankAll.tank.position.barrel = 4; break;
			case 3: case 4: lst->curr->tankAll.tank.position.barrel = 1; break;
			}
		}
		else
		{
			switch (position)
			{
			case 1: case 3: lst->curr->tankAll.tank.position.barrel = 3; break;
			case 2: case 4: lst->curr->tankAll.tank.position.barrel = 2; break;
			}
		}
	}
	
}

void hard_bot()
{

	int s;
	struct timeb vreme;
	clock_t x;
	int position;
	Box box, b_box;
	ftime(&vreme);
		if (lst->curr->tankAll.tank.phase == 2)
		{
			lst->curr->tankAll.tank.counter1 = 0;
			lst->curr->tankAll.tank.time = clock();
			lst->curr->tankAll.tank.pp = lst->curr->tankAll.tank.mm = vreme.millitm;
			lst->curr->tankAll.tank.phase = 0;
			lst->curr->tankAll.tank.start = lst->curr->tankAll.tank.end = vreme.millitm;
			lst->curr->tankAll.tank.counter = 1;
			lst->curr->tankAll.projectile[0].counter = 0;
		}
		lst->curr->tankAll.tank.mm = lst->curr->tankAll.tank.end = vreme.millitm;

		b_box.max_x = 0;
		b_box.max_y = 0;
		b_box.min_y = 0;
		b_box.min_x = 0;

		box.max_x = 0;
		box.max_y = 0;
		box.min_y = 0;
		box.min_x = 0;

		get_box(box);
		position = position_in_box(box);
		if (!position)
		{
			if (!lst->curr->tankAll.projectile[0].phase)
				find_bullet();
			lst->curr->tankAll.tank.on_player = 0;
			if (lst->curr->tankAll.tank.counter1++ == 1)
			{
				lst->curr->tankAll.tank.start = lst->curr->tankAll.tank.end = vreme.millitm;
				lst->curr->tankAll.tank.counter = 1;
				lst->curr->tankAll.tank.pp = lst->curr->tankAll.tank.mm = vreme.millitm;
			}
			lst->curr->tankAll.tank.end = vreme.millitm;
			if (!lst->curr->tankAll.projectile[0].phase)
			{
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
						if (array_bot_barrel1[x1] == lst->curr->tankAll.tank.position.barrel)
						{
							x1++;
							x1 %= 9;
						}
						if (lst->curr->tankAll.tank.time != x)
							lst->curr->tankAll.tank.position.barrel = array_bot_barrel1[x1]; // Ovde neka budu dodele vrednosti generatora za sve tezine.
					}
				}
				lst->curr->tankAll.tank.start = vreme.millitm;
			}
			// ubaci sta se dogadja kad bot nije u kutiji 
		}
		else if (position == 5)
		{

			if (!lst->curr->tankAll.projectile[0].phase)
			{

				find_bullet();
			}
			lst->curr->tankAll.tank.on_player = 1;
		}
		else
		{
			lst->curr->tankAll.tank.on_player = 1;
			get_direction(position);
		}
		base_box(b_box);
		position = position_in_b_box(b_box);
		if (!position)
			lst->curr->tankAll.tank.on_base = 0;
		else
		{
			int a = lst->curr->tankAll.tank.position.x - x1b;
			int b = lst->curr->tankAll.tank.position.y - y1b;

			switch (position)
			{
			case 1:
				lst->curr->tankAll.tank.position.barrel = 4;
				lst->curr->tankAll.projectile[0].phase = 1;
				break;
			case 2:
				lst->curr->tankAll.tank.position.barrel = 3;
				lst->curr->tankAll.projectile[0].phase = 1;
				break;
			case 3:
				lst->curr->tankAll.tank.position.barrel = 2;
				lst->curr->tankAll.projectile[0].phase = 1;
				break;
			case 4:
				if (abs(b - baseY - 1) > abs(a - baseX1 - 1))
					lst->curr->tankAll.tank.position.barrel = 3;
				else
					lst->curr->tankAll.tank.position.barrel = 4;
				break;
			case 5:
				if (abs(b - baseY - 1) > abs(a - baseX1 - 1))
					lst->curr->tankAll.tank.position.barrel = 2;
				else
					lst->curr->tankAll.tank.position.barrel = 4;
				break;
			}
			lst->curr->tankAll.tank.on_base = 1;
		}
		if (delay_s(100, lst->curr->tankAll.tank.mm, lst->curr->tankAll.tank.pp, lst->curr->tankAll.tank.phase))
		{
			if (lst->curr->tankAll.tank.phase != 5)
			{
				action(lst->curr->tankAll.tank.position.barrel, &lst->curr->tankAll);
				lst->curr->tankAll.projectile[0].position.projectil_dir = lst->curr->tankAll.tank.position.last_move;
			}

			ftime(&vreme);
			lst->curr->tankAll.tank.pp = lst->curr->tankAll.tank.mm = vreme.millitm;
			if (!lst->curr->tankAll.projectile[0].phase)
			{
				if (!(lst->curr->tankAll.projectile[0].counter))
				{
					lst->curr->tankAll.projectile[0].phase = 1;
				}
				lst->curr->tankAll.projectile[0].counter++;
				lst->curr->tankAll.projectile[0].counter %= 5;
				lst->curr->tankAll.projectile[0].position.projectil_dir = lst->curr->tankAll.tank.position.last_move;
			}
		}
	}
	//================================================================================================================================


void find_bullet_demo()
{
	int i = 0;
	while ((matrix[lst->curr->tankAll.tank.position.y - y1b - 2 - i][lst->curr->tankAll.tank.position.x - x1b] == ' ') ||
		(matrix[lst->curr->tankAll.tank.position.y - y1b - 2 - i][lst->curr->tankAll.tank.position.x - x1b] == 'g') ||
		(matrix[lst->curr->tankAll.tank.position.y - y1b - 2 - i][lst->curr->tankAll.tank.position.x - x1b] == 'w'))
		i++;

	if ((matrix[lst->curr->tankAll.tank.position.y - y1b - 2 - i][lst->curr->tankAll.tank.position.x - x1b] == '*') ||
		(matrix[lst->curr->tankAll.tank.position.y - y1b - 2 - i][lst->curr->tankAll.tank.position.x - x1b] == 't'))
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

	if ((matrix[lst->curr->tankAll.tank.position.y - y1b][lst->curr->tankAll.tank.position.x - x1b - 2 - i] == '*') ||
		(matrix[lst->curr->tankAll.tank.position.y - y1b][lst->curr->tankAll.tank.position.x - x1b - 2 - i] == 't'))
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
	if ((matrix[lst->curr->tankAll.tank.position.y - y1b][lst->curr->tankAll.tank.position.x - x1b + 2 + i] == '*')||
		(matrix[lst->curr->tankAll.tank.position.y - y1b][lst->curr->tankAll.tank.position.x - x1b + 2 + i] == 't'))
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

	if ((matrix[lst->curr->tankAll.tank.position.y - y1b + 2 + i][lst->curr->tankAll.tank.position.x - x1b] == '*') ||
		(matrix[lst->curr->tankAll.tank.position.y - y1b + 2 + i][lst->curr->tankAll.tank.position.x - x1b] == 't'))
	{
		lst->curr->tankAll.tank.position.barrel = 4;
		lst->curr->tankAll.projectile[0].phase = 1;
		lst->curr->tankAll.projectile[0].position.projectil_dir = lst->curr->tankAll.tank.position.barrel;
		return;
	}
}

void hard_bot_demo()
{
	int s,flag=0;
	struct timeb vreme;
	clock_t x;
	ftime(&vreme);
	if (lst->curr->tankAll.tank.phase == 2)
	{
		lst->curr->tankAll.tank.counter1 = 0;
		lst->curr->tankAll.tank.time = clock();
		lst->curr->tankAll.tank.pp = lst->curr->tankAll.tank.mm = vreme.millitm;
		lst->curr->tankAll.tank.phase = 0;
		lst->curr->tankAll.tank.start = lst->curr->tankAll.tank.end = vreme.millitm;
		lst->curr->tankAll.tank.counter = 1;
		lst->curr->tankAll.projectile[0].counter = 0;
	}
	lst->curr->tankAll.tank.mm = lst->curr->tankAll.tank.end = vreme.millitm;
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

	if (!lst->curr->tankAll.projectile[0].phase){
		if(!flag)find_bullet_demo();
	}

	if (lst->curr->tankAll.tank.counter1++ == 1)
	{
		lst->curr->tankAll.tank.start = lst->curr->tankAll.tank.end = vreme.millitm;
		lst->curr->tankAll.tank.counter = 1;
		lst->curr->tankAll.tank.pp = lst->curr->tankAll.tank.mm = vreme.millitm;
	}
	lst->curr->tankAll.tank.end = vreme.millitm;


	if (!lst->curr->tankAll.projectile[0].phase)
	{
		if ((((x = clock()) - lst->curr->tankAll.tank.time) / CLOCKS_PER_SEC) > 2)
		{
			
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
			if(!flag) shoot();
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
				if (array_bot_barrel2[x1] == lst->curr->tankAll.tank.position.barrel)
				{
					x1++;
					x1 %= 9;
				}
				if (lst->curr->tankAll.tank.time != x)
					lst->curr->tankAll.tank.position.barrel = array_bot_barrel2[x1]; // Ovde neka budu dodele vrednosti generatora za sve tezine.
			}
		}
		lst->curr->tankAll.tank.start = vreme.millitm;
	}
	
	
	if (delay_s(100, lst->curr->tankAll.tank.mm, lst->curr->tankAll.tank.pp, lst->curr->tankAll.tank.phase))
	{
		if (lst->curr->tankAll.tank.phase != 5)
		{
			action(lst->curr->tankAll.tank.position.barrel, &lst->curr->tankAll);
			lst->curr->tankAll.projectile[0].position.projectil_dir = lst->curr->tankAll.tank.position.last_move;
		}

		ftime(&vreme);
		lst->curr->tankAll.tank.pp = lst->curr->tankAll.tank.mm = vreme.millitm;
		if (!lst->curr->tankAll.projectile[0].phase)
		{
			
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