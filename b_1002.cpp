//https://www.acmicpc.net/problem/1002
// x1, x2, y1, y2가 뭘 나타내는지 잘 보자.
#include<iostream>
#include<cmath>
#include<algorithm>
using namespace std;

double distance(int x1, int x2, int y1, int y2) {
	double result;
	result = (x1 - x2)*(x1 - x2) + (y1 - y2)*(y1 - y2);
	return sqrt(result);
}

int main() {
	int n;
	cin >> n;
	while (n--) {
		int x1, y1, x2, y2, r1, r2;
		cin >> x1 >> y1 >> r1 >> x2 >> y2 >> r2;

		int sum = r1 + r2;
		int result = -1;

		double dist = distance(x1, x2, y1, y2);
		if (x1 == x2 && y1 == y2 && r1 == r2) result = -1;
		else if (sum < dist) result = 0;
		else if (sum == dist) result = 1;
		else if (dist + min(r1, r2) == max(r1, r2)) result = 1;
		else if (dist + min(r1, r2) < max(r1, r2)) result = 0;
		else if (sum > dist) result = 2;
		cout << result << endl;
	}
}
