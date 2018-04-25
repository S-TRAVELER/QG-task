#include"game.h"
using namespace std;

char s[1024];//用于清空stdin

int main()
{
	palyer palyer01;
	initgraph(640, 324);
	string str;
	IMAGE img;	// 定义 IMAGE 对象
	int x = 0, y = 0;
	int choice;

	loadimage(&img, "game\\game03_MEitu_1.jpg");	// 读取图片到 img 对象中
	putimage(0, 0, &img);	// 在坐标 (0, 0) 位置显示 IMAGE 对象

	MOUSEMSG m;						// 定义鼠标消息
	
	while (1) {
		m = GetMouseMsg();
		if (m.uMsg == WM_LBUTTONDOWN) {
			break;
		}
	}
	fstream fin("out.txt");

	setlinecolor(WHITE);
	loadimage(&img, "game\\game17_meitu_2.jpg");	// 读取图片到 img 对象中
	

	if (fin.is_open())
	{
		string readline;
		int str_y = 150;
		setbkmode(TRANSPARENT);
		setfillcolor(BLACK);

		settextcolor(YELLOW);
		while (getline(fin, readline)) {
			putimage(0, 0, &img);	// 在坐标 (0, 0) 位置显示 IMAGE 对象
			outtextxy(10, 10, "<明末 顺天府>");
			outtextxy(180, 280, (char*)readline.data());
			
			fillrectangle(580, 295, 623, 320);
			outtextxy(585, 300, "NEXT");
			while (true) {
				m = GetMouseMsg();
				if (m.uMsg == WM_LBUTTONDOWN) {
					if (m.x > 580&& m.x < 613 && m.y >300) {
						break;
					}
				}
			}
		}
		fin.close();
	}

	

	

	
	
	while (1) {
		loadimage(&img, "game\\game13_meitu_4.jpg");	// 读取图片到 img 对象中
		putimage(0, 0, &img);
		while (true) {
			m = GetMouseMsg();
			if (m.uMsg == WM_LBUTTONDOWN) {
				if (m.x > 488 && m.x < 607) {
					choice = (m.y - 16) / 50+1;
					break;
				}
			}
		}

		switch (choice) {//主菜单选择
		case 1:
			palyer01.market();
			system("cls");
			break;
		case 2:
			palyer01.show();
			system("cls");
			break;
		case 3:
			system("cls");
			palyer01.enlarge();
			system("cls");
			break;
		case 4:
			system("cls");
			palyer01.task();
			system("cls");
			break;
		case 5:
			system("cls");
			palyer01.renew();
			system("cls");
			break;
		case 6:
			system("cls");
			getText("help.txt");
			system("cls");
			break;
		default:
			break;
		}
		choice = 0;

	}

	_getch();
	closegraph();

	return 0;
}
