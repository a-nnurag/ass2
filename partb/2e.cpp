#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cmath>

// Function to perform Run-Length Encoding (RLE)
std::string runLengthEncode(const std::string &text)
{
    std::string encodedText;
    int count = 1;
    for (size_t i = 1; i < text.length(); ++i)
    {
        if (text[i] == text[i - 1])
        {
            count++;
        }
        else
        {
            encodedText += text[i - 1] + std::to_string(count);
            count = 1;
        }
    }
    encodedText += text.back() + std::to_string(count);
    return encodedText;
}

// Function to calculate compression ratio
double compressionRatio(const std::string &original, const std::string &compressed)
{
    return static_cast<double>(original.length()) / compressed.length();
}

int main()
{
    // Read text from file
    std::ifstream inFile("input.txt");
    if (!inFile)
    {
        std::cerr << "Failed to open input file!" << std::endl;
        return 1;
    }
    std::string originalText((std::istreambuf_iterator<char>(inFile)), std::istreambuf_iterator<char>());
    inFile.close();

    // Perform Run-Length Encoding (RLE)
    std::string rleEncodedText = runLengthEncode(originalText);

    // Perform Huffman encoding (implementation required)
    std::string huffmanEncodedText; // Implement Huffman encoding

    // Calculate compression ratios
    double rleCompressionRatio = compressionRatio(originalText, rleEncodedText);
    double huffmanCompressionRatio = compressionRatio(originalText, huffmanEncodedText);

    // Output compression ratios
    std::cout << "Compression Ratio (RLE): " << rleCompressionRatio << std::endl;
    std::cout << "Compression Ratio (Huffman): " << huffmanCompressionRatio << std::endl;

    return 0;
}
