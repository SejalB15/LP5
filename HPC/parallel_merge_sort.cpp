#include <iostream>
#include <omp.h>
#include <ctime>
#include <iomanip>

using namespace std;

// Merge Function
void merge(int arr[], int l, int m, int r)
{
    int n1 = m - l + 1;
    int n2 = r - m;

    int L[n1], R[n2];

    for(int i = 0; i < n1; i++)
        L[i] = arr[l + i];

    for(int j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];

    int i = 0, j = 0, k = l;

    while(i < n1 && j < n2)
    {
        if(L[i] <= R[j])
        {
            arr[k] = L[i];
            i++;
        }
        else
        {
            arr[k] = R[j];
            j++;
        }

        k++;
    }

    while(i < n1)
    {
        arr[k] = L[i];
        i++;
        k++;
    }

    while(j < n2)
    {
        arr[k] = R[j];
        j++;
        k++;
    }
}

// Sequential Merge Sort
void sequentialMergeSort(int arr[], int l, int r)
{
    if(l < r)
    {
        int m = l + (r - l) / 2;

        sequentialMergeSort(arr, l, m);
        sequentialMergeSort(arr, m + 1, r);

        merge(arr, l, m, r);
    }
}

// Parallel Merge Sort
void parallelMergeSort(int arr[], int l, int r)
{
    if(l < r)
    {
        int m = l + (r - l) / 2;

        #pragma omp parallel sections
        {
            #pragma omp section
            {
                parallelMergeSort(arr, l, m);
            }

            #pragma omp section
            {
                parallelMergeSort(arr, m + 1, r);
            }
        }

        merge(arr, l, m, r);
    }
}

// Print Array
void printArray(int arr[], int n)
{
    for(int i = 0; i < n; i++)
    {
        cout << arr[i] << " ";
    }

    cout << endl;
}

int main()
{
    int n;

    cout << "Enter number of elements: ";
    cin >> n;

    int arr1[n], arr2[n];

    cout << "Enter elements:\n";

    for(int i = 0; i < n; i++)
    {
        cin >> arr1[i];
        arr2[i] = arr1[i];
    }

    clock_t start, end;

    // Sequential Merge Sort
    start = clock();

    sequentialMergeSort(arr1, 0, n - 1);

    end = clock();

    double seq_time =
    double(end - start) / CLOCKS_PER_SEC;

    // Parallel Merge Sort
    start = clock();

    parallelMergeSort(arr2, 0, n - 1);

    end = clock();

    double par_time =
    double(end - start) / CLOCKS_PER_SEC;

    cout << "\nSequential Merge Sort:\n";
    printArray(arr1, n);

    cout << "\nParallel Merge Sort:\n";
    printArray(arr2, n);

    cout << fixed << setprecision(6);

    cout << "\nSequential Time: "
         << seq_time << " seconds";

    cout << "\nParallel Time: "
         << par_time << " seconds";

    return 0;
}