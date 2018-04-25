#include"game.h"

char c[1024];//�������stdin

palyer::palyer() {//����Ϸ���ݳ�ʼ��
	

	hamburger.name = "����";
	hamburger.material = "���";
	hamburger.making_num = 0;
	hamburger.num = 0;
	hamburger.material_num = 0;
	hamburger.buy_price = 2;
	hamburger.sell_price = 6;
	hamburger.next = &milky_tea;
	hamburger.limit_K = 3600;

	milky_tea.name = "�̲�";
	milky_tea.material = "ţ��";
	milky_tea.making_num = 0;
	milky_tea.num = 0;
	milky_tea.material_num = 0;
	milky_tea.buy_price = 5;
	milky_tea.sell_price = 12;
	milky_tea.next = &chicken;
	milky_tea.limit_K = 10800;

	chicken.name = "ը��";
	chicken.material = "����";
	chicken.making_num = 0;
	chicken.num = 0;
	chicken.material_num = 0;
	chicken.buy_price = 10;
	chicken.sell_price = 20;
	chicken.next = NULL;
	chicken.limit_K = 24000;

	p_task[0].name = "��������˽��";
	p_task[0].dialogue = "С��ͯ�����磬���ǵ�˽���Ѿ��ܵ����ˣ����ܰ��������ؽ���";
	p_task[0].detail = "����С��ͯ�ؽ�����˽��";
	p_task[0].isopen = 0;
	p_task[0].p_task_money = 600;

	p_task[1].name = "����";
	p_task[1].dialogue = "ũ��С�ֵܣ����������������֣��������գ�ϣ�����ܰ������Ƕɹ���κ��֡�";
	p_task[1].detail = "�������ذ��նɹ�����";
	p_task[1].isopen = 0;
	p_task[1].p_task_money = 1200;

	p_task[2].name = "�Ｏ����";
	p_task[2].dialogue = "�ᶽ���ˣ��������ѣ�ƥ�����𣬽�������Ҵ�����ϣ������Ϊ���ҹ���һ��������";
	p_task[2].detail = "�������ӣ��������";
	p_task[2].isopen = 0;
	p_task[2].p_task_money = 2000;

	money =800;//���
	money_temp = money;
	store = 1;
	lv = 0;//�ȼ�
	make_limit = 90;

}

palyer::~palyer()
{
}

void palyer::show()//չ�����״̬
{
	MOUSEMSG m;						// ���������Ϣ
	string str_temp;
	int buy_choice;
	char s[5];
	IMAGE img;	// ���� IMAGE 
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
		settextstyle(16, 0, _T("����"));
		settextcolor(WHITE);

		outtextxy(190, 30, "��ң�");
		sprintf(s, "%d", money);
		outtextxy(230, 30, s);
		outtextxy(190, 50, "����:");
		outtextxy(230, 50, (char*)title[lv].data());
		outtextxy(190, 70, "ӵ�е��̣�");
		sprintf(s, "%d", store);
		outtextxy(270, 70,s);
		outtextxy(190, 90, "����:");
		sprintf(s, "%d", store*3);
		outtextxy(230, 90, s);
		outtextxy(10, 125, "(ÿ������һ�������30��ʳƷ)");
		cout << "ÿ���غ����" << store * 200 << endl;
		Goods* p = (Goods*)&hamburger;
		int i = 1;
		for (; p != NULL; p = p->next) {
			str_temp= p->name+"��ʣ�������" +to_string(p->num) +",���ۼ۸�" +to_string(p->sell_price)+"������������" +to_string( p->making_num) + ")";
			outtextxy(10, str_y, (char*)str_temp.data());
			str_y += 20;
		}
		
		p = (Goods*)&hamburger;
		for (; p != NULL; p = p->next) {
			str_temp = p->material + "��ʣ�������" + to_string(p->material_num) + ",����۸�" + to_string(p->buy_price) + ")";
			outtextxy(10, str_y, (char*)str_temp.data());
			str_y += 20;
		}
		str_temp="�˻غ��㻹������" +to_string( make_limit) + "��ʳƷ" ;
		outtextxy(10, str_y, (char*)str_temp.data());
		setfillcolor(YELLOW);
		settextcolor(BLACK);
		for (int i = 0; i < 6; i++) {
			fillrectangle(button_x - 5, button_y, button_x + 35,button_y + 20);
			if (i < 3) {
				outtextxy(button_x, button_y,"����");
			}
			else {
				outtextxy(button_x, button_y, "����");
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
				InputBox(s, 5, "��������Ҫ����������");
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
							str_temp= "�����ɹ���������" +to_string(p->making_num) + "��"+p->name +"��������";
							outtextxy(10, 304,(char*)str_temp.data());
						}
						else {
							outtextxy(10, 304,"����ʧ�ܣ���û����ô���ԭ�ϣ���ȥ�г�����");
						}
					}
					else {
						outtextxy(10, 304,"��Ĺ����޷������ô��������뿪��ֵ������ӹ��ˡ�");
					}
				}
				else {
					outtextxy(10,304,"����ʧ�ܡ�");
				}
				break;
			}
		case 4:case 5:case 6:
			int price_choice;
			price_choice = 7 - temp_choice;
			int price;

			if (price_choice > 0 && price_choice < 4) {//�ƶ��۸�
				InputBox(s, 5, "��������Ҫ�ƶ��ļ۸�");
				sscanf(s, "%d", &price);
				p = (Goods*)&hamburger;
				if (price > 0) {
					while (--price_choice) {
						p = p->next;
					}
					p->sell_price = price;
					str_temp = "�����ɹ���";
					outtextxy(10, 304, (char*)str_temp.data());
				}
				else {
					str_temp = "�۸���С��0";
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

void palyer::market()//�̵�
{
	MOUSEMSG m;						// ���������Ϣ
	int choice;
	Goods* p;
	int i = 1;
	string str_temp;
	int buy_choice; 
	char s[5];
	IMAGE img;	// ���� IMAGE 
	int button_x=140, button_y=80;
	
	
	loadimage(NULL, "game\\game12_meitu_2_meitu_3.jpg");	// ��ȡͼƬ�� img ������
	while (1) {
		m = GetMouseMsg();
		if (m.uMsg == WM_LBUTTONDOWN || kbhit()) {
			break;
		}
	}
	while (1) {
		loadimage(NULL, "game\\game12_meitu_2.jpg");	// ��ȡͼƬ�� img ������

		setbkmode(TRANSPARENT);
		settextcolor(WHITE);
		sprintf(s, "%d", money);
		outtextxy(10, 8, "��ң� ");
		outtextxy(55, 8, s);

		for (int i = 0; i < 3; i++) {
			setfillcolor(YELLOW);
			settextcolor(BLACK);
			fillrectangle(button_x, button_y, button_x + 38, button_y + 20);
			outtextxy(button_x + 3, button_y + 3, "����");
			button_y += 50;
		}
		fillrectangle(7, 35, 45, 60);
		outtextxy(10, 38, "����");

		p = (Goods*)&hamburger;
		for (int str_y=80; p != NULL; p = p->next) {
			settextcolor(WHITE);
			setbkmode(OPAQUE);
			str_temp = p->material + "���۸�" + to_string(p->buy_price) + "��ӵ������" + to_string(p->material_num) + ",��������" + p->name + ")";//ʵ�ֶ������ݵ���ʱ���
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

void palyer::buy(Goods* p)//����
{
	int amount;
	char s[5];
	InputBox(s,5,"�����빺�������");
	sscanf(s, "%d", &amount);
	setbkmode(TRANSPARENT);
	settextcolor(WHITE);
	if (amount >= 0)
		if (amount*p->buy_price <= money) {
			p->material_num += amount;
			money -= amount * p->buy_price;
			outtextxy(310,310,"����ɹ���");
		}
		else {
			outtextxy(310, 310,"��Ľ�Ҳ���");
		}
	else {
		outtextxy(310, 310,"����ʧ��");
	}
	Sleep(1000);
}

void palyer::enlarge() //���ֵ�
{
	MOUSEMSG m;						// ���������Ϣ
	string str_temp;
	int buy_choice;
	char s[5];
	IMAGE img;	// ���� IMAGE 
	int button_x = 280, button_y = 120;
	int temp_choice;
	int str_y = 145;
	HWND wnd = GetHWnd();

	str_y = 140;
	button_y = 140;
	loadimage(&img, "game\\game02_meitu_2.jpg");

	setbkmode(TRANSPARENT);
	settextstyle(16, 0, _T("����"));
	settextcolor(WHITE);

	while (1) {
		putimage(0, 0, &img);
		settextcolor(WHITE);
		setlinecolor(WHITE);
		rectangle(5, 280, 630, 321);
		outtextxy(10, 284, "����ֵ�ʱ����Ҫ��1000���ң�֮��ÿ���غϵ��������200��ҡ�����ֵ������");
		outtextxy(10, 304, "�Ǻܴ��Ŷ�����ܸ�������3������");

		button_x = 280; 
		button_y = 100;

		rectangle(510, 5, 630, 95);
		str_temp = "��ң�" + to_string(money);
		outtextxy(520,10,(char*)str_temp.data()) ;
		str_temp = "ӵ�е��̣�" + to_string(store) + "��";
		outtextxy(520, 30, (char*)str_temp.data());
		str_temp="����:" +to_string(store * 3 );
		outtextxy(520, 50, (char*)str_temp.data());
		str_temp = "���:" + to_string(store*200);
		outtextxy(520, 70, (char*)str_temp.data());
		
		setfillcolor(YELLOW);//����
		settextcolor(BLACK);
		fillrectangle(button_x - 10, button_y - 5, button_x + 70, button_y + 25);
		outtextxy(button_x, button_y, "����ֵ�");
		button_y += 50;
		fillrectangle(button_x - 10, button_y - 5, button_x + 70, button_y + 25);
		outtextxy(button_x, button_y, "���ز˵�");

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
			if (MessageBox(wnd, "�Ƿ���ֵ�", "ѯ��", MB_YESNO | MB_ICONQUESTION) == IDYES){

			}
			else {
				break;
			}
			
			if (1000 <= money) {
				outtextxy(250,button_y+50,"����ֵ�ɹ����ֵ�����+1");
				money -= 1000;
				store += 1;
				make_limit += 90;
			}
			else {
				outtextxy(250, button_y + 50, "��Ľ�Ҳ���");
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

void palyer::renew()//�����غ�
{
	MOUSEMSG m;
	string str_temp;
	IMAGE img;
	int str_y=10;
	
	bout++;
	setlinecolor(WHITE);//ˢ�½���
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
			str_temp = "����" + to_string(p->num)+"��"+p->name+"�����ӽ��:"+to_string(p->sell_price*p->num);
			outtextxy(200, str_y, (char*)str_temp.data());
			str_y += 30;
		}
		else {
			int temp;
			temp = (int)(p->limit_K /( p->sell_price*p->sell_price));
			money += temp*p->sell_price;
			p->num = p->num - temp + p->making_num;
			p->making_num = 0;
			str_temp = "����" + to_string(p->num) + "��" + p->name + "�����ӽ��:" + to_string(p->sell_price*p->num);
			outtextxy(200, str_y, (char*)str_temp.data());
			str_y += 30;
		}
	}
	
	money -= 200 * store;
	str_temp = "���غ�֧�����" + to_string(200*store)+"���" ;
	outtextxy(200, str_y, (char*)str_temp.data());
	str_y += 30;
	if (money_temp < money) {
		str_temp = "���غ�Ӫ��" + to_string(money - money_temp)+"���";
	}
	else {
		str_temp = "���غϿ���" + to_string( money_temp-money) + "���";
	}
	outtextxy(200, str_y, (char*)str_temp.data());

	setfillcolor(BLACK);
	fillrectangle(290, 240, 350, 280);
	settextcolor(WHITE);
	outtextxy(305, 250, "����");
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

	if (money<0) {//��Ϸ��������
		//getimage(&img, 280, 70, 350, 310);
		settextcolor(BLACK);
		outtextxy(220, 60, "���Ʋ��ˣ���Ϸʧ��");

		setfillcolor(BLACK);
		fillrectangle(290, 240, 350, 280);
		settextcolor(WHITE);
		outtextxy(305, 250, "����");
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
		str_temp = "��ϲ��������<" + title[lv] + ">";
		outtextxy(240, 60, (char*)str_temp.data());
		if (lv == 4) {//��Ϸ��������
			outtextxy(280, 100, "��Ϸʤ��");
			setfillcolor(BLACK);
			fillrectangle(290, 240, 350, 280);
			settextcolor(WHITE);
			outtextxy(305, 250, "����");
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
			outtextxy(280, 100, "��������Ŷ");
		}

		setfillcolor(BLACK);
		fillrectangle(290, 240, 350, 280);
		settextcolor(WHITE);
		outtextxy(305, 250, "����");
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
		str_temp = "��������" + p_task[lv - 1].name + "��";
		outtextxy(230,180, (char*)str_temp.data());
		p_task[lv - 1].isopen = 1;

		setfillcolor(BLACK);
		fillrectangle(290, 240, 350, 280);
		settextcolor(WHITE);
		outtextxy(305, 250, "����");
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
	str_temp = "��" + to_string(bout) + "�غ�";
	settextcolor(BLACK);
	outtextxy(280, 70, (char*)str_temp.data());
	Sleep(800);
	make_limit = 90 * store;
	money_temp = money;
	
}

void palyer::task()//����
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
		outtextxy(10, 30, "��ң� ");
		outtextxy(55, 30, s);

		for (int i = 0; i < 3; i++) {
			if (p_task[i].isopen !=0) {		
				if (p_task[i].isopen == 1) {
					str_temp = "   ���";
				}
				else {
					str_temp = "�������";
				}
				
				fillrectangle(button_x - 5, button_y - 3, button_x +70, button_y + 20);
				outtextxy(button_x, button_y, (char*)str_temp.data());

				
				str_temp = p_task[i].name + "(" + p_task[i].detail + ";���������ң�" + to_string(p_task[i].p_task_money) + ")";
				outtextxy(button_x+80,button_y,(char*)str_temp.data());
				have_task = true;
				button_y += 35;
			}
		}
		if (have_task == false) {
			outtextxy(270,100,"��ǰ��û������");
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
				str_temp = "�Ƿ��ύ" + to_string(p_task[task_choice - 1].p_task_money)+"�����";
				if (MessageBox(wnd, str_temp.data(), "ѯ��", MB_YESNO | MB_ICONQUESTION) == IDYES) {

				}
				else {
					break;
				}

				if (money < p_task[task_choice - 1].p_task_money) {
					outtextxy(280, 300, "��Ľ�Ҳ���");
				}
				else {
					money -= p_task[task_choice - 1].p_task_money;
					p_task[task_choice - 1].isopen = 2;
					outtextxy(280, 300, "�ɹ��������");
				}
		default:
			break;
			}
			Sleep(1000);
		}
	}
	
}




