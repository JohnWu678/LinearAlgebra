#include <iostream>
#include <math.h>
#include <process.h>

using namespace std;

class cholesky
{
private:
    int i, j, k, n;
    double sum, *b, *d, *x, **a;
public:
void cholesky_input();
void cholesky_decomposition();
void cholesky_output();
~cholesky()
{
    delete []b;
    delete []d;
    delete []x;
    for(i=0; i<n; i++)
    {
        delete []a[i];
    }
    delete []a;
}
};

int main()
{
    cholesky solution;
    solution.cholesky_input();
    solution.cholesky_decomposition();
    solution.cholesky_output();

    return 0;
}

void cholesky::cholesky_input()
{
    cout << "\nInput number of equations:";
    cin >> n;
    b = new double[n];
    d = new double[n];
    x = new double[n];
    a = new double*[n];
    for(i=0; i<n; i++)
    {
        a[i] = new double[n];
    }
    for(i=0; i<n; i++)
    {
        for(j=0; j<n; j++)
        {
            cout << "\nInput a[" << i << "][" << j << "]=";
            cin >> a[i][j];
        }
    }
    for(i=0; i<n; i++)
    {
        for(j=0; j<n; j++)
        {
            if(a[i][j] != a[j][i])
            {
                cout << "\nThe matrix is not symmetric. fail..." << endl;
                exit(0);
            }
        }
    }
    for(i=0; i<n; i++)
    {
        cout << "\nInput b[" << i << "]=";
        cin >> b[i];
    }

}

void cholesky::cholesky_decomposition()
{
    for(i=0; i<n; i++)
    for(j=0; j<n; j++)
    {
        sum = a[i][j];
        for(k=0; k<=(i-1); k++)
        {
            sum -= a[i][k]*a[j][k];
        }
        if(i == j)
        {
            if(sum <= 0)
            {
                cout << "\nThe matrix is not definite. fail..." << endl;
                exit(0);
            }
            d[i] = sqrt(sum);
        }
        else
        {
            a[j][i] = sum/d[i];
        }
    }
    for(i=0; i<n; i++)
    {
        sum = b[i];
        for(k=0; k<=(i-1); k++)
        {
            sum -= a[i][k]*x[k];
        }
        x[i] = sum/d[i];
    }
    for(i=n-1; i>=0; i--)
    {
        sum = x[i];
        for(k=n-1; k>i; k--)
        {
            sum -= a[k][i]*x[k];
        }
        x[i] = sum/d[i];
    }
}

void cholesky::cholesky_output()
{
    cout << "\nResult: " << endl;
    for(i=0; i<n; i++)
    {
        cout << "\nx[" << i << "]=" << x[i] << endl;
    }
}