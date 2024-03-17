#include <iostream>
#include <fstream>
#include <queue>
#include <unordered_map>
#include <vector>

using namespace std;

// Node structure for Huffman tree
struct Node
{
    char data;
    int frequency;
    Node *left;
    Node *right;

    Node(char data, int frequency) : data(data), frequency(frequency), left(nullptr), right(nullptr) {}

    // Comparison operator for priority queue
    bool operator>(const Node &other) const
    {
        return frequency > other.frequency;
    }
};

// Function to construct Huffman tree
Node *buildHuffmanTree(const unordered_map<char, int> &frequencies)
{
    // Priority queue to store nodes
    priority_queue<Node, vector<Node>, greater<Node>> pq;

    // Create leaf nodes for each character
    for (const auto &pair : frequencies)
    {
        pq.push(Node(pair.first, pair.second));
    }

    // Build Huffman tree
    while (pq.size() > 1)
    {
        Node *left = new Node(pq.top().data, pq.top().frequency);
        pq.pop();
        Node *right = new Node(pq.top().data, pq.top().frequency);
        pq.pop();

        Node *parent = new Node('\0', left->frequency + right->frequency);
        parent->left = left;
        parent->right = right;

        pq.push(*parent);
    }

    return new Node(pq.top().data, pq.top().frequency);
}

// Function to build Huffman codes
void buildHuffmanCodes(Node *root, const string &code, unordered_map<char, string> &codes)
{
    if (root == nullptr)
    {
        return;
    }

    if (root->data != '\0')
    {
        codes[root->data] = code;
    }

    buildHuffmanCodes(root->left, code + "0", codes);
    buildHuffmanCodes(root->right, code + "1", codes);
}

// Function to encode text using Huffman codes
string encodeText(const string &text, const unordered_map<char, string> &codes)
{
    string encodedText;
    for (char c : text)
    {
        encodedText += codes.at(c);
    }
    return encodedText;
}

// Function to decode text using Huffman tree
string decodeText(const string &encodedText, Node *root)
{
    string decodedText;
    Node *current = root;
    for (char bit : encodedText)
    {
        if (bit == '0')
        {
            current = current->left;
        }
        else
        {
            current = current->right;
        }
        if (current->left == nullptr && current->right == nullptr)
        {
            decodedText += current->data;
            current = root;
        }
    }
    return decodedText;
}

int main()
{
    // Read text from file
    ifstream inFile("input.txt");
    if (!inFile)
    {
        cerr << "Failed to open input file!" << endl;
        return 1;
    }

    string text((istreambuf_iterator<char>(inFile)), istreambuf_iterator<char>());
    inFile.close();

    // Calculate character frequencies
    unordered_map<char, int> frequencies;
    for (char c : text)
    {
        frequencies[c]++;
    }

    // Build Huffman tree
    Node *root = buildHuffmanTree(frequencies);

    // Build Huffman codes
    unordered_map<char, string> codes;
    buildHuffmanCodes(root, "", codes);

    // Encode text using Huffman codes
    string encodedText = encodeText(text, codes);

    // Write encoded text to file
    ofstream outFile("encoded.txt");
    if (!outFile)
    {
        cerr << "Failed to open output file!" << endl;
        return 1;
    }
    outFile << encodedText;
    outFile.close();

    // Decode encoded text using Huffman tree
    string decodedText = decodeText(encodedText, root);

    // Write decoded text to file for verification
    ofstream decodedFile("decoded.txt");
    if (!decodedFile)
    {
        cerr << "Failed to open decoded file!" << endl;
        return 1;
    }
    decodedFile << decodedText;
    decodedFile.close();

    // Clean up memory
    delete root;

    return 0;
}
