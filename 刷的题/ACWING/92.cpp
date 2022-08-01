#include<iostream>
#include<vector>
using namespace std;
int arr[21];
vector<int> v1;
int n = 0;
void cal(int arr[21], int i)
{
	if (i == n)
	{
		for (int j = 0; j < v1.size(); j++)
		{
			cout << v1[j] << " ";
		}
		cout << endl;
		return;
	}
	//不选择的分支
	cal(arr, i + 1);		//求解子问题

	//选择的分支
	v1.push_back(arr[i]);	//记录i已被选择
	cal(arr, i + 1);
	v1.pop_back();			//回溯到上一问题之前，还原
}
int main()
{
	cin >> n;
	for (int i = 0; i < n; i++)
	{
		arr[i] = i + 1;
	}
	cal(arr, 0);

	return 0;
}