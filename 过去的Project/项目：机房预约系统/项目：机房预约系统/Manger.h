#pragma once
#include<iostream>
#include<string>
#include"ComputerOrderSystem.h"
#include"AccountInformation.h"
#include"Teacher.h"
#include"Student.h"

#define Login_M_A "Login_M_A.txt"
#define SCI "SCI.txt"
using namespace std;

class Manger
{
public:
	Manger();
	~Manger();

	/*登录前*/
	void Manger_main();			//管理员登录界面

	void Show_Register_Menu();			//展示登录界面

	void Read_Login_In();			//读取注册完的账号

	map<string, Account_Information>Login_In_List;			//注册账号的表

	char Admin_Number[20];			//登录账号

	/*登录后*/

	void Manger_Using_menu();		//操作界面显示

	void Manger_Using_main();		//操作主界面
	
	void Pass_Account_A();			//审批账号申请
	void Pass_Account_A_S();		//审批学生账号申请
	void Pass_Account_A_T();			//审批教师账号申请

	void Read_Login_In_ST();			//读取所有账号的申请信息

	void Update_Login_In_S();			//更新所有修改后的学生账号申请信息
	void Update_Login_In_T();			//更新所有修改后的教师账号申请信息


	void Show_All_Account();			//展示所有账号信息
	void Show_All_S_Account();			//展示所有学生账号信息
	void Show_All_T_Account();			//展示所有教师账号信息

	void Show_All_Apply();			//查看所有预约信息

	void Change_CI();			//修改机房信息
	void Add_CI();			//添加机房
	void Change_CI_Change();			//修改某个机房信息

	map<int, Account_Information>Login_In_List_S;		//所有学生账号信息

	map<int, Account_Information>Login_In_List_T;			//所有教师账号信息

};