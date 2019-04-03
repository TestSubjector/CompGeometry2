// Include Guard
#ifndef __CONVEX_HULL_STRUCTS_INCLUDED__
#define __CONVEX_HULL_STRUCTS_INCLUDED__
#include<cmath>
#include<stdlib.h>
#include<iostream>

extern int complexVisualiseFlag;

/// Struct that describes a point in polar coordinates
struct PolarPoint
{
  double r;
  double theta;
  int index;
  PolarPoint(double x, double y,int i):r(x),theta(y),index(i){}
  PolarPoint(){}
};

/// Struct that describes a point in cartesian coordinates
struct Point
{
  double x;
  double y;
  int index;
  Point(double x1, double y1, int ind) : x(x1), y(y1),index(ind){}
  Point(double x1, double y1) : x(x1), y(y1){}
  Point(){}
};

/// Struct that describes a node in a stack
struct Node
{
  Point point;
  Node* next;
};

/// Struct that describes a pair of Points
struct Pairing
{
  Point p;
  Point q;
  int redact;
  Pairing(Point a1, Point a2) : p(a1), q(a2), redact(0) {}
  Pairing(): redact(0){};
};

PolarPoint convertToPolar(Point p, Point origin);
int compareTheta(PolarPoint p, PolarPoint q);

int isEmpty(Node* root);
void push(Point p,Node** root);
Point pop(Node** root);
Point peek(Node** root);
void printStack(Node** root);

void printArray(PolarPoint p[], int n);
void printArray(Point p[], int n);
void swap(int i,int j, PolarPoint inp[]);
void swap(int i,int j, Point inp[]);
void swap(int i,int j, double inp[]);
void swap_all(Point inp[]);
void flipSelf(Point inp[], int size);
void flipAll(Point inp[], Point out[], int size);

Pairing sortPair(Pairing z);
int partitioning(int l, int u, Point sample[]);
int quickselect(int reqIndex, int l, int u, Point sample[]);
int partitioning(int l, int u, double sample[]);
int quickselect(int reqIndex, int l, int u, double sample[]);

#endif
