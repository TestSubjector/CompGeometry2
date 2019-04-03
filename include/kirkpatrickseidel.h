#ifndef __KIRKPATRICKSEIDEL_H__
#define __KIRKPATRICKSEIDEL_H__

#include<iostream>
#include <fstream>
#include<stdlib.h>
#include "convex_hull_structs.h"

extern int pointTracker;

int kpsHullCompute(Point input[],Point result[],int N);

void upperHull(Point input[],Point result[], int N, std::ofstream &visualiseOut);
void connect(Point minxIndex, Point maxIndex, Point upperPoints[], Point result[], int lesserN, std::ofstream &visualiseOut);
Pairing bridgeFinder(Point upperPoints[], int upperLine, int size);

void safeInitialization(int arr[], int size);
void safeInitialization(double arr[], int size);
void copyInitialization(Point target[], Point base[], int size);
void copyInitialization(double target[], double base[], int size);

int kpsGetLeftMostPoint(Point p[], int N);
int kpsGetRightMostPoint(Point p[], int N);

#endif