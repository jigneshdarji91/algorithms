#include <iostream>
#include <climits>
#include <iomanip>

using namespace std;

#define CHAIN_SIZE 4

int print_optimal_parans(int (&p)[CHAIN_SIZE + 1], int i, int j);
int matrix_chain_order_recursive(int (&p)[CHAIN_SIZE + 1], int i, int j);

static int m[CHAIN_SIZE][CHAIN_SIZE];
static int s[CHAIN_SIZE][CHAIN_SIZE];
static int recursive_calls = 0;

int main()
{
    int p[CHAIN_SIZE + 1] = {22, 145, 10, 25, 67};
    
    matrix_chain_order_recursive(p, 0, CHAIN_SIZE - 1);
    cout << "***Recursive Matrix Chain Multiplication***\n";
    
    cout << "Recursive calls made: " << recursive_calls << endl;
    //Print M
    cout << "Matrix M: \n";
    for(int i = 0; i < CHAIN_SIZE; i++)
    {
        for(int j = 0; j < CHAIN_SIZE; j++)
            cout << " " << setw(6) << m[i][j];
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

int matrix_chain_order_recursive(int (&p)[CHAIN_SIZE + 1], int i, int j)
{
    recursive_calls++;
    int n = CHAIN_SIZE;
    int q = 0;
    if(i == j)
        return 0;
    m[i][j] = INT_MAX;

    for(int k = i; k < j; k++)
    {
        q = matrix_chain_order_recursive(p, i, k)
            + matrix_chain_order_recursive(p, k + 1, j)
            + p[i]*p[k+1]*p[j + 1];
        if(q < m[i][j])
        {
            m[i][j] = q;
            s[i][j] = k + 1;
        }
    }
    
    return m[i][j];
}

