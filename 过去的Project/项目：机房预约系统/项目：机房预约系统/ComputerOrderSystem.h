#pragma once
#include"Computer_Information.h"
#include<fstream>
#include<iostream>
#include<vector>
#include<map>
#include<string>

#define SCI "SCI.txt"
using namespace std;
class COS
{
public:
	COS();
	~COS();
	void Show_MainMenu();			//չʾ��ҳ��

	void Exit();				//�˳�

	void Read_SC_Apply();			//��ȡ���е�ԤԼ��Ϣ

	void Read_SCI();			//��ȡ���о�̬������Ϣ

	void Update_SC();		//���µ���ԤԼ��Ϣ

	void Update_Static_SC();		//���¾�̬������Ϣ�������ж�ԤԼ�Ƿ���Ч

	void Show_All_CI();			//չʾ���л�����Ϣ

	map<int ,Computer_Information>CI_mp;		//����ԤԼ����Ϣ(ԤԼ�ĵ��Լ�����������)

	map<int, Computer_Information>static_CI_mp;			//���л�������Ϣ	����ȷ��Ŀǰ��������Ϣ�����ж�ԤԼ�Ƿ���Ч

	int SC_O_Number;			//����ԤԼ����
};