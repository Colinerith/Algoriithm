#include <string>
#include <vector>
#include <queue>

bool visited[200];
using namespace std;

struct Node{
    vector<int> child;
};
Node nodes[200];

int solution(int n, vector<vector<int>> computers) {
    int answer = 0;
    
    for(int i=0;i< computers.size() - 1; i++){
        for(int j=i+1;j< computers.size();j++){
            if(computers[i][j]){
                nodes[i].child.push_back(j);
                nodes[j].child.push_back(i);
            }
        }
    }
    
    for(int i=0;i<computers.size();i++){
        queue<int> q;
        if(!visited[i]){
            answer++;
            visited[i]=true;
            q.push(i);
            while(!q.empty()){
                int n = q.front();
                q.pop();
                for(int j:nodes[n].child){
                    if(!visited[j]){
                        q.push(j);
                        visited[j]=true;
                    }
                }
            }
        }
    }
    
    return answer;
}
