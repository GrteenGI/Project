#include"SpeechMangersystem.h";

class Listcmp
{
public:
	bool operator()(contestant a, contestant b)
	{
		return a.m_score > b.m_score;
	}
};

void SpeechMangersystem::update()				//д���ı������е���Ϣ
{
	this->Ordernum = getnum();
	int num = 0;
	ifstream ifs;
	ifs.open(FILENAME, ios::in);
	
	char name;
	int ID;
	double score;
	int Ordtimes;
	while (ifs >> name && ifs >> ID && ifs >> score && ifs >> Ordtimes)
	{
		this->OrderList[Ordtimes].push_back(contestant(name, ID, score));
	}
	ifs.close();
}

int SpeechMangersystem::getnum()				//��ȡ�ı��е�����
{
	int num = 0;
	ifstream ifs;
	ifs.open(FILENAME, ios::in);
	char buf[1024] = { 0 };
	while (ifs.getline(buf, sizeof(buf)))
	{
		num++;
	}
	ifs.close();
	return num;
}

SpeechMangersystem::SpeechMangersystem()
{
	ifstream ifs;
	ifs.open(FILENAME, ios::in);
	if (!ifs.is_open())
	{
		this->Ordernum = 0;
		return;
	}

	char ch;
	ifs >> ch;
	if (ifs.eof())
	{
		this->Ordernum = 0;
		return;
	}
	this->update();
	ifs.close();
}

SpeechMangersystem::~SpeechMangersystem()
{

}

void SpeechMangersystem::showmenu()				//�˵�
{
	cout << "��ӭʹ���ݽ��������̹���ϵͳ" << endl;
	cout << "1.��ʼ�ݽ�����" << endl;
	cout << "2.�鿴�����¼" << endl;
	cout << "3.��������¼" << endl;
	cout << "0.�˳�����ϵͳ" << endl;
	cout << endl;
}

void SpeechMangersystem::exitsystem()			//�˳�ϵͳ
{
	cout << "��ӭ�´�ʹ�ã�" << endl;
	system("pause");
	exit(0);
}

void SpeechMangersystem::initList()					//�������ÿ��ѡ�ֵ���Ϣ�ͷ���
{
	contestant::initnameseed();
	int k = 0;
	int t = contestant::contestantnum / contestant::dividnum;
	for (vector<char>::iterator it = contestant::m_initseed.begin(); it != contestant::m_initseed.end(); it++)
	{
		this->List[k % t].push_back(contestant(contestant::m_initseed[k], 10000 + k, contestant::givescore()));
		k++;
	}
		
}

void SpeechMangersystem::_prev()			//Ԥ��
{
	cout << "���������ѡ��������";
	cin >> contestant::contestantnum;
	while (1)
	{
		if (contestant::contestantnum > 26)
		{
			cout << "�����������Ӳ����İ���" << endl;
			cin >> contestant::contestantnum;
		}
		if (contestant::contestantnum <= 0)
		{
			cout << "emmmmm,ɧ����" << endl;
			cin >> contestant::contestantnum;
		}
		if (contestant::contestantnum > 0 && contestant::contestantnum <= 26)
			break;
	}
	cout << endl << "���������ѡ��ÿ��������";
	cin >> contestant::dividnum;
	while (1)
	{
		if (contestant::dividnum > contestant::contestantnum)
		{
			cout << "�ҾͲ����㻹�ָܷ�С�����������������룡" << endl;			//��ֹ��������������
			cin >> contestant::dividnum;
		}
		if (contestant::dividnum <= 0)
		{
			cout << "�֣������ӷ�" << endl;
			cin >> contestant::dividnum;
		}
		if (contestant::dividnum > 0 && contestant::dividnum < contestant::contestantnum)
			break;
	}
	int t = contestant::contestantnum / contestant::dividnum;				//����
	initList();																//����ÿ��ĳ�Ա
	int minsize = 1e9;			
	for (int i = 0; i < t; i++)
	{
		cout << "��" << i + 1 << "������Ϊ��" << this->List[i].size() << endl;
		minsize = min(minsize, (int)this->List[i].size());				//��¼�������ٵ�����
	}
	cout << endl << "������Ԥ��ÿ���������" << endl;
	cin >> contestant::advancenum;
	while (1)
	{
		if (contestant::advancenum > minsize)
		{
			cout << "������ĳ����ȫ����ֱ˵�����������룡" << endl;
			cin >> contestant::advancenum;
		}
		if (contestant::advancenum <= 0)
		{
			cout << "emmmmm,ɧ����" << endl;
			cin >> contestant::advancenum;
		}
		if (contestant::advancenum > 0 && contestant::advancenum <= minsize)
			break;
	}
	system("cls");
	cout << "Ԥ�������" << endl;

	for (int i = 0; i < t; i++)
	{
		cout << "��" << i + 1 << "�飺 " << endl;
		for (vector<contestant>::iterator it = this->List[i].begin(); it != this->List[i].end(); it++)		//ѭ�����ĳ��������ѡ����Ϣ
		{
			it->showinfo();
		}
		sort(List[i].begin(), List[i].end(), Listcmp());				//���շ�����������

		for (int j = 0; j < contestant::advancenum; j++)				//ѡ������ѡ�֣�����������б�
		{
			this->AdvList.push_back(List[i][j]);
		}
		cout << endl;
	}
	cout << "��������鿴������Ա����" << endl;
	system("pause");
	for (vector<contestant>::iterator it = this->AdvList.begin(); it != this->AdvList.end(); it++)		//չʾ�����б�������ѡ����Ϣ
	{
		it->showinfo();
	}
}

void SpeechMangersystem::_final()			//����
{
	cout << "���������ʼ���о���" << endl;
	system("pause");
	system("cls");
	cout << "���������" << endl;
	for (vector<contestant>::iterator it = this->AdvList.begin(); it != this->AdvList.end(); it++)		//չʾ�������
	{
		it->m_score = contestant::givescore();
		it->showinfo();
	}
	
	sort(AdvList.begin(), AdvList.end(), Listcmp());			//��������������

	cout << "��������鿴����" << endl;
	system("pause");

	ofstream ofs;
	ofs.open(FILENAME, ios::app);
	int i = 0;
	for (vector<contestant>::iterator it = this->AdvList.begin(); it != this->AdvList.end() && i < 3; it++)		//չʾǰ����������У�ѡ�ֵ���Ϣ
	{
		cout << "��" << ++i << "��Ϊ��";
		it->showinfo();	
		ofs << it->m_name << " " << it->m_ID << " " << it->m_score << " " << this->getnum() << " ";		//д���ļ�
		cout << endl;
	}
	ofs << endl;
	ofs.close();
}

void SpeechMangersystem::start()
{
	this->_prev();
	this->_final();
	cout << "��¼�ѱ��� " << endl;
	this->tempclear();					//��������ļ����б���ֹ�ظ� ����Ϊupdate�����Ὣ������Ϣȫ��д��һ�飩
	this->update();
}

void SpeechMangersystem::showorder()			//չʾ����������
{
	int k = this->Ordernum;
	if (k == 0)
	{
		cout << "����ʱû������ı��������Ϣ" << endl;
	}
	for (int i = 0; i < k; i++)
	{
		cout << "��" << i + 1 << "����������" << endl;
		for (vector<contestant>::iterator it = this->OrderList[i].begin(); it != this->OrderList[i].end(); it++)
			it->showinfo();
		cout << endl;
	}
}

void SpeechMangersystem::tempclear()			//�������ʱ���б���Ϣ
{
	for (int i = 0; i < this->Ordernum; i++)
		this->OrderList[i].clear();
}

void SpeechMangersystem::textclear()			//����ı���Ϣ
{
	int choice = 0;
	cout << "�������������������еļ�¼�������Ҫ���д˲��������ٴ�����3" << endl;
	cin >> choice;
	if (choice == 3)
	{
		this->Ordernum = 0;
		ofstream ofs;
		ofs.open(FILENAME, ios::out);
		ofs.close();
		cout << "����ɹ���" << endl;
	}
	return;
}