#include "MergeSort.h"

int recursiveCalls = 0;

void merge(vector<int>& arr, int l, int m, int r) {
    vector<int> left(arr.begin() + l, arr.begin() + m + 1);
    vector<int> right(arr.begin() + m + 1, arr.begin() + r + 1);

    int i = 0, j = 0, k = l;
    
    while (i < left.size() && j < right.size()) {
        if (left[i] <= right[j]) arr[k++] = left[i++];
        else arr[k++] = right[j++];
    }

    while (i < left.size()) 
        arr[k++] = left[i++];
        
    while (j < right.size()) 
        arr[k++] = right[j++];
}

void mergeSort(vector<int>& arr, int l, int r) {
    recursiveCalls++;

    if (l >= r) return;

    int m = l + (r - l) / 2;

    // sort each half before merging them back together
    mergeSort(arr, l, m);
    mergeSort(arr, m+1, r);
    
    merge(arr, l, m, r);
}