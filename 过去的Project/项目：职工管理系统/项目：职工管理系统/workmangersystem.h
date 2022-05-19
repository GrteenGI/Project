#pragma once
#include<iostream>
#include<fstream>
#include<algorithm>
#include"Worker.h"
using namespace std;

#define FILENAME "empfile.txt"

class workmangersystem
{
public:
	workmangersystem();
	~workmangersystem();
	
	void showmenu();

	void save();

	int get_empnum();		//���ڸ�������

	void update();			//��ʼ��

	int is_exist(string x);			//�ж�Ա���Ƿ����

	void exitsystem();
	
	void add_emp();

	void show_emp();

	void del_emp();

	void change_emp();

	void find_emp();

	void sort_emp();

	void clear_emp();

	int m_Empnum;

	bool m_File_is_empty;		//�ж��ļ��Ƿ�Ϊ��

	Worker** m_Emparr;			//Ա���б������ָ��
};