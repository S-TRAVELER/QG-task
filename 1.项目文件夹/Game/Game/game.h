#pragma warning( disable : 4996)//����������scanf��������쳣
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
	string name;//��Ʒ���� 
	string material;//ԭ������ 
	int making_num;//������������Ʒ���� 
	int num;// ��Ʒ���� 
	int material_num;//ԭ������ 
	int buy_price;//����۸� 
	int sell_price;//���ۼ۸� 
	float limit_K;//����
	Goods* next;
};

struct Tasks {
	string name;
	string dialogue;
	string detail;
	int p_task_money;
	int isopen;//0Ϊδ���ţ�1Ϊ�ѿ��ţ�2Ϊ�����
};



class palyer {
public:
	Goods hamburger;//����
	Goods milky_tea;//�̲�
	Goods chicken;//ը��
	Tasks p_task[3];//����

	int money;//���
	int money_temp = 0;
	int store;//ӵ�е�������
	int make_limit;//ÿ�غ���������
	int lv;//�ȼ�
	int bout = 1;//�غ�
	string title[5] = { "����С��","С������","�����ʦ","��ҷ緶","һ����ʦ" };

public:
	palyer();
	~palyer();
	void show();//��ʾ״̬
	void market();//�г�
	void buy(Goods*);//����
	void enlarge();//����ֵ�
	void renew();//�غϸ���
	void task();//����

};

inline void getText(string str_file)//�ļ���ȡ
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
