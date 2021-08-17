void mstrcpy(char dst[], const char src[]) {
	int c = 0;
	while ((dst[c] = src[c]) != 0)
		++c;
}

int mstrlen(const char str[]) {
	int ret = 0;
	while (str[ret])
		++ret;
	return ret;
}
//
//int mstrcmp(const char str1[], const char str2[]) {
//	int c = 0;
//	while (str1[c] != 0 && str1[c] == str2[c])
//		++c;
//	return str1[c] - str2[c];
//}
struct Node {
	int time; // 클수록 최근
	int count;
	//bool banned; // banned를 지우니까 통과했다
	char str[20];
	Node* alloc(int t, char* buf) {
		time = t;
		count = 1;
	//	banned = false;
		mstrcpy(str, buf);
		return this;
	}
} nodes[25000];
int nodeCnt;
struct Trie {
	Trie* child[27];
	int idx; //추천 인덱스

	Trie* alloc();
	void add(char* str, char* buf, int t) {
		if (*buf == '\0') {
			if (child[26] == nullptr) { // 없었으면
				child[26] = alloc();
				child[26]->idx = nodeCnt;
				nodes[nodeCnt++].alloc(t, str);
			}
			else if(child[26]->idx != -1) {
				nodes[child[26]->idx].count++;
				nodes[child[26]->idx].time = t;
			}
			if (child[26]->idx != -1) {
				if (nodes[child[26]->idx].count > nodes[idx].count ||
					(nodes[child[26]->idx].count == nodes[idx].count &&
						nodes[child[26]->idx].time > nodes[idx].time)) {
					idx = child[26]->idx;
				}
			}
		}
		else {
			if (child[*buf - 'a'] == nullptr)
				child[*buf - 'a'] = alloc();
			child[*buf - 'a']->add(str, buf + 1, t);

			if (nodes[idx].count < nodes[child[*buf - 'a']->idx].count
				|| (nodes[idx].count == nodes[child[*buf - 'a']->idx].count
					&& nodes[idx].time < nodes[child[*buf - 'a']->idx].time)) {
				idx = child[*buf - 'a']->idx;
			}
		}
	}
	void ban(char* str, char* buf) { // 찾아간 다음 nodes에서 번호로 접근해서 ban
		// 없으면? -> 만들면서 끝까지 들어간다.
		if (*buf == '\0') {
			if (child[26] == nullptr) { // 없었으면
				child[26] = alloc();
				child[26]->idx = -1;
				if (idx == 0)
					idx = -1;
			}
			else {
				nodes[child[26]->idx].count = -100000;
				nodes[child[26]->idx].time = -100000;
				//nodes[child[26]->idx].banned = true;
				child[26]->idx = -1;
				if (idx == 0)
					idx = -1;
				else {
					int maxCnt = 0, maxTime = 0, maxIdx = -1;
					for (int i = 0; i < 27; i++) {
						if (child[i] != nullptr && child[i]->idx != -1) {
							if (nodes[child[i]->idx].count > maxCnt ||
								(nodes[child[i]->idx].count == maxCnt &&
									nodes[child[i]->idx].time > maxTime)) {
								maxIdx = child[i]->idx;
								maxCnt = nodes[child[i]->idx].count;
								maxTime = nodes[child[i]->idx].time;
							}
						}
					}
					idx = maxIdx;
				}
			}
		}
		else {
			if (child[*buf - 'a'] == nullptr)
				child[*buf - 'a'] = alloc();
			child[*buf - 'a']->ban(str, buf + 1);

			// 나올 때 번호 업데이트
			if (idx == 0) { // 원래 비어있었으면
				idx = -1; return;
			}
			int maxCnt = 0, maxTime = 0, maxIdx = -1;
			for (int i = 0; i < 27; i++) {
				if (child[i] != nullptr && child[i]->idx != -1) {
					if (nodes[child[i]->idx].count > maxCnt ||
						(nodes[child[i]->idx].count == maxCnt &&
							nodes[child[i]->idx].time > maxTime)) {
						maxIdx = child[i]->idx;
						maxCnt = nodes[child[i]->idx].count;
						maxTime = nodes[child[i]->idx].time;
					}
				}
			}
			idx = maxIdx;
		}
	}

	void search(char* str, char* buf, char* answer) {
		// 없으면? -> 만들면서 끝까지 들어간다.
		if (*buf == '\0') {
			if (idx == 0 || idx == -1) { // 없거나 밴
				mstrcpy(answer, str);
				return;
			}
			else mstrcpy(answer, nodes[idx].str);
		}
		else {
			if (child[*buf - 'a'] == nullptr) {
				mstrcpy(answer, str);
				return;
			}
			return child[*buf - 'a']->search(str, buf + 1, answer);
		}
	}
} trieNodes[250000];
int trieCnt;

Trie* Trie::alloc() {
	Trie* t = &trieNodes[trieCnt++];
	t->idx = 0;
	for (int i = 0; i < 27; i++)
		t->child[i] = nullptr;
	return t;
}

Trie* root;
int time;
void init() {
	time = 0;
	nodeCnt = 0;
	trieCnt = 0;
	char rootChar[2] = "";
	root = trieNodes[trieCnt++].alloc();
	root->idx = 0;
	nodes[nodeCnt++].alloc(0, rootChar);
}

void inputWord(char mWord[20]) {
	root->add(mWord, mWord, ++time);
}

int recommend(char mUser[20], char mAnswer[20]) {
	root->search(mUser, mUser, mAnswer);
	return mstrlen(mAnswer);
}

void banWord(char mWord[20]) {
	root->ban(mWord, mWord);
}
