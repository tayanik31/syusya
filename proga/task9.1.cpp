#include <iostream>
#include <fstream>
#include <string>
using namespace std;
struct Sotrudnik {
	string familiya;
	string dolzhnost;
	int den;
	int mes;
	int god;
	int stazh;
	int zarp;
	Sotrudnik* next;
};
struct Hashtable {
	Sotrudnik* korobki[13];
	void init() {
		for (int i = 0; i < 13; i++) {
			korobki[i] = NULL;
		}
	}
	int hash(int zarp) {
		return zarp % 13;
	}
	void add(Sotrudnik noviy) {
		int index = hash(noviy.zarp);
		Sotrudnik* noviynode = new Sotrudnik;
		*noviynode = noviy; //копируем все поля
		noviynode->next = korobki[index]; //новый указывает на старого
		korobki[index] = noviynode; //новый становится первым
		cout << "Добавлен: " << noviy.familiya << "(з/п" << noviy.zarp << ") в коробку " << index << endl;
	}
	void loadfromfile(string filename) {
		ifstream file(filename.c_str());
		if (!file.is_open()) {
			cout << "Невозможно открыть файл " << filename << endl;
			return;
		}
		Sotrudnik s;
		while (file >> s.familiya >> s.dolzhnost >> s.den >> s.mes >> s.god >> s.stazh >> s.zarp) {
			add(s);
		}
		file.close();
		cout << "\nфайл загружен\n";
	}
	void find(int zarp) {
		int index = hash(zarp);
		Sotrudnik* tekushiy = korobki[index];
		while (tekushiy != NULL) {
			if (tekushiy->zarp == zarp) {
				cout << "Фамилия: " << tekushiy->familiya << endl;
				cout << "Должность: " << tekushiy->dolzhnost << endl;
				cout << "Дата рождения: " << tekushiy->den << "." << tekushiy->mes << "." << tekushiy->god << endl;
				cout << "Стаж: " << tekushiy->stazh << " лет" << endl;
				cout << "Зарплата: " << tekushiy->zarp << endl;
				return;
			}
			tekushiy = tekushiy->next;
		}
		cout << "Сотрудник с зарплатой " << zarp << " не найден.\n";
	}
	void remove(int zarp) {
		int index = hash(zarp);
		Sotrudnik* tekushiy = korobki[index];
		Sotrudnik* predidushiy = NULL;
		int udaleno = 0;
		while (tekushiy != NULL) {
			if (tekushiy->zarp == zarp) {
				if (predidushiy == NULL) {
					korobki[index] = tekushiy->next;
				}
				else {
					predidushiy->next = tekushiy->next;
				}
				Sotrudnik* udalyaemiy = tekushiy;
				tekushiy = tekushiy->next;
				delete udalyaemiy;
				udaleno++;
			}
			else {
				predidushiy = tekushiy;
				tekushiy = tekushiy->next;
			}
		}
		if (udaleno > 0) {
			cout << "Удалено " << udaleno << " сотрудников с зарплатой " << zarp << endl;
		}
		else {
			cout << "Сотрудник с зарплатой " << zarp << " не найден.\n";
		}
	}
	void show() {
		cout << "\nХЭШ-ТАБЛИЦА\n";
		for (int i = 0; i < 13; i++) {
			cout << i << ": ";
			Sotrudnik* tekushiy = korobki[i];
			if (tekushiy == NULL) {
				cout << "пусто";
			}
			else {
				while (tekushiy != NULL) {
					cout << tekushiy->familiya << "(" << tekushiy->zarp << ") ";
					tekushiy = tekushiy->next;
				}
			}
			cout << endl;
		}
	}
};
int main() {
	setlocale(LC_ALL, "RUS");
	Hashtable ht;
	ht.init();
	ht.loadfromfile("sotrudniki.txt");
	ht.show();
	int poisk;
	cout << "Введите зарплату для поиска: ";
	cin >> poisk;
	ht.find(poisk);
	int udalenie;
	cout << "Введите зарплату для удаления: ";
	cin >> udalenie;
	ht.remove(udalenie);
	ht.show();

	return 0;
}