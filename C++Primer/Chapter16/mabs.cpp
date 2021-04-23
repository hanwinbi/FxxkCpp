#include <complex>
#include <iostream>

using namespace std;

template <typename T> T mabs(const T &num){
    return abs(num);
}

int main(){
    int a;
    double b;
    cin >> a >> b; 
    cout << mabs(a) << " " << mabs(b) <<endl;
}