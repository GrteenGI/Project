#pragma once
#include<iostream>
#include<string>
#include<vector>
#include<deque>
#include<algorithm>
#include<numeric>
using namespace std;

class contestant				//ѡ��
{
public:
	contestant();
	~contestant();
	contestant(char name, int id, double score);

	void showinfo();			//չʾ��Ϣ

	static double givescore();			//����з�
	static void initnameseed();			//�������ѡ�ֵ�����
	static int dividnum;		//��������
	static int contestantnum;			//ѡ������
	static int advancenum;			//Ԥѡ����������

	static vector <char> m_initseed;	//����ѡ���������
	double m_score;

	char m_name;
	int m_ID;
};