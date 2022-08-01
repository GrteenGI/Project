#include<iostream>
using namespace std;
int F[1 << 20][21];
int len[21][21];
int min(int a, int b)
{
	if (a >= b)
	{
		return b;
	}
	else
	{
		return a;
	}
}
int main()
{
	for (int i = 0; i < 1<<20; i++)
	{
		for (int j = 0; j < 21; j++)
		{
			F[i][j] = 1000000000 ;
		}
	}
	/*memset(F, 0x3f, sizeof(F));*/  
	int n = 1;
	cin >> n;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			cin >> len[i][j];
		}
	}
	F[1][0] = 0;
	for (int i = 1; i < 1 << n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			if (i >> j & 1)
			{
				for (int k = 0; k < n; k++)
				{
					if ((i xor 1 << j) >> k & 1)
					{
						F[i][j] = min(F[i xor (1 << j)][k] + len[k][j], F[i][j]);
					}
				}
			}
		}
	}
	printf("%d\n", F[(1 << n) - 1][n-1]);
	return 0;
}