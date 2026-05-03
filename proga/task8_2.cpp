#include <iostream>
#include <vector>
using namespace std;
int main() {
	setlocale(LC_ALL, "RUS");
	int n, m;
	cout << "Введите количество вершин и рёбер: ";
	cin >> n >> m;
	vector<vector<int>>Gr(n);
	cout << "Введите рёбра:" << endl;
	for (int i = 0; i < m; i++) {
		int x, y;
		cin >> x >> y;
		Gr[x].push_back(y);
		Gr[y].push_back(x);
	}
	// Вводим вершины A и B, между которыми нужно добавить ребро
	int a, b;
	cout << "\nВведите A и B для добавления ребра: ";
	cin >> a >> b;
	//добавляем ребро
	Gr[a].push_back(b);
	Gr[b].push_back(a);
	//результат
	for (int i = 0; i < n; i++) {
		cout << i << ": ";
		for (int j = 0; j < Gr[i].size(); j++) {
			cout << Gr[i][j]<< " ";
		}
		cout << endl;
	}
	return 0;
}