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
	cout << "ְ����ţ� " << this->m_ID << "\t"
		<< "���ű��:  " << this->m_DepartID << "\t"
		<< "ְ������:  " << this->m_Name << "\t"
		<< "ְ�����䣺 " << this->m_Age << endl;
}

string NormalWorker::getdepartname()
{
	return string("��ũ");
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
	cout << "ְ����ţ� " << this->m_ID << "\t"
		<< "���ű��:  " << this->m_DepartID << "\t"
		<< "ְ������:  " << this->m_Name << "\t"
		<< "ְ�����䣺 " << this->m_Age << endl;
}

string Manger::getdepartname()
{
	return string("����");
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
	cout << "ְ����ţ� " << this->m_ID << "\t"
		<< "���ű��:  " << this->m_DepartID << "\t"
		<< "ְ������:  " << this->m_Name << "\t"
		<< "ְ�����䣺 " << this->m_Age << endl;
}

string Boss::getdepartname()
{
	return string("�ϰ�");
}