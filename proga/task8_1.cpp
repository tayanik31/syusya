#include <iostream>
#include<vector>
using namespace std;
vector<vector<int>>Gr;
vector<bool> used;
int main() {
	int n, m; //n-вершины, m - рёбра
	cin >> n >> m;
	vector<vector<int>> Gr(n);
	//считываем все рёбра
	for (int i = 0; i < m; i++) {
		int x, y;
		cin >> x >> y; // ребро из x в y
		Gr[x].push_back(y); // добавляем y в список смежности вершины x
	}
	// Вводим вершину, для которой хотим посчитать смежные
	int v;
	cin >> v;
	cout << Gr[v].size() << endl;
	return 0;
}