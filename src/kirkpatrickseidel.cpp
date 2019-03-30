#include "kirkpatrickseidel.h"
using namespace std;

int pointTracker = 0;

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

int partitioning(int l, int u, Point sample[])
{
    int pivot = sample[u].x;
    int i = l-1, j;
    for(j = l; j < u; j++)
    {
        if(sample[j].x <= pivot)
        {
            i++;
            swap(i, j, sample);
        }
    }
    i++;
    swap(i, u, sample);
    return i;
}

int quickselect(int reqIndex, int l, int u, Point sample[])
{
    if(l<=u) // Safety check
    {
        int partitionIndex = partitioning(l,u,sample);
        if (partitionIndex == reqIndex - 1)
        {
            return partitionIndex;
        }
        else if(partitionIndex < reqIndex - 1)
        {
            return quickselect(reqIndex, partitionIndex + 1, u, sample);
        }
        return quickselect(reqIndex, l, partitionIndex - 1, sample);
    }
    cout<< "WARNING : Illegal bounds for quickselect"<< endl;
    return -1;
}

void connect(int minxIndex, int maxIndex, Point upperPoints[], int result[], int lesserN)
{
    if (minxIndex == maxIndex)
    {
        result[pointTracker] = minxIndex;
    }
    Point temp[lesserN];
    copyInitialization(temp, upperPoints, lesserN);
    Point max_left = temp[quickselect(lesserN/2 - 1, 0, lesserN - 1, temp)];
    copyInitialization(temp, upperPoints, lesserN);
    Point min_right = temp[quickselect(lesserN/2, 0, lesserN - 1, temp)];
    // cout<<max_left.x<<" "<< max_left.y<<endl;
    // cout<<min_right.x<<" "<<min_right.y<<endl;

}

void upperHull(Point input[],int result[], int N)
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
    // printArray(upperPoints, lesserN);
    connect(minxIndex, maxxIndex, upperPoints, result, lesserN);
    return;
}

int kpsHullCompute(Point input[],int result[],int N)
{
    Point upper[N];
    copyInitialization(upper, input, N);
    Point lower[N];
    copyInitialization(lower, input, N);
    upperHull(input, result, N);
    for(int i=0;i<N;i++)
	{
        result[i] = i;
    }
    return N;
}