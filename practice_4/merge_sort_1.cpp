#include <iostream>
#include <fstream>

using namespace std;

void split(int & portionLen) { // фаза разделения 
    ifstream A;
    ofstream B, C;
    A.open("D:\\4siaod\\A.txt");
    B.open("D:\\4siaod\\B.txt");
    C.open("D:\\4siaod\\C.txt");
    int temp, itr;
    while(!A.eof()) {
        itr = 0;
        while(itr < portionLen) {
            A >> temp;
            if(A.eof()) break;
            B << temp << " ";
            itr++;
        }
        itr = 0;
        while(itr < portionLen) {
            A >> temp;
            if(A.eof()) break;
            C << temp << " ";
            itr++;
        }
    }

    A.close();
    B.close();
    C.close();
}

void merge(int & portionLen, int fileSize) {
    ifstream B, C;
    ofstream A;
    A.open("D:\\4siaod\\A.txt");
    B.open("D:\\4siaod\\B.txt");
    C.open("D:\\4siaod\\C.txt");

    int fileItr = 1, itrB = 0, itrC = 0;
    int numB, numC;

    while(itrB + itrC < fileSize) {
        while(itrB < portionLen * fileItr && itrC < portionLen * fileItr) {
            if(itrB == itrC && itrB == portionLen * (fileItr - 1)) {
                B >> numB;
                C >> numC;
            } else {
                if (numB < numC) B >> numB;
                else if (numC <= numB) C >> numC;
            }

            if (B.eof()) break;
            if(C.eof()) break;
            
            if (numB < numC) {
                A << numB << " ";
                itrB++;
            } else {
                A << numC << " ";
                itrC++;
            }
        }

        while(itrB < portionLen * fileItr && !B.eof()) {
            A << numB << " ";
            if(itrB + 1 >= portionLen * fileItr) break;
            B >> numB;
            if (B.eof()) break;
            itrB++;
        }

        while(itrC < portionLen * fileItr && !C.eof()) {
            A << numC << " ";
            if(itrC + 1 >= portionLen * fileItr) break;
            C >> numC;
            if(C.eof()) break;
            itrC++;
        }

        itrB = itrC = portionLen * fileItr;
        fileItr++;
    }

    A.close();
    B.close();
    C.close();

}

void execute() {
    int portionLen = 1, fileSize = 0;
    int temp;

    ifstream A;
    A.open("D:\\4siaod\\A.txt");
    while(!A.eof()) {
        A >> temp;
        fileSize++;
    }
    A.close();
    while(portionLen < fileSize) {
        split(portionLen);
        merge(portionLen, fileSize - 1);
        portionLen *= 2;
    }
    
}

int main() {
    execute();
    //print file

    return 0;
}