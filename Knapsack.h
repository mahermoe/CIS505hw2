#pragma once
// Class Slides
#include <iostream>
#include <vector>
#include <string>

using namespace std;

struct Item {
    string name;
    int value;
    int weight;
};

int knapTab(int capacity, const vector<Item>& items, vector<vector<int>>& dp);
vector<string> knapItems(const vector<Item>& items, const vector<vector<int>>& dp, int capacity);