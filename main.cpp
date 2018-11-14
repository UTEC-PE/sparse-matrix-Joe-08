#include <iostream>

#include "matrix.h"

using namespace std;

int main(int argc, char *argv[]) {
    Matrix<int> a(3, 3);
    a.set(0,0,1);
    a.set(0,1,4);
    a.set(1,0,2);
    a.set(1,1,0);
    a.set(2,0,-3);
    a.set(2,1,-2);
    
    cout<<"a"<<endl;
    a.print();
    cout<<endl;
    
    cout<<"a*0"<<endl;
    Matrix<int> c = (a*0);
    c.print();
    cout<<endl;

    Matrix<int> b(3,3);
    b.set(0,0,3);
    b.set(0,1,2);
    b.set(0,2,-1);
    b.set(1,0,1);
    b.set(1,1,4);
    b.set(1,2,5);
    
    cout<<"b"<<endl;
    b.print();
    cout<<endl;

    cout<<"a+b"<<endl;
    (a+b).print();
    cout<<endl;

    cout<<"a-b"<<endl;
    (a-b).print();
    cout<<endl;

    cout<<"a*b"<<endl;
    (a*b).print();
    //system("PAUSE");
    return EXIT_SUCCESS;
}