#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>

// Data structure to store symbols and their probabilities
struct Symbol
{
    char symbol;
    double probability;
};

// Function to recursively generate Shannon-Fano codes
void generateShannonFanoCodes(std::vector<Symbol> &symbols, int start, int end, std::string code)
{
    if (start == end)
    {
        std::cout << symbols[start].symbol << ": " << code << std::endl;
        return;
    }

    // Calculate total probability in the range
    double totalProbability = 0;
    for (int i = start; i <= end; ++i)
    {
        totalProbability += symbols[i].probability;
    }

    // Find the split point
    double sum = 0;
    int splitIndex = start;
    for (int i = start; i <= end; ++i)
    {
        sum += symbols[i].probability;
        if (sum >= totalProbability / 2)
        {
            splitIndex = i;
            break;
        }
    }

    // Generate codes recursively for left and right partitions
    for (int i = start; i <= end; ++i)
    {
        if (i <= splitIndex)
        {
            generateShannonFanoCodes(symbols, start, splitIndex, code + "0");
        }
        else
        {
            generateShannonFanoCodes(symbols, splitIndex + 1, end, code + "1");
        }
    }
}

int main()
{
    // Example symbols with probabilities
    std::vector<Symbol> symbols = {
        {'A', 0.2},
        {'B', 0.15},
        {'C', 0.1},
        {'D', 0.15},
        {'E', 0.2},
        {'F', 0.2}};

    // Sort symbols by probabilities in descending order
    std::sort(symbols.begin(), symbols.end(), [](const Symbol &a, const Symbol &b)
              { return a.probability > b.probability; });

    // Generate Shannon-Fano codes
    generateShannonFanoCodes(symbols, 0, symbols.size() - 1, "");

    return 0;
}
