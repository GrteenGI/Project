#pragma once
#include<iostream>
#include<string>
#include<vector>
#include<deque>
#include<algorithm>
#include<numeric>
using namespace std;

class contestant				//选手
{
public:
	contestant();
	~contestant();
	contestant(char name, int id, double score);

	void showinfo();			//展示信息

	static double givescore();			//随机判分
	static void initnameseed();			//随机参赛选手的姓名
	static int dividnum;		//分组人数
	static int contestantnum;			//选手人数
	static int advancenum;			//预选赛晋级人数

	static vector <char> m_initseed;	//参赛选手随机姓名
	double m_score;

	char m_name;
	int m_ID;
};