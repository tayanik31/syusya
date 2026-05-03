#include<iostream>
#include<vector>
using namespace std;
vector<vector<int>>Gr;
vector<bool> used;
void dfs(int x) {
	used[x] = true;
	for (int i = 0; i < Gr[x].size(); i++) {
		if (!used[Gr[x][i]]) {
			dfs(Gr[x][i]);
		}
	}
}
int main() {
	setlocale(LC_ALL, "RUS");
	int n, m;
	cin >> n >> m;
	Gr.resize(n);
	for (int i = 0; i < m; i++) {
		int x, y;
		cin >> x >> y;
		Gr[x].push_back(y);
	}
	int st;
	cin >> st; //с какой начинаем
	used.assign(n, false); //заполняет вектор used значением false для всех элементов
	dfs(st);
	//недостижимые
	cout << "Вершины, недостижимые из " << st << ": ";
	bool find = false;
	for (int i = 0; i < n; i++) {
		if (!used[i]) {
			cout << i << " ";
			find = true;
		}
	}
	if (!find) {
		cout << "все вершины достижимы";
	}
	return 0;
}