#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <cmath>
#include <limits>

using namespace std;

struct Point
{
    int x, y;
};

// Function to calculate the area of a triangle given three points
double triangleArea(const Point &p1, const Point &p2, const Point &p3)
{
    return abs((p1.x * (p2.y - p3.y) + p2.x * (p3.y - p1.y) + p3.x * (p1.y - p2.y)) / 2.0);
}

// Function to parse a CSV line and extract points for a polygon
vector<Point> parseCSVLine(const string &line)
{
    vector<Point> polygon;
    stringstream ss(line);
    int size;
    char comma;
    ss >> size >> comma; // Read size of the polygon
    for (int i = 0; i < size; ++i)
    {
        Point vertex;
        ss >> vertex.x >> comma >> vertex.y >> comma; // Read x and y coordinates
        polygon.push_back(vertex);
    }
    return polygon;
}

// Function to find the minimum area triangulation of a convex polygon using dynamic programming
double minTriangulationArea(const vector<Point> &polygon)
{
    int n = polygon.size();
    // Create a 2D table to store the minimum area triangulation of sub-polygons
    vector<vector<double>> dp(n, vector<double>(n, 0));

    // Base case: triangles have zero area
    for (int i = 0; i < n; ++i)
    {
        dp[i][(i + 1) % n] = 0;
    }

    // Loop through the chain length (i.e., number of vertices in the sub-polygon)
    for (int chainLen = 3; chainLen <= n; ++chainLen)
    {
        for (int i = 0; i < n; ++i)
        {
            int j = (i + chainLen - 1) % n; // Get the end vertex index

            dp[i][j] = numeric_limits<double>::max();

            // Try all cuts to find the minimum triangulation
            for (int k = i + 1; k < i + chainLen - 1; ++k)
            {
                dp[i][j] = min(dp[i][j], dp[i][k % n] + dp[k % n][j] + triangleArea(polygon[i], polygon[k % n], polygon[j]));
            }
        }
    }

    return dp[0][n - 1]; // Return the minimum area triangulation of the entire polygon
}

int main()
{
    ifstream inFile("convex_polygons.csv"); // Open the CSV file
    if (!inFile)
    {
        cerr << "Failed to open the input file!" << endl;
        return 1;
    }

    // Write the generated dataset to a CSV file
    ofstream outFile("convex_polygons_mcm.csv");
    if (!outFile)
    {
        cerr << "Failed to open the output file!" << endl;
        return 1;
    }

    string line;
    while (getline(inFile, line))
    {
        vector<Point> polygon = parseCSVLine(line);
        double minArea = minTriangulationArea(polygon);
        outFile << polygon.size() << "," << minArea << endl;
        cout << "Minimum area of triangulation for polygon: " << minArea << endl;
    }

    inFile.close();
    outFile.close();

    return 0;
}
