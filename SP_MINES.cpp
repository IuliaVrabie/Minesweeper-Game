#include <iostream>
using namespace std;

class Game {
private:
	bool** field_hidden; //locul ascuns de marimea NxN
	char** field; //locul vizibil
	int size;

public:
	Game();
	Game(int);
	~Game();
	//functie pentru curatarea locului
	void clear_field(char s = '*') {
		for (int i = 0; i < size; i++) {
			for (int j = 0; j < size; j++) {
				field[i][j] = s;
				field_hidden[i][j] = 0;

			}
		}
	}

	//functie pentru setarea minelor pana nu ajunge la nr necesar in cazul dat 10
	void set_mine_count(int count = 10) {
		for (int i = 0; i < count;) {
			int x = rand() % size;
			int y = rand() % size;
			//ai controlam daca este mina sau nu 
			//daca in acest loc este 0 schimbam in 1
			//doar cand plasam o mina i se incrememteaza
			if (!field_hidden[x][y]) {
				field_hidden[x][y] = 1;
				i++;
			}
		}
	}


	//afisarea locului celula-spatiu 
	//randurile sunt insemnate cu litere 
	//coloanele sunt insemnate cu cifre
	void show_field() {
		cout << "  ";
		for (int i = 0; i < size; i++) {
			cout << i << " ";
		}
		cout << "\n ---------------------\n";
		for (int i = 0; i < size; i++) {
			//primim numere de la 0 la 9, pentru a le transforma in litere +65
			cout << (char)(i + 65) << '|';
			for (int j = 0; j < size; j++) {
				cout << field[i][j] << " ";
				//cout << field_hidden[i][j] << " "; //pentru a vedea unde sunt amplasate minele
			}
			cout << endl;
		}
	}

	//functie pentru a vedea daca am ochit sau nu mina, returneaza t/f
	bool shot(int x, int y) {
		//daca am dat de mina 
		if (field_hidden[x][y]) return false;
		//daca am ochit bine atunci mergem mai departe
		//analizam cate mine sunt in jur fara sa iesim din margini
		int count = 0; //cate mine sunt in jur
		for (int i = x - 1; i <= x + 1 && i < size; i++) {
			for (int j = y - 1; j <= y + 1 && j < size; j++) {
				//daca in jur am gasit mina adaugam la count
				if (i >= 0 && j >= 0) count += field_hidden[i][j];
			}
		}
		//daca am ochit bine in locul vizibil schimbam simbolul * in nr de mine care se afla pe langa 
		field[x][y] = count + 0x30; //+0x30 ca sa=l transforme in simbol nu in smile
		return true;
	}

	void game() {
		clear_field();
		set_mine_count();

		int y;
		char x;
		do {
			system("cls");
			show_field();
			cout << "\n ALEGE TINTA: \n";
			cin >> x >> y;
			x = x - 65;
		} while (shot(x, y));

		cout << "**GAME OVER**" << endl << endl;
	}

};

//CONSTRUCTOR
Game::Game()
{
	const int n = 10;
	this->size = n;
	this->field_hidden = new bool* [n];
	for (int i = 0; i < n; i++)
	{
		this->field_hidden[i] = new bool[n];
	}
	this->field = new char* [n];
	for (int i = 0; i < n; i++)
	{
		this->field[i] = new char[n];
	}
}

Game::Game(int n)
{
	this->size = n;
	this->field_hidden = new bool* [n];
	for (int i = 0; i < n; i++)
	{
		this->field_hidden[i] = new bool[n];
	}
	this->field = new char* [n];
	for (int i = 0; i < n; i++)
	{
		this->field[i] = new char[n];
	}
}

//DESTRUCTOR
Game::~Game()
{
	for (int i = 0; i < size; i++)
	{
		delete[]field[i];
		delete[]field_hidden[i];
	}
	delete[]field;
	delete[]field_hidden;
}



int main() {
	Game minesweeper(10);
	
	char again;
	do {
		minesweeper.game();

		cout << "PLAY AGAIN?" << endl;
		cin >> again;
	} while (again == 'Y');
};


