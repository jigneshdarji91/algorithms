#include <iostream>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

int denominations[] = { 15, 10, 5, 1};

void change(int n)
{
    if(n == 0)
        return;
    for(int i = 0; i < sizeof(denominations); i++)
    {
        if(n / denominations[i] != 0)
        {
            cout << denominations[i] << " cent(s)\n";
            n = n - denominations[i];
            break;
        }
    }
    change(n);
}

int main(int argc, char* argv[])
{
    change(atoi(argv[1]));
}

