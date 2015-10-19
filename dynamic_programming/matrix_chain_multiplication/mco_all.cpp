#include <iostream>
#include <limits>
#include <vector>
#include <iomanip>
#include "../../utilities.h"

using namespace std;

#define MATRIX_MAXDIM 10

int print_1Dvector(vector<int> &a)
{
    cout << "Array: \n";
    for(int i = 0; i < a.size(); i++)    
        cout << " " << a[i];
    cout << "\n";
}

int print_2Dvector(vector< vector<int> > &a)
{
    cout << "Array: \n";
    for(int i = 0; i < a.size(); i++)
    {
        for(int j = 0; j < a[i].size(); j++)
            cout << " " << setw(MATRIX_MAXDIM / 10 + 2) << a[i][j];
        cout << "\n";
    }
    cout << "\n";
}

int generate_size_chain(vector<int> &chain, int size)
{

    for(int i = 0; i <= size; i++)
    {
        chain.push_back(rand() % MATRIX_MAXDIM + 1 );
    }
}

int initialize_2Dvector(vector< vector<int> > &a, int r, int c, int value)
{
    LOG("begin r: " << r << " c: " << c << " value: " << value);
    for(int i = 0; i < r; i++)   
    {
        vector<int> temp;
        for(int j = 0; j < c; j++)
            temp.push_back(value);
        a.push_back(temp);
    }
}

int print_optimal_parans(vector<int> &chain, vector< vector<int> > &s, int i, int j)
{
    if(i == j)
        cout << "A" << i + 1;
    else
    {
        cout << "(";
        print_optimal_parans(chain, s, i, s[i][j] - 1);
        print_optimal_parans(chain, s, s[i][j], j);
        cout << ")";
    }
}

int matrix_chain_order(vector<int> &chain,vector< vector<int> > &m, vector< vector<int> > &s  )
{
    LOG("begin");
    int n = chain.size() - 1;
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
                int q = m[i][k] + m[k+1][j] + chain[i]*chain[k+1]*chain[j+1];
                if(q < m[i][j])
                {
                    m[i][j] = q;
                    s[i][j] = k + 1;
                }
            }
        }
    }
    print_2Dvector(m);
    print_2Dvector(s);
    print_optimal_parans(chain, s, 0, n - 1);
    cout << "\n";
    LOG("end");
}

int matrix_chain_order_recursive(vector<int> &p, vector< vector<int> > &m, vector< vector<int> > &s, int i, int j)
{
    int n = p.size() - 1;
    int q = 0;
    if(i == j)
        return 0;
    m[i][j] = INT_MAX;

    for(int k = i; k < j; k++)
    {
        q = matrix_chain_order_recursive(p, m, s, i, k)
            + matrix_chain_order_recursive(p, m, s, k + 1, j)
            + p[i]*p[k+1]*p[j];
        if(q < m[i][j])
        {
            m[i][j] = q;
            s[i][j] = k + 1;
        }
    }

    return m[i][j];
}

int lookup_chain(vector< vector<int> > &m, vector< vector<int> > &s, vector<int> &p, int i, int j)
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
            q = lookup_chain(m, s, p, i, k)
                + lookup_chain(m, s, p, k + 1, j)
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

int memoized_matrix_chain(vector<int> &p, vector< vector<int> > &m, vector< vector<int> > &s)
{
    int n = p.size() - 1;

    for(int i = 0; i < n; i++)
        for(int j = 0; j < n; j++)
            m[i][j] = INT_MAX;

    return lookup_chain(m, s, p, 0, n - 1);
}

int main()
{
    vector<int> chain;
    int size;
    cout << "Number of Matrices: ";
    cin >> size;
    generate_size_chain(chain, size);
    int n = chain.size() - 1;
    vector< vector<int> > m, s;
    initialize_2Dvector(s, n, n, 0);
    initialize_2Dvector(m, n, n, 0);
    print_1Dvector(chain);
    
    //Dynamic Programming
    {
    JCHECK_PERF_AND_ERROR(matrix_chain_order,(chain, m, s));
    }
    //Recursive
    for(int i = 0; i < n; i++)
        m[i][i] = 0;
    {
    JCHECK_PERF_AND_ERROR(matrix_chain_order_recursive, (chain, m, s, 0, n - 1));
    }
    cout << "Recursive M: \n";
    print_2Dvector(m);
    cout << "\n Recursive S: \n";
    print_2Dvector(s);
    print_optimal_parans(chain, s, 0, chain.size() - 2);

    //Memoized
    for(int i = 0; i < n; i++)
        m[i][i] = INT_MAX;
    
    {
        JCHECK_PERF_AND_ERROR(memoized_matrix_chain, (chain, m, s));
    }
    cout << "Memoized M: \n";
    print_2Dvector(m);
    cout << "\nMemoized S: \n";
    print_2Dvector(s);
    print_optimal_parans(chain, s, 0, chain.size() - 2);

}
