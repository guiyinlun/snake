#include<iostream>
#include"snake.h"
using namespace std;
struct Snake
{
	int x;
	int y;
	struct  Snake* next;
};
//头指针，食物指针，遍历指针
struct Snake *List = NULL,*food=NULL,*p=NULL;
//游戏结束类型
int gameover=0;
//得分
int sumscore=0,score=10;


//开始
void gameStart()
{
	
	srand((unsigned)time(NULL));//初始化随机数
	gameMap();
	List = initSnake();
	runGame(List);
	
}
//说明
void explainGame()

{
	int i,j = 1;
	system("cls");
	   color(11);
	   gotoXY(46,3);
	   cout<<"游戏说明";
	   color(7);
	   for (i = 6; i <= 22; i++)   //输出上下边框===
	   {
	   	for (j = 23; j <= 75; j++)  //输出左右边框||
	   	{
	   		gotoXY(j, i);
			if (i == 6 || i == 22)
			{
				if (j == 23) cout << " "; 
				cout << "=";
			}
				
			else if (j == 23 || j == 75) cout << "||";
			
	   	}
	   }
	color(14);
	gotoXY(30, 8);
	cout << "1. 不能穿墙，不能咬到自己";
	
	gotoXY(30, 11);
	cout << "2. 用 w.s.a.d 分别控制蛇的移动";

	gotoXY(30, 14);
	cout << "3. 不能朝对立的方向移动";
	
	gotoXY(30, 17);
	cout << "4. 按空格键暂停游戏，再按空格键继续";
	
	gotoXY(30, 20);
	cout << "5. 按ESC键退出本次游戏";
	color(11);
	gotoXY(40, 28);
	cout << "按任意键返回主界面";
	_getch();                //按任意键返回主界面
	system("cls");
	welcome();

}
//欢迎
void welcome()
{	int n;
	gotoXY(39, 10);
	color(11);
	cout << "欢 迎 来 到 贪 吃 蛇";
	gotoXY(0, 0);
	color(13);
	cout << "作者：甘";
	gotoXY(0, 1);
	cout << "QQ:1178814817";
	color(12);
	gotoXY(25, 20);
	cout<<"1.开始游戏";
	gotoXY(44, 20);
	cout<<"2.退出游戏";
	gotoXY(64, 20);
	cout << "3.游戏说明";
	gotoXY(0,30);
	color(10);
	cout << "开始前请先按ctrl+space切换输入法为英文！";
	gotoXY(37, 26);
	color(3);
	cout<<"请选择 1 - 3 后按回车: ";
	color(14);
	cin >> n;   		//输入选项
	switch (n)
	{
	case 1:
		system("cls");
		break;
	case 2:
		color(11);
		gotoXY(43, 29);
		cout << "按任意键退出";
		color(0);
		gotoXY(0, 29);
		exit(0);     		//退出游戏
		break;
	case 3:
		explainGame(); 	//说明	
		break;
	default:
		color(12);
		gotoXY(43, 29);
		cout<<"请输入1 - 3!";
		_getch();			//输入任意键
		system("cls");		//清屏
		welcome();
	}
	gotoXY(0, 30);
}

//地图
void gameMap()
{
	color(15);
	for (int i = 0; i < 60; i += 2)
	{
		gotoXY(i,0);
		cout << "■";
		gotoXY(i, 29);
		cout << "■";
	}
	for (int i = 1; i < 30; i ++)
	{
		gotoXY(0, i);
		cout << "■";
		gotoXY(58, i);
		cout << "■";
	}
	color(6);
	gotoXY(66, 2);
	cout << "得分 : ";
	gotoXY(73, 2);
	cout << sumscore;
	gotoXY(66, 6);
	cout << "说明 : "; 
	gotoXY(66, 8);
	cout << "单个食物分数 : " << score;
	gotoXY(66, 10);
	cout << "使用“w,a,d,s”来控制蛇的移动 ";
	gotoXY(66, 12);
	cout << "按space空格键暂停 ";
	gotoXY(66, 14);
	cout << "按esc结束游戏 ";
	
}
//颜色
int color(int c)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), c);        //更改文字颜色
	return 0;
}
//光标
void gotoXY(int x,int y)
{
	//隐藏光标
	CONSOLE_CURSOR_INFO cursor_info = { 1, 0 };
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor_info);
	COORD pos = { x,y };
	HANDLE hOut = GetStdHandle(STD_ERROR_HANDLE);
	SetConsoleCursorPosition(hOut, pos);
}

//初始化
struct Snake* initSnake()
{
	int x = 20, y = 15;
	struct Snake *snakeHead = new Snake;
	snakeHead->next = NULL;
	snakeHead->x = 0;
	snakeHead->y = 0;
	food = new Snake;
	food->next = NULL;
	food->x = 0;
	food->y = 0;
	p=snakeHead;
	for (int i = 1; i <= 5; i++)
	{//尾插
		struct Snake *tempS = new Snake;
		tempS->next = NULL;
		tempS->x = 20 + 2 * i;
		tempS->y= 15;
		p->next = tempS;
		p = tempS;
	}
	p = snakeHead->next;
	color(10);
	while (p != NULL)
	{
		gotoXY(p->x, p->y);
		cout << "■";
		if (p->next == NULL) break;
		p = p->next;
	}
	p= snakeHead;
	return snakeHead;
}
//运行
void runGame(struct Snake* snakeHead)
{
	createFood(snakeHead);
	int dir=77;
	char ch1='d' ,ch2;
	while (1)
	{
		//判断是否输入
		if (_kbhit())
		{
			 ch2 = _getch();
			 if (ch1 == 'w' && ch2 == 's' || ch1 == 's'&& ch2 == 'w' || ch1 == 'a' && ch2 == 'd' || ch1 == 'd' && ch2 == 'a') continue;
			 switch (ch2)
			 {
				 //控制
			 case 'w'://上
				 dir = 72;
				 break;
			 case 'a'://左
				 dir = 75;
				 break;
			 case 'd'://右
				 dir = 77;
				 break;
			 case 's'://下
				 dir = 80;
				 break;
			 case 32:// 
				 while (1)
				 {
					 if (_kbhit())
					 {
						 ch2 = _getch();
						 if (ch2 == 32)
							 break;
					 } 
					 Sleep(300);
				 }
				 break;
			 case 27://下
				 gameover = 3;    //按esc键，直接到结束界面
				
				 break;
			 }
			     if(ch2!=32) ch1 = ch2;					
		}
		endGame(gameover);
		//移动
		snakeHead =moveSnake(dir, snakeHead);
		Sleep(150);
		//死亡
		biteself(snakeHead);
		endGame(gameover);
		strikeWall(snakeHead);
		endGame(gameover);
		if (gameover) break;
	}
}
//移动
struct Snake* moveSnake(int dir, struct Snake* snakeHead)
{
	 p = snakeHead;
	//找到蛇头链表尾
	while (p != NULL && p->next != NULL) 
	{
		if (p->next == NULL) break;
		p = p->next;
	}
	struct Snake *tempS = new Snake;
	tempS->next = NULL;
	switch (dir) 
	{
	case 72://上
		tempS->x = p->x;
		tempS->y = p->y - 1;
		break;
	case 75://左
		tempS->x = p->x - 2;
		tempS->y = p->y;
		break;
	case 77://右
		tempS->x = p->x + 2;
		tempS->y = p->y;
		break;
	case 80://下
		tempS->x = p->x;
		tempS->y = p->y  + 1;
		break;
	}
	p->next = tempS;
	//显示
	color(10);
	gotoXY(tempS->x, tempS->y);
	cout << "■";
	if (food->x == tempS->x&&food->y == tempS->y)
	{
		createFood(snakeHead);
		sumscore += score;
		color(6);
		gotoXY(73, 2);
		cout << sumscore;
		return snakeHead;
	}
	else {
		gotoXY(snakeHead->next->x, snakeHead->next->y);
		cout << "  ";
		//删除头
		p = snakeHead;
		p= snakeHead->next->next;
		snakeHead->x = snakeHead->next->x;
		snakeHead->y = snakeHead->next->y;
		delete(snakeHead->next);
		snakeHead->next = p;
		return snakeHead;
	}
}

//随机出现食物 
void createFood(struct Snake* snakeHead)
{
		food->x = rand() % 53 + 4;              //食物随机出现
	if ((food->x) % 2) food->x++;
	food->y = rand() % 26 + 2;
	for (p = snakeHead->next; p != NULL; p = p->next)
	{
		if (p->x == food->x && p->y == food->y) 
		{
			createFood(snakeHead);
			break;
		}
	}
	//输出食物
	gotoXY(food->x, food->y);
	color(12);
	cout << "●";           
}
//判断是否咬到了自己
void biteself(struct Snake* snakeHead)
{
	struct Snake *self;            //定义self为蛇身上的一个节点
	self = snakeHead;    //self是蛇头之外的蛇身上的节点
	p = snakeHead->next;
	while (p != NULL && p->next != NULL)
	{
		if (p->next == NULL) break;
		p = p->next;
	}
	while (self != NULL && self->next != NULL && self!=p )
	{
		if (self->x==p->x   && self->y== p->y )
		{
			gameover = 1;   //返回1
			break;
		}
		else self = self->next;
	}
}

//撞墙
void strikeWall(struct Snake* snakeHead)
{
	struct Snake * p = snakeHead;
	//找到蛇头链表尾
	while (p != NULL && p->next != NULL)
	{
		if (p->next == NULL) break;
		p = p->next;
	}
	if (p->x == 0 || p->x == 58 || p->y == 0 || p->y == 29)
	{
			gameover=2;
	}
}
//结束
void endGame(int g)
{
	color(4);
	switch (g)
	{
	case 0: 
		break;
	case 1:
		gotoXY(66, 19);
		cout << "GAME OVER!";
		gotoXY(66, 21);
		cout << "您咬死了自己！";
		break;
	case 2:
		gotoXY(66, 19);
		cout << "GAME OVER!";
		gotoXY(66, 21);
		cout << "您撞墙了！";
		break;
	case 3: 
		gotoXY(66, 19);
		cout << "您退出了游戏！";
		break;
	}
	if (g) overchoose();
}

//结束选择
void overchoose()
{
	gotoXY(75, 23);
	cout << "                         ";
	gotoXY(66, 26);
	cout << "                         ";
	int i;
	color(11);
	gotoXY(66, 23);
	cout << "请选择 : ";
	gotoXY(66, 24);
	cout << "1.重玩";
	gotoXY(80, 24);
	cout << "2.退出";
	gotoXY(75, 23);
	cin >> i;
	switch (i)
	{
	case 1:
		system("cls");          //清屏
		score = 0;				//分数归零
		gameover = 0;        
		destroyList(List);
		gameStart();
		break;
	case 2:
		color(11);
		gotoXY(66, 27);
		cout << "按任意键退出";
		color(0);
		gotoXY(0, 29);
		exit(0);                //退出游戏
		break;
	default:
		gotoXY(66, 26);
		color(11);
		cout<<"输入有误 重新输入 !";
		color(0);
		gotoXY(0, 30);
		system("pause");
		overchoose();
		break;
	}
}
//释放链表
void destroyList(struct Snake* pHead) {
	_ASSERT(pHead != NULL);

	Snake *pNext = pHead->next;
	while (pNext != NULL)
	{
		delete pHead;
		pHead = pNext;
		pNext = pHead->next;
	};
	delete pHead;
	pHead = NULL;
}
// 提取指定模块中的资源文件
// 参数：
//     strDstFile:     目标文件名。提取的资源将保存在这里；
//     strResType:     资源类型；
//     strResName:     资源名称；
// 返回值：
//     true: 执行成功；
//     false: 执行失败。
bool ExtractResource(LPCTSTR strDstFile, LPCTSTR strResType, LPCTSTR strResName)
{
	// 创建文件
	HANDLE hFile = ::CreateFile(strDstFile, GENERIC_WRITE, NULL, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_TEMPORARY, NULL);
	if (hFile == INVALID_HANDLE_VALUE)
		return false;

	// 查找资源文件中、加载资源到内存、得到资源大小
	HRSRC    hRes = ::FindResource(NULL, strResName, strResType);
	HGLOBAL    hMem = ::LoadResource(NULL, hRes);
	DWORD    dwSize = ::SizeofResource(NULL, hRes);

	// 写入文件
	DWORD dwWrite = 0; // 返回写入字节
	::WriteFile(hFile, hMem, dwSize, &dwWrite, NULL);
	::CloseHandle(hFile);

	return true;
}
int main()
{
	// 产生临时文件的文件名
	TCHAR tmpmp3[_MAX_PATH];
	::GetTempPath(_MAX_PATH, tmpmp3);
	_tcscat_s(tmpmp3, _T("testapp_background.mp3"));     
	// 将 MP3 资源提取为临时文件
	ExtractResource(tmpmp3, _T("MP3"), _T("background.mp3"));

	mciSendString(_T("close mymusic"), NULL, 0, NULL);				//关闭

	TCHAR mcicmd[300];
	_stprintf_s(mcicmd, _T("open \"%s\" alias mymusic"), tmpmp3);     // 打开
	mciSendString(mcicmd, NULL, 0, NULL);

	mciSendString(_T("play mymusic repeat"), NULL, 0, NULL);			//播放

	system("mode con cols=100 lines=33");
	SetConsoleTitle("贪吃蛇");
	welcome();
	gameStart();

	mciSendString(_T("close mymusic"), NULL, 0, NULL);
	DeleteFile(tmpmp3);

	color(0);
	gotoXY(0,30);
	return 0;
}