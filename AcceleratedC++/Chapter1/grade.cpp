#include <iostream>
#include <ios>
#include <string>
#include <iomanip>
using namespace std;


int main(){
    cout << "please enter your first name :";
    string name;
    cin >> name;
    cout << "hello ,"  << name << endl;
    cout << "Please enter you midterm and final exam grades: ";
    double midterm, final_;
    cin >> midterm >> final_;
    cout << "Enter you homework grades, "
            "followed by end-of-file: ";
    int count = 0;
    double sum = 0;
    double x;
    while (cin >> x)
    {
        ++count;
        sum += x;
    }
    streamsize prec = cout.precision();
    cout << "yout final grade is " << setprecision(3) 
    << 0.2 * midterm + 0.4 * final_ + 0.4 * sum / count 
    << setprecision(prec) << endl;
    return 0;
}