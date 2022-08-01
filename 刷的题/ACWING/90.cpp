#include<iostream>
using namespace std;
int main()
{
	long long a, b, p;
	long long ans = 0;
	cin >> a >> b >> p;
	while (b > 0)
	{
		if (b & 1)
		{
			ans = (ans + a) % p;
		}
		a = a * 2 % p;
		b = b >> 1;
	}
	cout << ans << endl;
	return 0;
}