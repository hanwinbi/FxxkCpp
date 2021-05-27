#include <iostream>
#include <fstream>
#include <string>
#include <set>
#include <map>
using namespace std;

int main(int argc, char *argv[]){
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