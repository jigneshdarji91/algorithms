#include <iostream>
#include <vector>
#include <stdlib.h>
#include "../../utilities.h"

using namespace std;

#define MATRIX_MAXDIM 10
#define MATRIX_MAXVAL 10

typedef struct matrix
{
    int **value;
    int rsize;
    int csize;
    matrix();
    matrix(int r, int c) : rsize(r), csize(c)
    {
        value = new int *[rsize];
        for(int j = 0; j < rsize; j++)
            value[j] = new int[csize];
    }
}matrix;

typedef vector<matrix> matrix_chain;

int matrix_multiply(matrix &a, matrix &b, matrix &c);
int print_matrix(matrix &m);
int generate_matrix_values(matrix &m);
int generate_matrix_chain(matrix_chain &chain, int size);

int matrix_multiply(matrix &a, matrix &b, matrix &c)
{
    //LOG("begin");
    if(a.csize != b.rsize)
        return -1; 
    
    for(int i = 0; i < a.rsize; i++)
    {
        for(int j = 0; j < b.csize; j++)    
        {
            c.value[i][j] = 0;
            for(int k = 0; k < a.csize; k++)
            {
                c.value[i][j] +=  a.value[i][k]*b.value[k][j];
            }
        }
    }
    //LOG("end");
}

int print_matrix(matrix &m)
{
    //LOG("begin rowsize: " << m.rsize << " colsize: " << m.csize);
    for(int i = 0; i < m.rsize; i++)
    {
        for(int j = 0; j < m.csize; j++) 
        {
            cout << " " << m.value[i][j];
        }
        cout << "\n";
    }
    //LOG("end");
}

int generate_matrix_values(matrix &m)
{
    LOG("begin rsize: " << m.rsize << " csize: " << m.csize);
    for(int i = 0; i < m.rsize; i++)
    {
        for(int j = 0; j < m.csize; j++)    
        {
            m.value[i][j] = rand() % MATRIX_MAXVAL;
        }
    }
    print_matrix(m);
    LOG("end");
}

int generate_matrix_chain(matrix_chain &chain, int size)
{
    LOG("begin size: " << size);
    int prev_colsize = rand() % MATRIX_MAXDIM;
    int rowsize = 0, colsize = 0;
    for(int i = 0; i < size; i++)
    {
        rowsize = prev_colsize;
        colsize = rand() % MATRIX_MAXDIM;
        int **temp = new int *[rowsize];
        for(int j = 0; j < rowsize; j++)
            temp[j] = new int[colsize];
        matrix temp_m(rowsize, colsize);
        temp_m.value = temp;
        temp_m.rsize = rowsize;
        temp_m.csize = colsize;
        LOG("matrix " << i << " rsize: " << temp_m.rsize << " csize: " << temp_m.csize );
        generate_matrix_values(temp_m);
        chain.push_back(temp_m);
        prev_colsize = colsize;
    }
    LOG("end");
}

int matrix_chain_inorder(matrix_chain &chain)
{
    LOG("begin");
    matrix_chain::iterator chain_itr = chain.begin();
    matrix output = *chain_itr;
    chain_itr++;
    while(chain_itr != chain.end())
    {
        matrix a = *chain_itr;
        chain_itr++;
        matrix c(output.rsize, a.csize);
        matrix_multiply(output, a, c);
        output = c;
    }
    print_matrix(output);
    LOG("end");
}

int main()
{
   matrix_chain chain;
   int size;
   cout << "size of chain: ";
   cin >> size;
   generate_matrix_chain(chain, size);
   matrix_chain_inorder(chain);
}
