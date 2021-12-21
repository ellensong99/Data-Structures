#include <utility>
#include <vector>
#include <stdexcept>
#include <iostream>
#include <cstdlib>
#include <string>
#include <math.h>
using namespace std;


//-----------------------------------------//
// a helper function to print arrays       //
//-----------------------------------------//
void print(std::vector <int> const &a)
{
    for(int i=0; i < a.size(); i++)
        std::cout << a.at(i) << " ";
    cout << endl;
}

//-----------------------------------------//
// splits A into k sub-arrays              //
//-----------------------------------------//
vector<vector<int>> split(const vector<int> & A, int k)
{
    vector<vector<int>> LoA;
    int n = A.size();
    int q = n / k;
    int r = n % k;
    int idx = 0;
    for (int i = 0; i < r; i++) {
        vector<int> Ai = vector<int>(q+1, 0);
        for (int j = 0; j <= q; j++) {
            Ai[j] = A[idx];
            idx++;
        }
        LoA.push_back(Ai);
    }

    for (int i = r; i < k; i++) {
        vector<int> Ai = vector<int>(q, 0);
        for (int j = 0; j < q; j++) {
            Ai[j] = A[idx];
            idx++;
        }
        LoA.push_back(Ai);
    }
    return LoA;
}

int ArgMin(vector<pair<int, int>> &M) {
    int l = 0;
    int m = M.size();
    for (int i = 0; i < m; i++) {
        if (M[i].first < M[l].first) {
            l = i;
        }
    }
    return l;
}

//-------------------------------------------------//
// k-way merge implemented as in the assignment    //
// if all Aj's are sorted, the output must be      //
// sorted as well                                  //
//-------------------------------------------------//
vector<int> kWayMerge(const vector<vector<int>> & Aj)
{
    int k = Aj.size();                
    vector<int> I = vector<int>(k, 0); // updated indices
    vector<int> N;   // len of each array
    int n = 0;
    for (int i = 0; i < k; i++) {
        int len = Aj[i].size();
        n += len;
        N.push_back(len);
    }
    vector<int> A = vector<int>(n);
    for (int i = 0; i < n; i++) {
        vector<pair<int, int>> M;
        for (int j = 0; j < k; j++) {
            if (I[j] < N[j]) {
                M.push_back(make_pair(Aj[j][I[j]], j));
            }
        }
        int l = ArgMin(M);
        int j = M[l].second;
        A[i] = Aj[j][I[j]];
        I[j] = I[j] + 1;
    }
    return A;
}

//-----------------------------------------//
// mergesort                               //
//-----------------------------------------//
void kWayMergeSort(vector<int> & A, int k)
{
    int l = A.size();
    if (l <= 1) {
        return;
    }
    vector<vector<int>> LoA = split(A, k);
    for (int i = 0; i < k; i++) {
        kWayMergeSort(LoA[i], k);
    }
    A = kWayMerge(LoA);
}

//-----------------------------------------//
// reads k and the entries in A            //
// calls kWayMergeSort and prints A        //
// do not change anything below            //
//-----------------------------------------//
#ifndef TESTING
int main()
{
    string line;
    getline(cin, line);
    std::vector<int> A;
    int k = atoi(line.c_str());  // k: number of arrays

    while(true){
        string line;
        if(!getline(cin, line))
            break;
        int a = atoi(line.c_str());
        A.push_back(a);
    }

    print(A);
    kWayMergeSort(A, k);
    print(A);
}
#endif