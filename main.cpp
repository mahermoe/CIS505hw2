#include "MergeSort.h"
#include "Huffman.h"
#include "Knapsack.h"

#include <fstream>
#include <algorithm>
#include <chrono>
#include <iomanip>
#include <random>

int main() {

    // For A. Merge Sort ------------------------------------------------------------------------------------------------------
    ifstream inputFile("A_input_numbers.txt");

    if (!inputFile) {
        cout << "Error opening input file." << endl;
        return 1;
    }

    vector<int> Anumbers;
    int number;

    while (inputFile >> number) {
        Anumbers.push_back(number);
    }

    inputFile.close();

    vector<int> Aoriginal = Anumbers;
    vector<int> AbuiltIn = Anumbers;
    vector<int> testSizes = {1000, 5000, 10000};

    // https://ikriv.com/blog/?p=5213
    // https://www.geeksforgeeks.org/cpp/measure-execution-time-function-cpp/ 
    // https://stackoverflow.com/questions/22387586/measuring-execution-time-of-a-function-in-c

    // Measure execution time of mergeSort
    auto start = chrono::high_resolution_clock::now();
    mergeSort(Anumbers, 0, Anumbers.size() - 1);
    auto end = chrono::high_resolution_clock::now();
    double executionTime = chrono::duration<double>(end - start).count();
    
    // Verify that the sorting is correct by comparing with built-in sort
    sort(AbuiltIn.begin(), AbuiltIn.end());
    bool correct = (Anumbers == AbuiltIn);

    ofstream outputFile("A_output.txt");

    outputFile << "Original List: ";
    for (int n : Aoriginal) {
        outputFile << n << " ";
    }

    outputFile << endl << "Sorted List: ";
    for (int n : Anumbers) {
        outputFile << n << " ";
    }

    outputFile << endl << "Total Recursive Calls: " << recursiveCalls << endl;
    outputFile << fixed << setprecision(8);
    outputFile << "Execution Time: " << executionTime << " seconds" << endl;
    outputFile << "Sorting Correct: " << (correct ? "Yes" : "No") << endl;
    outputFile << "Testing with Various Sizes: " << endl << "==============================" << endl;

    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dist(1, 1000000);

    for (int size : testSizes) {
        vector<int> testData;

        for (int i = 0; i < size; i++){
            testData.push_back(dist(gen));
        }

        recursiveCalls = 0; // reset recursive calls for each test

        auto start = chrono::high_resolution_clock::now();
        mergeSort(testData, 0, testData.size() - 1);
        auto end = chrono::high_resolution_clock::now();
        double executionTime = chrono::duration<double>(end - start).count();

        outputFile << fixed << setprecision(8);
        outputFile << "Size: " << size << ", Recursive Calls: " << recursiveCalls << ", Execution Time: " << executionTime << " seconds" << endl;
    }

    outputFile.close();

    cout << "A. DONE" << endl;

    // For B. Huffman Coding --------------------------------------------------------------------------------------------------
    ifstream inputFileB("B_input_numbers.txt");

    if (!inputFileB) {
        cout << "Error opening input file b." << endl;
        return 1;
    }
    
    vector<pair<char, int>> frequencies;
    char letter;
    int frequency;

    // Fill vector with input
    while (inputFileB >> letter >> frequency) {
        frequencies.push_back(make_pair(letter, frequency));
    }

    inputFileB.close();

    HuffmanNode* root = buildHuffmanTree(frequencies);
    
    unordered_map<char, string> huffmanCodes;
    generateHuffmanCodes(root, "", huffmanCodes);

    // Post output of huffman tree results
    ofstream outputFileB("B_output.txt");
    outputFileB << "Letter | Frequency | Huffman Code" << endl;
    outputFileB << "----------------------------------" << endl;
    
    for (const auto& item : frequencies) {
        outputFileB << item.first << "        " << item.second << "          " << huffmanCodes[item.first] << endl;
    }

    outputFileB << fixed << setprecision(2);
    outputFileB << endl << "Average Code Length: " << calculateAverageCodeLength(frequencies, huffmanCodes) << endl;
    outputFileB.close();

    cout << "B. DONE" << endl;

    // For C. 0/1 Knapsack Problem --------------------------------------------------------------------------------------------
    ifstream inputFileC("C_input_numbers.txt");

    if (!inputFileC) {
        cout << "Error opening input file c." << endl;
        return 1;
    }

    string capacityLabel;
    string itemsLabel;
    int capacity;
    inputFileC >> capacityLabel >> capacity;
    inputFileC >> itemsLabel;

    vector<Item> items;
    Item item;

    while (inputFileC >> item.name >> item.value >> item.weight) {
        items.push_back(item);
    }
    inputFileC.close();

    vector<vector<int>> dp;
    int maxValue = knapTab(capacity, items, dp);
    vector<string> selectedItems = knapItems(items, dp, capacity);

    ofstream outputFileC("C_output.txt");
    outputFileC << "Dynamic Programming Table: " << endl << "       ";
    for (int w = 0; w <= capacity; w++) {
        outputFileC << w << " ";
    }
    outputFileC << endl;

    for (int i = 1; i < dp.size(); i++) {
        outputFileC << items[i-1].name << ": ";

        for (int w = 0; w <= capacity; w++) {
            outputFileC << dp[i][w] << " ";
        }
        outputFileC << endl;
    }

    int totalWeight = 0;

    outputFileC << endl << "Maximum Value: " << maxValue << endl << "Selected Items: ";

    for (string name : selectedItems){
        outputFileC << name << " ";
        // calc weight of chosen item
        for (const Item& item : items) {
            if (item.name == name) {
                totalWeight += item.weight;
                break;
            }
        }
    }
    
    outputFileC << endl << "Total Weight: " << totalWeight << endl;
    outputFileC.close();

    cout << "C. DONE" << endl;

    return 0;
}