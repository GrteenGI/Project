#pragma once
#include<iostream>
#include<string>
#include"ComputerOrderSystem.h"
#include"AccountInformation.h"
#include"Teacher.h"
#include"Student.h"

#define Login_M_A "Login_M_A.txt"
#define SCI "SCI.txt"
using namespace std;

class Manger
{
public:
	Manger();
	~Manger();

	/*��¼ǰ*/
	void Manger_main();			//����Ա��¼����

	void Show_Register_Menu();			//չʾ��¼����

	void Read_Login_In();			//��ȡע������˺�

	map<string, Account_Information>Login_In_List;			//ע���˺ŵı�

	char Admin_Number[20];			//��¼�˺�

	/*��¼��*/

	void Manger_Using_menu();		//����������ʾ

	void Manger_Using_main();		//����������
	
	void Pass_Account_A();			//�����˺�����
	void Pass_Account_A_S();		//����ѧ���˺�����
	void Pass_Account_A_T();			//������ʦ�˺�����

	void Read_Login_In_ST();			//��ȡ�����˺ŵ�������Ϣ

	void Update_Login_In_S();			//���������޸ĺ��ѧ���˺�������Ϣ
	void Update_Login_In_T();			//���������޸ĺ�Ľ�ʦ�˺�������Ϣ


	void Show_All_Account();			//չʾ�����˺���Ϣ
	void Show_All_S_Account();			//չʾ����ѧ���˺���Ϣ
	void Show_All_T_Account();			//չʾ���н�ʦ�˺���Ϣ

	void Show_All_Apply();			//�鿴����ԤԼ��Ϣ

	void Change_CI();			//�޸Ļ�����Ϣ
	void Add_CI();			//��ӻ���
	void Change_CI_Change();			//�޸�ĳ��������Ϣ

	map<int, Account_Information>Login_In_List_S;		//����ѧ���˺���Ϣ

	map<int, Account_Information>Login_In_List_T;			//���н�ʦ�˺���Ϣ

};