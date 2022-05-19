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

	void Show_Information();		//展示机房信息

	int Number;			//机房编号
	int Max_Size;			//机房最高容量
	int Now_Size;			//机房当前容量

	multimap<int, Single_Computer>SC_mp;			//所有电脑
};