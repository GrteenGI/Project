#include"Computer_Information.h"

Computer_Information::Computer_Information()
{

}

Computer_Information::~Computer_Information()
{

}

Computer_Information::Computer_Information(int Number, int Max_Size, int Start_Number)
{
	this->Number = Number;
	this->Max_Size = Max_Size;
	this->Now_Size = Max_Size;
	char p[20] = { 0 };
	for (int i = 0; i < Max_Size; i++)		//��������������������ж��õ����Ƿ����
	{
		SC_mp.insert(make_pair(Start_Number + i, Single_Computer(Number, Start_Number + i)));
	}
}


void Computer_Information::Show_Information()
{
	cout << "������ţ�" << this->Number << " " << "�����������" << this->Max_Size << " ";
	cout << "���������е��Ա�ţ�" << this->SC_mp.begin()->second.Number << "-" << this->SC_mp.begin()->second.Number + this->Max_Size - 1 << endl;
}