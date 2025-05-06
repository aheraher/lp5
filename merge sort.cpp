#include <iostream>
#include <stdlib.h>
#include <omp.h>
using namespace std;

void merge(int a[], int i1, int j1, int i2, int j2) {
    int* temp = new int[j2 - i1 + 1];
    int i = i1, j = i2, k = 0;

    while (i <= j1 && j <= j2) {
        if (a[i] < a[j])
            temp[k++] = a[i++];
        else
            temp[k++] = a[j++];
    }

    while (i <= j1) temp[k++] = a[i++];
    while (j <= j2) temp[k++] = a[j++];

    for (i = i1, k = 0; i <= j2; i++, k++)
        a[i] = temp[k];

    delete[] temp;
}

void mergesort_parallel(int a[], int i, int j) {
    if (i < j) {
        int mid = (i + j) / 2;

        #pragma omp parallel sections
        {
            #pragma omp section
            {
                mergesort_parallel(a, i, mid);
            }

            #pragma omp section
            {
                mergesort_parallel(a, mid + 1, j);
            }
        }

        merge(a, i, mid, mid + 1, j);
    }
}

void mergesort_sequential(int a[], int i, int j) {
    if (i < j) {
        int mid = (i + j) / 2;
        mergesort_sequential(a, i, mid);
        mergesort_sequential(a, mid + 1, j);
        merge(a, i, mid, mid + 1, j);
    }
}

int main() {
    int *a, *b, n;
    cout << "\nEnter total number of elements => ";
    cin >> n;
    a = new int[n];
    b = new int[n];

    cout << "\nEnter elements => ";
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        b[i] = a[i]; // Copy for parallel sort
    }

    double start_seq = omp_get_wtime();
    mergesort_sequential(a, 0, n - 1);
    double end_seq = omp_get_wtime();

    double start_par = omp_get_wtime();
    mergesort_parallel(b, 0, n - 1);
    double end_par = omp_get_wtime();

    cout << "\nSorted array using Sequential Merge Sort => ";
    for (int i = 0; i < n; i++)
        cout << a[i] << " ";

    cout << "\nSorted array using Parallel Merge Sort => ";
    for (int i = 0; i < n; i++)
        cout << b[i] << " ";

    cout << "\n\nTime taken by Sequential Merge Sort: " << end_seq - start_seq << " seconds";
    cout << "\nTime taken by Parallel Merge Sort:   " << end_par - start_par << " seconds\n";

    delete[] a;
    delete[] b;

    return 0;
}
// g++ mergesort.cpp -fopenmp -o mergesort
