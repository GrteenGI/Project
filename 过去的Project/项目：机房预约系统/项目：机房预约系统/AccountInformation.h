#pragma once
#include<iostream>
#include<string>
using namespace std;

class Account_Information
{
public:
	Account_Information();
	~Account_Information();
	Account_Information(string Account, string Password, string Condition);

	string Account;
	string Password;
	string Condition;

	void Show_Information();
};