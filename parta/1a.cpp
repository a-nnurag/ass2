#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;

struct Point
{
    int x, y;
};

// Function to generate a convex polygon with a given number of vertices
vector<Point> generateConvexPolygon(int numVertices)
{
    vector<Point> polygon;
    srand(time(0));

    // Generate random vertices
    for (int i = 0; i < numVertices; ++i)
    {
        Point vertex;
        vertex.x = rand() % 100; // Adjust the range as needed
        vertex.y = rand() % 100;
        polygon.push_back(vertex);
    }

    // Sort the vertices in clockwise order
    // This step is important to ensure convexity
    // Sorting logic can be added here

    return polygon;
}

int main()
{
    // Prepare dataset
    vector<vector<Point>> dataset;
    int numPolygons = 100; // Change the number of polygons as needed

    // Generate polygons with increasing number of vertices
    for (int i = 3; i <= numPolygons; ++i)
    { // Starting from triangle
        dataset.push_back(generateConvexPolygon(i));
    }

    // Write the generated dataset to a CSV file
    ofstream outFile("convex_polygons.csv");
    if (!outFile)
    {
        cerr << "Failed to open the output file!" << endl;
        return 1;
    }

    // Write polygons to the file
    for (int i = 0; i < dataset.size(); ++i)
    {
        outFile << dataset[i].size() << ",";
        for (const auto &vertex : dataset[i])
        {
            outFile << vertex.x << "," << vertex.y << ",";
        }
        outFile << endl;
    }

    cout << "Data has been written to convex_polygons.csv" << endl;
    outFile.close();

    return 0;
}
