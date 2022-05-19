#include"SpeechMangersystem.h";

class Listcmp
{
public:
	bool operator()(contestant a, contestant b)
	{
		return a.m_score > b.m_score;
	}
};

void SpeechMangersystem::update()				//写入文本中所有的信息
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

int SpeechMangersystem::getnum()				//获取文本中的人数
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

void SpeechMangersystem::showmenu()				//菜单
{
	cout << "欢迎使用演讲比赛流程管理系统" << endl;
	cout << "1.开始演讲比赛" << endl;
	cout << "2.查看往届记录" << endl;
	cout << "3.清空往届记录" << endl;
	cout << "0.退出管理系统" << endl;
	cout << endl;
}

void SpeechMangersystem::exitsystem()			//退出系统
{
	cout << "欢迎下次使用！" << endl;
	system("pause");
	exit(0);
}

void SpeechMangersystem::initList()					//随机分配每组选手的信息和分数
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

void SpeechMangersystem::_prev()			//预赛
{
	cout << "请输入参赛选手总数：";
	cin >> contestant::contestantnum;
	while (1)
	{
		if (contestant::contestantnum > 26)
		{
			cout << "哥我名称种子不够的啊！" << endl;
			cin >> contestant::contestantnum;
		}
		if (contestant::contestantnum <= 0)
		{
			cout << "emmmmm,骚操作" << endl;
			cin >> contestant::contestantnum;
		}
		if (contestant::contestantnum > 0 && contestant::contestantnum <= 26)
			break;
	}
	cout << endl << "请输入参赛选手每组人数：";
	cin >> contestant::dividnum;
	while (1)
	{
		if (contestant::dividnum > contestant::contestantnum)
		{
			cout << "我就不信你还能分个小数出来，请重新输入！" << endl;			//防止分组数大于总数
			cin >> contestant::dividnum;
		}
		if (contestant::dividnum <= 0)
		{
			cout << "分，给老子分" << endl;
			cin >> contestant::dividnum;
		}
		if (contestant::dividnum > 0 && contestant::dividnum < contestant::contestantnum)
			break;
	}
	int t = contestant::contestantnum / contestant::dividnum;				//组数
	initList();																//分配每组的成员
	int minsize = 1e9;			
	for (int i = 0; i < t; i++)
	{
		cout << "第" << i + 1 << "组人数为：" << this->List[i].size() << endl;
		minsize = min(minsize, (int)this->List[i].size());				//记录组内最少的人数
	}
	cout << endl << "请输入预赛每组晋级人数" << endl;
	cin >> contestant::advancenum;
	while (1)
	{
		if (contestant::advancenum > minsize)
		{
			cout << "你想让某个组全过就直说，请重新输入！" << endl;
			cin >> contestant::advancenum;
		}
		if (contestant::advancenum <= 0)
		{
			cout << "emmmmm,骚操作" << endl;
			cin >> contestant::advancenum;
		}
		if (contestant::advancenum > 0 && contestant::advancenum <= minsize)
			break;
	}
	system("cls");
	cout << "预赛结果：" << endl;

	for (int i = 0; i < t; i++)
	{
		cout << "第" << i + 1 << "组： " << endl;
		for (vector<contestant>::iterator it = this->List[i].begin(); it != this->List[i].end(); it++)		//循环输出某组内所有选手信息
		{
			it->showinfo();
		}
		sort(List[i].begin(), List[i].end(), Listcmp());				//按照分数降序排序

		for (int j = 0; j < contestant::advancenum; j++)				//选出晋级选手，并插入晋级列表
		{
			this->AdvList.push_back(List[i][j]);
		}
		cout << endl;
	}
	cout << "按任意键查看晋级人员名单" << endl;
	system("pause");
	for (vector<contestant>::iterator it = this->AdvList.begin(); it != this->AdvList.end(); it++)		//展示晋级列表中所有选手信息
	{
		it->showinfo();
	}
}

void SpeechMangersystem::_final()			//决赛
{
	cout << "摁任意键开始进行决赛" << endl;
	system("pause");
	system("cls");
	cout << "决赛结果：" << endl;
	for (vector<contestant>::iterator it = this->AdvList.begin(); it != this->AdvList.end(); it++)		//展示决撒结果
	{
		it->m_score = contestant::givescore();
		it->showinfo();
	}
	
	sort(AdvList.begin(), AdvList.end(), Listcmp());			//按分数降序排列

	cout << "摁任意键查看排名" << endl;
	system("pause");

	ofstream ofs;
	ofs.open(FILENAME, ios::app);
	int i = 0;
	for (vector<contestant>::iterator it = this->AdvList.begin(); it != this->AdvList.end() && i < 3; it++)		//展示前三名（如果有）选手的信息
	{
		cout << "第" << ++i << "名为：";
		it->showinfo();	
		ofs << it->m_name << " " << it->m_ID << " " << it->m_score << " " << this->getnum() << " ";		//写入文件
		cout << endl;
	}
	ofs << endl;
	ofs.close();
}

void SpeechMangersystem::start()
{
	this->_prev();
	this->_final();
	cout << "记录已保存 " << endl;
	this->tempclear();					//清除运行文件的列表，防止重复 （因为update函数会将所有信息全部写入一遍）
	this->update();
}

void SpeechMangersystem::showorder()			//展示历届比赛结果
{
	int k = this->Ordernum;
	if (k == 0)
	{
		cout << "您暂时没有历届的比赛结果信息" << endl;
	}
	for (int i = 0; i < k; i++)
	{
		cout << "第" << i + 1 << "届比赛结果：" << endl;
		for (vector<contestant>::iterator it = this->OrderList[i].begin(); it != this->OrderList[i].end(); it++)
			it->showinfo();
		cout << endl;
	}
}

void SpeechMangersystem::tempclear()			//清除运行时的列表信息
{
	for (int i = 0; i < this->Ordernum; i++)
		this->OrderList[i].clear();
}

void SpeechMangersystem::textclear()			//清除文本信息
{
	int choice = 0;
	cout << "这个操作将会清除您所有的记录，如果您要进行此操作，请再次输入3" << endl;
	cin >> choice;
	if (choice == 3)
	{
		this->Ordernum = 0;
		ofstream ofs;
		ofs.open(FILENAME, ios::out);
		ofs.close();
		cout << "清除成功！" << endl;
	}
	return;
}