#pragma once
#include<iostream>
#include<string>
#include<map>
#include"ComputerOrderSystem.h"
#include"AccountInformation.h"
using namespace std;
#define Login_T_A "Login_T_A.txt"

class Teacher
{
public:
	Teacher();
	~Teacher();
	//��½ǰ
	void Teacher_main();			//��ʦ��¼������

	void Show_Register_Menu();			//չʾ��¼����

	int Get_Now_Number();			//��ȡ��ǰ����ע��ĵ���

	void T_Login_In();			//��ʦע��

	void Read_Login_In();			//��ȡ�Ѿ�ͨ�����˺�
	//��½��
	void Teacher_Using_menu();		//����������ʾ

	void Teacher_Using_main();		//����������

	void Pass_Apply();		//ͨ��ԤԼ����

	void Show_All_Apply();			//չʾ����ԤԼ��Ϣ

	int Now_Number;					//���ڵĵ���

	char Admin_Number[20];			//��¼�˺�

	map<string, Account_Information>Login_In_List;		//ע���˺ŵı�
};