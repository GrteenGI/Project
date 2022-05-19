#include"ComputerOrderSystem.h"
COS::COS()
{
	this->Read_SC_Apply();
	this->Read_SCI();
}

COS::~COS()
{

}

void COS::Show_MainMenu()		//ҳ��
{
	cout << "��ӭʹ����ҽ���Ļ���ԤԼϵͳ!" << endl;
	cout << "1.ѧ���˵�¼" << endl;
	cout << "2.��ʦ�˵�¼" << endl;
	cout << "3.����Ա�˵�½" << endl;
	cout << "0.�˳�ϵͳ" << endl;
}

void COS::Exit()			//�˳�
{
	cout << "��л����ʹ�ã�" << endl;
	exit(0);
}

void COS::Update_SC()			//д��map����������Single Computer��ԤԼ��Ϣ
{
	ofstream ofs;
	ofs.open(SC, ios::out | ios::binary);
	for (map<int, Computer_Information>::iterator it = this->CI_mp.begin(); it != this->CI_mp.end(); it++)
		for (multimap<int, Single_Computer>::iterator it2 = it->second.SC_mp.begin(); it2 != it->second.SC_mp.end(); it2++)
		{
			ofs.write((const char*)&(it2->second), sizeof(Single_Computer));
		}
	ofs.close();
}

void COS::Read_SC_Apply()			//��ȡ����ԤԼ��Ϣ
{
	fstream fs;
	fs.open(SC, ios::in | ios::binary);
	Single_Computer T[100];
	memset(T, 0, sizeof(T));
	this->SC_O_Number = 10000;			//���µ���
	fs.read((char*)&T, sizeof(Single_Computer) * 100);
	for (int i = 0; i < sizeof(T) / sizeof(T[0]); i++)
	{
		if (T[i].Order_Number)				//������Ų�Ϊ0
		{
			this->SC_O_Number = T[i].Order_Number;				//���µ���
			if (this->CI_mp.count(T[i].Belong_Number) == 0)			//���û�иû������
				this->CI_mp.insert(make_pair(T[i].Belong_Number, Computer_Information()));		//����Ӹû���
			this->CI_mp[T[i].Belong_Number].SC_mp.insert(make_pair(T[i].Number, T[i]));		//������������û���
		}
	}
	fs.close();
}

void COS::Read_SCI()
{
	fstream fs;
	fs.open(SCI, ios::in | ios::binary);
	Single_Computer T[150];
	memset(T, 0, sizeof(T));
	fs.read((char*)&T, sizeof(Single_Computer) * 150);
	for (int i = 0; i < sizeof(T) / sizeof(T[0]); i++)
	{
		if (T[i].Belong_Number)				//����û�����Ų�Ϊ0
		{
			if (this->static_CI_mp.count(T[i].Belong_Number) == 0)			//���û�иû������
			{
				this->static_CI_mp[T[i].Belong_Number].Max_Size = 0;
				this->static_CI_mp[T[i].Belong_Number].Number = T[i].Belong_Number;
				this->static_CI_mp.insert(make_pair(T[i].Belong_Number, Computer_Information()));
			}
			this->static_CI_mp[T[i].Belong_Number].SC_mp.insert(make_pair(T[i].Number, T[i]));
			this->static_CI_mp[T[i].Belong_Number].Max_Size++;
		}
	}
	fs.close();
}

void COS::Update_Static_SC()				//�����е��Ժͻ�����Ϣд���ļ�
{
	ofstream ofs;
	ofs.open(SCI, ios::out | ios::binary);
	for (map<int, Computer_Information>::iterator it = this->static_CI_mp.begin(); it != this->static_CI_mp.end(); it++)
		for (multimap<int, Single_Computer>::iterator it2 = it->second.SC_mp.begin(); it2 != it->second.SC_mp.end(); it2++)
		{
			ofs.write((const char*)&(it2->second), sizeof(Single_Computer));
		}
	ofs.close();
}

void COS::Show_All_CI()		//չʾ���л�����Ϣ
{
	for (map<int, Computer_Information>::iterator it = this->static_CI_mp.begin(); it != this->static_CI_mp.end(); it++)
	{
		it->second.Show_Information();
	}
}