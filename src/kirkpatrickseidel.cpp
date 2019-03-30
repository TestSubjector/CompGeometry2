#include "kirkpatrickseidel.h"
using namespace std;

void safeInitialization(int arr[], int size)
{
    int i = 0;
    for(i = 0; i < size; i++)
    {
        arr[i] = -1;
    }
    return;
}

void copyInitialization(Point target[], Point base[], int size)
{
    int i = 0;
    for(i = 0; i < size; i++)
    {
        target[i] = base[i];
    }
}

int kpsGetLeftMostPoint(Point p[], int N)
{
  int index_ref = 0;
  for (int i = 1; i < N; i++)
  {
    if(p[i].x < p[index_ref].x)
    {
      index_ref = i;
    }
    else if(p[i].x == p[index_ref].x)
    {
      if(p[i].y > p[index_ref].y)
      {
        index_ref = i;
      }
    }
  }
  return index_ref;
}

int kpsGetRightMostPoint(Point p[], int N)
{
  int index_ref = 0;
  for (int i = 1; i < N; i++)
  {
    if(p[i].x > p[index_ref].x)
    {
      index_ref = i;
    }
    else if(p[i].x == p[index_ref].x)
    {
      if(p[i].y > p[index_ref].y)
      {
        index_ref = i;
      }
    }
  }
  return index_ref;
}

void upperHull(Point input[], int N)
{
    // cout<<kpsGetLeftMostPoint(input, N)<<endl;
    // cout<<kpsGetRightMostPoint(input, N)<<endl;
    int minxIndex = kpsGetLeftMostPoint(input, N);
    int maxxIndex = kpsGetRightMostPoint(input, N);
    int i = 0, lesserN = 0, j = 0;
    for(i = 0; i < N; i++)
    {
        if((input[i].x > input[minxIndex].x && input[i].x < input[maxxIndex].x) || i == minxIndex || i == maxxIndex)
        {
            lesserN++;
        }
    }
    Point upperPoints[lesserN]; // excluding the possible vertical edges of xmin and xmax
    for(i = 0; i < N; i++)
    {
        if((input[i].x > input[minxIndex].x && input[i].x < input[maxxIndex].x) || i == minxIndex || i == maxxIndex)
        {
            upperPoints[j++] = input[i];
        }
    }
    printArray(upperPoints, lesserN);
    return;
}

int kpsHullCompute(Point input[],int result[],int N)
{
    Point upper[N];
    copyInitialization(upper, input, N);
    Point lower[N];
    copyInitialization(lower, input, N);
    upperHull(input, N);
    for(int i=0;i<N;i++)
	{
        result[i] = i;
    }
    return N;
}