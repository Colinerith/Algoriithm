#include<iostream>
using namespace std;

int T, test_case, num;
bool flag;

struct TreeNode {
	int num;
	int left;
	int right;
} treeNode[1001];

int check(int i) {
	return (treeNode[i].left == 0 || treeNode[i].right == 0);
}

void traverse(int n) {
	if (treeNode[n].num == -1 || treeNode[n].num == -2 ||
		treeNode[n].num == -3 || treeNode[n].num == -4) {
		if (check(n)) {
			flag = false;
			return;
		}
		traverse(treeNode[n].left);
		traverse(treeNode[n].right);
	}
	else {
		if (treeNode[n].left != 0 || treeNode[n].right != 0)
			flag = false;
	}
	//else treeNode[n].num;
}
int main(int argc, char** argv) {
	ios::sync_with_stdio(false); cin.tie(NULL);
	T = 10;
	for (test_case = 1; test_case <= T; ++test_case) {
		flag = true;
		cin >> num;
		char a;
		cin.get();

		for (int i = 1; i <= num; i++) {
			treeNode[i].left = 0;
			treeNode[i].right = 0;
		}
		// +: -1, -: -2, *: -3, /: -4, 숫자: 양의 정수
		int l, r, trash, n;
		for (register int i = 1; i <= num; i++) {
			cin >> trash;
			cin.get();
			a = cin.get();
			if (a == '+' || a == '-' || a == '*' || a == '/') {
				switch (a) {
				case '+': treeNode[i].num = -1; break;
				case '-': treeNode[i].num = -2; break;
				case '*': treeNode[i].num = -3; break;
				case '/': treeNode[i].num = -4; break;
				}
				a = cin.get();
			}
			else {
				n = 0;
				while (a != '\n' && a != ' ') {
					n = n * 10 + (a - '0');
					a = cin.get();
				}
				treeNode[i].num = n;
			}
			if (a == '\n')
				continue;
			// 공백이면
			l = r = 0;
			a = cin.get();
			while (a != ' ' && a != '\n') {
				l = l * 10 + (a - '0');
				a = cin.get();
			}
			treeNode[i].left = l;
			if (a == '\n')
				continue;
			a = cin.get();
			while (a != '\n') {
				r = r * 10 + (a - '0');
				a = cin.get();
			}
			treeNode[i].right = r;
		}
		traverse(1);
		cout << "#" << test_case << " " << flag << "\n";
	}
	return 0;
}
