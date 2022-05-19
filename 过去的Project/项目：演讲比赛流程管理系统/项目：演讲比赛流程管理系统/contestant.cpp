#include"contestant.h"

contestant::contestant() {}
contestant::~contestant() {}

int contestant::contestantnum = 0;
int contestant::dividnum = 0;
int contestant::advancenum = 0;
vector<char> contestant::m_initseed;

vector<int>vec;
void initvec()										//将所有姓名塞入一个容器中
{
	if (!vec.empty())
		vec.clear();
	for (int i = 0; i < 26; i++)
		vec.push_back(i + 65);
}

contestant::contestant(char name, int id, double score)
{
	this->m_ID = id;
	this->m_name = name;
	this->m_score = score;
}

void contestant::showinfo()				//展示信息
{
	cout << "姓名：" << this->m_name << " "
		<< "编号：" << this->m_ID << ""
		<< "分数：" << this->m_score << endl;
}


void contestant::initnameseed()					//随机化姓名种子
{
	initvec();
	while (contestant::m_initseed.size() < contestant::contestantnum)
	{
		int t = rand() % (contestant::contestantnum - contestant::m_initseed.size());
		contestant::m_initseed.push_back(vec[t]);
		vec.erase(vec.begin() + t);
	}
}

double contestant::givescore()					//随即给分
{
	deque<int>score;
	for (int i = 0; i < 10; i++)
	{
		score.push_back(rand() % 40 + 60);
	}
	sort(score.begin(), score.end());
	score.pop_back();
	score.pop_front();
	return (double)accumulate(score.begin(), score.end(), 0) / 8;
}