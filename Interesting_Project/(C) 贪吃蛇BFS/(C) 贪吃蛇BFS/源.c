#include <stdio.h>
#include <time.h>
#include <Windows.h>

void cout(int x) {
	printf("%d", x);
}

const int dx[4] = { -1 , 0 , 1 , 0 };	//��������
const int dy[4] = { 0 , 1 , 0 , -1 };
int lasti;		//���ĳ��� ����ȷ���������λ��


//class SNK   //̰�����������º����б�����
void _SNK_main_menu();		//������
void _SNK_show_menu();		//������չʾ
void _SNK_start();		//������ʼ
void _SNK_printmap();		//��ӡ��ǰ��ͼ״��
void _SNK_BFS();		//����
int _SNK_DFS(struct crd now);		//����ȷ������
void _SNK_update_snk();		//�����ߵ�������Ϣ
struct crd _SNK_walk();		//û��������  ��ֹ���̲�������ֱ��return 0
int _SNK_valid(int x ,int y);		//�Ϸ��Լ��


//class SNK_map  //̰���ߵ�ͼ
//���ô���� ���������Լ�����
int _SNK_map[22][42];		//��ͼ
int visit[22][42];			//BFS��
int d[22][42];			//�����پ���
void _SNK_map_init();		//��ͼ��ʼ��
void _SNK_d_clear();		//d��������
int _SNK_check_in_map(int x, int y);		//����Ƿ��ڵ�ͼ��
void _SNK_update_map();		//���µ�ͼ

//class SNK_snk		//��
struct snk {
	int x;
	int y;
};

int _SNK_length = 0;
struct snk body[1000];
void _SNK_head_init();		//��ʼ����ͷ
struct snk _SNK_snk_copy(struct snk _copy_element);	//snk�Ŀ�������
void _SNK_snk_add(struct snk _add_element);		//��snkβ������µ�body

//class crd		//����
struct crd {
	int x;
	int y;
};

struct crd point;		//�ǹ�

void _SNK_crd_copy();		//crd�Ŀ�������

//template<typename T>
//class queue		//crd

struct queue {
	struct crd que[1000];		//����;
	int length;		//���г���
};

struct queue q;		//��ʵ�ߵĶ���
struct queue vir_q;		//�����ߵĶ���

void _q_pop(struct queue *q);		//ɾ����βԪ��
void _q_push(struct crd _push_element, struct queue *q);		//��Ԫ�ط����ͷ
void _q_clear(struct queue *q);		//��ն���
struct crd _q_front(struct queue q);		//���ض�ͷ


int main() {
	srand((unsigned)time(NULL));
	_SNK_main_menu();		//���˵�
	return 0;
}


//class SNK  
void _SNK_main_menu() {
	int choice = 0;
	_SNK_show_menu();		
	while (scanf_s("%d", &choice) && choice != 1) { //����ѡ��(��Ȼֻ������1);
		printf("��1����\n");
	}
	if (choice == 1)
		_SNK_start();
}
void _SNK_show_menu() {			//����չʾ
	printf("����1��������Ҫ��ʼ��");
}

void _SNK_printmap() {			//��ӡ��ͼ
	for (int i = 1; i <= 20; i++) {
		for (int j = 1; j <= 40; j++) {
			if (_SNK_map[i][j] == 2 || _SNK_map[i][j] == 4)		//��
				printf("��");
			else if (_SNK_map[i][j] == 3)	//��
				printf("��");
			else					//����
				printf("  ");
		}
		printf("\n");
	}
	printf("��ǰ����Ϊ�� %d", _SNK_length);
}

void _SNK_start() {			//������

	system("cls");		//����
	_SNK_map_init();		//��ʼ����ͼ
	_SNK_d_clear();		//��dȫΪ0
	_SNK_head_init();		//��ʼ���Դ�
	
	_SNK_map[10][20] = 4;		//��ͷĬ�ϳ�����10 , 20
	int food_is_exist = 0;		//1��ʾ��ǰ��ͼ�ϴ���ʳ��
	while (1) {
		if (!food_is_exist) {			//�����ͼ��û����
			food_is_exist = 1;			//������
			int first = 1 + rand() % 20;		//x
			int second = 1 + rand() % 40;		//y
			while (_SNK_map[first][second] != 0) {		//��������鲻Ϊ��
				first = 1 + rand() % 20;		//������
				second = 1 + rand() % 40;
			}
			_SNK_map[first][second] = 3;
			point.x = first;			//�ǵ�����
			point.y = second;
		}
		_SNK_BFS();			//����
		struct crd headcrd;			//��ͷ��������
		headcrd.x = body[1].x;
		headcrd.y = body[1].y;
		int result = _SNK_DFS(headcrd);			//���� �����������
		if (result == 0) {			//���û�ѵ�
			struct crd newhead = _SNK_walk();		//û�������� ��������ͷ�����
			if (newhead.x == -1 && newhead.y == -1) {
				_SNK_printmap();
				printf("�ߺ� ������û·���ˣ�");
				system("pause");
				break;
			}
			_SNK_update_snk();		//���³�ͷ�������������
			body[1].x = newhead.x;	//�����Դ�
			body[1].y = newhead.y;
			_SNK_update_map();		//���µ�ͼ
			_SNK_printmap();		//��ӡ��ͼ
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
		else {				//����ѵ���
			food_is_exist = 0;			//��û��
			struct snk newbody;			//����������
			if (_SNK_length == 1) {			//�����ͷ
				newbody.x = body[1].x - dx[lasti];
				newbody.y = body[1].y - dy[lasti];
			}
			else {			//�������������  ����������������β�͵��淽��һ��
				newbody.x = 2 * body[_SNK_length].x - body[_SNK_length - 1].x;
				newbody.y = 2 * body[_SNK_length].y - body[_SNK_length - 1].y;
			}
			_SNK_snk_add(newbody);			//���������
			_SNK_update_map();
		}
	}
}

void _SNK_BFS() {			//����
	_q_clear(&q);			//��ն���
	_SNK_d_clear();			//���d����
	struct crd now;				//�ǹ�
	now.x = point.x;			
	now.y = point.y;
	d[now.x][now.y] = 1;		//��ʼ����Ϊ1
	_q_push(now, &q);		//��(�յ�)�������
	while (q.length) {
		struct crd now; 
		now.x = _q_front(q).x; 
		now.y = _q_front(q).y;
		_q_pop(&q);
		for (int i = 0; i < 4; i++) {
			//����Ϸ�����δ���ʹ�
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

	
int _SNK_DFS(struct crd now) {			//����
	if (body[1].x == point.x && body[1].y == point.y) {		//����Ѿ�����Ŀ�꣬ȫ����֧����
		return 1;
	}
	for (int i = 0; i < 4; i++) {
		int Nextx = now.x + dx[i];		//�������һ������
		int Nexty = now.y + dy[i];
		//����߷��������·��
		if (_SNK_valid(Nextx, Nexty) == 1 && d[Nextx][Nexty] + 1 == d[now.x][now.y]) {
			_SNK_update_snk();		//�������������������
			body[1].x += dx[i];		//������ͷ����
			body[1].y += dy[i];
			lasti = i;			//����ȷ��ֻ����ͷʱ����ȷ���淽��
			_SNK_update_map();		//���µ�ͼ
			_SNK_printmap();		//��ӡ�µ�ͼ
			//Sleep(10);
			system("cls");			//��յ�ͼ
			struct crd Next;
			Next.x = Nextx;
			Next.y = Nexty;
			if (_SNK_DFS(Next))			//������һ��
				return 1;
		}
	}
	return 0;	
}

void _SNK_update_snk() {			//�����ߵ��������飨����ͷ��
	for (int i = _SNK_length; i > 1; i--) {
		body[i].x = body[i - 1].x;
		body[i].y = body[i - 1].y;
	}
}

struct crd _SNK_walk() {		//û�¾�����
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
	return _return_head;		//���׼���
}	

int _SNK_valid(int x ,int y) {			//�Ϸ����ж�
	if (_SNK_check_in_map(x, y) && _SNK_map[x][y] != 1 && _SNK_map[x][y] != 2) {
		return 1;
	}
	return 0;
}

//class SNK_map
void _SNK_map_init() {			//��ͼ��ʼ��
	for (int i = 1; i <= 20; i++)
		for (int j = 1; j <= 40; j++)
			_SNK_map[i][j] = 0;
	for (int i = 0; i <= 41; i++) {
		_SNK_map[0][i] = 1;		//1��ʾ�ϰ� 2Ϊ���� 3Ϊ�ǹ�
		_SNK_map[21][i] = 1;
	}
	for (int i = 0; i <= 21; i++) {
		_SNK_map[i][0] = 1;
		_SNK_map[i][41] = 1;
	}
	_SNK_map[point.x][point.y] = 3;
}

void _SNK_d_clear() {			//d��������
	for (int i = 1; i <= 20; i++)
		for (int j = 1; j <= 40; j++)
			d[i][j] = 0;
}

int _SNK_check_in_map(int x , int y) {			//����Ƿ��ڵ�ͼ��
	if (x < 0 || x > 20 || y < 0 || y > 40)
		return 0;
	return 1;
}

void _SNK_update_map() {			//���µ�ͼ
	_SNK_map_init();
	for (int i = 1; i <= _SNK_length; i++) {
		if (i == 1)
			_SNK_map[body[i].x][body[i].y] = 4;		//��ͷ
		else
			_SNK_map[body[i].x][body[i].y] = 2;
	}
}

//template queue
void _q_pop(struct queue *q) {		//ɾ����ͷԪ��
	q->length -= 1;
	for (int i = 1; i <= q->length; i++) {
		q->que[i] = q->que[i + 1];
	}
}

void _q_push(struct crd _push_element, struct queue *q) {		//�����βԪ��
	q->length += 1;
	q->que[q->length] = _push_element;
}

void _q_clear(struct queue *q) {		//�������
	struct crd init;
	init.x = 0;
	init.y = 0;
	for (int i = 0; i <= q->length; i++)
		q->que[i] = init;
	q->length = 0;
}

struct crd _q_front(struct queue q) {		//���ض�ͷԪ��
	return q.que[1];
}

//snk

void _SNK_head_init() {			//��ͷ��ʼ��
	body[1].x = 10;
	body[1].y = 20;
	_SNK_length = 1;
}

void _SNK_snk_add(struct snk _add_element) {			//���������
	body[++_SNK_length] = _add_element;
}

struct snk _SNK_snk_copy(struct snk _copy_element) {		//��������
	struct snk _return_element;
	_return_element.x = _copy_element.x;
	_return_element.y = _copy_element.y;
	return _return_element;
}