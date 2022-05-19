#include<iostream>
#include"ComputerOrderSystem.h"
#include"Student.h"
#include"Teacher.h"
#include"Manger.h"
using namespace std;

int main()
{
	COS cos;
	int choice;
	//cos.CI_mp["1"].SC_mp.find(101)->second.Show_Information();
	while (1)
	{
		cos.Show_MainMenu();		//主菜单
		cout << "请输入您的选项： ";
		cin >> choice;
		if (choice == 1)			//学生端入口
		{
			system("cls");
			Student STU;
			STU.Student_main();
		}
		else if (choice == 2)		//教师端入口
		{
			system("cls");
			Teacher TEA;
			TEA.Teacher_main();
		}
		else if (choice == 3)		//管理员端入口
		{
			system("cls");
			Manger MAN;
			MAN.Manger_main();
		}
		else if (choice == 0)		//退出
		{
			cos.Exit();
		}
		else
		{
			cout << "您的输入非法，请重新输入" << endl; 
		}
	}
	system("pause");
	return 0;
}