#define bucketNum 1001 //bucket의 수
#define bucketSize 100 //한 bucket에 들어가는 track 수
#define bufferSize 100000

const int MAX = 100000;
//int bucketNum; // bucket의 수. 2 <= bucketNum <= 1000
int trackSize;
int head;

struct Node {
	int val;
	Node *prev;
	Node *next;

	Node *alloc(int _val) {
		val = _val;
		prev = nullptr;
		next = nullptr;
		return this;
	}
} buf[bufferSize * 2], *bucket[bucketNum];	// buf: 정적 할당을 위한 buffer, bucket: linked list의 head.

int cnt;
int bucketCnt[bucketNum];	// bucketCnt: 각 bucket에 담긴 숫자의 개수를 담음.
Node* tails[bucketNum]; // 각 bucket의 tail 포인터를 담음
Node* fcfsHead; // 들어온 순서대로 저장하는 연결리스트의 head
Node* fcfsTail;
bool direction; // look의 진행 방향. true:좌, false:우

void init(int track_size, int _head) {
	trackSize = track_size;
	head = _head;
	direction = true;

	fcfsHead = nullptr;
	fcfsTail = nullptr;
	cnt = 0;
	for (int i = 0; i <= track_size / bucketSize; i++) {
		bucketCnt[i] = 0;
		bucket[i] = nullptr;
	}
}

void request(int track) {
	Node* newTrack = buf[cnt++].alloc(track);
	//fcfs 리스트에 붙이기. 얘는 prev 없어도 됨
	if (fcfsHead == nullptr) {
		fcfsHead = newTrack;
		fcfsTail = newTrack;
		fcfsHead->next = fcfsTail; // 자신을 next로 만들 수 있나?
	}
	else {
		fcfsTail->next = newTrack;
		fcfsTail = newTrack;
	}

	//bucket에 넣기. prev 필요
	Node* newTrack2 = buf[cnt++].alloc(track);

	int idx = track / bucketSize;
	bucketCnt[idx] += 1;

	Node* cur = bucket[idx];
	if (cur == nullptr) {
		bucket[idx] = newTrack2; // head
		tails[idx] = newTrack2; // tail
		//bucketCnt[idx] += 1;
	}
	else {
		if (track < cur->val) {
			newTrack2->next = cur;
			cur->prev = newTrack2;
			bucket[idx] = newTrack2; // head 업데이트
			return;
		}
		while (cur->next != nullptr) {
			if (track < cur->next->val) {
				newTrack2->next = cur->next;
				cur->next = newTrack2;
				newTrack2->prev = cur;
				newTrack2->next->prev = newTrack2;
				return;
			}
			cur = cur->next;
		}
		// if cur->next == nullptr
		newTrack2->prev = tails[idx];
		tails[idx]->next = newTrack2;
		tails[idx] = newTrack2;
	}
}


void removefcfs(int val) {
	// fcfsList에서 삭제. tail도 고려할 것
	Node* cur = fcfsHead;
	if (cur->val == val) { // head 삭제
		if (fcfsHead == fcfsTail) {
			fcfsHead = nullptr;
			fcfsTail = nullptr;
			return;
		}
		fcfsHead = fcfsHead->next;
	}
	else {
		while (cur->next != nullptr) {
			if (cur->next->val == val) {
				if (cur->next == fcfsTail) { //tail이면
					fcfsTail = cur;
				}
				cur->next = cur->next->next;
				break;
			}
			cur = cur->next;
		}
	}
}

//bucket에서 삭제
void removeBucket(int idx, Node* cur) {
	bucketCnt[idx]--;
	// cur가 head일 때
	if (cur == bucket[idx]) {
		// cur가 head이자 tail일 때
		if (cur == tails[idx]) {
			bucket[idx] = nullptr;
			tails[idx] = nullptr;
			return;
		}
		bucket[idx] = bucket[idx]->next;
		bucket[idx]->prev = nullptr;
	}
	// cur가 tail일 때 (head는 아닌)
	else if (cur == tails[idx]) {
		tails[idx] = tails[idx]->prev;
		tails[idx]->next = nullptr;
	}
	else { //head도 tail도 아님
		cur->prev->next = cur->next;
		cur->next->prev = cur->prev;
	}
}

int fcfs() { // 요청 순서대로 처리
	int track_no = fcfsHead->val;
	removefcfs(track_no);

	int idx = track_no / bucketSize;
	Node* cur = bucket[idx];
	while (cur != nullptr) {
		if (cur->val == track_no) {
			removeBucket(idx, cur);
			break;
		}
		cur = cur->next;
	}

	head = track_no;
	return track_no;
}

//현재 Head 위치를 기준으로 탐색 거리가 가장 짧은 요청을 먼저 처리.
//가능한 Track이 2개인 경우 좌측(번호가 작은) track을 먼저 처리.
int sstf() {
	int track_no = -1;	// TO DO : Need to be changed
	int leftDistance = 100000;
	int rightDistance = 100000;
	Node* leftTrack = nullptr;
	Node* rightTrack = nullptr;
	int leftidx, rightidx;

	int idx = head / bucketSize;
	// 왼쪽 거리 (같은경우도 포함. 없는 경우도 고려)
	// head값이 있는 버킷이 비어있거나 첫째 값보다 작음
	if (bucket[idx] == nullptr || head < bucket[idx]->val) {
		while (idx != 0 && bucketCnt[idx - 1] == 0) {
			idx--;
		}
		if (idx != 0) {
			// (값이 있는) 이전 버킷의 마지막 값과의 거리
			idx--;
			leftDistance = head - tails[idx]->val;
			leftTrack = tails[idx];
			leftidx = idx;
		}
	}
	else { // 버킷이 비어있지 않고, head값 >= 첫째->val
		if (head == bucket[idx]->val) {
			leftDistance = 0;
			leftTrack = bucket[idx];
			leftidx = idx;
		}
		else {
			Node* cur = bucket[idx];
			while ((cur->next != nullptr) && (head > cur->next->val)) {
				cur = cur->next;
			}
			leftDistance = head - cur->val;
			leftTrack = cur;
			leftidx = idx;
		}
	}

	// 오른쪽 거리
	// head값이 있는 버킷이 비어있거나 마지막 값보다 큼
	if (bucket[idx] == nullptr || head > tails[idx]->val) {
		while (idx != (trackSize / bucketSize) && bucketCnt[idx + 1] == 0) {
			idx++;
		}
		if (idx != (trackSize / bucketSize)) {
			// (값이 있는) 이후 버킷의 첫 번째 값과의 거리
			idx++;
			rightDistance = bucket[idx]->val - head;
			rightTrack = bucket[idx];
			rightidx = idx;
		}
	}
	else { // 버킷이 비어있지 않고, head값 <= 마지막->val
		if (head == tails[idx]->val) {
			rightDistance = 0;
			rightTrack = tails[idx];
			rightidx = idx;
		}
		else {
			if (bucket[idx] == tails[idx]) { // 값이 하나만 있었다면
				rightDistance = bucket[idx]->val - head;
				rightTrack = bucket[idx];
				rightidx = idx;
			}
			else {
				Node* cur = bucket[idx];
				while ((cur->next != nullptr) && (head > cur->next->val)) {
					cur = cur->next;
				}
				rightDistance = cur->next->val - head;
				rightTrack = cur->next;
				rightidx = idx;
			}
		}
	}

	if (leftDistance <= rightDistance) {
		track_no = leftTrack->val;
		removeBucket(leftidx, leftTrack);
	}
	else {
		track_no = rightTrack->val;
		removeBucket(rightidx, rightTrack);
	}

	head = track_no;
	removefcfs(track_no);
	return track_no;
}

/* Head 의 진행방향 중 가장 짧은 거리의 요청을 먼저 처리.
  현재 진행방향에서 더 이상 처리할 것이 없는 경우 방향을 반대로 전환.
  초기 진행방향은 좌측 방향. (track 번호가 작아지는 방향) */
int look() {
	if (head == 99686)
		int a = 1;
	int track_no = -1;	// TO DO : Need to be changed

	if (direction) { // 좌측
		int idx = head / bucketSize;
		// head값이 있는 버킷이 비어있음
		if (bucket[idx] == nullptr) {
			while (idx != 0 && bucketCnt[idx - 1] == 0) {
				idx--;
			}
			if (idx == 0) { // head 위치의 왼쪽 버킷이 다 비었으면
				direction = !direction; // 방향 바꾸고 오른쪽 탐색					
				idx = head / bucketSize;
				while (bucketCnt[idx + 1] == 0) {
					idx++;
				}
				idx++;
				track_no = bucket[idx]->val;
				removeBucket(idx, bucket[idx]); //해당 버킷의 첫째 삭제
			}
			else {
				// (값이 있는) 이전 버킷의 마지막 값 삭제
				idx--;
				track_no = tails[idx]->val;
				removeBucket(idx, tails[idx]);
			}
		}
		// head값이 버킷의 첫번째 값보다 작음
		else if (head < bucket[idx]->val) {
			while (idx != 0 && bucketCnt[idx - 1] == 0) {
				idx--;
			}
			if (idx == 0) { // head 위치의 왼쪽 버킷이 다 비었으면
				direction = !direction; // 방향 바꾸고 오른쪽 삭제				
				idx = head / bucketSize;
				track_no = bucket[idx]->val;
				removeBucket(idx, bucket[idx]); //해당 버킷의 첫째 삭제
			}
			else {
				// (값이 있는) 이전 버킷의 마지막 값 삭제
				idx--;
				track_no = tails[idx]->val;
				removeBucket(idx, tails[idx]);
			}
		}
		else { // 버킷이 비어있지 않고, head값 >= 첫째->val
			if (head == bucket[idx]->val) {
				track_no = bucket[idx]->val;
				removeBucket(idx, bucket[idx]);
			}
			else {
				Node* cur = bucket[idx];
				while ((cur->next != nullptr) && (head > cur->next->val)) {
					cur = cur->next;
				}
				//cur 삭제
				track_no = cur->val;
				removeBucket(idx, cur);
			}
		}
	}
	else { // 우측
		int idx = head / bucketSize;

		if (bucket[idx] == nullptr) { // head값이 있는 버킷이 비어있음
			while (idx != (trackSize / bucketSize) && bucketCnt[idx] == 0) { // 오른쪽 탐색
				idx++;
			}
			if (idx == (trackSize / bucketSize)) { // head 위치의 오른쪽 버킷이 다 비었으면
				direction = !direction; // 방향 바꾸고 왼쪽 탐색					
				idx = head / bucketSize;
				while (bucketCnt[idx - 1] == 0) {
					idx--;
				}
				idx--;
				track_no = tails[idx]->val;
				removeBucket(idx, tails[idx]); //해당 버킷의 마지막 삭제
			}
			else {
				// (값이 있는) 이후 버킷의 첫번째 값 삭제
				track_no = bucket[idx]->val;
				removeBucket(idx, bucket[idx]);
			}
		}
		// head값이 버킷의 마지막 값보다 큼
		else if (head > tails[idx]->val) {
			while (bucketCnt[idx + 1] == 0 && idx != trackSize / bucketSize) {
				idx++;
			}
			if (idx == trackSize / bucketSize) { // head 위치의 오른쪽 버킷이 다 비었으면
				direction = !direction; // 방향 바꾸고 왼쪽 삭제				
				idx = head / bucketSize;
				track_no = tails[idx]->val;
				removeBucket(idx, tails[idx]); //해당 버킷의 마지막 삭제
			}
			else {
				// (값이 있는) 이후 버킷의 첫 번째 값 삭제
				track_no = bucket[idx + 1]->val;
				removeBucket(idx + 1, bucket[idx + 1]);
			}
		}
		else { // 버킷이 비어있지 않고, head값 <= 마지막->val
			if (head <= bucket[idx]->val) {
				track_no = bucket[idx]->val;
				removeBucket(idx, bucket[idx]);
			}
			else {
				if (bucket[idx] == tails[idx]) { // 값이 하나만 있었다면
					track_no = bucket[idx]->val;
					removeBucket(idx, bucket[idx]);
				}
				else {
					Node* cur = bucket[idx];
					while ((cur->next != nullptr) && (head > cur->next->val)) {
						cur = cur->next;
					}
					//cur->next 삭제
					track_no = cur->next->val;
					removeBucket(idx, cur->next);
				}
			}
		}
	}

	head = track_no;
	removefcfs(track_no);
	return track_no;
}

/* Head의 진행방향 중 가장 짧은 거리의 요청을 먼저 처리.
   LOOK과의 차이점은 진행방향이 좌측으로 고정이고,
   더 이상 처리할 것이 없는 경우 Head 가 우측 끝으로 돌아가서
   가장 우측에 있는 track 을 처리한다.*/
int clook() {
	int track_no = -1;	// TO DO : Need to be changed

	int idx = head / bucketSize;
	// head값이 있는 버킷이 비어있거나 첫째 값보다 작음
	if (bucket[idx] == nullptr || head < bucket[idx]->val) {
		while (bucketCnt[idx - 1] == 0 && idx != 0) {
			idx--;
		}
		if (idx == 0) { // head 위치의 왼쪽 버킷이 다 비었으면 우측 끝으로 가서 삭제	
			idx = trackSize / bucketSize; // 가장 마지막 버킷
			while (bucketCnt[idx] == 0) {
				idx--;
			}
			track_no = tails[idx]->val; // 값이 있는 버킷의 tail
			removeBucket(idx, tails[idx]);
		}
		else {
			// (값이 있는) 이전 버킷의 마지막 값 삭제
			idx--;
			track_no = tails[idx]->val;
			removeBucket(idx, tails[idx]);
		}
	}
	else { // 버킷이 비어있지 않고, head값 >= 첫째->val
		if (head == bucket[idx]->val) {
			track_no = bucket[idx]->val;
			removeBucket(idx, bucket[idx]);
		}
		else {
			Node* cur = bucket[idx];
			while ((cur->next != nullptr) && (head > cur->next->val)) {
				cur = cur->next;
			}
			//cur 삭제
			track_no = cur->val;
			removeBucket(idx, cur);
		}
	}

	head = track_no;
	removefcfs(track_no);
	return track_no;
}
