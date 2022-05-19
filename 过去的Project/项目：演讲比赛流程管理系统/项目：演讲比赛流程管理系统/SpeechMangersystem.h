#pragma once
#include<iostream>
#include<deque>
#include<algorithm>
#include<fstream>

#define FILENAME "Order.csv"		//记录文件

#include"contestant.h"

using namespace std;

class SpeechMangersystem
{
public:
	SpeechMangersystem();
	~SpeechMangersystem();

	void showmenu();		//菜单

	void exitsystem();		//退出系统

	void _prev();			//预赛

	void _final();			//决赛

	void start();			//开始演讲比赛流程

	void initList();			//初始化选手列表

	void update();			//更新记录

	int getnum();			//获取记录条数

	void showorder();			//展示记录

	void tempclear();			//清理运行时的列表数据

	void textclear();			//清理文本文件的列表数据

	int Ordernum;			//记录数量

	vector<contestant>OrderList[100];		//记录条目

private:
	vector<contestant>List[26];			//选手列表
	vector<contestant>AdvList;		//预赛晋级选手列表	
};