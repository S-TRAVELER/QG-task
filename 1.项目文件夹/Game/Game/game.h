#pragma warning( disable : 4996)//本程序需用scanf消除输出异常
#include<iostream>
#include<stdlib.h>
#include<windows.h>
#include<fstream>
#include<string>
#include<graphics.h>
#include<conio.h>
#include<cstdio>

using namespace std;

struct Goods {
	string name;//商品名称 
	string material;//原料名称 
	int making_num;//正在制作的商品数量 
	int num;// 商品数量 
	int material_num;//原料数量 
	int buy_price;//购买价格 
	int sell_price;//出售价格 
	float limit_K;//限制
	Goods* next;
};

struct Tasks {
	string name;
	string dialogue;
	string detail;
	int p_task_money;
	int isopen;//0为未开放，1为已开放，2为已完成
};



class palyer {
public:
	Goods hamburger;//汉堡
	Goods milky_tea;//奶茶
	Goods chicken;//炸鸡
	Tasks p_task[3];//任务

	int money;//金币
	int money_temp = 0;
	int store;//拥有店铺数量
	int make_limit;//每回合制作限制
	int lv;//等级
	int bout = 1;//回合
	string title[5] = { "落魄小厨","小有名气","资深厨师","大家风范","一代宗师" };

public:
	palyer();
	~palyer();
	void show();//显示状态
	void market();//市场
	void buy(Goods*);//购物
	void enlarge();//开设分店
	void renew();//回合更新
	void task();//任务

};

inline void getText(string str_file)//文件读取
{
	fstream fin(str_file);
	MOUSEMSG m;

	setlinecolor(WHITE);
	for (int i = 0; i < 640; i++) {
		line(i, 0, i, 324);
		if (i % 5 == 0) {
			Sleep(1);
		}
	}
	if (fin.is_open())
	{
		string readline;
		int str_y = 30;
		setbkmode(TRANSPARENT);
		
		settextcolor(BLACK);
		while (getline(fin, readline)) {
			outtextxy(10,str_y, (char*)readline.data());
			str_y += 30;
		}
		fin.close();
	}
	
	setfillcolor(BLACK);
	settextcolor(WHITE);
	fillrectangle(600, 3, 630, 25);

	outtextxy(605, 5, "<<");

	while (true) {
		m = GetMouseMsg();
		if (m.uMsg == WM_LBUTTONDOWN) {
			if (m.x > 600 && m.x < 635 && m.y < 25) {
				return;

			}
		}
	}
}


#pragma once#pragma once
