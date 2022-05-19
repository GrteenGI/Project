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
	for (int i = 0; i < Max_Size; i++)		//将电脑塞入机房，用于判定该电脑是否存在
	{
		SC_mp.insert(make_pair(Start_Number + i, Single_Computer(Number, Start_Number + i)));
	}
}


void Computer_Information::Show_Information()
{
	cout << "机房编号：" << this->Number << " " << "机房最大容量" << this->Max_Size << " ";
	cout << "机房内所有电脑编号：" << this->SC_mp.begin()->second.Number << "-" << this->SC_mp.begin()->second.Number + this->Max_Size - 1 << endl;
}