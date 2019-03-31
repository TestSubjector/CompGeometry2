#ifndef __KIRKPATRICKSEIDEL_H__
#define __KIRKPATRICKSEIDEL_H__

#include<iostream>
#include<stdlib.h>
#include "convex_hull_structs.h"

extern int pointTracker;

int kpsHullCompute(Point input[],int result[],int N);

void upperHull(Point input[],int result[], int N);
void connect(int minxIndex, int maxIndex, Point upperPoints[], int result[], int lesserN);
void bridgeFinder(Point upperPoints[], int upperLine, int size);

void safeInitialization(int arr[], int size);
void copyInitialization(Point target[], Point base[], int size);

int kpsGetLeftMostPoint(Point p[], int N);
int kpsGetRightMostPoint(Point p[], int N);



#endif