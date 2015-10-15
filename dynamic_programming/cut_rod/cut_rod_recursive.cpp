/*
    Program: Find the optimal solution to the rod cut problem.
    Pseucode has been taken from Introduction to Algorithms, pg 363
    
    Intention: To check how slow the recursive method is
    
    Input: rod size n
    Output the max revenue
    
    Cost matrix has been assumed to equal to rod size.
    
    Results:
    Size        Time
    26          0.23
    27          0.45
    28          0.9
    29          1.8
    30          3.6
    31          7.3
    40          
    */
#include <iostream>
#include "../../utilities.h"

using namespace std;

int cut_rod_recursive(int n);
int main()
{
    int n = 0;
    cout << "Enter size of rod: ";
    cin >> n;

    int q = cut_rod_recursive(n);
    JCHECK_PERF_AND_ERROR(cut_rod_recursive,(n));
    LOG("Max revenue: " << q);
}

int cut_rod_recursive(int n)
{
    if(0 == n)    
        return 0;
    int q = -1;
    for(int i = 1; i < n; i++)
    {
        int temp = i + cut_rod_recursive(n-i);
        if(q < temp)
            q = temp;
    }
    return q;
}
