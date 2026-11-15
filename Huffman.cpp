#include "Huffman.h"

HuffmanNode* buildHuffmanTree(const vector<pair<char, int>>& frequencies) {
    priority_queue<HuffmanNode*, vector<HuffmanNode*>, Compare> pq;

    for(const auto& item : frequencies) {
        pq.push(new HuffmanNode(item.first, item.second));
    }

    while(pq.size() > 1){
        // combine two nodes with smallest frequencies into a new node and push it back to priority queue
        HuffmanNode* left = pq.top(); pq.pop();
        HuffmanNode* right = pq.top(); pq.pop();

        HuffmanNode* merged = new HuffmanNode('\0', left->frequency + right->frequency);
        merged->left = left;
        merged->right = right;

        pq.push(merged);
    }

    return pq.top();
}

void generateHuffmanCodes(HuffmanNode* root, string code, unordered_map<char, string>& huffmanCodes) {
    if (!root) return;

    if (!root->left && !root->right) {
        // if node is a leaf, assign the accumlated code to the letter
        huffmanCodes[root->letter] = code;
    }

    generateHuffmanCodes(root->left, code + "0", huffmanCodes);
    generateHuffmanCodes(root->right, code + "1", huffmanCodes);
}

double calculateAverageCodeLength(const vector<pair<char, int>>& frequencies, const unordered_map<char, string>& huffmanCodes) {
    int totalFrequency = 0;
    int weightedCodeLength = 0;

    // weight each code length by multiplying it by the frequency of its letter, then sum products and divide by total frequency
    for (const auto& item : frequencies) {
        totalFrequency += item.second;
        weightedCodeLength += item.second * huffmanCodes.at(item.first).length();
    }

    return static_cast<double>(weightedCodeLength) / totalFrequency;
}