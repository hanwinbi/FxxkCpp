#include <iostream>
using namespace std;

int main(){
    cout << "what is your name?";
    string name;
    cin >> name;
    cout << "hello," << name << endl << "and what is yours?";
    cin >> name;
    cout << "hello," << name << ",nice to meet you too!"<< endl;
    return 0;
}