#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <chrono>
#define endl '\n'
using namespace std;
using namespace chrono;

// this function to generate random data
vector<int> generateRandomData(int size) {
    vector<int> data(size);
    for (int i = 0; i < size; i++) {
        data[i] = rand();
    }
    return data;
}

// function to generate sorted data
vector<int> generateSortedData(int size) {
    vector<int> data(size);
    for (int i = 0; i < size; i++) {
        data[i] = i;
    }
    return data;
}

// Function to generate reverse sorted data
vector<int> generateReverseSortedData(int size) {
    vector<int> data(size);
    for (int i = 0; i < size; i++) {
        data[i] = size - i - 1;
    }
    return data;
}

// Insertion Sort
void insertionSort(vector<int>& data) {
    int n = data.size();
    for (int i = 1; i < n; i++) {
        int key = data[i];
        int j = i - 1;
        while (j >= 0 && data[j] > key) {
            data[j + 1] = data[j];
            j--;
        }
        data[j + 1] = key;
    }
}

// Merge Sort
void merge(vector<int>& data, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    vector<int> L(n1);
    vector<int> R(n2);

    for (int i = 0; i < n1; i++)
        L[i] = data[left + i];
    for (int j = 0; j < n2; j++)
        R[j] = data[mid + 1 + j];

    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            data[k] = L[i];
            i++;
        }
        else {
            data[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        data[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        data[k] = R[j];
        j++;
        k++;
    }
}

void mergeSort(vector<int>& data, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSort(data, left, mid);
        mergeSort(data, mid + 1, right);
        merge(data, left, mid, right);
    }
}

// Quick Sort
int partition(vector<int>& data, int low, int high) {
    int pivot = data[high];
    int i = (low - 1);
    for (int j = low; j <= high - 1; j++) {
        if (data[j] < pivot) {
            i++;
            swap(data[i], data[j]);
        }
    }
    swap(data[i + 1], data[high]);
    return (i + 1);
}

void quickSort(vector<int>& data, int low, int high) {
    while (low < high) {
        int pi = partition(data, low, high);

        if (pi - low < high - pi) {
            quickSort(data, low, pi - 1);
            low = pi + 1;
        }
        else {
            quickSort(data, pi + 1, high);
            high = pi - 1;
        }
    }
}

// Main Function
int main() {
    bool flag = true;
    while (flag) {
        srand(time(0));
        int n;
        cout << "Enter the size of set: ";
        cin >> n;

        int choice;
        cout << "Select the type of input data: \n1. Random data\n2. Sorted data\n3. Reverse sorted data  " << endl;

        cin >> choice;

        vector<int> data;
        switch (choice) {
        case 1:
            data = generateRandomData(n);
            break;
        case 2:
            data = generateSortedData(n);
            break;
        case 3:
            data = generateReverseSortedData(n);
            break;
        default:
            cout << "Invalid choice!";
            return 1;
        }

        int algo_choice;
        cout << "Select the sorting algorithm: \n";
        cout << "1. Insertion Sort\n";
        cout << "2. Merge Sort\n";
        cout << "3. Quick Sort\n";
        cin >> algo_choice;

        auto start = high_resolution_clock::now();

        switch (algo_choice) {
        case 1:
            insertionSort(data);
            break;
        case 2:
            mergeSort(data, 0, data.size() - 1);
            break;
        case 3:
            quickSort(data, 0, data.size() - 1);
            break;
        default:
            cout << "Invalid choice!";
            return 1;
        }

        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<milliseconds>(stop - start);

        cout << "Time taken to sort the data: " << duration.count() << " milliseconds\n";
        cout << "If you want to complete programm enter 1 if no enter 0" << endl;
        char ch_com;
        cin >> ch_com;
        if (ch_com == '1') {
            flag = true;
        }
        else {
            flag = false;
        }
    }



    /*  if you want to print the time of execution as a microseconds , you can change the milliseconds to microseconds in this
    * equation :   auto duration = duration_cast<microseconds>(stop - start);
    *
    * and the same thing for the secound : auto duration = duration_cast<secounds>(stop - start);
    */
    return 0;
}
