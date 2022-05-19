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

	int get_empnum();		//用于更新人数

	void update();			//初始化

	int is_exist(string x);			//判断员工是否存在

	void exitsystem();
	
	void add_emp();

	void show_emp();

	void del_emp();

	void change_emp();

	void find_emp();

	void sort_emp();

	void clear_emp();

	int m_Empnum;

	bool m_File_is_empty;		//判断文件是否为空

	Worker** m_Emparr;			//员工列表数组的指针
};