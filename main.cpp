#include <iostream>

#include "matrix.h"

using namespace std;

int main(int argc, char *argv[]) {
    Matrix<int> a(3, 2);
    a.set(0,0,1);
    a.set(0,1,4);
    a.set(1,0,2);
    a.set(1,1,0);
    a.set(2,0,-3);
    a.set(2,1,-2);
    
    a.printRow();

    cout<<endl;
    for (int i = 0; i < 2; ++i){
    	for (int j = 0; j < 3; ++j){
    		cout<<a(j,i)<<" ";
    	}
    	cout<<endl;
    }

    Matrix<int> b(2,3);
    b.set(0,0,3);
    b.set(0,1,2);
    b.set(0,2,-1);
    b.set(1,0,1);
    b.set(1,1,4);
    b.set(1,2,5);
    
    cout<<endl;
    cout<<endl;
    (a*b).printRow();
    //system("PAUSE");
    return EXIT_SUCCESS;
}