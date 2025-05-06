#include<iostream>
#include<stdlib.h>
#include<omp.h>
using namespace std;

void bubble_parallel(int *, int);
void bubble_sequential(int *, int);
void swap(int &, int &);

void bubble_parallel(int *a, int n)
{
    for (int i = 0; i < n; i++)
    {
        int first = i % 2;

        #pragma omp parallel for shared(a, first)
        for (int j = first; j < n - 1; j += 2)
        {
            if (a[j] > a[j + 1])
            {
                swap(a[j], a[j + 1]);
            }
        }
    }
}

void bubble_sequential(int *a, int n)
{
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            if (a[j] > a[j + 1])
            {
                swap(a[j], a[j + 1]);
            }
        }
    }
}

void swap(int &a, int &b)
{
    int temp = a;
    a = b;
    b = temp;
}

int main()
{
    int *a, *b, n;
    cout << "\nEnter total number of elements => ";
    cin >> n;

    a = new int[n];
    b = new int[n];

    cout << "\nEnter elements => ";
    for (int i = 0; i < n; i++)
    {
        cin >> a[i];
        b[i] = a[i]; // copy for parallel sort
    }

    double start_seq = omp_get_wtime();
    bubble_sequential(a, n);
    double end_seq = omp_get_wtime();

    double start_par = omp_get_wtime();
    bubble_parallel(b, n);
    double end_par = omp_get_wtime();

    cout << "\nSorted array using Sequential Bubble Sort => ";
    for (int i = 0; i < n; i++)
        cout << a[i] << " ";

    cout << "\nSorted array using Parallel Bubble Sort => ";
    for (int i = 0; i < n; i++)
        cout << b[i] << " ";

    cout << "\n\nTime taken by Sequential Bubble Sort: " << end_seq - start_seq << " seconds";
    cout << "\nTime taken by Parallel Bubble Sort:   " << end_par - start_par << " seconds\n";

    delete[] a;
    delete[] b;

    return 0;
}
