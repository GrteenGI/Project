#pragma once
#include<iostream>
#include<fstream>
using namespace std;

class Time
{
public:
	int Year;
	int Month;
	int Day;

	int Hour;
	int Minute;

	Time(int Year, int Month, int Day, int Hour, int Minute);
	Time();
	~Time();

	bool operator>=(Time t);

	void Show_Time();
};

class Single_Computer
{
public:

	Single_Computer();
	/*预约的构造函数*/
	Single_Computer(int Order_Number, int Belong_Number, int Number, Time Beg, Time End, char* Apply_Number, int Condition);
	/*创建单个电脑信息的构造函数*/
	Single_Computer(int Belong_Number, int Number);
	~Single_Computer();

	void Show_Information();

	Time Beg;
	Time End;
	int Number;			//编号
	int Belong_Number;		//所属的机房

	int Condition;		//审核状态
	char Apply_Number[20];		//预约人账号
	int Order_Number;			//单号
};