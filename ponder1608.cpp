// solver for Ponder This August 2016
// (C) 2016 by Harald Bögeholz

#include <stdio.h>
#include <stdlib.h>

const int n_flags = 10000;
const int BAGS = 10;

bool f[n_flags];
int a[BAGS+1];

int maxN = 174;

bool checkall(int depth)
{
	int ad = a[depth];
	if (f[ad]) return false;
	for (int i = depth+1; i<= BAGS; ++i)
		if (f[ad + a[i]]) return false;
	for (int i = depth+1; i<= BAGS; ++i)
		for (int j = i+1; j <= BAGS; ++j)
			if (f[ad + a[i] + a[j]]) return false;

	return true;
}


void setall(int depth, bool val)
{
	int ad = a[depth];
	f[ad] = val;
	for (int i = depth+1; i <= BAGS; ++i)
		f[ad + a[i]] = val;
	for (int i = depth+1; i <= BAGS; ++i)
		for (int j = i+1; j <= BAGS; ++j)
			f[ad + a[i] + a[j]] = val;
}


void print_solution(void)
{
	for (int i=1; i<= BAGS; ++i)
		printf("%d ", a[i]);
	printf("\n");
	exit(0);
}


void run(int depth)
{
	if (depth == 0)
		{
			print_solution();
			return;
		}

	for (a[depth] = (depth == BAGS ? maxN : a[depth+1]-1);
			 a[depth] >= depth;
			 --a[depth])
		{
			if (checkall(depth))
				{
					setall(depth, true);
					run(depth-1);
					setall(depth, false);
				}
		}
}


int main(void)
{
  for (int i=0; i<n_flags; ++i)
		f[i] = false;

	run(BAGS);

  return 0;
}
