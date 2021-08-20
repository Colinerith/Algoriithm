int rLen, cLen, rangeCnt;
int state; // 0:초기상태, 1:최근에 병합되었음, 2:최근 분리되었음, 3:최근 undo

struct Range {
	int firstX;
	int firstY;
	int lastX;
	int lastY;
	int cnt; // 셀이 몇개 병합되어 있는지
	Range* alloc(int x1, int y1, int x2, int y2) {
		firstX = x1;
		firstY = y1;
		lastX = x2;
		lastY = y2;
		cnt = (lastX - firstX + 1)*(lastY - firstY + 1);
		return this;
	}
} ranges[1000000];

int map[1000][1000];
int copyMap[1000][1000];
int undoMap[1000][1000];
Range* group[100000];

void init(int R, int C) {
	rLen = R; cLen = C;
	state = 0;
	rangeCnt = 1;
	for (int i = 1; i <= rLen; i++) {
		for (int j = 1; j <= cLen; j++) {
			copyMap[i][j] = 0;
			undoMap[i][j] = 0;
			map[i][j] = 0;
		}
	}
}

void getRect(int r, int c, int rect[]) { // (r,c) 셀의 영역 정보를 rect에 저장
	if (map[r][c] == 0) {
		rect[0] = r; rect[1] = c; rect[2] = r; rect[3] = c;
	}
	else {
		Range* rr = group[map[r][c]];
		rect[0] = rr->firstX; rect[1] = rr->firstY;
		rect[2] = rr->lastX; rect[3] = rr->lastY;
	}
}

int x1, x2, y1, y2;
struct xy {
	int x;
	int y;
};

int mergeCells(int cnt, int rs[], int cs[], int rect[]) {
	xy topLeft{ 1001, 1001 }, topRight{ 1001, -1 },
		downLeft{ -1, 1001 }, downRight{ -1, -1 },
		leftTop{ 1001, 1001 }, leftDown{ -1, 1001 },
		rightTop{ 1001, -1 }, rightDown{ -1, -1 };

	int cellCnt = 0;
	for (int i = 0; i < cnt; i++) {
		// 직사각형 모양인지, 중복되지 않는지 확인
		// 꼭짓점 저장
		if (rs[i] <= topLeft.x && cs[i] <= topLeft.y) {
			topLeft.x = rs[i]; topLeft.y = cs[i];
		}
		if (rs[i] <= topRight.x && cs[i] >= topRight.y) {
			topRight.x = rs[i]; topRight.y = cs[i];
		}
		if (rs[i] >= downLeft.x && cs[i] <= downLeft.y) {
			downLeft.x = rs[i]; downLeft.y = cs[i];
		}
		if (rs[i] >= downRight.x && cs[i] >= downRight.y) {
			downRight.x = rs[i]; downRight.y = cs[i];
		}
		if (cs[i] <= leftTop.y && rs[i] <= leftTop.x) {
			leftTop.y = cs[i]; leftTop.x = rs[i];
		}
		if (cs[i] <= leftDown.y && rs[i] >= leftDown.x) {
			leftDown.y = cs[i]; leftDown.x = rs[i];
		}
		if (cs[i] >= rightTop.y && rs[i] <= rightTop.x) {
			rightTop.y = cs[i]; rightTop.x = rs[i];
		}
		if (cs[i] >= rightDown.y && rs[i] >= rightDown.x) {
			rightDown.y = cs[i]; rightDown.x = rs[i];
		}

		if (map[rs[i]][cs[i]] != 0) {
			Range* rr = group[map[rs[i]][cs[i]]];
			cellCnt += rr->cnt;

			if (rr->firstX <= topLeft.x && rr->firstY <= topLeft.y) {
				topLeft.x = rr->firstX; topLeft.y = rr->firstY;
			}
			if (rr->firstX <= topRight.x && rr->lastY >= topRight.y) {
				topRight.x = rr->firstX; topRight.y = rr->lastY;
			}
			if (rr->lastX >= downLeft.x && rr->firstY <= downLeft.y) {
				downLeft.x = rr->lastX; downLeft.y = rr->firstY;
			}
			if (rr->lastX >= downRight.x && rr->lastY >= downRight.y) {
				downRight.x = rr->lastX; downRight.y = rr->lastY;
			}
			if (rr->firstY <= leftTop.y && rr->firstX <= leftTop.x) {
				leftTop.y = rr->firstY; leftTop.x = rr->firstX;
			}
			if (rr->firstY <= leftDown.y && rr->lastX >= leftDown.x) {
				leftDown.y = rr->firstY; leftDown.x = rr->lastX;
			}
			if (rr->lastY >= rightTop.y && rr->firstX <= rightTop.x) {
				rightTop.y = rr->lastY; rightTop.x = rr->firstX;
			}
			if (rr->lastY >= rightDown.y && rr->lastX >= rightDown.x) {
				rightDown.y = rr->lastY; rightDown.x = rr->lastX;
			}
		}
		else cellCnt++;
	}

	if (leftTop.x != topLeft.x || leftTop.y != topLeft.y ||
		rightTop.x != topRight.x || rightTop.y != rightTop.y ||
		leftDown.x != downLeft.x || leftDown.y != downLeft.y ||
		rightDown.x != downRight.x || rightDown.y != downRight.y ||
		leftTop.x != rightTop.x || leftDown.x != rightDown.x ||
		leftTop.y != leftDown.y || rightTop.y != rightDown.y ||
		cellCnt != (rightTop.y - leftTop.y + 1) * (leftDown.x - leftTop.x + 1))
		return 0;

	// MERGED
	state = 1;
	// map 업데이트
	int newGid = rangeCnt;
	if (newGid == 91) {
		int a = 2;
	}
	group[newGid] = ranges[rangeCnt++].alloc(leftTop.x, leftTop.y, rightDown.x, rightDown.y);

	x1 = leftTop.x; y1 = leftTop.y; x2 = rightDown.x; y2 = rightDown.y;
	for (int i = x1; i <= x2; i++) {
		for (int j = y1; j <= y2; j++) {
			copyMap[i][j] = map[i][j]; // 복사해둠
			map[i][j] = newGid;
		}
	}
	rect[0] = x1; rect[1] = y1;
	rect[2] = x2; rect[3] = y2;

	return 1;
}

int sr1, sr2, sc1, sc2;
int splitCell(int r, int c, int rect[]) {
	if (map[r][c] == 0)
		return 0;

	//split 가능
	state = 2;
	Range* rr = group[map[r][c]];
	int r1 = rr->firstX, r2 = rr->lastX, c1 = rr->firstY, c2 = rr->lastY;
	sr1 = r1; sr2 = r2; sc1 = c1; sc2 = c2;
	for (int i = r1; i <= r2; i++) {
		for (int j = c1; j <= c2; j++) {
			copyMap[i][j] = map[i][j]; // 복사
			map[i][j] = 0; // 분리
		}
	}
	//rect에 저장
	rect[0] = r1; rect[1] = c1;
	rect[2] = r2; rect[3] = c2;

	return 1;
}

int ux1, ux2, uy1, uy2;
void undo() { // 병합->undo->undo: 병합->분리->병합
	if (state == 0)
		return;
	if (state == 1) { // 최근에 병합된 셀들을 분리
		state = 3;
		for (int i = x1; i <= x2; i++) {
			for (int j = y1; j <= y2; j++) {
				undoMap[i][j] = map[i][j];
				map[i][j] = copyMap[i][j];
			}
		}
		ux1 = x1; ux2 = x2; uy1 = y1; uy2 = y2;
	}
	else if (state == 2) { // 최근에 분리된 셀들을 병합
		state = 3;
		for (int i = sr1; i <= sr2; i++) {
			for (int j = sc1; j <= sc2; j++) {
				undoMap[i][j] = map[i][j];
				map[i][j] = copyMap[i][j];
			}
		}
		ux1 = sr1; ux2 = sr2; uy1 = sc1; uy2 = sc2;
	}
	else { // 최근에 undo
		for (int i = ux1; i <= ux2; i++) {
			for (int j = uy1; j <= uy2; j++) {
				int temp = map[i][j];
				map[i][j] = undoMap[i][j];
				undoMap[i][j] = temp;
			}
		}
	}
}

int checkRectangle(int r1, int c1, int r2, int c2) { // 겹치는 셀이 있는지 확인
	for (int i = r1; i <= r2; i++) {
		for (int j = c1; j <= c2; j++) {
			if (map[i][j] != 0 &&
				(group[map[i][j]]->firstX < r1 ||
					group[map[i][j]]->lastX > r2 ||
					group[map[i][j]]->firstY < c1 ||
					group[map[i][j]]->lastY > c2))
				return 1;
		}
	}
	return 0;
}
