#include <iostream>
#include <climits>
#include <iomanip>

using namespace std;

#define CHAIN_SIZE 4

int print_optimal_parans(int (&p)[CHAIN_SIZE + 1], int i, int j);
int matrix_chain_order(int (&p)[CHAIN_SIZE + 1]);

static int m[CHAIN_SIZE][CHAIN_SIZE];
static int s[CHAIN_SIZE][CHAIN_SIZE];

int main()
{
    int p[CHAIN_SIZE + 1] = {22, 145, 10, 25, 67};
    
    matrix_chain_order(p);
    cout << "***Dynamic Matrix Chain Multiplication***\n";
    cout << "Matrix M: \n";
    for(int i = 0; i < CHAIN_SIZE; i++)
    {
        for(int j = 0; j < CHAIN_SIZE; j++)
            cout << " " << setw(4) << m[i][j];
        cout << "\n";
    }
    cout << "\n";
    
    cout << "Matrix S: \n";
    for(int i = 0; i < CHAIN_SIZE; i++)
    {
        for(int j = 0; j < CHAIN_SIZE; j++)
            cout << " " << setw(4) << s[i][j];
        cout << "\n";
    }
    cout << "\n";

    print_optimal_parans(p, 0, CHAIN_SIZE - 1);
    cout << "\n";

}

int print_optimal_parans(int (&p)[CHAIN_SIZE + 1], int i, int j)
{
    if(i == j)
        cout << "A" << i + 1;
    else
    {
        cout << "(";
        print_optimal_parans(p, i, s[i][j] - 1);
        print_optimal_parans(p, s[i][j], j);
        cout << ")";
    }
}

int matrix_chain_order(int (&p)[CHAIN_SIZE + 1])
{
    int n = CHAIN_SIZE;
    for(int i = 0; i < n; i++)
        m[i][i] = 0;

    for(int l = 2; l <= n; l++)
    {
        for(int i = 0; i < n - l + 1; i++)
        {
            int j = i + l - 1;
            m[i][j] = INT_MAX;
            for(int k = i; k <= j - 1; k++)
            {
                int q = m[i][k] + m[k+1][j] + p[i]*p[k+1]*p[j+1];
                if(q < m[i][j])
                {
                    m[i][j] = q;
                    s[i][j] = k + 1;
                }
            }
        }
    }
}

