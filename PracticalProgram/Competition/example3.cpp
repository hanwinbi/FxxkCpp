#include <iostream>
#include <fstream>
#include <string>
#include <set>
#include <map>
using namespace std;

int main(int argc, char *argv[]){
    string str;
    cin >> str;
    int len = str.size();
    if(len < 4 || len > 4){
        cout << "Rejected" << endl;
    }
    map<char, int> m_map;
    for(int i = 0; i < len; ++i){
        if(str[i] >= 'a' || str[i] <= 'z' || str[i] >= 'A' || str[i] <= 'Z'){
            cout << "Reject" << endl;
            return 0;
        }
        m_map[str[i]]++;
    }
    auto it = m_map.begin();
    if(it->second < 4){
        cout << "Accept" << endl;
    }else{
        cout << "Reject" << endl;
    }
}