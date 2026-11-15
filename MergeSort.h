#pragma once
#include <vector>
#include <iostream>
// Class Slides
using namespace std;

extern int recursiveCalls;

void merge(vector<int>& arr, int l, int m, int r);
void mergeSort(vector<int>& arr, int l, int r);