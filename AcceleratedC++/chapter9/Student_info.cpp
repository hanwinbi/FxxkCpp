#include <iostream>
#include <string>
#include <vector>

struct Student_info{
    std::string name;
    double midterm, finalterm;
    std::vector<double> homework;

    std::istream& read(std::istream&);
    double grade() const;
};

using namespace std;

istream& Student_info::read(istream& is){
    is >> name >> midterm >> finalterm;
    read_hw(is, homework);
    return is;
}

double Student_info::grade() const{
    return::grade{midterm, finalterm, homework};
}