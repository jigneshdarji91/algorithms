#include <iostream>
#include <stack>
#include "../utilities.h"

using namespace std;

int a[] = {55, 56, 77, 44, 22, 11, 10, 5, 47};

int partition(int p, int r)
{
    int x = a[r];
    int i = p - 1;
    int temp = 0;
    for(int j = p; j < r; j++)
    {
        if(a[j] <= x)
        {
            i++;
            temp = a[i];
            a[i] = a[j];
            a[j] = temp;
        }
    }
    temp = a[i+1];
    a[i+1] = a[r];
    a[r] = temp;
    LOG(" p: " << p << " r: " << r << " q: " << i + 1);
    return (i + 1);
}

int rselect_iterative(int p, int r, int k)
{
    LOG("begin p: " << p << " r: " << r << " k: " << k);
    stack<int> stack_right;
    while(1)
    {
        if(p > r)
        {
            if(stack_right.size() == 0)
            {
                LOG("end of job! Yay!");
                break;
            }
            else
            {
                r = stack_right.top();
                stack_right.pop();
                p = stack_right.top();
                stack_right.pop();
                continue;
            }
        }
        int q = partition(p, r);
        LOG("p: " << p << " q: " << q << "r: " << r);
        if(q == k)
        {
            LOG("found it! a[" << k << "]: " << a[k]);
            return a[k];
        }
        
        stack_right.push(q+1);
        stack_right.push(r);
        p = p;
        r = q - 1;
    }
}

int main()
{
    LOG("begin");
    int k;
    cout << "Enter sorted element position: ";
    cin >> k;
    rselect_iterative(0, sizeof(a)/sizeof(a[0]) - 1, k);
    LOG("end");
}

