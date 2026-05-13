#include <iostream>
#include <fstream>
#include <string>
using namespace std;
// Структура сотрудника
struct Sotrudnik {
    string familiya;
    string dolzhnost;
    int den;
    int mes;
    int god;
    int stazh;
    int zarp;
};
struct Yacheyka {
    Sotrudnik data;
    bool zanyato;   // занято ли место
    bool udaleno;   // помечено как удалённое
};
struct Hashtable {
    Yacheyka* tablica;
    int m;          // размер таблицы
    int kolvo;      // количество элементов
    // Инициализация
    void init(int razmer) {
        m = razmer;
        tablica = new Yacheyka[m];
        for (int i = 0; i < m; i++) {
            tablica[i].zanyato = false;
            tablica[i].udaleno = false;
        }
        kolvo = 0;
    }
    // Хэш-функция: метод умножения по стажу
    int hash(int stazh) {
        double A = 0.618034;  // золотое сечение
        double proizvedenie = stazh * A;
        double drobnaya = proizvedenie - (int)proizvedenie;  // дробная часть
        return (int)(drobnaya * m);
    }
    // Линейное хэширование: поиск свободной ячейки
    int naitiSvobodnuyu(int stazh) {
        int index = hash(stazh);
        int popytok = 0;
        while (popytok < m) {
            if (!tablica[index].zanyato) {
                return index;
            }
            index = (index + 1) % m;
            popytok++;
        }
        return -1;  // таблица переполнена
    }
    // Поиск индекса по стажу
    int naitiIndex(int stazh) {
        int index = hash(stazh);
        int popytok = 0;
        while (popytok < m) {
            if (!tablica[index].zanyato && !tablica[index].udaleno) {
                return -1;  // не нашли
            }
            if (tablica[index].zanyato && tablica[index].data.stazh == stazh) {
                return index;  // нашли
            }
            index = (index + 1) % m;
            popytok++;
        }
        return -1;
    }
    // Добавление сотрудника
    void dobavit(Sotrudnik s) {
        if (kolvo >= m) {
            cout << "Таблица переполнена!\n";
            return;
        }

        int index = naitiSvobodnuyu(s.stazh);
        if (index == -1) {
            cout << "Нет свободного места!\n";
            return;
        }
        tablica[index].data = s;
        tablica[index].zanyato = true;
        tablica[index].udaleno = false;
        kolvo++;

        cout << "Добавлен: " << s.familiya << " (стаж " << s.stazh << ") в ячейку " << index << endl;
    }
    // Загрузка из файла
    void zagruzitIzFile(string filename) {
        ifstream file(filename.c_str());

        if (!file.is_open()) {
            cout << "Не могу открыть файл " << filename << endl;
            return;
        }

        Sotrudnik s;
        while (file >> s.familiya >> s.dolzhnost >> s.den >> s.mes >> s.god >> s.stazh >> s.zarp) {
            dobavit(s);
        }

        file.close();
        cout << "\nФайл загружен!\n";
    }
    // Поиск и вывод данных
    void poisk(int stazh) {
        int index = naitiIndex(stazh);

        if (index != -1 && tablica[index].zanyato) {
            cout << "\n=== НАЙДЕН ===\n";
            cout << "Фамилия: " << tablica[index].data.familiya << endl;
            cout << "Должность: " << tablica[index].data.dolzhnost << endl;
            cout << "Дата рождения: " << tablica[index].data.den << "." << tablica[index].data.mes << "." << tablica[index].data.god << endl;
            cout << "Стаж: " << tablica[index].data.stazh << " лет" << endl;
            cout << "Зарплата: " << tablica[index].data.zarp << endl;
            cout << "Ячейка: " << index << endl;
        }
        else {
            cout << "Сотрудник со стажем " << stazh << " лет не найден.\n";
        }
    }
    // Удаление сотрудника
    void udalit(int stazh) {
        int index = naitiIndex(stazh);

        if (index != -1 && tablica[index].zanyato) {
            tablica[index].zanyato = false;
            tablica[index].udaleno = true;
            kolvo--;
            cout << "Удалён сотрудник со стажем " << stazh << " лет (ячейка " << index << ")" << endl;
        }
        else {
            cout << "Сотрудник со стажем " << stazh << " лет не найден.\n";
        }
    }
    // Удаление сотрудника
    void udalit(int stazh) {
        int index = naitiIndex(stazh);

        if (index != -1 && tablica[index].zanyato) {
            tablica[index].zanyato = false;
            tablica[index].udaleno = true;
            kolvo--;
            cout << "Удалён сотрудник со стажем " << stazh << " лет (ячейка " << index << ")" << endl;
        }
        else {
            cout << "Сотрудник со стажем " << stazh << " лет не найден.\n";
        }
    }
    // Вывод всей таблицы
    void pokazat() {
        cout << "Размер: " << m << " | Элементов: " << kolvo << "\n";
        for (int i = 0; i < m; i++) {
            cout << i << ": ";
            if (!tablica[i].zanyato && !tablica[i].udaleno) {
                cout << "NULL";
            }
            else if (!tablica[i].zanyato && tablica[i].udaleno) {
                cout << "[УДАЛЁН]";
            }
            else {
                cout << tablica[i].data.familiya << "(стаж " << tablica[i].data.stazh << ")";
            }
            cout << endl;
        }
    }
};
int main() {
    Hashtable ht;
    ht.init(23);  // размер таблицы 23 (больше 20)
    cout << "Хэш-функция: метод умножения по стажу\n";
    cout << "Метод: линейное хэширование\n\n";

    // Загружаем из файла
    ht.zagruzitIzFile("sotrudniki.txt");

    // Показываем таблицу
    ht.pokazat();

    // Поиск
    int poiskStazh;
    cout << "Введите стаж для поиска: ";
    cin >> poiskStazh;
    ht.poisk(poiskStazh);

    // Удаление
    int udalenieStazh;
    cout << "Введите стаж для удаления: ";
    cin >> udalenieStazh;
    ht.udalit(udalenieStazh);

    // Показываем таблицу после удаления
    ht.pokazat();
    return 0;
}