/*input
ababccc
abccc
*/
#include <iostream>

using namespace std;

int main(){
    cin.sync_with_stdio(0);
    cin.tie(0);
    string s, t;
    cin >> s >> t;
    int sz = s.size();
    int tz = t.size();
    for(int i=0; i<=sz-tz;){
        if(s[i]==t[0]){
            if(s[i+tz-1] == t[tz-1]){
                bool valid = true;
                for(int j=i; j<i+tz; j++){
                    if(s[j]!=t[j-i]){
                        valid = false;
                        break;
                    }
                }
                if(valid){
                    printf("%d", i);
                    return 0;
                }else{
                    i += tz-1;
                }
            }else{
                i++;
            }
        }else{
            i++;
        }
    }
    printf("-1");
    return 0;
}