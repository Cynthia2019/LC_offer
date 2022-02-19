//1573
class Solution {
public:
    int numWays(string s) {
        int sum = 0; 
        int mod = 1000000007;
        for(int i = 0; i < s.size(); i++){
            if(s[i] == '1') sum++;
        }
        if(sum % 3 != 0) return 0; 
        int num = sum / 3; 
        if(num == 0) {
            long ans = (long)(s.size() - 1) * (s.size() - 2) / 2;
            return ans % mod;
        }
        int count_prefix = 0;
        int ans_prefix = 0;
        for(int i = 0; i < s.size() - 2; i++){
            if(s[i] == '1') count_prefix++; 
            if(count_prefix == num){
                ans_prefix++;
            }
            else if(count_prefix > num) break; 
        }
        int count_suffix = 0; 
        int ans_suffix = 0; 
        for(int i = s.size() - 1; i >= 2; i--){
            if(s[i] == '1') count_suffix++; 
            if(count_suffix == num){
                ans_suffix++;
            }
            else if(count_suffix > num) break; 
        }  
        long ans = (long)ans_prefix * ans_suffix; 
        return (int)(ans % mod);
    }
};