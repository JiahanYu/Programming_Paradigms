#include <iostream>
#include "random.h"
#include "vector.h"
#include "iomanip"
using namespace std;

void printHeader();
void countComparisons(int nElements, int nTrials);
void searchTrial(int nElements, int & nLinear, int & nBinary);
int linearSearch(int key, Vector<int> & vec, int & ncmp);
int binarySearch(int key, Vector<int> vec, int p1, int p2, int & ncmp);

float nLinear;
float nBinary;

void Q3() {
    printHeader();

    // the number in column N, which represents number of elements in array for each run
    Vector<int> N_vec = {10, 50, 100, 500, 1000, 5000, 10000, 50000, 100000};

    //print the data for each run
    // its format follows the sample in the exercise description
    int nTrials = 25; //nTrials is the number of independent trials made for that element count.
    for (int i = 0; i < 9; i++) {
        countComparisons(N_vec[i], nTrials);
        cout.setf(ios::fixed);
        cout << " " << setw(7) << setprecision(1) << N_vec[i] << "  |";
        cout << " " << setw(7) << setprecision(1) << nLinear << "  |";
        cout << setw(7) << setprecision(1) << nBinary << endl;
    }
}

void printHeader(){
    //print the header
    cout << "     N    |  Linear  |  Binary  " << endl;
    cout << " ---------+----------+----------" << endl;
}


//nElements is the number of elements in the array
void countComparisons(int nElements, int nTrials){
    int sumL = 0;
    int sumB = 0;
    for (int i = 0; i < nTrials; i++){
        int nLcmp = 0;
        int nBcmp = 0;
        searchTrial(nElements, nLcmp, nBcmp);
        sumL += nLcmp;
        sumB += nBcmp;
    }
    nLinear = float(sumL)/nTrials;
    nBinary = float(sumB)/nTrials;
}


//nLinear is the counter in linear search
//nBinary is the counter in binary search
void searchTrial(int nElements, int & nLinear, int & nBinary) {
    Vector<int> vec;
    for (int i = 0; i < nElements; i++) {
        vec.add(randomInteger(1, nElements));
    }
    sort(vec.begin(), vec.end()); // sort the above generated random array, ensuring the array in order

    int key = randomInteger(1, nElements); // random choose a key to search
    linearSearch(key, vec, nLinear); // nLinear is the number of comparisons in linear search
    binarySearch(key, vec, 0, nElements-1, nBinary); // nBinary is the number of comparisons in binary search
}


//ncmp is the counter
//key is the value you want to find in the integer list
//vec is the list of integer
int linearSearch(int key, Vector<int> & vec, int & ncmp){
    for (ncmp = 0; ncmp < vec.size(); ++ncmp) {
        if (key == vec[ncmp]) return ncmp;
    }
    return -1;
}

int binarySearch(int key, Vector<int> vec, int p1, int p2, int & ncmp){
    ncmp++;
    if (p1 > p2) return -1;
    int mid= (p1 + p2) / 2;

    if (key == vec[mid]) return mid;
    if (key < vec[mid]) {
        return binarySearch(key, vec, p1, mid -1, ncmp);
    }else{
        return binarySearch(key, vec, mid + 1, p2, ncmp);
    }
}
