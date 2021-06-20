#include<iostream>
#include<string>
#include<vector>
using namespace std;

//int arr1[6];
//int arr2[6];

int main() {
	int t, l, tmp;
	string a, b;
	string filter, f_reverse;
	cin >> t;
	tmp = t;

	while (t--) {
		vector<int> v1;
		vector<int> v2;

		cin >> a >> b >> l;
		cin >> filter;
		int count = 0;

		int idx = 5;
		for (int i = 0; i < a.length();i++) {
			//arr1[idx--] = a[i]-'0';
			v1.push_back(a[i] - '0');
		}
		idx = 5;
		for (int i = 0; i < b.length(); i++) {
			//arr2[idx--] = b[i]-'0';
			v2.push_back(b[i] - '0');
		}

		for (int i = 0; i < v1.size(); i++) {
			if (a == b) break;
			if (v1.size() > v2.size()) {
				if (filter[0] == '-') {
					
				}
				else if (f_reverse[0] == '-') {

				}
				else {
					count = -1;
					break;
				}
			}
			for (int j = 0; j < v2.size(); j++) {

			}
		}
		cout << "#" << tmp - t << " " << count << "\n";
	}

}
