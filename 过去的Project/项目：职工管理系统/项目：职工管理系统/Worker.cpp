#include"Worker.h"

NormalWorker::NormalWorker(string ID, string DepartID, string Name, int Age)
{
	this->m_ID = ID;
	this->m_DepartID = DepartID;
	this->m_Name = Name;
	this->m_Age = Age;
}

void NormalWorker::showinfo()
{
	cout << "职工编号： " << this->m_ID << "\t"
		<< "部门编号:  " << this->m_DepartID << "\t"
		<< "职工姓名:  " << this->m_Name << "\t"
		<< "职工年龄： " << this->m_Age << endl;
}

string NormalWorker::getdepartname()
{
	return string("码农");
}



Manger::Manger(string ID, string DepartID, string Name, int Age)
{
	this->m_ID = ID;
	this->m_DepartID = DepartID;
	this->m_Name = Name;
	this->m_Age = Age;
}

void Manger::showinfo()
{
	cout << "职工编号： " << this->m_ID << "\t"
		<< "部门编号:  " << this->m_DepartID << "\t"
		<< "职工姓名:  " << this->m_Name << "\t"
		<< "职工年龄： " << this->m_Age << endl;
}

string Manger::getdepartname()
{
	return string("经理");
}


Boss::Boss(string ID, string DepartID, string Name, int Age)
{
	this->m_ID = ID;
	this->m_DepartID = DepartID;
	this->m_Name = Name;
	this->m_Age = Age;
}

void Boss::showinfo()
{
	cout << "职工编号： " << this->m_ID << "\t"
		<< "部门编号:  " << this->m_DepartID << "\t"
		<< "职工姓名:  " << this->m_Name << "\t"
		<< "职工年龄： " << this->m_Age << endl;
}

string Boss::getdepartname()
{
	return string("老板");
}