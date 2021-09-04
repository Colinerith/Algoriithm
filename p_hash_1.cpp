#include <string>
#include <vector>
#include <unordered_map>
using namespace std;

string solution(vector<string> participant, vector<string> completion) {
    string answer = "";
    
    unordered_map<string, int> m;
    for(string s : completion){
        m[s]++;
    }
    for(string s : participant){
       if(m[s] == 0){
           answer = s;
           break;
       }
       m[s]--;
    }
    return answer;
}
