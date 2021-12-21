
#include <iostream>
#include <cstdlib>
#include <vector>
#include <stack>
#include <iostream>
# include <chrono>
#include <assert.h>


using namespace std;
using std::cin;
using std::cout;
using std::endl;
using  ns = chrono::nanoseconds;
using get_time = chrono::steady_clock;


using namespace std;

int getDigit(unsigned long int n, int d, int m) {
    unsigned long int k = 10;
    for (int i = 1; i < (m - d); i++) {
        n = n / k;
    }
    return n % 10; 
}

void bucketSort(vector<unsigned long int> &A, int l, int r, int d, int m) {
    vector<vector<unsigned long int>> B(10);
    for (int i = 0; i < 10; i++) {
        B[i] = vector<unsigned long int>(0); 
    }
    for (int i = l; i <= r; i++) {
        unsigned long int next = A[i];
        int digit = getDigit(A[i], d, m);
        B[digit].push_back(next);
    }
    int i = l;
    for (int j = 0; j < 10; j++) {
        int size = B[j].size();
        for (int k = 0; k < size; k++) {
            A[i++] = B[j][k];
        }
    }
}

void MSDSort(vector<unsigned long int> &A, int m, int l, int r, int d, int threshold, int &total_num_calls)
{
    total_num_calls++;
    if (r - l + 1 <= threshold) {
        for (int i = l+1; i <= r; i++) {
            unsigned long int k = A[i];
            int j = i - 1;
            while (j >= l && A[j] > k) {
                A[j+1] = A[j];
                j--;
            }
            A[j+1] = k;
        }
        return;
    }
    if (l < r) {
        bucketSort(A, l, r, d, m);
        if (m - d > 1) {
            int l1 = l;
            while (l1 <= r) {
                int digit = getDigit(A[l1], d, m);
                int r1 = l1;
                while (digit == getDigit(A[r1], d, m)) {
                    r1++;
                }
                r1--;
                MSDSort(A, m, l1, r1, d+1, threshold, total_num_calls);
                l1 = r1 + 1;
            }
        }
    }
}


//--------------------------------------------//
// helper function to generate a random array //
//--------------------------------------------//

void getRandomArray(vector<unsigned long int>& A)
{

    for (unsigned int i = 0; i < A.size(); i++)
        A[i] = (unsigned long int) rand() * (unsigned long int)  rand() * (unsigned long int)  rand();

}

#ifndef TESTING
int main()
{
    int m = 10;
    int threshold = 1;
    int n = 100000;
    vector<unsigned long int> A;

    // for tests on a random array, set this variable to false
    bool read_input_from_cin = true;
    
    if (read_input_from_cin)
    {
        cin >> n;  // read the size of array A
        cin >> threshold;  // read the threshold for the sorting algorithm 

        A.resize(n);

        // read array A from standard input
        for (int i = 0; i < n; i++)
            cin >> A[i];

    }
    else {
        A.resize(n);
        getRandomArray(A);

    }
    
    auto start = get_time::now(); //use auto keyword to minimize typing strokes :)

    int total_num_calls = 0;
    MSDSort(A, m, 0, n-1, 0, threshold, total_num_calls);
 
    auto end = get_time::now();
    auto diff = end - start;

    
    bool sorted = true;
    // print re-arranged A  to standard output    
    cout << A[0] << endl;
    for (int i = 1; i < n; i++)
    {
        cout << A[i] << endl;
        if (A[i] < A[i - 1])
            sorted = false;       
    }
    
     cout << total_num_calls << endl;
        
    // uncomment this line to have running time printed to the standard output
    //cout << "Time to sort: " <<  chrono::duration <double, milli>(diff).count() << " ms" << endl;

    return 0;

}

#endif
