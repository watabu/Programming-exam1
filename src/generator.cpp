#include "header.hpp"

//テストケース生成用
//60進数に対応していない
int main(){
    int n;
    cin >> n;
    
    string S1 = ",10.20.30.1/16,10";
    string S2 = ",10.20.30.2/16,5";
    
    ll start = 20201019133124;
    ll delta = 10;
    
    cout << n * 2 << endl;
    ll x = start;
    for (size_t i = 0; i < n; i++)
    {
        cout << x << S1 << endl;
        cout << x + 2 << S2 << endl;
        x += delta;
    }
    return 0;
}