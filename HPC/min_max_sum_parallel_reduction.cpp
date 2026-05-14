#include <iostream>
#include <omp.h>
#include <climits>
#include <iomanip>

using namespace std;

// Minimum using Parallel Reduction
void min_reduction(int arr[], int n)
{
    int min_value = INT_MAX;

    #pragma omp parallel for reduction(min:min_value)
    for(int i = 0; i < n; i++)
    {
        if(arr[i] < min_value)
        {
            min_value = arr[i];
        }
    }

    cout << "\nMinimum Value = " << min_value;
}

// Maximum using Parallel Reduction
void max_reduction(int arr[], int n)
{
    int max_value = INT_MIN;

    #pragma omp parallel for reduction(max:max_value)
    for(int i = 0; i < n; i++)
    {
        if(arr[i] > max_value)
        {
            max_value = arr[i];
        }
    }

    cout << "\nMaximum Value = " << max_value;
}

// Sum using Parallel Reduction
void sum_reduction(int arr[], int n)
{
    int sum = 0;

    #pragma omp parallel for reduction(+:sum)
    for(int i = 0; i < n; i++)
    {
        sum += arr[i];
    }

    cout << "\nSum = " << sum;
}

// Average using Parallel Reduction
void average_reduction(int arr[], int n)
{
    int sum = 0;

    #pragma omp parallel for reduction(+:sum)
    for(int i = 0; i < n; i++)
    {
        sum += arr[i];
    }

    double average = (double)sum / n;

    cout << fixed << setprecision(2);

    cout << "\nAverage = " << average;
}

int main()
{
    int n;

    cout << "Enter total number of elements: ";
    cin >> n;

    int arr[n];

    cout << "Enter elements:\n";

    for(int i = 0; i < n; i++)
    {
        cin >> arr[i];
    }

    min_reduction(arr, n);

    max_reduction(arr, n);

    sum_reduction(arr, n);

    average_reduction(arr, n);

    return 0;
}