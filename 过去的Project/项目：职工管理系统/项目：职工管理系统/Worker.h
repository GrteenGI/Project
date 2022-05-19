#pragma once
#include<iostream>
#include<string>
using namespace std;

class Worker
{
public:
	virtual void showinfo() = 0;		//显示职工信息
	virtual string getdepartname() = 0;		//显示岗位

	int m_Age;
	string m_Name;
	string m_ID;
	string m_DepartID;
};

class NormalWorker:public Worker
{
public:
	NormalWorker(string ID, string DepartID, string Name, int Age);
	void showinfo();
	string getdepartname();
};

class Manger :public Worker
{
public:
	Manger(string ID, string DepartID, string Name, int Age);
	void showinfo();
	string getdepartname();
};

class Boss :public Worker
{
public:
	Boss(string ID, string DepartID, string Name, int Age);
	void showinfo();
	string getdepartname();
};