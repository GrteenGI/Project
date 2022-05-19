#include"Single_Computer.h"

Single_Computer::~Single_Computer()
{

}

Single_Computer::Single_Computer()
{

}
/*创建预约时的构造函数*/
Single_Computer::Single_Computer(int Order_Number, int Belong_Number, int Number, Time Beg, Time End, char* Apply_Number, int Condition)
{
	this->Order_Number = Order_Number;
	this->Belong_Number = Belong_Number;
	this->Number = Number;
	this->Beg = Beg;
	this->End = End;
	for (int i = 0; i < 20; i++)
		this->Apply_Number[i] = Apply_Number[i];
	this->Condition = Condition;
}
/*创建单个电脑时的构造函数*/
Single_Computer::Single_Computer(int Belong_Number, int Number)
{
	this->Belong_Number = Belong_Number;
	this->Number = Number;
}

void Single_Computer::Show_Information()		//展示所有信息
{
	cout << "单号：" << this->Order_Number << " ";
	cout << "所属机房：" << this->Belong_Number << " " << "编号：" << this->Number << " " << "预约开始时间：";
	this->Beg.Show_Time();
	cout << " ";
	cout << "预约结束时间：";
	this->End.Show_Time();
	cout << " ";
	cout << "预约人：" << this->Apply_Number << " ";
	cout << "状态：";
	if (this->Condition == 1)
		cout << "已通过";
	else if (this->Condition == 2)
		cout << "未通过";
	else
		cout << "审核中";
	cout << endl;
}

Time::Time(int Year, int Month, int Day, int Hour, int Minute)
{
	this->Year = Year;
	this->Minute = Minute;
	this->Month = Month;
	this->Hour = Hour;
	this->Day = Day;
}

Time::Time()
{

}

Time::~Time()
{

}

bool Time::operator>=(Time t)
{
	if (this->Year > t.Year) return true;
	else if (this->Year < t.Year) return false;
	if (this->Month > t.Month) return true;
	else if (this->Month < t.Month) return false;
	if (this->Day > t.Day) return true;
	else if (this->Day < t.Day) return false;
	if (this->Hour > t.Hour) return true;
	else if (this->Hour < t.Hour) return false;
	if (this->Minute > t.Minute) return true;
	else if (this->Minute < t.Minute) return false;

	return true;		//全部相同
}

void Time::Show_Time()
{
	cout << this->Year << "/" << this->Month << "/" << this->Day << "/" << " " << this->Hour << ":" << this->Minute;
}