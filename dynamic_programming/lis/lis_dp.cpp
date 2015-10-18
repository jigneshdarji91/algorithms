#include <iostream>
#include <vector>
#include "../../utilities.h"

using namespace std;

#define MAX_VAL 50

int generate_array(vector<int> &a, int size)
{
    int temp = 0;
    for(int i = 0; i < size; i++)
    {
        temp = rand() % MAX_VAL;
        a.push_back(temp);
    }
}

int print_vector(vector<int> &a)
{
    cout << "Array: ";
    for(int i = 0; i < a.size(); i++)    
        cout << " " << a[i];
    cout << "\n";
}

int lis(vector<int> &s, vector<int> &l)
{
    LOG("begin s.size: " << s.size());
    for(int i = 0; i < s.size(); i++)   
    {
        int l_i = 0, maxlj = 0;
        for(int j = 0; j < i; j++)
        {
            if(maxlj < l[j] && s[i] >= s[j])
                maxlj = l[j];
            l_i = 1 + maxlj;
            l[i] = l_i;
        }
    }
}

int main()
{
    vector<int> S, l;
    int size;
    cout << "Enter size of array: ";
    cin >> size;
    
    generate_array(S, size);
    print_vector(S);

    for(int i = 0; i < size; i++)
        l.push_back(1);
    lis(S, l);
    print_vector(l);
}
