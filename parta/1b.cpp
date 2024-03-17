#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <cmath>
#include <bits/stdc++.h>

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

// Function to find the minimum area triangulation of a convex polygon using brute force
double minTriangulationArea(const vector<Point> &polygon)
{
    int n = polygon.size();
    double minArea = INT_MAX;

    // Iterate through all possible diagonals
    for (int i = 1; i < n - 1; ++i)
    {
        for (int j = i + 1; j < n; ++j)
        {
            double area = triangleArea(polygon[0], polygon[i], polygon[j]);

            // Calculate remaining areas recursively
            for (int k = 1; k < n - 1; ++k)
            {
                area += triangleArea(polygon[i], polygon[j], polygon[(i + k) % n]);
            }
            if (area < minArea)
            {
                minArea = area;
            }
        }
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

    ofstream outFile("convex_polygons_solution.csv"); // Open the CSV file to write data in
    if (!outFile)
    {
        cerr << "Failed to open the input file!" << endl;
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
