int map[10][10];
bool visited[10][10];

class Node{
public:
	int length;
	int x;
	int y;
	Node* next;
	Node(){
		this->length = 0;
		next = nullptr;
	}
};

class Queue{
public:
	int size;
	Node* rear, *front;
	Queue(){
		this->size = 0;
		rear = front = nullptr;
	}

	void push(int x, int y, int length){
		Node* newNode = new Node;
		newNode->length = length;
		newNode->x = x;
		newNode->y = y;
		newNode->next = nullptr;

		if (empty())
			rear = front = newNode;
		else{
			rear->next = newNode;
			rear = newNode;
		}
		this->size++;
	}

	Node pop(){
		if (!empty()) {
			Node tempFrontData = *front;
			Node* tempFrontNode = front;
			front = front->next;
			this->size--;
			delete tempFrontNode;
			return tempFrontData;
		}
	}

	bool empty(){
		if (this->size == 0) return true;
		return false;
	}

	int Size(){
		return this->size;
	}

	Node top(){
		return *front;
	}
};

void bfs_init(int N, int _map[10][10]) {
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			map[i][j] = _map[i][j];
		}
	}
}

int bfs(int x1, int y1, int x2, int y2) {
	for (int i = 0; i < 10; i++) {
		for(int j=0;j<10;j++)
			visited[i][j] = false;
	}
	Queue q;
	q.push(x1 - 1, y1 - 1, 0);
	visited[y1 - 1][x1 - 1] = true;
	while (!q.empty()) {
		int x = q.top().x;
		int y = q.top().y;
		int len = q.top().length;
		q.pop();
		visited[y][x] = true;
		if (x == (x2 - 1) && y == (y2 - 1)) {
			return len;
		}

		if (y - 1 >= 0 && !visited[y - 1][x] && map[y - 1][x] == 0) //상
			q.push(x, y - 1, len + 1);
		if (y + 1 < 10 && !visited[y + 1][x] && map[y + 1][x] == 0) //하
			q.push(x, y + 1, len + 1);
		if (x - 1 >= 0 && !visited[y][x - 1] && map[y][x - 1] == 0)//좌
			q.push(x - 1, y, len + 1);
		if (x + 1 < 10 && !visited[y][x + 1] && map[y][x + 1] == 0)//우
			q.push(x + 1, y, len + 1);
	}
	return -1;
}
