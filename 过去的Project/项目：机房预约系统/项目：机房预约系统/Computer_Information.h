#pragma once
#include<iostream>
#include<string>
#include<map>
#include"Single_Computer.h"

#define SC "SC.txt"
using namespace std;

class Computer_Information
{
public:
	Computer_Information();
	Computer_Information(int Number, int Max_Size, int Start_Number);
	~Computer_Information();

	void Show_Information();		//չʾ������Ϣ

	int Number;			//�������
	int Max_Size;			//�����������
	int Now_Size;			//������ǰ����

	multimap<int, Single_Computer>SC_mp;			//���е���
};