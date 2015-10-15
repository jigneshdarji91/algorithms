#include <iostream>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

int denominations[] = { 50, 25, 10, 5, 1};

void change(int n)
{
    int i = 0;
    while(n > 0 && i < sizeof(denominations))
    {
        if(n / denominations[i] != 0)
        {
            cout << denominations[i] << " cent(s)\n";
            n = n - denominations[i];
        }
        else
            i++;
    }
}

int main(int argc, char* argv[])
{
    change(atoi(argv[1]));
}

