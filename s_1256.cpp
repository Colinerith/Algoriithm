#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<queue>
#include<string>
using namespace std;

int test_case, k;

int main(int argc, char** argv) {
	scanf("%d", &k);
	for (test_case = 1; test_case <= 10; ++test_case) {
		scanf("%d", &k);
		string str;
		cin >> str;
		priority_queue<string, vector<string>, greater<string>> pq;
		string temp = "";
		for (int i = str.length() - 1; i >= 0; i--) {
			temp = str[i] + temp;
			pq.push(temp);
		}
		for (int i = 0; i < k - 1; i++)
			pq.pop();
		cout << "#" << test_case << " " << pq.top() << "\n";
	}
	return 0;
}
