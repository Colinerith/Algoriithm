#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<string>
using namespace std;

int T, test_case, n;
string name;
string note[20000];
string sortedNote[20000];

void mergeSort(int a, int b) {
	if (a == b) return;
	int mid = (a + b) / 2;
	mergeSort(a, mid);
	mergeSort(mid + 1, b);

	int l = a; int r = mid + 1;
	int sortedIdx = l;

	while (l <= mid && r <= b) {
		if (note[l].length() < note[r].length())
			sortedNote[sortedIdx++] = note[l++];
		else if(note[l].length() > note[r].length())
			sortedNote[sortedIdx++] = note[r++];
		else { // 길이가 같음
			if (note[l].compare(note[r]) == 0) {
				sortedNote[sortedIdx++] = note[l++];
				r++; // 넣지 않고 인덱스만 증가
				sortedNote[sortedIdx++] = "";
			}
			else if (note[l].compare(note[r]) < 0)
				sortedNote[sortedIdx++] = note[l++];
			else
				sortedNote[sortedIdx++] = note[r++];
		}
	}
	//남아있다면?
	if (l <= mid) {
		while (l <= mid)
			sortedNote[sortedIdx++] = note[l++];
	}
	else {
		while (r <= b)
			sortedNote[sortedIdx++] = note[r++];
	}
	// 배열복사 반드시 필요함
	for (int i = a; i <= b; i++)
		note[i] = sortedNote[i];
}

int main(int argc, char** argv) {
	ios::sync_with_stdio(false); cin.tie(NULL);
	cin >> T;
	for (test_case = 1; test_case <= T; ++test_case) {
		cin >> n;
		for (int i = 0; i < n; i++) {
			cin >> note[i];
		}
		mergeSort(0, n - 1);

		cout << "#" << test_case << "\n";
		for (int i = 0; i < n; i++) {
			if (note[i] != "")
				cout << note[i] << "\n";
		}
	}
	return 0;
}
