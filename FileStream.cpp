#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main(){
    ifstream datafile("hello.txt");
    ofstream outfile;
    outfile.open("out.txt");
    string tx="";
    int i = 0;
    while(getline(datafile, tx)){
        outfile << tx << endl;
        cout << "line "<< i << ":" << tx << endl;
        ++i;
    }
    datafile.close();
    outfile.close();
    return 0;
}