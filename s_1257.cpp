#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<set>
#include<string>
using namespace std;

int T, test_case, k;

int main(int argc, char** argv){
	scanf("%d", &T);
	for (test_case = 1; test_case <= T; ++test_case){
		scanf("%d", &k);
		string str;
		cin >> str;
		string temp = "";
		set<string, less<string>> s;
		for (int i = 1; i <= str.length(); i++){
			for (int j = 0; j < str.length(); j++) {
				s.insert(str.substr(j, i));
			}
		}

		string result;
		if (s.size() < k) {
			result = "none";
		}
		else {
			for (int i = 0; i < k - 1; i++)
				s.erase(s.begin());
			result = *s.begin();
		}
		cout << "#" << test_case << " " << result << "\n";
	}
	return 0;
}
