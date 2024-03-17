#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <cmath>
#include <algorithm>

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

// Function to find the minimum area triangulation of a convex polygon using a greedy strategy
double minTriangulationAreaGreedy(const vector<Point> &polygon)
{
    int n = polygon.size();
    double minArea = 0.0;

    // Iterate through all vertices and form non-intersecting diagonals in sorted order
    for (int i = 1; i < n - 1; ++i)
    {
        minArea += triangleArea(polygon[0], polygon[i], polygon[i + 1]);
    }

    return minArea;
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
    ofstream outFile("convex_polygons_greedy.csv");
    if (!outFile)
    {
        cerr << "Failed to open the output file!" << endl;
        return 1;
    }

    string line;
    while (getline(inFile, line))
    {
        vector<Point> polygon = parseCSVLine(line);
        double minArea = minTriangulationAreaGreedy(polygon);
        outFile << polygon.size() << "," << minArea << endl;
        cout << "Minimum area of triangulation for polygon: " << minArea << endl;
    }

    inFile.close();
    outFile.close();

    return 0;
}
