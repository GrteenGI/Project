#include "workmangersystem.h"
#include "Worker.h"
#include <iostream>
using namespace std;
int choice = 0;

int main()
{
	workmangersystem wms;
	
	while (1)
	{
		wms.showmenu();
		cout << "����������ѡ�  ";
		cin >> choice;
		switch (choice)
		{
		case 1:			//����Ա����Ϣ
			wms.add_emp();
			break;
		case 2:			//��ʾְ����Ϣ
			wms.show_emp();
			break;
		case 3 :		//ɾ��ְ����Ϣ
			wms.del_emp();
			break;
		case 4 :		//�޸�ְ����Ϣ
			wms.change_emp();
			break;
		case 5:			//����ְ����Ϣ
			wms.find_emp();
			break;
		case 6:			//����
			wms.sort_emp();
			break;
		case 0:			//�˳�����ϵͳ
			wms.exitsystem();
			break;
		case 7:			//ɾ��������Ϣ
			wms.clear_emp();
			break;
		default:
			cout << "���벻�Ϸ������������룡" << endl;
			system("pause");
			system("cls");
			break;
		}
	}
	system("pause");
	return 0;
}