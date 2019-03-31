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

void safeInitialization(double arr[], int size)
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
    cout<< "WARNING : Illegal bounds for quickselect1"<< endl;
    return -1;
}

int partitioning(int l, int u, double sample[])
{
    double pivot = sample[u];
    int i = l-1, j;
    for(j = l; j < u; j++)
    {
        if(sample[j] <= pivot)
        {
            i++;
            swap(i, j, sample);
        }
    }
    i++;
    swap(i, u, sample);
    return i;
}

int quickselect(int reqIndex, int l, int u, double sample[])
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
    cout<< "WARNING : Illegal bounds for quickselect2"<< endl;
    cout<<l<<" "<<u<<endl;
    return -1;
}

Pairing bridgeFinder(Point upperPoints[], int upperLine, int size)
{
    Point candidates[size];
    int update = 0;
    if (size == 2)
    {
        Pairing tempPair = Pairing(upperPoints[0], upperPoints[1]);
        sortPair(tempPair);
        return tempPair;
    }

    int numPairs = 0;
    if (size%2 == 1) // Add the left out element to pairings
    {
        candidates[update] = upperPoints[size-1];
        update++;
        numPairs = (size-1)/2;
    }
    else
    {
        numPairs = size/2;
    }
    int i = 0;
    Pairing pairs[numPairs];
    for(i = 0; i < size-1; i+=2)
    {
        pairs[i/2] = Pairing(upperPoints[i], upperPoints[i+1]);
        // cout<<"Points "<<pairs[i/2].p.x<<" "<<pairs[i/2].p.y<<" "<<pairs[i/2].q.x<<" "<<pairs[i/2].q.y<<endl;
        sortPair(pairs[i/2]);
        // cout<<"Points "<<pairs[i/2].p.x<<" "<<pairs[i/2].p.y<<" "<<pairs[i/2].q.x<<" "<<pairs[i/2].q.y<<endl;
    }

    // cout<<"Size is"<<size<<endl;
    // cout<<"NumPairs is"<<numPairs<<endl;

    double slopes[numPairs];
    safeInitialization(slopes, numPairs);
    int slopeUpdate = 0;
    for(i = 0; i < numPairs; i+=1)
    {
        Pairing temp = pairs[i];
        if(temp.p.x == temp.q.x)
        {
            pairs[i/2].redact = 1; // Remove from consideration
            if(temp.p.y > temp.q.y)
            {
                candidates[update] = temp.p;
                update++;
            }
            else
            {
                candidates[update] = temp.q;
                update++;
            }
        }
        else
        {
            // cout<<"Points2 "<<pairs[i].p.x<<" "<<pairs[i].p.y<<" "<<pairs[i].q.x<<" "<<pairs[i].q.y<<endl;
            slopes[slopeUpdate] = ((temp.p.y - temp.q.y) / (temp.p.x - temp.q.y));
            // cout<<slopes[slopeUpdate]<<endl;
            slopeUpdate++;
        }
    }

    // cout<<"SlopeUpdate is"<<slopeUpdate<<endl;
    // cout<<slopes[0]<<" "<<slopes[1]<<endl;

    int medianIndex;
    if(slopeUpdate%2 == 0)
    {
        medianIndex = slopeUpdate/2;
    }
    else
    {
        medianIndex = slopeUpdate/2 - 1;
    }

    // int medianSlope = quickselect(medianIndex, 0, slopeUpdate, slopes);
    // cout<< "MS"<<medianSlope<<endl;
}

void connect(int minxIndex, int maxIndex, Point upperPoints[], int result[], int lesserN)
{
    if (minxIndex == maxIndex)
    {
        result[pointTracker] = minxIndex;
        pointTracker++;
    }
    Point temp[lesserN];
    copyInitialization(temp, upperPoints, lesserN);
    Point max_left = temp[quickselect(lesserN/2 - 1, 0, lesserN - 1, temp)];
    copyInitialization(temp, upperPoints, lesserN);
    Point min_right = temp[quickselect(lesserN/2, 0, lesserN - 1, temp)];
    // cout<<max_left.x<<" "<< max_left.y<<endl;
    // cout<<min_right.x<<" "<<min_right.y<<endl;
    bridgeFinder(upperPoints, (max_left.x + min_right.x)/2, lesserN);
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