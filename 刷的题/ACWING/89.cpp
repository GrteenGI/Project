#include<iostream>
using namespace std;
int main()
{
	long long a, b, p, ans;
	cin >> a >> b >> p;
	ans = 1 % p;
	while (b > 0)
	{
		if (b & 1)
		{
			ans = ans * a % p;
		}
		a = a * a % p;
		b = b >> 1;
	}
	cout << ans << endl;
	return 0;
}