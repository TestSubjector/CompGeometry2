#include <stdlib.h>
#include <string.h>
#include <iomanip>
#include <iostream>
#include <fstream>
#include "graham_scan.h"
#include "jmarch.h"
#include "kirkpatrickseidel.h"
#include "hayai.hpp"

int complexVisualiseFlag = 0;

using namespace std;
// This assumes only one delimiter per string
Point parsePoint(string inp, char delim = ' ')
{
    size_t loc = inp.find(delim);
    double f1,f2;
    // Though there will always be one delimiter
    if(loc != string::npos)
    {
      f1 = stof(inp.substr(0, loc));
      f2 = stof(inp.substr(loc+1));
      return Point(f1,f2);
    }
    return Point();
}

BENCHMARK(Benchmark_Graham, DeliverPackage, 1, 2)
{
    Node *root;
    ifstream inputFile;
    ofstream outputFile;
    string filePath;
    // cout << "Enter input file path: ";
    filePath = "/home/testsubjector/code/github_c++/CompGeom2/test/testcase6.txt";
    inputFile.open(filePath,ios::in);
    string lineinput;
    int total_points = 0;

    if(inputFile.is_open())
    {
        getline(inputFile, lineinput);
        total_points = stoi(lineinput);
    }

    Point inp[total_points];

    for(int i = 0; i < total_points; i++)
    {
        getline(inputFile,lineinput);
        inp[i] = parsePoint(lineinput);
        // Index needed only for Graham
        inp[i].index = i;
    }
    inputFile.close();

    getHull(inp, total_points, &root);
}

BENCHMARK(Benchmark_Jarvis, DeliverPackage, 1, 2)
{

    ifstream inputFile;
    ofstream outputFile;
    string filePath;
    // cout << "Enter input file path: ";
    filePath = "/home/testsubjector/code/github_c++/CompGeom2/test/testcase6.txt";
    inputFile.open(filePath,ios::in);
    string lineinput;
    int total_points = 0;

    if(inputFile.is_open())
    {
        getline(inputFile, lineinput);
        total_points = stoi(lineinput);
    }

    Point inp[total_points];

    for(int i = 0; i < total_points; i++)
    {
        getline(inputFile,lineinput);
        inp[i] = parsePoint(lineinput);
        // Index needed only for Graham
        inp[i].index = i;
    }
    inputFile.close();
    int result[total_points];
    hull_compute(inp,result,total_points);
}

BENCHMARK(Benchmark_KirkPatrickSeidel, DeliverPackage, 1, 2)
{
    ifstream inputFile;
    ofstream outputFile;
    string filePath;
    // cout << "Enter input file path: ";
    filePath = "/home/testsubjector/code/github_c++/CompGeom2/test/testcase6.txt";
    inputFile.open(filePath,ios::in);
    string lineinput;
    int total_points = 0;

    if(inputFile.is_open())
    {
        getline(inputFile, lineinput);
        total_points = stoi(lineinput);
    }

    Point inp[total_points];

    for(int i = 0; i < total_points; i++)
    {
        getline(inputFile,lineinput);
        inp[i] = parsePoint(lineinput);
        // Index needed only for Graham
        inp[i].index = i;
    }
    inputFile.close();
    Point result[total_points];
    kpsHullCompute(inp,result,total_points);
}

int main(int argc, char const *argv[])
{

    if(strcmp(argv[1],"t") == 0)
    {
        hayai::ConsoleOutputter consoleOutputter;
        hayai::Benchmarker::AddOutputter(consoleOutputter);
        hayai::Benchmarker::RunAllTests();
        exit(0);
    }

    ifstream inputFile;
    ofstream outputFile;
    string filePath;
    cout << "Enter input file path: ";
    getline(cin, filePath);
    inputFile.open(filePath,ios::in);
    string lineinput;
    int total_points = 0;

    // The first argument is the executable, second is the algorithm to be used, third is the complex visualisation flag
    if(argc != 2 && argc !=3)
    {
        //  cout<<argc<<endl;
        cout<<"Error, convex hull algorithm argument not specified (g, j, k or t). Or too many arguments. Exiting"<<endl;
        exit(0);
    }

    if(argc == 3)
    {
        complexVisualiseFlag = 1;
    }

    // First line gives number of points in input
    if(inputFile.is_open())
    {
        getline(inputFile, lineinput);
        total_points = stoi(lineinput);
    }

    Point inp[total_points];

    for(int i = 0; i < total_points; i++)
    {
        getline(inputFile,lineinput);
        inp[i] = parsePoint(lineinput);
        // Index needed only for Graham
        inp[i].index = i;
    }
    inputFile.close();

    // Using KirkPatrickSeidel
    if(strcmp(argv[1],"k") == 0)
    {
        cout<<"Running KirkPatrickSeidel algorithm"<<endl;
        Point result[total_points];
        int points_on_hull = kpsHullCompute(inp,result,total_points);
        outputFile.open("output/output_kps.ch");
        outputFile << "CHK" << endl;
        outputFile << total_points << " " << points_on_hull << endl;
          for(int i=0;i < total_points; i++)
        {
            outputFile << inp[i].x << " " << inp[i].y << " 0.0" << endl;
        }
        for(int i=0;i < points_on_hull;i++)
        {
            outputFile<<result[i].x<<","<<result[i].y<<" ";
        }
        outputFile << endl;
        outputFile.close();
    }
    // KirkPatrickSeidel end


    // Using  JMarch
    if(strcmp(argv[1],"j") == 0)
    {
        cout<<"Running JarvisMarch algorithm"<<endl;
        int result[total_points];
        int points_on_hull = hull_compute(inp,result,total_points);
        // cout << points_on_hull << endl;
        outputFile.open("output/output_jarvis.ch");
        outputFile << "CHJ" << endl;
        outputFile << total_points << " " << points_on_hull << endl;
        for(int i=0;i < total_points; i++)
        {
            outputFile << inp[i].x << " " << inp[i].y << " 0.0" << endl;
        }
        for(int i=0;i < points_on_hull;i++)
        {
            outputFile<<result[i]<<" ";
        }
        outputFile << endl;
        outputFile.close();
    }
    // JMarch end


    // Using Graham's Scan
    if(strcmp(argv[1],"g") == 0)
    {
        cout<<"Running GrahamsScan algorithm"<<endl;
        Node *root;
        int points_on_hull = getHull(inp, total_points, &root);
        if(points_on_hull==-1)
        {
          return 0;
        }
        outputFile.open("output/output_graham.ch");
        outputFile << "CHG" << endl;
        outputFile << total_points << " " << points_on_hull << endl;

        for (int i = 0; i < total_points; i++) {
            outputFile << inp[i].x << " " << inp[i].y << " 0.0" << endl;
        }
        for (int i = 0; i < points_on_hull; i++)
        {
            Point temp = pop(&root);
            outputFile << temp.index << " ";
        }
        outputFile << endl;
        outputFile.close();
        }
    // Graham's end

}
