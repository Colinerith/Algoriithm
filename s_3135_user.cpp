int nodeCnt;
struct Trie {
	int childCnt;
	Trie* children[26];
	void add(int buffer_size, char* buf) {
		if (buffer_size == 0) { // 마지막 글자
			childCnt++;
		}
		else {
			if (children[*buf - 'a'] == nullptr)
				children[*buf - 'a'] = alloc();
			children[*buf - 'a']->add(buffer_size - 1, buf + 1);
			childCnt++;
		}
	}
	int count(int buffer_size, char* buf) {
		if (buffer_size == 0) { // 끝자리 검사 중
			if (childCnt == 0) return 1; //끝자리까지 완전 일치
			return childCnt;
		}
		if (children[*buf - 'a'] == nullptr)
			return 0;
		return children[*buf-'a']->count(buffer_size - 1, buf + 1);
	}
	void clear() {
		for (int i = 0; i < 26; i++) {
			children[i] = nullptr;
		}
	}
	Trie* alloc();

} nodes[1000000];

Trie* Trie::alloc() {
	Trie* t = &nodes[nodeCnt++];
	t->clear();
	t->childCnt = 0;
	return t;
}

Trie* root;
void init(void) {
	nodeCnt = 0;
	root = nodes[nodeCnt++].alloc();
}

void insert(int buffer_size, char *buf) {
	root->add(buffer_size, buf);
}

int query(int buffer_size, char *buf) {
	return root->count(buffer_size, buf);
}
