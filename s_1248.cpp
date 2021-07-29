#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
using namespace std;

struct Node {
	int data;
	Node* left;
	Node* right;
	Node* parent;
	Node* alloc(int i) {
		data = i;
		left = nullptr;
		right = nullptr;
		parent = nullptr;
		return this;
	}
};

int T, test_case;
Node* vertex[10001];
Node nodes[10001];
int cnt;

int nearV;
int check(int v, int v1, int v2, int cnt) { // v의 자손들 중 v1, v2가 모두 있는지
	//cnt = v1과 v2중 몇개 찾았는지
	int cntTemp = cnt;
	if (vertex[v]->left != nullptr) {
		if (vertex[v]->left->data == v1 || vertex[v]->left->data == v2)
			cnt++;
		else
			cnt = check(vertex[v]->left->data, v1, v2, cnt);

		if (vertex[v]->right != nullptr) {
			if(vertex[v]->right->data == v1 || vertex[v]->right->data == v2)
				cnt++;
			else
				cnt += check(vertex[v]->right->data, v1, v2, cntTemp);
		}
	}
	if (cnt == 2 && nearV == 0) {
		nearV = v;
	}
	return cnt;
}

int counting(int v, int cnt) {
	if (vertex[v]->left != nullptr) {
		//cnt++;
		int cntTemp = cnt;
		cnt += counting(vertex[v]->left->data, cnt);
		if (vertex[v]->right != nullptr) {
			//cnt++;
			cnt += counting(vertex[v]->right->data, cntTemp);
		}
	}
	return cnt+1;
}

int main(int argc, char** argv) {
	ios::sync_with_stdio(false); cin.tie(NULL);
	cin >> T;
	for (test_case = 1; test_case <= T; ++test_case) {
		nearV = 0; // 공통조상 중 가장 가까운 정점
		int tSize = 0; // nearV를 루트로 하는 서브 트리의 크기
		cnt = 0;
		int v, e, v1, v2;
		cin >> v >> e >> v1 >> v2;
		for (int i = 1; i <= v; i++) {
			vertex[i] = nodes[cnt++].alloc(i);
			//nodes[u
		}

		int a, b;
		for (int i = 0; i < e; i++) {
			cin >> a >> b;
			if (vertex[a]->left == nullptr)
				vertex[a]->left = vertex[b];
			else
				vertex[a]->right = vertex[b];
			vertex[b]->parent = vertex[a];
		}

		check(1, v1, v2, 0); // 루트인 1부터 시작
		tSize = counting(nearV, 0);

		printf("#%d %d %d\n", test_case, nearV, tSize);
	}
	return 0;
}
