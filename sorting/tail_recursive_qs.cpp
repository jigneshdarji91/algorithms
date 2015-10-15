#include <iostream>

using namespace std;

int a[] = {55, 56, 77, 44, 22, 11, 10, 5, 87};

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
    cout << "partition p: " << p << " r: " << r << " q: " << i + 1 <<"\n";
    return (i + 1);
}
void tail_recursive_qs(int p, int r)
{
    cout << "tail_recursive_qs begin p: " << p << " r: " << r << "\n";
    while (p < r)
    {
        int q = partition(p, r);
        tail_recursive_qs(p, q-1);
        p = q+1;
    }
}
int main()
{
    cout << "main begin\n";
    tail_recursive_qs(0, (sizeof(a) - 1)/sizeof(*a));
    for(int i = 0; i < sizeof(a)/sizeof(*a); i++)
        cout << " " << a[i];
    cout << "\n";
}
