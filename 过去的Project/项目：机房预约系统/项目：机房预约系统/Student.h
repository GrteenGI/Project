#pragma once
#include<iostream>
#include<string>
#include<fstream>
#include<map>
#include"ComputerOrderSystem.h"
#include"AccountInformation.h"

#define Login_S_A "Login_S_A.txt"
using namespace std;

class Student
{
public:
	Student();

	~Student();
	/*��¼ǰ*/

	void Student_main();			//��¼��ҳ��

	void Show_Register_Menu();		//��¼��ʾ

	void Login_In();				//ע�����

	void Read_Login_In();			//��ȡע������˺�

	int Get_Now_Number();			//��ȡ��ǰ����ע��ĵ���

	/*��¼��Ľ���*/
	void Student_Using_menu();		//����������ʾ

	void Student_Using_main();		//����������

	void Apply_For_Computer();		//�������

	void Show_All_My_Apply();			//��ʾ�ҵ�����

	void delete_My_Apply();			//ȡ��ԤԼ

	map<string, Account_Information>Login_In_List;			//ע���˺ŵı�

	int Now_Number;					//���ڵĵ���

	char Admin_Number[20];			//��¼�˺�
};