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
		cos.Show_MainMenu();		//���˵�
		cout << "����������ѡ� ";
		cin >> choice;
		if (choice == 1)			//ѧ�������
		{
			system("cls");
			Student STU;
			STU.Student_main();
		}
		else if (choice == 2)		//��ʦ�����
		{
			system("cls");
			Teacher TEA;
			TEA.Teacher_main();
		}
		else if (choice == 3)		//����Ա�����
		{
			system("cls");
			Manger MAN;
			MAN.Manger_main();
		}
		else if (choice == 0)		//�˳�
		{
			cos.Exit();
		}
		else
		{
			cout << "��������Ƿ�������������" << endl; 
		}
	}
	system("pause");
	return 0;
}