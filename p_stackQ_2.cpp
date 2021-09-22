#include <string>
#include <vector>
#include <queue>

using namespace std;

int solution(vector<int> priorities, int location) {
    int answer = 0;
    int number = priorities[location];
    priority_queue<int> pq;
    for(int i=0;i<priorities.size();i++)
        pq.push(priorities[i]);
    
    int idx = 0;
    while(!pq.empty()){
        if(priorities[idx] == number){
            return answer;
        }
        if(pq.top() != priorities[idx]){
            int tmp = priorities[idx];
            priorities.push_back(tmp);
        }
        else{
            pq.pop();
        }
        idx++;
        number++;
    }
    
    //return answer;
}
