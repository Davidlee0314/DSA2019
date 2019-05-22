#include <iostream>
#include <string>
using namespace std;
int main(){
    string s;
    int m = 0, index = 0;
    cin >> m;
    while(m != 0){
        cin >> s;
        cout << m << "\n";
        cout << s.substr(41, 40)<< "\n";
        cin >> m;
    }
}
