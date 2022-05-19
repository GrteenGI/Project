#include <iostream>
#include <cmath>
using namespace std;


int Reverse(int n, int a[])
{
    int t = 0;
    for (int i = 1; i < n; i++)
    {
        for (int h = 0; h < i; h++)
        {
            if (a[i] < a[h])
            {
                t = t + 1;
            }
        }
    }

    return t;
}

int Answer(int arr[10][10], int a[], int n, int t)
{
    int answer = 0;
    int temp_answer = 1;
    int t_2 = 0;

    for (int i = 0; i < n; i++)
    {
        temp_answer = temp_answer * arr[i][a[i] - 1];
    }

    t_2 = pow(-1, t);

    answer = temp_answer * t_2;

    return answer;
}

void Perm(int start, int end, int a[], int arr[10][10], int& Final_Answer)
{

    if (start == end)
    {
        Final_Answer = Final_Answer + Answer(arr, a, end, Reverse(end, a));
        return;
    }
    for (int i = start; i < end; i++)
    {
        swap(a[start], a[i]);
        Perm(start + 1, end, a, arr, Final_Answer);
        swap(a[i], a[start]);
    }

}


int main()
{
    int Final_Answer = 0;
    int i, n, a[10];
    int arr[10][10];
    cout << "请输入行列式的阶数" << endl;
    cin >> n;
    for (i = 0; i < n; i++)         //给排列赋值
    {
        a[i] = i + 1;
    }

    for (int i = 0; i < n; i++)
    {
        cout << endl;
        for (int h = 0; h < n; h++)
        {
            cout << "a" << i + 1 << h + 1 << " 的值：";
            cin >> arr[i][h];
        }
    }

    Perm(0, n, a, arr, Final_Answer);

    cout << "行列式的值为： " << Final_Answer << endl;

    return 0;
}