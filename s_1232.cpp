// tree- 사칙 연산
#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;

int T, test_case, num;

struct TreeNode {
	int num;
	int left;
	int right;
} treeNode[1001];

int traverse(int n) {
	if (treeNode[n].num == -1)
		return traverse(treeNode[n].left) + traverse(treeNode[n].right);
	else if (treeNode[n].num == -2)
		return traverse(treeNode[n].left) - traverse(treeNode[n].right);
	else if (treeNode[n].num == -3)
		return traverse(treeNode[n].left) * traverse(treeNode[n].right);
	else if (treeNode[n].num == -4)
		return traverse(treeNode[n].left) / traverse(treeNode[n].right);
	else return treeNode[n].num;
}
int main(int argc, char** argv) {
	ios::sync_with_stdio(false); cin.tie(NULL);
	freopen("input (7).txt", "r", stdin);
	T = 10;
	for (test_case = 1; test_case <= T; ++test_case) {
		cin >> num;
		char a;
		cin.get();
		// +: -1, -: -2, *: -3, /: -4, 숫자: 양의 정수
		int l, r, trash, n;
		for (register int i = 1; i <= num; i++) {
			cin >> trash;
			cin >> a;
			n = 0;
			if (a == '+' || a == '-' || a == '*' || a == '/') {
				switch (a) {
				case '+': treeNode[i].num = -1; break;
				case '-': treeNode[i].num = -2; break;
				case '*': treeNode[i].num = -3; break;
				case '/': treeNode[i].num = -4; break;
				}
				cin >> l >> r;
				treeNode[i].left = l;
				treeNode[i].right = r;
			}
			else {
				while (a != '\n') {
					n = n * 10 + (a - '0');
					a = cin.get();
				}
				treeNode[i].num = n;
			}
		}
		cout << "#" << test_case << " " << traverse(1) << "\n";
	}
	return 0;
}
