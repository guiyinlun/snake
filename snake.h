#pragma once
#include<stdio.h>
#include<string>
#include<stdlib.h>
#include<windows.h>
#include<conio.h>
#include<ctime>
#include<iostream>
#include<Mmsystem.h>
#include <graphics.h>
#pragma comment(lib, "Winmm.lib") 
using namespace std;
//开始
void gameStart();
//说明
void explainGame();
//欢迎
void welcome();
//地图
void gameMap();
//颜色
int color(int c);
//光标
void gotoXY(int x, int y);
//初始化
struct Snake* initSnake();
//运行
void runGame(struct Snake* snakeHead);
//移动
struct Snake* moveSnake(int dir, struct Snake* snakeHead);
//随机出现食物 
void createFood(struct Snake* snakeHead);
//判断是否咬到了自己
void biteself(struct Snake* snakeHead);
//撞墙
void strikeWall(struct Snake* snakeHead);
//结束
void endGame(int g);
//结束选择
void overchoose();
//释放链表
void destroyList(struct Snake* pHead);
// 提取指定模块中的资源文件
bool ExtractResource(LPCTSTR strDstFile, LPCTSTR strResType, LPCTSTR strResName);
