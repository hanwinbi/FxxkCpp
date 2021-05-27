#include <iostream>
using namespace std;

int main(int argc, char *argv[]){
    string str;
    while(cin >> str){
        string ch;
        cin >> ch;
        int len = str.size();
        int pos=INT_MAX;
        for(int i = 0; i < len; ++i){
            if(str[i] > ch[0]){
                pos = i;
                break;
            }
        }
        if(pos == INT_MAX){
            str.insert(len, ch);
        }else{
            str.insert(pos, ch);
        }
        cout << str << endl;
    }
    return 0;
}