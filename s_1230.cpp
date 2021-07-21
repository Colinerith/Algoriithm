#define MAX_NODE 1000000
#include<iostream>
using namespace std;

struct Node {
	int data;
	Node* prev;
	Node* next;
};

Node node[MAX_NODE];
int nodeCnt;
Node* head;
Node* tail;
int totalNum;

Node* getNode(int data) {
	node[nodeCnt].data = data;
	node[nodeCnt].prev = nullptr;
	node[nodeCnt].next = nullptr;
	return &node[nodeCnt++];
}

void init(int length){
	nodeCnt = 0;
	totalNum = length;
	head = getNode(-1);
	tail = getNode(-1);
	head->next = tail;
	tail->prev = head;

	int a;
	Node* cur = head;

	while (length--) {
		cin >> a;
		cur->next = getNode(a);
		cur = cur->next;
	}
	cur->next = tail;
	tail->prev = cur;
}

void add(){
	int count, data;
	cin >> count;
	totalNum += count;

	Node* cur = tail->prev;

	while (count--) {
		cin >> data;
		cur->next = getNode(data);
		cur = cur->next;
	}
	cur->next = tail;
	tail->prev = cur;
}

void insert(){
	int index, count;
	cin >> index >> count;
	totalNum += count;

	if (index == 0) {
		int a;
		Node* cur = head;
		Node* temp = head->next;

		while (count--) {
			cin >> a;
			cur->next = getNode(a);
			cur = cur->next;
		}
		cur->next = temp;
		temp->prev = cur;

		return;
	}

	Node* cur = head;
	int idx = 1;
	while (cur->next != tail && idx <= index) {
		cur = cur->next;
		idx++;
	}
	Node* temp = cur->next;

	int a;
	while (count--) {
		cin >> a;
		cur->next = getNode(a);
		cur = cur->next;
	}
	cur->next = temp;
	temp->prev = cur;
}

void del(){
	int index, count;
	cin >> index >> count;

	totalNum -= count;

	Node* cur = head;
	int idx = 1;
	while (cur->next != tail && idx <= index) {
		cur = cur->next;
		idx++;
	}
	Node* temp = cur;

	while (count--) {
		cur = cur->next;
	}
	temp->next = cur->next;
}

void printNode() {
	Node* cur = head->next;
	for (int i = 0; i < 10; i++) {
		cout << " " << cur->data;
		cur = cur->next;
	}
	cout << "\n";
}

int main() {
	int test_case;
	for (test_case = 1; test_case <= 10; ++test_case) {
		int length;
		cin >> length;
		init(length);

		int n; // 명령어의 개수
		char c;
		cin >> n;
		while (n--) {
			cin >> c;
			switch (c) {
			case 'I':
				insert(); break;
			case 'D':
				del(); break;
			case 'A':
				add(); break;
			}
		}

		cout << "#" << test_case;
		printNode();
	}
	return 0;
}
