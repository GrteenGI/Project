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
	/*ԤԼ�Ĺ��캯��*/
	Single_Computer(int Order_Number, int Belong_Number, int Number, Time Beg, Time End, char* Apply_Number, int Condition);
	/*��������������Ϣ�Ĺ��캯��*/
	Single_Computer(int Belong_Number, int Number);
	~Single_Computer();

	void Show_Information();

	Time Beg;
	Time End;
	int Number;			//���
	int Belong_Number;		//�����Ļ���

	int Condition;		//���״̬
	char Apply_Number[20];		//ԤԼ���˺�
	int Order_Number;			//����
};