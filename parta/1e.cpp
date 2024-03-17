#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <cmath>
#include <bits/stdc++.h>

using namespace std;

// Function to parse a CSV line and extract points for a polygon
// pair<double, double> parseCSVLine(const string &line)
// {
//     pair<double, double> polygon;
//     stringstream ss(line);
//     int size;
//     char comma;
//     ss >> size >> comma; // Read size of the polygon
//     for (int i = 0; i < size; ++i)
//     {
//         double a;
//         double b;
//         ss >> polygon.first >> comma >> polygon.second >> comma; // Read x and y coordinates
//     }
//     return polygon;
// }

pair<int, double> parseCSVLine(const string line)
{
    pair<int, double> data;
    stringstream ss(line);
    char comma;
    ss >> data.first >> comma >> data.second; // Read size and minimum area separated by a comma
    return data;
}

int main()
{
    ifstream inFile1("convex_polygons_mcm.csv"); // Open the CSV file
    if (!inFile1)
    {
        cerr << "Failed to open the input file1 !" << endl;
        return 1;
    }

    ifstream inFile2("convex_polygons_greedy.csv"); // Open the CSV file
    if (!inFile2)
    {
        cerr << "Failed to open the input file1 !" << endl;
        return 1;
    }

    ofstream outFile("convex_polygons_mismatch.csv"); // Open the CSV file to write data in
    if (!outFile)
    {
        cerr << "Failed to open the input file!" << endl;
        return 1;
    }

    // reading dp file
    string line1;
    vector<pair<double, double>> polygon1;
    while (getline(inFile1, line1))
    {
        pair<double, double> data = parseCSVLine(line1);
        polygon1.push_back(data);
    }

    // reading greedy file
    string line2;
    vector<pair<double, double>> polygon2;
    while (getline(inFile2, line2))
    {
        pair<double, double> data = parseCSVLine(line2);
        polygon2.push_back(data);
    }

    for (int i = 0; i < polygon1.size(); i++)
    {
        cout << polygon1[i].first << " " << polygon1[i].second << endl;
    }

    for (int i = 0; i < polygon2.size(); i++)
    {
        cout << polygon2[i].first << " " << polygon2[i].second << endl;
    }

    for (int i = 0; i < polygon1.size(); i++)
    {
        double errorpercent = ((polygon2[i].second - polygon1[i].second) / polygon1[i].second) * 100;
        outFile << polygon1[i].first << "," << errorpercent << endl;
        cout << polygon1[i].first << "," << errorpercent << endl;
    }

    inFile1.close();
    inFile2.close();
    outFile.close();

    return 0;
}
