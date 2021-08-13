// hash - 문자열 교집합
#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#define HASH_SIZE (1<<21) // 이걸 18로 하면 시간초과, 21로 하면 성공
#define DIV (HASH_SIZE - 1)
typedef unsigned long long ll;
using namespace std;

int T, test_case, n, m;
void strCpy(char dst[], char src[]) {
	while (*src)
		*dst++ = *src++;
	*dst = 0;
}
bool strCmp(char a[], char b[]) {
	int i = 0;
	for (; a[i]; i++) {
		if (a[i] != b[i])
			return false;
	}
	return a[i] == b[i];
}
struct Node {
	bool exist;
	char key[51];
	Node* next;
	Node* alloc(char k[], Node* n) {
		strCpy(key, k);
		next = n;
		return this;
	}
	bool existCheck(char k[]) { // 'key'와 일치하는 노드가 있는지
		Node* ptr = this;
		while (ptr) {
			if (strCmp(k, ptr->key)) return true;
			ptr = ptr->next;
		}
		return false;
	}
};

int nodeCnt;
Node nodes[100000];
Node hashTable[HASH_SIZE];
void init() {
	nodeCnt = 0;
	for (int i = 0; i < n; i++)
		hashTable[i].next = nullptr;
}
int getKey(char k[]) {
	ll key = 5381;
	for (int i = 0; k[i]; i++)
		key = ((key << 5) + key) + (k[i] - 'a' + 1);
	return (int)(key&DIV);
}
void add(char k[]) {
	int target = getKey(k);
	hashTable[target].next = nodes[nodeCnt++].alloc(k, hashTable[target].next);
}
int check(char k[]) {
	int target = getKey(k);
	return hashTable[target].existCheck(k);
}

int main(int argc, char** argv) {
	scanf("%d", &T);
	for (test_case = 1; test_case <= T; ++test_case) {
		scanf("%d %d", &n, &m);
		init();
		char str[51];
		for (int i = 0; i < n; i++) {
			scanf("%s", str);
			add(str);
		}
		int cnt = 0;
		for (int i = 0; i < m; i++) {
			scanf("%s", str);
			if (check(str)) cnt++; // 충돌이 발생하면 카운트 증가
		}

		printf("#%d %d\n", test_case, cnt);
	}
	return 0;
}
