#pragma once
// https://www.geeksforgeeks.org/cpp/huffman-coding-in-cpp/
#include <iostream>
#include <queue>
#include <unordered_map>
#include <vector>
#include <string>

using namespace std;

struct HuffmanNode {
    char letter;
    int frequency;

    HuffmanNode* left;
    HuffmanNode* right;

    HuffmanNode(char l, int f) : letter(l), frequency(f), left(nullptr), right(nullptr) {}
};

struct Compare {
    bool operator()(HuffmanNode* a, HuffmanNode* b) {
        return a->frequency > b->frequency;
    }
};

HuffmanNode* buildHuffmanTree(const vector<pair<char, int>>& frequences);

void generateHuffmanCodes(HuffmanNode* root, string code, unordered_map<char, string>& huffmanCodes);

double calculateAverageCodeLength(const vector<pair<char, int>>& frequencies, const unordered_map<char, string>& huffmanCodes);