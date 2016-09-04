// Solver for Ponder This August 2016
// http://researchweb.watson.ibm.com/haifa/ponderthis/challenges/August2016.html
// (C) 2016 by Harald Bögeholz
// See LICENSE file for license information

#include <stdio.h>
#include <stdlib.h>

const int n_flags = 10000;
const int BAGS = 10;

bool f[n_flags]; // flags for forbidden sums
int a[BAGS+1];   // solution being constructed (using indexes 1 .. BAGS)

int maxN = 174;


/* check if new value at a[depth] and its sums with one or two already
chosen values is forbidden */
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


/* set forbidden state for value at a[depth| and its sums with one or
two already chosen values */
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
	printf("\n");
	for (int i=BAGS; i>=1 ; --i)
		printf("%d ", a[i]);
	printf("\n");
}


void run(int depth)
{
	if (depth == 0)
		{
			print_solution();
			maxN = a[1] - 1;
			return;
		}

	for (a[depth] = (depth == BAGS ? 1 : a[depth+1] + 1);
			 a[depth] <= maxN - depth + 1;
			 ++a[depth])
		{
			if (checkall(depth))
				{
					if (depth == BAGS - 2)
						fprintf(stderr, "(%d, %d, %d .. %d)", a[BAGS], a[BAGS-1], a[BAGS-2], maxN);
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
