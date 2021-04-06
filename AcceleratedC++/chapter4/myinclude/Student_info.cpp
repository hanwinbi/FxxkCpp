#include "Student_info.h"
#include <iostream>
#include <string>
#include <vector>

using namespace std;

bool compare(const Student_info& x, const Student_info& y){
    return x.name < y.name;
}

istream& read_hw(istream& in, vector<double>& hw){
    if(in){
        in.clear();
        double x;
        while(in>>x){
            hw.push_back(x);
        }
        in.clear();
    }
    return in;
}

istream& read(istream& is, Student_info& s){
    is >> s.name >> s.midterm >> s.finalterm;
    read_hw(is, s.homework);
    return is;
}