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
	//��ѡ��ķ�֧
	cal(arr, i + 1);		//���������

	//ѡ��ķ�֧
	v1.push_back(arr[i]);	//��¼i�ѱ�ѡ��
	cal(arr, i + 1);
	v1.pop_back();			//���ݵ���һ����֮ǰ����ԭ
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