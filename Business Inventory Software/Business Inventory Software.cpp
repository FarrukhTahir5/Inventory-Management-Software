#include <conio.h>
#include <dos.h>
#include <stdio.h>
#include <iostream>
#include <Windows.h>
#include<string>
#include <vector>
#include<fstream>
#include <sstream>
#include <limits>
#include<iomanip>
using namespace std;
void fontsize(int, int);
void add_product();
void save();
void color(int color);
void gotoxy(int x, int y);
void modify();
void search_();
void showall();
void credits();
void saveas();
void init();
void menu();
void load_screen();
void management();
void find_();
int Inventory_menu();
int update();
int n = 0;
HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
struct Product {
	int PID, Quantity;
	string category, name;
	float buyP, sellP;
};
Product product[100];
int main() {
	fontsize(25, 25);
	init();
	SendMessage(::GetConsoleWindow(), WM_SYSKEYDOWN, VK_RETURN, 0x20000000);
	SetConsoleTitleA("\t\tBusiness Inventory Software");
	load_screen();
	menu();
	return 0;
}
void init() {
	update();
	ifstream file;
	string word;
	int i = 0, j = 0;
	file.open("Inventory Backup.txt");
	if (file.is_open())
		while (file >> word)
		{
			for (int j = 0; j < 7 && i == 0; j++)
				file >> word;
			if (i == 0)
				file >> word;
			product[i].PID = stoi(word);
			file >> word;
			product[i].category = word;
			file >> word;
			product[i].name = word;
			file >> word;
			product[i].Quantity = stoi(word);
			file >> word;
			product[i].buyP = stof(word);
			file >> word;
			product[i].sellP = stof(word);
			i++;
		}
}
void show(Product p) {
	cout << "\n\t\tProduct ID:" << p.PID << "\nCategory:" << p.category << "\nProduct Name:" << p.name << "\nQuantity:" << p.Quantity << "\nBuy Price:" << p.buyP << "\nSell Price:" << p.sellP << endl;
}
int update() {
	int i = 0;
	ifstream file;
	string line;
	file.open("Inventory Backup.txt");
	if (!file.eof())
	{
		while (getline(file >> ws, line))
			i++;
	}
	n = i - 1;
	file.close();
	return i;
}
int Inventory_menu() {
	system("cls");
	cout << "\t\t\t\tWelcome To Inventory Management" << endl;
	int Set[] = { 7,7,7,7,7 }; // DEFAULT COLORS
	int counter = 1;
	char key;

	for (int i = 0;;)
	{


		gotoxy(10, 5);
		color(Set[0]);
		cout << "1. Add Product";

		gotoxy(10, 6);
		color(Set[1]);
		cout << "2. Modify";

		gotoxy(10, 7);
		color(Set[2]);
		cout << "3. Search By ID";

		gotoxy(10, 8);
		color(Set[3]);
		cout << "4. Find";

		gotoxy(10, 9);
		color(Set[4]);
		cout << "5. Back";

		key = _getch();

		if (key == 72 && (counter >= 2 && counter <= 5))
		{
			counter--;
		}
		if (key == 80 && (counter >= 1 && counter <= 4))
		{
			counter++;
		}
		if (key == '\r')//carriage return
		{
			if (counter == 1)
			{// if enter is click and highlight is on 1 the program will run the code here
				add_product();
			}
			if (counter == 2)
			{
				modify();
			}
			if (counter == 3)
			{
				search_();
			}
			if (counter == 4)
			{
				find_();
			}
			if (counter == 5)
			{
				menu();
			}
		}

		Set[0] = 7;
		Set[1] = 7;
		Set[2] = 7;
		Set[3] = 7;
		Set[4] = 7;

		if (counter == 1)
		{
			Set[0] = 3;
		}
		if (counter == 2)
		{
			Set[1] = 3;
		}
		if (counter == 3)
		{
			Set[2] = 3;
		}
		if (counter == 4)
		{
			Set[3] = 3;
		}
		if (counter == 5)
		{
			Set[4] = 3;
		}


	}
	return 0;
}
void management() {
	Inventory_menu();
}
void save() {
	ofstream file;
	file.open("Inventory Backup.txt");
	file << "PID   \tCategory\tProduct\t\tQuantity   \tBuy Price   \tSell Price   \n";
	if (!file) {
		cout << "Error";
		system("pause");
		system("cls");
	}
	int i = 0;
	while (i < n) {
		file << product[i].PID << "\t" << product[i].category << "\t" << "\t" << product[i].name << "\t" << "\t" << product[i].Quantity << "\t\t" << product[i].buyP << "\t\t" << product[i].sellP << "\n";
		i++;
	}
	file.close();

}
void add_product() {
	system("cls");
	n = update();
	if (n == 0)
		n = 1;
	product[n - 1].PID = n - 1;
	cout << "Category:";

	getline(cin >> ws, product[n - 1].category);
	cout << "Product Name:";
	getline(cin >> ws, product[n - 1].name);
	cout << "Quantity:";
	cin >> product[n - 1].Quantity;
	cout << "Buying Price:";
	cin >> product[n - 1].buyP;
	cout << "Selling Price:";
	cin >> product[n - 1].sellP;
	show(product[n - 1]);
	save();
	cout << endl;
	system("pause");
	Inventory_menu();
}
void load_screen() {
	system("cls");
	for (int i = 1; i <= 50; i++)
	{
		system("cls");
		cout << "\n\n\n\n\t\t\t\t   Loading " << '\n' << '\t' << '\t';
		for (int j = 1; j <= i; j++)
			cout << "²";
		cout << "\n\n\t " << 2 * i << "%";
		if (i > 1 && i < 20)
			cout << "\n\n\tCreating Temporary files";
		else if (i > 20 && i < 40)
			cout << "\n\n\tAccessing Main Memory";
		else if (i > 40 && i < 48)
			cout << "\n\n\tAccessing Cache";
		else cout << "\n\n\tComplete ";
		Sleep(150 - i * 3);
	}
}
void color(int color) {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}
void gotoxy(int x, int y) {
	COORD c;
	c.X = x;
	c.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}
void modify() {
	system("cls");
	int i;
	cout << "Product ID:";
	cin >> i;
	if (i >= n)
	{
		cout << "\nProduct Not Found!\n";
		system("Pause");
		Inventory_menu();
	}
	show(product[i]);
	cout << "\nCategory:";
	getline(cin >> ws, product[i].category);
	cout << "Product Name:";
	getline(cin >> ws, product[i].name);
	cout << "Quantity:";
	cin >> product[i].Quantity;
	cout << "Buying Price:";
	cin >> product[i].buyP;
	cout << "Selling Price:";
	cin >> product[i].sellP;
	save();
	cout << endl;
	show(product[i]);
	cout << endl << "MODIFIED!" << endl;
	system("pause");
	system("cls");
}
void showall() {
	system("cls");
	for (int i = 0; i < n; i++)
		show(product[i]);
	cout << endl;
	system("pause");
	system("cls");
}
void menu() {
	system("cls");
	cout << "\t\t\t\tBusiness Inventory Software";
	int Set[] = { 7,7,7,7,7 }; // DEFAULT COLORS
	int counter = 1;
	char key;

	for (int i = 0;;)
	{


		gotoxy(10, 5);
		color(Set[0]);
		cout << "1. Inventory Management";

		gotoxy(10, 6);
		color(Set[1]);
		cout << "2. Save Record As";

		gotoxy(10, 7);
		color(Set[2]);
		cout << "3. Credits";

		gotoxy(10, 8);
		color(Set[3]);
		cout << "4. Show Record";

		gotoxy(10, 9);
		color(Set[4]);
		cout << "5. Exit";

		key = _getch();

		if (key == 72 && (counter >= 2 && counter <= 5))
		{
			counter--;
		}
		if (key == 80 && (counter >= 1 && counter <= 4))
		{
			counter++;
		}
		if (key == '\r')//carriage return
		{
			if (counter == 1)
			{
				// if enter is click and highlight is on 1 the program will run the code here
				management();
			}
			if (counter == 2)
			{
				saveas();
			}
			if (counter == 3)
			{
				credits();
			}
			if (counter == 4)
			{
				showall();
			}
			if (counter == 5)
			{
				exit(1);
			}
		}

		Set[0] = 7;
		Set[1] = 7;
		Set[2] = 7;
		Set[3] = 7;
		Set[4] = 7;

		if (counter == 1)
		{
			Set[0] = 3;
		}
		if (counter == 2)
		{
			Set[1] = 3;
		}
		if (counter == 3)
		{
			Set[2] = 3;
		}
		if (counter == 4)
		{
			Set[3] = 3;
		}
		if (counter == 5)
		{
			Set[4] = 3;
		}


	}

}
void fontsize(int a, int b) {
	PCONSOLE_FONT_INFOEX lpConsoleCurrentFontEx = new CONSOLE_FONT_INFOEX();
	lpConsoleCurrentFontEx->cbSize = sizeof(CONSOLE_FONT_INFOEX);
	GetCurrentConsoleFontEx(out, 0, lpConsoleCurrentFontEx);
	lpConsoleCurrentFontEx->dwFontSize.X = a;
	lpConsoleCurrentFontEx->dwFontSize.Y = b;
	SetCurrentConsoleFontEx(out, 0, lpConsoleCurrentFontEx);
}
void credits() {
	system("cls");
	cout << "\t\t\t\tBusiness Inventory Software\n\n\n\t\t\t\tProgramming Fundamental Lab Project\n\n\n\t\t\t\tDeveloped By Mohammad Farrukh Tahir\n\n\n\t\t\t\tBCS 1st Semester\n\n\n\n\n\n\n\n";
	system("Pause");
	system("cls");
}
void find_() {
	int res=0,l=0;
	system("cls");
	string fline, line;
	ifstream file;
	file.open("Inventory Backup.txt");
	cout << "\tFind In Record:";
	getline(cin>>ws, fline);
	cout << endl << endl;
	while (!file.eof())
	{
		getline(file, line);
		if (l == 0)
			cout << line<<endl;
		if (line.find(fline) != std::string::npos)
		{
			cout << line << endl;
			res++;
		}
		l++;
	}
	cout << endl << endl<<"\t\t"<<res<<" Results Found!\n\n";
	file.close();
	system("pause");
	system("cls");
}
void search_() {
	system("cls");
	int i;
	cout << "Enter Product ID:";
	cin >> i;
	if (i >= n)
	{
		cout << "\nProduct Not Found!\n";
		system("Pause");
		Inventory_menu();
	}
	show(product[i]);
	cout << endl;
	system("pause");
	system("cls");
}
void saveas() {
	system("cls");
	//load_screen();
	system("cls");
	string path, fn, pn;
	cout << "File Name:";
	getline(cin >> ws, fn);
	cout << "Path:";
	getline(cin >> ws, pn);
	path = pn + fn + ".txt";
	ofstream file;
	file.open(path);
	file << "PID   \tCategory\tProduct\t\tQuantity   \tBuy Price   \tSell Price   \n";
	if (!file) {
		cout << "Error";
		system("pause");
		system("cls");
	}
	int i = 0;
	while (i < n) {
		file << product[i].PID << "\t" << product[i].category << "\t" << "\t" << product[i].name << "\t" << "\t" << product[i].Quantity << "\t\t" << product[i].buyP << "\t\t" << product[i].sellP << "\n";
		i++;
	}
	file.close();
	cout << "File Saved in " << path << endl;
	system("pause");
	system("cls");
}
