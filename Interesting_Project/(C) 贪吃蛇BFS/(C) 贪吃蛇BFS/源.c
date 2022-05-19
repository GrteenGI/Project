#include <stdio.h>
#include <time.h>
#include <Windows.h>

void cout(int x) {
	printf("%d", x);
}

const int dx[4] = { -1 , 0 , 1 , 0 };	//上右下左
const int dy[4] = { 0 , 1 , 0 , -1 };
int lasti;		//最后的朝向 用于确定蛇身产生位置


//class SNK   //贪吃蛇主程序下函数列表及变量
void _SNK_main_menu();		//主界面
void _SNK_show_menu();		//主界面展示
void _SNK_start();		//主程序开始
void _SNK_printmap();		//打印当前地图状况
void _SNK_BFS();		//广搜
int _SNK_DFS(struct crd now);		//深搜确定方向
void _SNK_update_snk();		//更新蛇的所有信息
struct crd _SNK_walk();		//没事走两步  防止智商不够导致直接return 0
int _SNK_valid(int x ,int y);		//合法性检测


//class SNK_map  //贪吃蛇地图
//懒得打表了 反正都是自己动的
int _SNK_map[22][42];		//地图
int visit[22][42];			//BFS用
int d[22][42];			//曼哈顿距离
void _SNK_map_init();		//地图初始化
void _SNK_d_clear();		//d数组清零
int _SNK_check_in_map(int x, int y);		//检测是否在地图内
void _SNK_update_map();		//更新地图

//class SNK_snk		//蛇
struct snk {
	int x;
	int y;
};

int _SNK_length = 0;
struct snk body[1000];
void _SNK_head_init();		//初始化蛇头
struct snk _SNK_snk_copy(struct snk _copy_element);	//snk的拷贝构造
void _SNK_snk_add(struct snk _add_element);		//在snk尾部添加新的body

//class crd		//坐标
struct crd {
	int x;
	int y;
};

struct crd point;		//糖果

void _SNK_crd_copy();		//crd的拷贝构造

//template<typename T>
//class queue		//crd

struct queue {
	struct crd que[1000];		//队列;
	int length;		//队列长度
};

struct queue q;		//真实蛇的队列
struct queue vir_q;		//虚拟蛇的队列

void _q_pop(struct queue *q);		//删除队尾元素
void _q_push(struct crd _push_element, struct queue *q);		//将元素放入队头
void _q_clear(struct queue *q);		//清空队列
struct crd _q_front(struct queue q);		//返回对头


int main() {
	srand((unsigned)time(NULL));
	_SNK_main_menu();		//主菜单
	return 0;
}


//class SNK  
void _SNK_main_menu() {
	int choice = 0;
	_SNK_show_menu();		
	while (scanf_s("%d", &choice) && choice != 1) { //输入选项(虽然只能输入1);
		printf("输1啊！\n");
	}
	if (choice == 1)
		_SNK_start();
}
void _SNK_show_menu() {			//界面展示
	printf("输入1代表你想要开始了");
}

void _SNK_printmap() {			//打印地图
	for (int i = 1; i <= 20; i++) {
		for (int j = 1; j <= 40; j++) {
			if (_SNK_map[i][j] == 2 || _SNK_map[i][j] == 4)		//蛇
				printf("■");
			else if (_SNK_map[i][j] == 3)	//糖
				printf("□");
			else					//空气
				printf("  ");
		}
		printf("\n");
	}
	printf("当前长度为： %d", _SNK_length);
}

void _SNK_start() {			//主程序

	system("cls");		//清屏
	_SNK_map_init();		//初始化地图
	_SNK_d_clear();		//让d全为0
	_SNK_head_init();		//初始化脑袋
	
	_SNK_map[10][20] = 4;		//蛇头默认出现在10 , 20
	int food_is_exist = 0;		//1表示当前地图上存在食物
	while (1) {
		if (!food_is_exist) {			//如果地图上没有糖
			food_is_exist = 1;			//就生成
			int first = 1 + rand() % 20;		//x
			int second = 1 + rand() % 40;		//y
			while (_SNK_map[first][second] != 0) {		//如果该区块不为空
				first = 1 + rand() % 20;		//就重置
				second = 1 + rand() % 40;
			}
			_SNK_map[first][second] = 3;
			point.x = first;			//糖的坐标
			point.y = second;
		}
		_SNK_BFS();			//广搜
		struct crd headcrd;			//蛇头的坐标类
		headcrd.x = body[1].x;
		headcrd.y = body[1].y;
		int result = _SNK_DFS(headcrd);			//深搜 返回搜索结果
		if (result == 0) {			//如果没搜到
			struct crd newhead = _SNK_walk();		//没事走两步 返回新蛇头的最表
			if (newhead.x == -1 && newhead.y == -1) {
				_SNK_printmap();
				printf("芜湖 ，彻底没路走了！");
				system("pause");
				break;
			}
			_SNK_update_snk();		//更新除头以外的所有蛇身
			body[1].x = newhead.x;	//更新脑袋
			body[1].y = newhead.y;
			_SNK_update_map();		//更新地图
			_SNK_printmap();		//打印地图
			//for (int i = 1; i <= 20; i++) {
			//	printf("\n");
			//	for (int j = 1; j <= 40; j++)
			//		printf("%d ", d[i][j]);
			//}
			//printf("\n");
			//printf("%d , %d  \n" , body[1].x, body[1].y);
			//printf("%d  \n", d[body[1].x][body[1].y]);
			//for (int i = 0; i <= 3; i++) {
			//	printf("%d \n", d[body[1].x + dx[i]][body[1].y + dy[i]]);
			//	printf("%d , %d \n", body[1].x + dx[i], body[1].y + dy[i]);
			//}
			//system("pause");
			system("cls");
		}
		else {				//如果搜到了
			food_is_exist = 0;			//糖没了
			struct snk newbody;			//创建新身体
			if (_SNK_length == 1) {			//如果蛇头
				newbody.x = body[1].x - dx[lasti];
				newbody.y = body[1].y - dy[lasti];
			}
			else {			//如果有两节以上  则新身体的坐标就是尾巴的逆方向一格
				newbody.x = 2 * body[_SNK_length].x - body[_SNK_length - 1].x;
				newbody.y = 2 * body[_SNK_length].y - body[_SNK_length - 1].y;
			}
			_SNK_snk_add(newbody);			//添加新身体
			_SNK_update_map();
		}
	}
}

void _SNK_BFS() {			//广搜
	_q_clear(&q);			//清空队列
	_SNK_d_clear();			//清空d数组
	struct crd now;				//糖果
	now.x = point.x;			
	now.y = point.y;
	d[now.x][now.y] = 1;		//初始距离为1
	_q_push(now, &q);		//将(终点)放入队列
	while (q.length) {
		struct crd now; 
		now.x = _q_front(q).x; 
		now.y = _q_front(q).y;
		_q_pop(&q);
		for (int i = 0; i < 4; i++) {
			//如果合法并且未访问过
			if (_SNK_valid(now.x + dx[i], now.y + dy[i]) == 1 && d[now.x + dx[i]][now.y + dy[i]] == 0) {
				d[now.x + dx[i]][now.y + dy[i]] = d[now.x][now.y] + 1;
				struct crd Next;
				Next.x = now.x + dx[i];
				Next.y = now.y + dy[i];
				_q_push(Next, &q);
			}
		}
	}
}

	
int _SNK_DFS(struct crd now) {			//深搜
	if (body[1].x == point.x && body[1].y == point.y) {		//如果已经到达目标，全部分支返回
		return 1;
	}
	for (int i = 0; i < 4; i++) {
		int Nextx = now.x + dx[i];		//走向的下一个坐标
		int Nexty = now.y + dy[i];
		//如果走法符合最短路径
		if (_SNK_valid(Nextx, Nexty) == 1 && d[Nextx][Nexty] + 1 == d[now.x][now.y]) {
			_SNK_update_snk();		//更新蛇所有区块的坐标
			body[1].x += dx[i];		//更新蛇头坐标
			body[1].y += dy[i];
			lasti = i;			//用来确保只有蛇头时可以确定逆方向
			_SNK_update_map();		//更新地图
			_SNK_printmap();		//打印新地图
			//Sleep(10);
			system("cls");			//清空地图
			struct crd Next;
			Next.x = Nextx;
			Next.y = Nexty;
			if (_SNK_DFS(Next))			//搜索下一个
				return 1;
		}
	}
	return 0;	
}

void _SNK_update_snk() {			//更新蛇的所有区块（除蛇头）
	for (int i = _SNK_length; i > 1; i--) {
		body[i].x = body[i - 1].x;
		body[i].y = body[i - 1].y;
	}
}

struct crd _SNK_walk() {		//没事就走走
	for (int i = 0; i < 4; i++) {
		int Nextx = body[1].x + dx[i];	
		int Nexty = body[1].y + dy[i];
		if (_SNK_valid(Nextx, Nexty) == 1) {
			struct crd _return_head;
			_return_head.x = Nextx;
			_return_head.y = Nexty;
			return _return_head;
		}
	}
	struct crd _return_head;
	_return_head.x = -1;
	_return_head.y = -1;
	return _return_head;		//彻底寄了
}	

int _SNK_valid(int x ,int y) {			//合法性判断
	if (_SNK_check_in_map(x, y) && _SNK_map[x][y] != 1 && _SNK_map[x][y] != 2) {
		return 1;
	}
	return 0;
}

//class SNK_map
void _SNK_map_init() {			//地图初始化
	for (int i = 1; i <= 20; i++)
		for (int j = 1; j <= 40; j++)
			_SNK_map[i][j] = 0;
	for (int i = 0; i <= 41; i++) {
		_SNK_map[0][i] = 1;		//1表示障碍 2为蛇身 3为糖果
		_SNK_map[21][i] = 1;
	}
	for (int i = 0; i <= 21; i++) {
		_SNK_map[i][0] = 1;
		_SNK_map[i][41] = 1;
	}
	_SNK_map[point.x][point.y] = 3;
}

void _SNK_d_clear() {			//d数组清零
	for (int i = 1; i <= 20; i++)
		for (int j = 1; j <= 40; j++)
			d[i][j] = 0;
}

int _SNK_check_in_map(int x , int y) {			//检测是否在地图内
	if (x < 0 || x > 20 || y < 0 || y > 40)
		return 0;
	return 1;
}

void _SNK_update_map() {			//更新地图
	_SNK_map_init();
	for (int i = 1; i <= _SNK_length; i++) {
		if (i == 1)
			_SNK_map[body[i].x][body[i].y] = 4;		//蛇头
		else
			_SNK_map[body[i].x][body[i].y] = 2;
	}
}

//template queue
void _q_pop(struct queue *q) {		//删除队头元素
	q->length -= 1;
	for (int i = 1; i <= q->length; i++) {
		q->que[i] = q->que[i + 1];
	}
}

void _q_push(struct crd _push_element, struct queue *q) {		//插入队尾元素
	q->length += 1;
	q->que[q->length] = _push_element;
}

void _q_clear(struct queue *q) {		//清除队列
	struct crd init;
	init.x = 0;
	init.y = 0;
	for (int i = 0; i <= q->length; i++)
		q->que[i] = init;
	q->length = 0;
}

struct crd _q_front(struct queue q) {		//返回队头元素
	return q.que[1];
}

//snk

void _SNK_head_init() {			//蛇头初始化
	body[1].x = 10;
	body[1].y = 20;
	_SNK_length = 1;
}

void _SNK_snk_add(struct snk _add_element) {			//添加新身体
	body[++_SNK_length] = _add_element;
}

struct snk _SNK_snk_copy(struct snk _copy_element) {		//拷贝构造
	struct snk _return_element;
	_return_element.x = _copy_element.x;
	_return_element.y = _copy_element.y;
	return _return_element;
}