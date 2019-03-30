#ifndef __KIRKPATRICKSEIDEL_H__
#define __KIRKPATRICKSEIDEL_H__

#include<iostream>
#include<stdlib.h>
#include "convex_hull_structs.h"

int kpsHullCompute(Point input[],int result[],int N);

void upperHull(Point input[], int N);

void safeInitialization(int arr[], int size);
void copyInitialization(Point target[], Point base[], int size);

int kpsGetLeftMostPoint(Point p[], int N);
int kpsGetRightMostPoint(Point p[], int N);



#endif