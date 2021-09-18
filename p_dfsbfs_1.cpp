#include <string>
#include <vector>
#include<iostream>

using namespace std;

int cnt, s, target;
vector<int> numbers;
void dfs(int idx, int num){
    //cout<<"now: "<<idx<<" "<<num<<endl;
    if(idx == s){
        if(num == target)
            cnt++;
        return;
    }
    dfs(idx+1, num+numbers[idx]);
    dfs(idx+1, num-numbers[idx]);
}

int solution(vector<int> n, int t) {
    //int answer = 0;
    cnt = 0; 
    s = n.size();
    target=t;
    numbers=n;
    dfs(0,0);
    
    return cnt;
}
