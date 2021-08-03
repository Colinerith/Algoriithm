// 중위 순회
#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#define MAX_POOL 100
#define MAX_NODE 100
using namespace std;

int T, test_case, num;
char tree[101];

void traverse(int n) {
	cout << tree[n];
}

void inorder(int n) {
	if (n > num)
		return;
	inorder(n * 2);
	traverse(n);
	inorder(n * 2 + 1);
}

int main(int argc, char** argv) {
	ios::sync_with_stdio(false); cin.tie(NULL);
	T = 10;
	for (test_case = 1; test_case <= T; ++test_case) {
		cin >> num;
		char a;
		char numChar;
		cin.get();
		//for (int i = 1; i <= num; i++)
		//	tree[i] = 0;

		// 어차피 완전이진트리니까 자식 정보 저장할 필요 없음
		// char만 받으면 된다.
		for (register int i = 1; i <= num; i++) {
			while (true) {
				a = cin.get();
				if (a == '\n')
					break;
				if (a == ' ' || (a >= '0' && a <= '9'))
					continue;
				numChar = a;
			}
			tree[i] = numChar;
		}

		cout << "#" << test_case << " ";
		inorder(1);
		cout << "\n";
	}
	return 0;
}
