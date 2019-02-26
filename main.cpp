#include <time.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <windows.h>


using namespace std;

void start()
{
	string gamemode;
	cout << "Приветствуем Вас в нашей игре \"Тайный Гитлер\"!" << endl;
	cout << "\t\tЧтобы начать игру, нажмите Y. Выйти - N: ";
	while (true) {
		cin >> gamemode;
		if (gamemode == "y")
		{
			system("cls");
			cout << "0 - Гитлер; 1-2 - Фашисты; 3-6 - Либералы." << endl;
			break;

		}
		if (gamemode == "n") exit(0); else cout << "Неверная кнопка, повторите своё действие!" << endl;
	}
}

struct gg {
	string name;
	int role;
	gg* next;
	gg* prev;
};

class role {
public:
	role();
	~role();
	gg* head;
	gg* tail;
	gg* head_l;
	gg* tail_l;
	void add_player(string n, int r);
	void add_law(int r);
	void print();
	int laws[17] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1 }; //0 - fash; 1 - lib
	int used_laws[17];
	int used_role_num = 0;
	int roles[7] = { 0, 1, 2, 3, 4, 5, 6 }; //0-hitler;1-2-red;3-6-blue
	int used_role[7];
	const char* plrs[7] = { "p1", "p2", "p3", "p4", "p5", "p6", "p7" };
	int test_role;
	int used_num = 0;
	bool fucked;
	void choice_role();
	string name_role;
	void take_pres();
	bool chk_cons(int cc);
	void elections();
	gg* first_steper;
	gg* president;
	gg* cancler;
	gg* last_cancler;
	gg* last_president;
	void deck_building();
	void delete_law();
	bool first_time_cansler = true;
	void chk_fash_law(gg* first_card, gg* second_card, gg* third_card, int res_law);
	void pres_get_law();
	void cans_get_law(int res_law);
	gg* first_card = new gg;
	gg* second_card = new gg;
	gg* third_card = new gg;
};


role::role() : head(nullptr), tail(nullptr) {}

role::~role() {
	while (head != 0) {
		gg* c = head;
		head = head->next;
		delete c;
	}
}

void role::add_player(string n, int r) {
	gg* c = new gg();
	c->name = n;
	c->role = r;
	if (head == nullptr) {
		c->next = nullptr;
		c->prev = nullptr;
		head = c;
		tail = c;
	}
	else {
		tail->next = c;
		c->prev = tail;
		tail = c;
		tail->next = head;
		head->prev = tail;
	}
}

void role::add_law(int l) {
	gg* c = new gg();
	c->role = l;
	if ((head_l == nullptr)) {
		c->next = nullptr;
		c->prev = nullptr;
		head_l = c;
		tail_l = c;
	}
	else {
		head_l->next = c;
		head_l = c;
		//head -> next -> next -> tail -> nullptr;
		//Последний пришел - первый ушел;
	}
}

void role::print() {
	gg* c = new gg();
	c = head;
	do {
		cout << "Name - " << c->name << endl;
		cout << "Role - " << c->role << endl << endl;
		c = c->next;
	} while (c != head);
}

//Расспределение ролей между игроками
void role::choice_role() {
	for (int i = 0; i < 7; i++) {
		do {
			fucked = false;
			test_role = roles[rand() % 7];
			for (int j = 0; j < used_num; j++) {
				if (test_role == used_role[j])
					fucked = true;
			}
		} while (fucked == true);
		name_role = plrs[i];
		used_role[used_num] = test_role;
		used_num++;
		add_player(name_role, test_role);
	}
}

//Колода законов
void role::deck_building() {
	for (int i = 0; i < 17; i++) {
		do {
			fucked = false;
			test_role = roles[rand() % 17];
			for (int j = 0; j < used_role_num; j++) {
				if (test_role == used_role[j])
					fucked = true;
			}
		} while (fucked == true);
		add_law(test_role);
		used_laws[used_role_num] = test_role;
		used_role_num++;
	}
}

void role::delete_law() {
	gg* c = new gg();
	c = head_l;
	head_l = head_l->prev;
	delete c;
}

void role::take_pres() {
	president = head;
	int step = rand() % 7;
	for (int i = 0; i < step; i++) president = president->next; //random president
	last_president = president;//назначили его бывшим
}

bool role::chk_cons(int cc) {
	for (int i = 0; i < cc; i++)
	{
		cancler = cancler->next;
	}
	if (cancler->name == last_cancler->name) {
		cout << "Вы не можете выбрать этого игрока, который бывший канцлер. Выберите другого:";
		return 0;
	}
	else
		return 1;
}


//Выборы 
void role::elections()
{
	int choice_player;
	bool voice, cansler_control;
	int j;
	int law;
	for (j = 1; j < 4; j++)
	{
		first_steper = president; //ход от президента
		cancler = president;
		last_cancler = cancler;
		cout << endl << "\t\tТоварищ президент был определён, это игрок: " << first_steper->name << endl;
		cout << "Выбирете игрока, которого хотите назначить канцлером: " << endl;
		cout << "\t1 - " << first_steper->next->name << endl;
		cout << "\t2 - " << first_steper->next->next->name << endl;
		cout << "\t3 - " << first_steper->next->next->next->name << endl;
		cout << "\t4 - " << first_steper->prev->prev->prev->name << endl;
		cout << "\t5 - " << first_steper->prev->prev->name << endl;
		cout << "\t6 - " << first_steper->prev->name << endl;
		cout << "Ваш выбор: "; cin >> choice_player;		//проверка игрока,он бывший канцлер или нет
		if (first_time_cansler != true) {
			cansler_control = chk_cons(choice_player);
			if (cansler_control == 0) {
				elections();
			}
		}
		first_time_cansler = false;
		cout << "\t\tПроводим голосование:" << endl;
		system("pause");

		cout << j << " голосование:" << endl;//j - счётчик. Какое голосование по счёту (j>3 - рандом закон).
		int ya = 0, nein = 0;
		do {
			cout << "Игрок под именем #" << first_steper->name << "# голосуй!(1 - ya, 0 - nein): "; cin >> voice;
			if (voice == 1) ya++;
			else nein++;
			first_steper = first_steper->next;
			system("cls");
		} while (first_steper != president);


		cout << "Проголосовало Ya: " << ya << " человек." << endl;
		cout << "Проголосовало Nein: " << nein << " человек." << endl;
		//назначение канцлера  
		if (ya > nein)
		{
			for (int i = 0; i < choice_player; i++)
			{
				cancler = cancler->next;
				j = 1;
			}
			break;
		}
		else
		{
			president = president->next;
			continue;
		}
	}
	if (j > 3)
	{
		law = laws[rand() % 17];
		cout << "Выбирается случайный закон, потому что канцлер не был выбран трижды...Подождите..." << endl;
		Sleep(3000);
		if (law == 0) cout << "Выбран случайный закон: ФАШИСТСКИЙ!" << endl;
		else cout << "Выбран случайный закон: ЛИБЕРАЛЬНЫЙ!" << endl;
		goto m1;
	}
	cout << "Игрок #" << cancler->name << "# назначен канцлером! " << endl;


m1:	system("pause");
	system("cls");
}

void role::chk_fash_law(gg* first_card, gg* second_card, gg* third_card, int res_law) {
	if (res_law != 1) {
		if (first_card->role == 0) {
			cout << "1 - Фашистский закон" << endl;
		}
		else {
			cout << "1 - Либеральный закон" << endl;
		}
	}
	if (res_law != 2) {
		if (second_card->role == 0) {
			cout << "2 - Фашистский закон" << endl;
		}
		else {
			cout << "2 - Либеральный закон" << endl;
		}
	}
	if (res_law != 3) {
		if (third_card->role == 0) {
			cout << "3 - Фашистский закон" << endl;
		}
		else {
			cout << "3 - Либеральный закон" << endl;
		}
	}
}

void role::pres_get_law() {

	int res_law;

	first_card = head_l;
	delete_law();
	second_card = head_l;
	delete_law();
	third_card = head_l;
	delete_law();

	chk_fash_law(first_card, second_card, third_card, 0);

	cout << "Удаляй закон, мудила!!(("; cin >> res_law;

	system("pause");
	system("cls");

	chk_fash_law(first_card, second_card, third_card, res_law);
	cans_get_law(res_law);
}

void role::cans_get_law(int res_law) {
	int resed_law;
	cout << "Выбирай закон, мудила!!(("; cin >> resed_law;
	if (resed_law == 1) {
		if (resed_law != res_law) {
			if (first_card->role == 0) {
				//+1 фаш закон
			}
			else {
				//+1 либ закон
			}
		}
		else {
			cout << "Нельзя принимать этот закон!!" << endl;
			cans_get_law(res_law);
		}
	}
	else if (resed_law == 2 && resed_law != res_law) {
		if (resed_law != res_law) {
			if (second_card->role == 0) {
				//+1 фаш закон
			}
			else {
				//+1 либ закон
			}
		}
		else {
			cout << "Нельзя принимать этот закон!!" << endl;
			cans_get_law(res_law);
		}
	}
	else if (resed_law == 3 && resed_law != res_law) {
		if (resed_law != res_law) {
			if (third_card->role == 0) {
				//+1 фаш закон
			}
			else {
				//+1 либ закон
			}
		}
		else {
			cout << "Нельзя принимать этот закон!!" << endl;
			cans_get_law(res_law);
		}
	}
}

int main()
{
	setlocale(LC_ALL, "Rus");
	srand((unsigned)time(NULL));
	start();
	role r;
	r.choice_role();		//17 законов (11 fashicst, 6 liberal)
	//r.print();
	r.take_pres();
	r.elections();

	system("PAUSE");
	return 0;
}