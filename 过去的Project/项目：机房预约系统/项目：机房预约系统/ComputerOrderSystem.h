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
	void Show_MainMenu();			//展示主页面

	void Exit();				//退出

	void Read_SC_Apply();			//读取所有的预约信息

	void Read_SCI();			//读取所有静态机房信息

	void Update_SC();		//更新电脑预约信息

	void Update_Static_SC();		//更新静态机房信息，用于判断预约是否有效

	void Show_All_CI();			//展示所有机房信息

	map<int ,Computer_Information>CI_mp;		//所有预约的信息(预约的电脑极其所属机房)

	map<int, Computer_Information>static_CI_mp;			//所有机房的信息	用于确定目前机房的信息，来判断预约是否有效

	int SC_O_Number;			//最新预约单号
};