#include <iostream>
#include <climits>
#include <iomanip>

using namespace std;

#define CHAIN_SIZE 4

int print_optimal_parans(int (&p)[CHAIN_SIZE + 1], int i, int j);
int memoized_matrix_chain(int (&p)[CHAIN_SIZE + 1]);
int lookup_chain(int (&p)[CHAIN_SIZE + 1], int i, int j);

static int m[CHAIN_SIZE][CHAIN_SIZE];
static int s[CHAIN_SIZE][CHAIN_SIZE];

int main()
{
    int p[CHAIN_SIZE + 1] = {22, 145, 10, 25, 67};
    
    memoized_matrix_chain(p);
    cout << "***Memoized Matrix Chain Multiplication***\n";
    
    //Print M
    cout << "Matrix M: \n";
    for(int i = 0; i < CHAIN_SIZE; i++)
    {
        for(int j = 0; j < CHAIN_SIZE; j++)
        {
            if(m[i][j] == INT_MAX)
                m[i][j] = 0;
            cout << " " << setw(6) << m[i][j];
        }
        cout << "\n";
    }
    cout << "\n";
    
    //Print S
    cout << "Matrix S: \n";
    for(int i = 0; i < CHAIN_SIZE; i++)
    {
        for(int j = 0; j < CHAIN_SIZE; j++)
            cout << " " << setw(6) << s[i][j];
        cout << "\n";
    }
    cout << "\n";

    //Print optimal paranthesization
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

int lookup_chain(int (&p)[CHAIN_SIZE + 1], int i, int j)
{
    int q = 0;
    if(m[i][j] < INT_MAX)
        return m[i][j];

    if(i == j)
        m[i][j] = 0;
    else
    {
       for(int k = i; k <= j - 1; k++) 
       {
            q = lookup_chain(p, i, k)
                + lookup_chain(p, k + 1, j)
                + p[i]*p[k+1]*p[j+1];
            if(q < m[i][j])
            {
                m[i][j] = q;
                s[i][j] = k + 1;
            }
        }
    }
    return m[i][j];
}

int memoized_matrix_chain(int (&p)[CHAIN_SIZE + 1])
{
    int n = CHAIN_SIZE;

    for(int i = 0; i < n; i++)
        for(int j = 0; j < n; j++)
            m[i][j] = INT_MAX;

    return lookup_chain(p, 0, n - 1);
}
