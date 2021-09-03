#include <iostream>
#include <vector>
using namespace std;

vector<int> solution(vector<vector<int> > v) {
    vector<int> ans;

    int a = v[0][0];
    int b = v[0][1];
    int c, d;
    int aCnt=1;
    int bCnt=1;
    for(int i=1;i<3;i++){
        if(v[i][0] == a)
            aCnt++;
        else c=v[i][0];
 
        if(v[i][1] == b)
            bCnt++;
        else d=v[i][1];
    }
    if(aCnt==2) ans.push_back(c);
    else ans.push_back(a);
    
    if(bCnt==2) ans.push_back(d);
    else ans.push_back(b);

    return ans;
}
