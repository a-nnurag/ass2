#include <iostream>
#include <queue>
#include <unordered_map>
#include <string>

// Node structure for Huffman tree
struct HuffmanNode
{
    char data;
    int frequency;
    HuffmanNode *left;
    HuffmanNode *right;

    HuffmanNode(char data, int frequency) : data(data), frequency(frequency), left(nullptr), right(nullptr) {}
};

// Comparison functor for priority queue
struct Compare
{
    bool operator()(HuffmanNode *a, HuffmanNode *b)
    {
        return a->frequency > b->frequency;
    }
};

// Function to build Huffman tree and return root node
HuffmanNode *buildHuffmanTree(std::unordered_map<char, int> &frequencies)
{
    std::priority_queue<HuffmanNode *, std::vector<HuffmanNode *>, Compare> pq;

    // Create leaf nodes for each character and add to priority queue
    for (auto &entry : frequencies)
    {
        pq.push(new HuffmanNode(entry.first, entry.second));
    }

    // Build Huffman tree
    while (pq.size() > 1)
    {
        HuffmanNode *left = pq.top();
        pq.pop();
        HuffmanNode *right = pq.top();
        pq.pop();

        HuffmanNode *newNode = new HuffmanNode('\0', left->frequency + right->frequency);
        newNode->left = left;
        newNode->right = right;
        pq.push(newNode);
    }

    // Return root node of Huffman tree
    return pq.top();
}

// Function to generate Huffman codes recursively
void generateHuffmanCodes(HuffmanNode *root, std::string code, std::unordered_map<char, std::string> &huffmanCodes)
{
    if (root == nullptr)
    {
        return;
    }

    if (root->data != '\0')
    {
        huffmanCodes[root->data] = code;
    }

    generateHuffmanCodes(root->left, code + "0", huffmanCodes);
    generateHuffmanCodes(root->right, code + "1", huffmanCodes);
}

// Function to perform Huffman encoding
std::string huffmanEncode(const std::string &text)
{
    std::unordered_map<char, int> frequencies;

    // Count frequencies of characters in the text
    for (char c : text)
    {
        frequencies[c]++;
    }

    // Build Huffman tree
    HuffmanNode *root = buildHuffmanTree(frequencies);

    // Generate Huffman codes
    std::unordered_map<char, std::string> huffmanCodes;
    generateHuffmanCodes(root, "", huffmanCodes);

    // Encode text using Huffman codes
    std::string encodedText;
    for (char c : text)
    {
        encodedText += huffmanCodes[c];
    }

    return encodedText;
}

int main()
{
    std::string text = "this is a test text to encode using Huffman encoding";
    std::string encodedText = huffmanEncode(text);

    std::cout << "Original Text: " << text << std::endl;
    std::cout << "Encoded Text: " << encodedText << std::endl;

    return 0;
}
