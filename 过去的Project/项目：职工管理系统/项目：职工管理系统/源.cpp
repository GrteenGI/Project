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
		cout << "请输入您的选项：  ";
		cin >> choice;
		switch (choice)
		{
		case 1:			//增加员工信息
			wms.add_emp();
			break;
		case 2:			//显示职工信息
			wms.show_emp();
			break;
		case 3 :		//删除职工信息
			wms.del_emp();
			break;
		case 4 :		//修改职工信息
			wms.change_emp();
			break;
		case 5:			//查找职工信息
			wms.find_emp();
			break;
		case 6:			//排序
			wms.sort_emp();
			break;
		case 0:			//退出管理系统
			wms.exitsystem();
			break;
		case 7:			//删除所有信息
			wms.clear_emp();
			break;
		default:
			cout << "输入不合法，请重新输入！" << endl;
			system("pause");
			system("cls");
			break;
		}
	}
	system("pause");
	return 0;
}