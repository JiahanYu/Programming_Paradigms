//its header file refers to q4.h
#include <iostream>
#include "random.h"

using namespace std;

void Merge(int *a, int *L, int n1, int *R, int n2);
void sort(int *a, int n);
void printArray(int arr[], int n);

const unsigned int numberOfinteger = 30;


/* This Q4() function is used for testing the program */
void Q4() {
    //generate an array with 30 random numbers in sequence
    int array[numberOfinteger];
    for (int i = 0; i < numberOfinteger; i++){
        array[i] = randomInteger(-1000,1000);
    }

    cout<<"Original Data:";
    printArray(array, numberOfinteger); //print out the original array

    sort(array, numberOfinteger); // Do Mergesort operation

    cout<<"\n\nSorted Data:";
    printArray(array, numberOfinteger); //print out the sorted array

}



// A function to merge the two half into a sorted data.
// n1 = number of elements in L; n2 = number of elements in R
void Merge(int *a, int *L, int n1, int *R, int n2) {
    int i, j, k;
    i = 0; // index of left aubarray (L)
    j = 0; // index of right sub-raay (R)
    k = 0; // index of merged subarray (A)

    while(i < n1 && j < n2) {
        if(L[i]  < R[j]) a[k++] = L[i++];
        else a[k++] = R[j++];
    }
    while(i < n1) a[k++] = L[i++];
    while(j < n2) a[k++] = R[j++];
}

void sort(int *a, int n) {
    int mid, i, *L, *R;
    if (n < 2) return; // base case. As the array has less than two element, no change to make.
    mid = n/2; // find the mid index

    L = new int[mid];
    R = new int[n - mid];
    for(i = 0; i < mid; i++) L[i] = a[i]; // creating left subarray: has mid elements (from index 0 till mid-1)
    for(i = mid; i < n; i++) R[i-mid] = a[i]; // creating right subarray: has (n-mid) elements (from mid to n-1)

    sort(L, mid); // sorting the left subarray
    sort(R, n-mid); // sorting the right subarray
    Merge(a, L, mid, R, n-mid); // Merge them to get sorted output.

    //delete operations
    delete [] R;
    delete [] L;
}


void printArray(int arr[], int n){
    // Printing the array
    for (int i = 0; i < n; i++){
        cout<<" "<<arr[i];
    }
}
