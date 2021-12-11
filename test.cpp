#include <iostream>
#include <string>
int ans = 0;
void backtrack(string& s, int startIndex, int split){
    if(startIndex >= (int)s.size()){
        ans++; 
        return ;
    }
    for(int i = startIndex; i < (int)s.size(); i++){
        int count = split; 
        while(count > 0) {
            if(s[i] == 'a') count--;
            i++; 
            cout << s[i] << endl;
        }
        while(count == 0){
            backtrack(s, i, split); 
        }
    }
}

int solution(string &S) {
    // write your code in C++14 (g++ 6.2.0)
    int countA = 0;
    for(int i = 0; i < S.size(); i++){
        char ch = S[i];
        if(ch == 'a') countA++;
    }
    if(countA % 3 != 0) return 0; 
    int split = countA % 3; 
    backtrack(S, 0, split);
    return ans;
}
int s = solution("babaa")
cout << s << endl; 