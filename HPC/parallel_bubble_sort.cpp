#include <iostream>
#include <omp.h>
#include <ctime>
#include <iomanip>

using namespace std;

// Sequential Bubble Sort
void sequentialBubbleSort(int arr[], int n)
{
    for(int i = 0; i < n - 1; i++)
    {
        for(int j = 0; j < n - i - 1; j++)
        {
            if(arr[j] > arr[j + 1])
            {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

// Parallel Bubble Sort
void parallelBubbleSort(int arr[], int n)
{
    for(int i = 0; i < n; i++)
    {
        int first = i % 2;

        #pragma omp parallel for shared(arr, first)
        for(int j = first; j < n - 1; j += 2)
        {
            if(arr[j] > arr[j + 1])
            {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
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

    // Sequential Bubble Sort
    start = clock();

    sequentialBubbleSort(arr1, n);

    end = clock();

    double seq_time =
    double(end - start) / CLOCKS_PER_SEC;

    // Parallel Bubble Sort
    start = clock();

    parallelBubbleSort(arr2, n);

    end = clock();

    double par_time =
    double(end - start) / CLOCKS_PER_SEC;

    cout << "\nSequential Bubble Sort:\n";
    printArray(arr1, n);

    cout << "\nParallel Bubble Sort:\n";
    printArray(arr2, n);

    cout << fixed << setprecision(6);

    cout << "\nSequential Time: "
         << seq_time << " seconds";

    cout << "\nParallel Time: "
         << par_time << " seconds";

    return 0;
}