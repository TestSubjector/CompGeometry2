#include <stdlib.h>
#include <string>
#include <iomanip>
#include <iostream>
#include <fstream>
#include "graham_scan.h"
#include "jmarch.h"

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

int main(int argc, char const *argv[]) {

  ifstream inputFile;
  ofstream outputFile;
  string filePath;
  cout << "Enter input file path: ";
  getline(cin, filePath);
  inputFile.open(filePath,ios::in);
  string lineinput;
  int total_points = 0;

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

  // Using  JMarch
  int result[total_points];
  int points_on_hull = hull_compute(inp,result,total_points);
  // cout << points_on_hull << endl;
  outputFile.open("output/output_jarvis.ch");
  outputFile << "CH" << endl;
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
  // JMarch end


  // Using Graham's Scan
  // Node *root;
  // int points_on_hull = getHull(inp, total_points, &root);
  // if(points_on_hull==-1)
  // {
  //   return 0;
  // }
  // outputFile.open("output/output_graham.ch");
  // outputFile << "CH" << endl;
  // outputFile << total_points << " " << points_on_hull << endl;

  // for (int i = 0; i < total_points; i++) {
  //     outputFile << inp[i].x << " " << inp[i].y << " 0.0" << endl;
  // }
  // for (int i = 0; i < points_on_hull; i++)
  // {
  //     Point temp = pop(&root);
  //     outputFile << temp.index << " ";
  // }
  // outputFile << endl;
  // outputFile.close();
  // Graham's end
}
