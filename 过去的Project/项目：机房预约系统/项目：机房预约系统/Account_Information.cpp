#include"AccountInformation.h"
Account_Information::Account_Information()
{

}

Account_Information::~Account_Information()
{

}

Account_Information::Account_Information(string Account, string Password, string Condition)
{
	this->Account = Account;
	this->Condition = Condition;
	this->Password = Password;
}

void Account_Information::Show_Information()
{
	cout << "�˺ţ�" << this->Account << " " << "���룺" << this->Password << "  " << "״̬��" << this->Condition << endl;
}