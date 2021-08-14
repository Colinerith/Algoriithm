#include <iostream> // KMP. 98ms로 통과.
using namespace std;

char book[500001];
char word[100001];
int F[100001];
int T;

void failureFunction() {
	F[0] = 0;
	for (int i = 1; word[i]; i++) {
		int j = F[i - 1];
		while (j > 0) {
			if (word[i] == word[j]) break;
			j = F[j - 1];
		}
		if (word[i] == word[j]) F[i] = j + 1;
		else F[i] = 0;
	}
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cin >> T;
	for (int test_case = 1; test_case <= T; test_case++) {
		cin >> book >> word;
		int cnt = 0;
		failureFunction();
		int i = 0, j = 0;
		while (book[i]) {
			if (book[i] == word[j]) {
				if (word[j+1] == '\0') cnt++;
				i++; j++;
			}
			else if (j > 0) j = F[j - 1];
			else i++;
		}
		cout << '#' << test_case << ' ' << cnt << '\n';
	}
	return 0;
}
