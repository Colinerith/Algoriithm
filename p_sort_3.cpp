#include <string>
#include <vector>
#include <algorithm>
using namespace std;

int solution(vector<int> citations) {
    int s = citations.size();
    sort(citations.begin(), citations.end());
    int tmp = 0;
    for(int i=s-1;i>=0;i--){
        if(citations[i] == s-i) return citations[i];
        else if(citations[i] < s-i) return s-i - 1;
    }
}
