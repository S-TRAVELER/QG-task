#include"game.h"

char c[1024];//用于清空stdin

palyer::palyer() {//给游戏数据初始化
	

	hamburger.name = "汉堡";
	hamburger.material = "面粉";
	hamburger.making_num = 0;
	hamburger.num = 0;
	hamburger.material_num = 0;
	hamburger.buy_price = 2;
	hamburger.sell_price = 6;
	hamburger.next = &milky_tea;
	hamburger.limit_K = 3600;

	milky_tea.name = "奶茶";
	milky_tea.material = "牛奶";
	milky_tea.making_num = 0;
	milky_tea.num = 0;
	milky_tea.material_num = 0;
	milky_tea.buy_price = 5;
	milky_tea.sell_price = 12;
	milky_tea.next = &chicken;
	milky_tea.limit_K = 10800;

	chicken.name = "炸鸡";
	chicken.material = "鸡肉";
	chicken.making_num = 0;
	chicken.num = 0;
	chicken.material_num = 0;
	chicken.buy_price = 10;
	chicken.sell_price = 20;
	chicken.next = NULL;
	chicken.limit_K = 24000;

	p_task[0].name = "资助当地私塾";
	p_task[0].dialogue = "小书童：大哥哥，我们的私塾已经很倒塌了，你能帮助我们重建吗？";
	p_task[0].detail = "帮助小书童重建他的私塾";
	p_task[0].isopen = 0;
	p_task[0].p_task_money = 600;

	p_task[1].name = "赈灾";
	p_task[1].dialogue = "农夫：小兄弟，今年我们遇到旱灾，颗粒无收，希望你能帮助我们渡过这次旱灾。";
	p_task[1].detail = "帮助当地百姓渡过旱灾";
	p_task[1].isopen = 0;
	p_task[1].p_task_money = 1200;

	p_task[2].name = "筹集军资";
	p_task[2].dialogue = "提督大人：国家有难，匹夫有责，金兵入侵我大明，希望你能为国家贡献一份力量。";
	p_task[2].detail = "资助军队，抵御金兵";
	p_task[2].isopen = 0;
	p_task[2].p_task_money = 2000;

	money =800;//金币
	money_temp = money;
	store = 1;
	lv = 0;//等级
	make_limit = 90;

}

palyer::~palyer()
{
}

void palyer::show()//展现玩家状态
{
	MOUSEMSG m;						// 定义鼠标消息
	string str_temp;
	int buy_choice;
	char s[5];
	IMAGE img;	// 定义 IMAGE 
	int button_x =420, button_y = 140;
	int temp_choice;
	int str_y = 145;

	setlinecolor(BLACK);
	for (int i = 0; i <470; i++) {
		line(i, 0, i, 324);
		if (i % 5 == 0) {
			Sleep(1);
		}
	}
	while (1) {
		for (int i = 0; i <470; i++) {
			line(i, 0, i, 324);
		}
		str_y = 140;
		button_y = 140;
		loadimage(&img, "game\\game09_meitu_1.jpg");
		putimage(20, 10, &img);

		setbkmode(TRANSPARENT);
		settextstyle(16, 0, _T("宋体"));
		settextcolor(WHITE);

		outtextxy(190, 30, "金币：");
		sprintf(s, "%d", money);
		outtextxy(230, 30, s);
		outtextxy(190, 50, "名号:");
		outtextxy(230, 50, (char*)title[lv].data());
		outtextxy(190, 70, "拥有店铺：");
		sprintf(s, "%d", store);
		outtextxy(270, 70,s);
		outtextxy(190, 90, "工人:");
		sprintf(s, "%d", store*3);
		outtextxy(230, 90, s);
		outtextxy(10, 125, "(每个工人一天可制作30份食品)");
		cout << "每个回合租金：" << store * 200 << endl;
		Goods* p = (Goods*)&hamburger;
		int i = 1;
		for (; p != NULL; p = p->next) {
			str_temp= p->name+"（剩余份数：" +to_string(p->num) +",出售价格：" +to_string(p->sell_price)+"，正在制作：" +to_string( p->making_num) + ")";
			outtextxy(10, str_y, (char*)str_temp.data());
			str_y += 20;
		}
		
		p = (Goods*)&hamburger;
		for (; p != NULL; p = p->next) {
			str_temp = p->material + "（剩余份数：" + to_string(p->material_num) + ",购买价格：" + to_string(p->buy_price) + ")";
			outtextxy(10, str_y, (char*)str_temp.data());
			str_y += 20;
		}
		str_temp="此回合你还可制作" +to_string( make_limit) + "份食品" ;
		outtextxy(10, str_y, (char*)str_temp.data());
		setfillcolor(YELLOW);
		settextcolor(BLACK);
		for (int i = 0; i < 6; i++) {
			fillrectangle(button_x - 5, button_y, button_x + 35,button_y + 20);
			if (i < 3) {
				outtextxy(button_x, button_y,"定价");
			}
			else {
				outtextxy(button_x, button_y, "制作");
			}
			button_y += 20;
		}
		setfillcolor(WHITE); 
		settextcolor(BLACK);
		fillrectangle(440, 3, 470, 25);
		
		outtextxy(450, 5, "<<");
		while (true) {
			m = GetMouseMsg();
			if (m.uMsg == WM_LBUTTONDOWN) {
				if (m.x > button_x&& m.x < button_x+35&&m.y>140) {
					temp_choice = (button_y-m.y) / 20 + 1;
					break;
				}
				else if (m.x > 470) {
					return;
				}
				else if (m.x > 430 && m.y < 30) {
					return;
				}
			}
		}
		int make_choice = 0;
		settextcolor(WHITE);
		switch (temp_choice) {
		case 1:case 2:case 3:
			make_choice =4-temp_choice;
			int make_num;
		
			if (make_choice>0 && make_choice<4) {
				InputBox(s, 5, "请输入你要制作的数量");
				sscanf(s, "%d", &make_num);
				p = (Goods*)&hamburger;
				if (make_num>0) {
					if (make_limit >= make_num) {
						while (--make_choice) {
							p = p->next;
						}
						if (make_num <= p->material_num) {
							p->material_num -= make_num;
							p->making_num += make_num;
							make_limit -= make_num;
							str_temp= "操作成功！现在有" +to_string(p->making_num) + "份"+p->name +"正在制作";
							outtextxy(10, 304,(char*)str_temp.data());
						}
						else {
							outtextxy(10, 304,"制作失败，你没有这么多的原料，请去市场购买");
						}
					}
					else {
						outtextxy(10, 304,"你的工人无法完成这么多的任务，请开设分店来增加工人。");
					}
				}
				else {
					outtextxy(10,304,"输入失败。");
				}
				break;
			}
		case 4:case 5:case 6:
			int price_choice;
			price_choice = 7 - temp_choice;
			int price;

			if (price_choice > 0 && price_choice < 4) {//制定价格
				InputBox(s, 5, "请输入你要制定的价格");
				sscanf(s, "%d", &price);
				p = (Goods*)&hamburger;
				if (price > 0) {
					while (--price_choice) {
						p = p->next;
					}
					p->sell_price = price;
					str_temp = "操作成功！";
					outtextxy(10, 304, (char*)str_temp.data());
				}
				else {
					str_temp = "价格不能小于0";
					outtextxy(10, 304, (char*)str_temp.data());
				}
			}
			break;
		default:
			break;
		}		
		Sleep(1200);
	}

}

void palyer::market()//商店
{
	MOUSEMSG m;						// 定义鼠标消息
	int choice;
	Goods* p;
	int i = 1;
	string str_temp;
	int buy_choice; 
	char s[5];
	IMAGE img;	// 定义 IMAGE 
	int button_x=140, button_y=80;
	
	
	loadimage(NULL, "game\\game12_meitu_2_meitu_3.jpg");	// 读取图片到 img 对象中
	while (1) {
		m = GetMouseMsg();
		if (m.uMsg == WM_LBUTTONDOWN || kbhit()) {
			break;
		}
	}
	while (1) {
		loadimage(NULL, "game\\game12_meitu_2.jpg");	// 读取图片到 img 对象中

		setbkmode(TRANSPARENT);
		settextcolor(WHITE);
		sprintf(s, "%d", money);
		outtextxy(10, 8, "金币： ");
		outtextxy(55, 8, s);

		for (int i = 0; i < 3; i++) {
			setfillcolor(YELLOW);
			settextcolor(BLACK);
			fillrectangle(button_x, button_y, button_x + 38, button_y + 20);
			outtextxy(button_x + 3, button_y + 3, "购买");
			button_y += 50;
		}
		fillrectangle(7, 35, 45, 60);
		outtextxy(10, 38, "返回");

		p = (Goods*)&hamburger;
		for (int str_y=80; p != NULL; p = p->next) {
			settextcolor(WHITE);
			setbkmode(OPAQUE);
			str_temp = p->material + "（价格：" + to_string(p->buy_price) + "，拥有量：" + to_string(p->material_num) + ",用于制作" + p->name + ")";//实现多种数据的延时输出
			outtextxy(185,str_y,(char*)str_temp.data());
			str_y += 50;
		}
		button_y = 80;
	
		while (true) {
			m = GetMouseMsg();
			if (m.uMsg == WM_LBUTTONDOWN) {
				if (m.x > 140 && m.x < 178) {
					buy_choice = (m.y - 80) / 50 + 1;
					break;
				}
				else if (m.x >= 7 && m.x <= 45 && m.y >= 35 && m.y <= 60) {
					 return;
				}
			}
		}
		switch (buy_choice) {
		case 1:
			buy(&hamburger);
			break;
		case 2:
			buy(&milky_tea);
			break;
		case 3:
			buy(&chicken);
			break;
		default:
			break;
		}
	}
}

void palyer::buy(Goods* p)//购买
{
	int amount;
	char s[5];
	InputBox(s,5,"请输入购买的数量");
	sscanf(s, "%d", &amount);
	setbkmode(TRANSPARENT);
	settextcolor(WHITE);
	if (amount >= 0)
		if (amount*p->buy_price <= money) {
			p->material_num += amount;
			money -= amount * p->buy_price;
			outtextxy(310,310,"购买成功！");
		}
		else {
			outtextxy(310, 310,"你的金币不足");
		}
	else {
		outtextxy(310, 310,"输入失败");
	}
	Sleep(1000);
}

void palyer::enlarge() //开分店
{
	MOUSEMSG m;						// 定义鼠标消息
	string str_temp;
	int buy_choice;
	char s[5];
	IMAGE img;	// 定义 IMAGE 
	int button_x = 280, button_y = 120;
	int temp_choice;
	int str_y = 145;
	HWND wnd = GetHWnd();

	str_y = 140;
	button_y = 140;
	loadimage(&img, "game\\game02_meitu_2.jpg");

	setbkmode(TRANSPARENT);
	settextstyle(16, 0, _T("宋体"));
	settextcolor(WHITE);

	while (1) {
		putimage(0, 0, &img);
		settextcolor(WHITE);
		setlinecolor(WHITE);
		rectangle(5, 280, 630, 321);
		outtextxy(10, 284, "开设分店时你需要交1000块金币，之后每个回合的租金增加200金币。开设分店的利润");
		outtextxy(10, 304, "是很大的哦，它能给你增加3个工人");

		button_x = 280; 
		button_y = 100;

		rectangle(510, 5, 630, 95);
		str_temp = "金币：" + to_string(money);
		outtextxy(520,10,(char*)str_temp.data()) ;
		str_temp = "拥有店铺：" + to_string(store) + "间";
		outtextxy(520, 30, (char*)str_temp.data());
		str_temp="工人:" +to_string(store * 3 );
		outtextxy(520, 50, (char*)str_temp.data());
		str_temp = "租金:" + to_string(store*200);
		outtextxy(520, 70, (char*)str_temp.data());
		
		setfillcolor(YELLOW);//按键
		settextcolor(BLACK);
		fillrectangle(button_x - 10, button_y - 5, button_x + 70, button_y + 25);
		outtextxy(button_x, button_y, "开设分店");
		button_y += 50;
		fillrectangle(button_x - 10, button_y - 5, button_x + 70, button_y + 25);
		outtextxy(button_x, button_y, "返回菜单");

		while (true) {
			m = GetMouseMsg();
			if (m.uMsg == WM_LBUTTONDOWN) {
				if (m.x > button_x-10 && m.x < button_x+70&&m.y>button_y-55&&m.y<button_y-25) {
					temp_choice = 1;
					break;
				}
				else if (m.x > button_x - 10 && m.x < button_x + 70 && m.y>button_y - 5 && m.y<button_y + 25) {
					temp_choice = 2;
					break;
				}
			}
		}

		settextcolor(WHITE);
		switch (temp_choice) {
		case 1:
			if (MessageBox(wnd, "是否开设分店", "询问", MB_YESNO | MB_ICONQUESTION) == IDYES){

			}
			else {
				break;
			}
			
			if (1000 <= money) {
				outtextxy(250,button_y+50,"开设分店成功！分店数量+1");
				money -= 1000;
				store += 1;
				make_limit += 90;
			}
			else {
				outtextxy(250, button_y + 50, "你的金币不足");
			}
			break;
		case 2:
			return;
		default:
			break;
		}
		Sleep(1000);
	}
}

void palyer::renew()//结束回合
{
	MOUSEMSG m;
	string str_temp;
	IMAGE img;
	int str_y=10;
	
	bout++;
	setlinecolor(WHITE);//刷新界面
	settextcolor(BLACK);
	setbkmode(TRANSPARENT);
	for (int i = 0; i <= 324; i++)
	{
		line(0, i, 640, i);	
		if (i % 10 == 0) {
			Sleep(1);
		}
	}
	getimage(&img, 280, 60, 350, 100);

	for (Goods* p = (Goods*)&hamburger; p != NULL; p = p->next) {
		if (p->num <= p->limit_K / (p->sell_price*p->sell_price)) {
			money += p->sell_price*p->num;
			p->num = p->making_num;
			p->making_num = 0;
			str_temp = "卖出" + to_string(p->num)+"份"+p->name+"，增加金币:"+to_string(p->sell_price*p->num);
			outtextxy(200, str_y, (char*)str_temp.data());
			str_y += 30;
		}
		else {
			int temp;
			temp = (int)(p->limit_K /( p->sell_price*p->sell_price));
			money += temp*p->sell_price;
			p->num = p->num - temp + p->making_num;
			p->making_num = 0;
			str_temp = "卖出" + to_string(p->num) + "份" + p->name + "，增加金币:" + to_string(p->sell_price*p->num);
			outtextxy(200, str_y, (char*)str_temp.data());
			str_y += 30;
		}
	}
	
	money -= 200 * store;
	str_temp = "本回合支付租金：" + to_string(200*store)+"金币" ;
	outtextxy(200, str_y, (char*)str_temp.data());
	str_y += 30;
	if (money_temp < money) {
		str_temp = "本回合营收" + to_string(money - money_temp)+"金币";
	}
	else {
		str_temp = "本回合亏损" + to_string( money_temp-money) + "金币";
	}
	outtextxy(200, str_y, (char*)str_temp.data());

	setfillcolor(BLACK);
	fillrectangle(290, 240, 350, 280);
	settextcolor(WHITE);
	outtextxy(305, 250, "继续");
	while (1) {
		m = GetMouseMsg();
		if (m.uMsg == WM_LBUTTONDOWN) {
			if (m.x >= 290 && m.y >= 240 && m.x <= 350 && m.y <= 280) {
				break;
			}
		}
	}
	
	for (int i = 0; i <= 324; i++)
	{
		line(0, i, 640, i);
	}

	if (money<0) {//游戏结束条件
		//getimage(&img, 280, 70, 350, 310);
		settextcolor(BLACK);
		outtextxy(220, 60, "你破产了，游戏失败");

		setfillcolor(BLACK);
		fillrectangle(290, 240, 350, 280);
		settextcolor(WHITE);
		outtextxy(305, 250, "继续");
		while (1) {
			m = GetMouseMsg();
			if (m.uMsg == WM_LBUTTONDOWN) {
				if (m.x >= 290 && m.y >= 240 && m.x <= 350 && m.y <= 280) {
					break;
				}
			}
		}
		exit(0);
	}
	else if (money / 1000 - lv && lv<4) {
		settextcolor(BLACK);
		lv++;
		str_temp = "恭喜你获得名号<" + title[lv] + ">";
		outtextxy(240, 60, (char*)str_temp.data());
		if (lv == 4) {//游戏结束条件
			outtextxy(280, 100, "游戏胜利");
			setfillcolor(BLACK);
			fillrectangle(290, 240, 350, 280);
			settextcolor(WHITE);
			outtextxy(305, 250, "继续");
			while (1) {
				m = GetMouseMsg();
				if (m.uMsg == WM_LBUTTONDOWN) {
					if (m.x >= 290 && m.y >= 240 && m.x <= 350 && m.y <= 280) {
						break;
					}
				}
			}
			exit(0);
		}
		else {
			outtextxy(280, 100, "继续加油哦");
		}

		setfillcolor(BLACK);
		fillrectangle(290, 240, 350, 280);
		settextcolor(WHITE);
		outtextxy(305, 250, "继续");
		while (1) {
			m = GetMouseMsg();
			if (m.uMsg == WM_LBUTTONDOWN ) {
				if (m.x >= 290 && m.y >= 240 && m.x <= 350 && m.y <= 280) {
					break;
				}
			}
		}
	}

	if (lv<4 && lv>0&&(money / 1300 - lv+1) && p_task[lv - 1].isopen == 0) {
		for (int i = 0; i <= 324; i++)
		{
			line(0, i, 640, i);
		}
		settextcolor(BLACK);
		outtextxy(10,50,(char*)(p_task[lv - 1].dialogue.data()));
		str_temp = "你获得任务“" + p_task[lv - 1].name + "”";
		outtextxy(230,180, (char*)str_temp.data());
		p_task[lv - 1].isopen = 1;

		setfillcolor(BLACK);
		fillrectangle(290, 240, 350, 280);
		settextcolor(WHITE);
		outtextxy(305, 250, "继续");
		while (1) {
			m = GetMouseMsg();
			if (m.uMsg == WM_LBUTTONDOWN) {
				if (m.x >= 290 && m.y >= 240 && m.x <= 350 && m.y <= 280) {
					break;
				}
			}
		}
	}
	for (int i = 0; i <= 324; i++)
	{
		line(0, i, 640, i);
	}
	str_temp = "第" + to_string(bout) + "回合";
	settextcolor(BLACK);
	outtextxy(280, 70, (char*)str_temp.data());
	Sleep(800);
	make_limit = 90 * store;
	money_temp = money;
	
}

void palyer::task()//任务
{
	bool have_task = false;
	string str_temp;
	int task_choice=0;
	IMAGE img;
	char s[10];
	MOUSEMSG m;
	int  button_x, button_y;
	HWND wnd = GetHWnd();

	loadimage(&img, "game\\game15_meitu_1.jpg");
	putimage(0, 0, &img);
	while (1) {
		putimage(0, 0, &img);
		button_x = 80;
		button_y = 65;
		setbkmode(TRANSPARENT);
		settextcolor(WHITE);
		setfillcolor(BLACK);
		fillrectangle(5, 3, 30, 25);
		outtextxy(10, 5, "<<");
		sprintf(s, "%d", money);
		outtextxy(10, 30, "金币： ");
		outtextxy(55, 30, s);

		for (int i = 0; i < 3; i++) {
			if (p_task[i].isopen !=0) {		
				if (p_task[i].isopen == 1) {
					str_temp = "   完成";
				}
				else {
					str_temp = "√已完成";
				}
				
				fillrectangle(button_x - 5, button_y - 3, button_x +70, button_y + 20);
				outtextxy(button_x, button_y, (char*)str_temp.data());

				
				str_temp = p_task[i].name + "(" + p_task[i].detail + ";任务所需金币：" + to_string(p_task[i].p_task_money) + ")";
				outtextxy(button_x+80,button_y,(char*)str_temp.data());
				have_task = true;
				button_y += 35;
			}
		}
		if (have_task == false) {
			outtextxy(270,100,"当前你没有任务");
		}
		while (1) {
			m = GetMouseMsg();
			if (m.uMsg == WM_LBUTTONDOWN) {
				if (m.x >= button_x-5 && m.x <= button_x + 70 && m.y <= button_y && m.y >= 65) {
					if (p_task[(m.y - 65) / 35].isopen == 1) {
						task_choice = (m.y - 65) / 35 + 1;
						break;
					}
				}
				else if (m.x >= 5 && m.x <= 30 && m.y >= 3 && m.y <= 25) {
					return;
				}
			}
		}

			
		switch (task_choice) {
		case 1:case 2:case 3:
			settextcolor(BLACK);
			if (p_task[task_choice - 1].isopen == 1) {
				str_temp = "是否提交" + to_string(p_task[task_choice - 1].p_task_money)+"个金币";
				if (MessageBox(wnd, str_temp.data(), "询问", MB_YESNO | MB_ICONQUESTION) == IDYES) {

				}
				else {
					break;
				}

				if (money < p_task[task_choice - 1].p_task_money) {
					outtextxy(280, 300, "你的金币不足");
				}
				else {
					money -= p_task[task_choice - 1].p_task_money;
					p_task[task_choice - 1].isopen = 2;
					outtextxy(280, 300, "成功完成任务！");
				}
		default:
			break;
			}
			Sleep(1000);
		}
	}
	
}




