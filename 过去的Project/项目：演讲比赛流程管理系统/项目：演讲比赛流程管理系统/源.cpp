#include<iostream>
#include<ctime>
#include"SpeechMangersystem.h"
#include"contestant.h"
using namespace std;

int menuchoice;
int main()
{
	SpeechMangersystem SMS;

	while (1)
	{
		srand(unsigned int(time(NULL)));
		SMS.showmenu();
		cout << "请输入您的选项:  ";
		cin >> menuchoice;
		if (menuchoice == 1)
		{
			SMS.start();
			system("pause");
			system("cls");
		}
		else if (menuchoice == 2)
		{
			SMS.showorder();
			system("pause");
			system("cls");
		}
		else if (menuchoice == 3)
		{
			SMS.textclear();
			system("pause");
			system("cls");
		}
		else if (menuchoice == 0)
		{
			SMS.exitsystem();
		}
	}
	system("pause");
	return 0;
}