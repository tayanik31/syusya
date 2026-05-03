#include <iostream>
#include<vector>
#include <queue>
using namespace std;
vector<vector<int>>Gr;
vector<bool> used;
void bfs(int x) {
	queue<int>q;
	q.push(x);
	used[x] = true;
	while (!q.empty()) {
		int cur = q.front();
		q.pop();
		for (int i = 0; i < Gr[cur].size(); i++) {
			int sosed = Gr[cur][i];
			if (!used[sosed]) {
				used[sosed] = true;
				q.push(sosed);
			}
		}
	}
}
int main() {
	setlocale(LC_ALL, "RUS");
	int n, m;
	cout << "Введите количество вершин и рёбер: ";
	cin >> n >> m;
	Gr.resize(n);
	cout << "Введите рёбра (ориентированный граф):" << endl;
	for (int i = 0; i < m; i++) {
		int x, y;
		cin >> x >> y;
		Gr[x].push_back(y);   
	}
	cout << "\nВершины, из которых можно попасть во все остальные: ";
	for (int start = 0; start < n; start++) {
		used.assign(n, false);
		bfs(start);
		bool allReachable = true;
		for (int i = 0; i < n; i++) {
			if (!used[i]) {
				allReachable = false;
				break;
			}
		}
		if (allReachable) {
			cout << start << " ";
		}
	}
	cout << endl;
	return 0;
}
