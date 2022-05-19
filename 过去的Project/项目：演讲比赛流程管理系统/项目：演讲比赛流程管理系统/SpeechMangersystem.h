#pragma once
#include<iostream>
#include<deque>
#include<algorithm>
#include<fstream>

#define FILENAME "Order.csv"		//��¼�ļ�

#include"contestant.h"

using namespace std;

class SpeechMangersystem
{
public:
	SpeechMangersystem();
	~SpeechMangersystem();

	void showmenu();		//�˵�

	void exitsystem();		//�˳�ϵͳ

	void _prev();			//Ԥ��

	void _final();			//����

	void start();			//��ʼ�ݽ���������

	void initList();			//��ʼ��ѡ���б�

	void update();			//���¼�¼

	int getnum();			//��ȡ��¼����

	void showorder();			//չʾ��¼

	void tempclear();			//��������ʱ���б�����

	void textclear();			//�����ı��ļ����б�����

	int Ordernum;			//��¼����

	vector<contestant>OrderList[100];		//��¼��Ŀ

private:
	vector<contestant>List[26];			//ѡ���б�
	vector<contestant>AdvList;		//Ԥ������ѡ���б�	
};