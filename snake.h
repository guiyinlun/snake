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
//��ʼ
void gameStart();
//˵��
void explainGame();
//��ӭ
void welcome();
//��ͼ
void gameMap();
//��ɫ
int color(int c);
//���
void gotoXY(int x, int y);
//��ʼ��
struct Snake* initSnake();
//����
void runGame(struct Snake* snakeHead);
//�ƶ�
struct Snake* moveSnake(int dir, struct Snake* snakeHead);
//�������ʳ�� 
void createFood(struct Snake* snakeHead);
//�ж��Ƿ�ҧ�����Լ�
void biteself(struct Snake* snakeHead);
//ײǽ
void strikeWall(struct Snake* snakeHead);
//����
void endGame(int g);
//����ѡ��
void overchoose();
//�ͷ�����
void destroyList(struct Snake* pHead);
// ��ȡָ��ģ���е���Դ�ļ�
bool ExtractResource(LPCTSTR strDstFile, LPCTSTR strResType, LPCTSTR strResName);
