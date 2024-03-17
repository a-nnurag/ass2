#include <iostream>
#include <string>
#include <unordered_map>

using namespace std;

// Example Huffman encoded data
string encodedData = "100101010001011101101110";

// Huffman decoding function
void huffmanDecode(const string &data, const unordered_map<string, char> &huffmanTable)
{
    string decodedText;
    string currentCode;

    for (char bit : data)
    {
        currentCode += bit;
        if (huffmanTable.find(currentCode) != huffmanTable.end())
        {
            decodedText += huffmanTable.at(currentCode);
            currentCode.clear();
        }
    }

    cout << "Decoded Text: " << decodedText << endl;
}

int main()
{
    // Example Huffman table
    unordered_map<string, char> huffmanTable = {
        {"00", 'A'},
        {"01", 'B'},
        {"10", 'C'},
        {"11", 'D'}};

    // Decode the example encoded data
    huffmanDecode(encodedData, huffmanTable);

    return 0;
}
