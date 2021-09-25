#include <string>
#include <vector>
#include <queue>

using namespace std;

int solution(int bridge_length, int weight, vector<int> truck_weights) {
    int time = 0;
    queue<pair<int, int>> onTheBridge;
    for(int i=0;i<truck_weights.size();i++){
        
    }
    int idx = 0;
    int tempWeight = weight;
    while(idx <= truck_weights.size()){
        time++;
        if(tempWeight >= truck_weights[idx]){
            onTheBridge.push({truck_weights[idx],time});
            tempWeight -= truck_weights[idx];
            idx++;
        }
        if(time - onTheBridge.front().second == bridge_length){
            tempWeight += onTheBridge.front().first;
            onTheBridge.pop();
        }
    }
    
    
    return time;
}
