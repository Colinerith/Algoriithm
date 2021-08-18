int length, nodeCnt;
char* str;

int strHash(int i) {
	int key = 0;
	for (int j = i; j < i + 2; j++)
		key = (key + (str[j] - 'a')) * 26;
	key = (key + (str[i + 2] - 'a'));
	return key;
}
struct Node {
	Node* next;
	Node* prev;
	int idx;
	Node* alloc(int i) {
		idx = i;
		next = nullptr;
		prev = nullptr;
		return this;
	}
	void add(int i);
	void delIdx(int i);
	int del(char string_B[]);
} nodes[1000000], indexes[200000];

void Node::add(int i) {
	Node* newNode = nodes[nodeCnt++].alloc(i);
	if (next == nullptr)
		next = newNode;
	else {
		Node* cur = next;
		if (i < cur->idx) {
			newNode->next = cur;
			cur->prev = newNode;
			this->next = newNode;
			return;
		}
		while (cur->next) {
			if (cur->next->idx == i) return; // 이미 있으면 안넣기
			else if (cur->next->idx > i) break;
			cur = cur->next;
		}
		if (cur->next == nullptr) {
			newNode->prev = cur;
			cur->next = newNode;
		}
		else {
			newNode->next = cur->next;
			newNode->prev = cur;
			cur->next = newNode;
			newNode->next->prev = newNode;
		}
	}
}
void Node::delIdx(int i) {
	Node* cur = next;
	while (cur) {
		if (cur->idx == i) {
			if (cur->prev) { // prev 있으면
				cur->prev->next = cur->next;
				if (cur->next) // next 있으면
					cur->next->prev = cur->prev;
			}
			else if (cur->next) { // next 있으면
				cur->next->prev = nullptr;
				this->next = cur->next;
			}
			else this->next = nullptr;
			return;
		}
		cur = cur->next;
	}
}
int Node::del(char string_B[]) {
	int delCnt = 0;
	Node* cur = next;
	while (cur) {
		int i = cur->idx;
		if (i - 1 >= 0) {
			indexes[strHash(i - 1)].delIdx(i - 1);
			if (i - 2 >= 0)
				indexes[strHash(i - 2)].delIdx(i - 2);
		}
		if (i + 1 <= length - 3) {
			indexes[strHash(i + 1)].delIdx(i + 1);
			if (i + 2 <= length - 3)
				indexes[strHash(i + 2)].delIdx(i + 2);
		}

		delCnt++;
		str[i] = string_B[0]; str[i + 1] = string_B[1]; str[i + 2] = string_B[2];
		if (cur->prev) { // prev 있으면
			cur->prev->next = cur->next;
			if (cur->next) // next 있으면
				cur->next->prev = cur->prev;
		}
		else if (cur->next) { // next 있으면
			cur->next->prev = nullptr;
			this->next = cur->next;
		}
		else this->next = nullptr;
		indexes[strHash(i)].add(i);

		if (i - 1 >= 0) {
			indexes[strHash(i - 1)].add(i - 1);
			if (i - 2 >= 0)
				indexes[strHash(i - 2)].add(i - 2);
		}
		if (i + 1 <= length - 3) {
			indexes[strHash(i + 1)].add(i + 1);
			if (i + 2 <= length - 3)
				indexes[strHash(i + 2)].add(i + 2);
		}
		while(cur->next && cur->next->idx < cur->idx + 3)
			cur = cur->next;
		cur = cur->next;
	}
	return delCnt;
}

void init(int N, char init_string[]) {
	length = N;
	str = init_string;
	nodeCnt = 0;
	for (int i = 0; i < 18000; i++)
		indexes[i].next = nullptr;
	//indexing
	for (int i = 0; i <= length - 3; i++) {
		int k = strHash(i);
		indexes[k].add(i);
	}
}
int change(char string_A[], char string_B[]) {
	if (string_A[0] == 'a' && string_A[1] == 'b' && string_A[2] == 'b' &&
		string_B[0] == 'a' && string_B[1] == 'b' && string_B[2] == 'a')
		int a = 2;

	int key = 0;
	for (int j = 0; j < 2; j++)
		key = (key + (string_A[j] - 'a')) * 26;
	key = (key + (string_A[2] - 'a'));

	return indexes[key].del(string_B);
}
void result(char ret[]) {
	for (int i = 0; i < length; i++)
		ret[i] = str[i];
}
