#include <iostream>
#include<vector>
using namespace std;
int main() {
	int n, m;
	cin >> n >> m;
	vector<vector<int>>Gr(n);
	for (int i = 0; i < m; i++) {
		int x, y;
		cin >> x>> y;
		Gr[x].push_back(y);
		Gr[y].push_back(x);
	}
	for (int i = 0; i < n; i++) {
		cout << i << ": " << Gr[i].size() << endl;
	}
	return 0;
}