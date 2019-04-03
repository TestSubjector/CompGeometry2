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

void copyInitialization(double target[], double base[], int size)
{
    int i = 0;
    for(i = 0; i < size; i++)
    {
        target[i] = base[i];
    }
}

int kpsGetLeftMostPoint(Point p[], int N)
{
  int index_ref = 0, i = 0;
  for (i = 1; i < N; i++)
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
  int index_ref = 0, i = 0;
  for (i = 1; i < N; i++)
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
    // cout<<"Aye Part "<<i<<endl;
    return i;
}

int quickselect(int reqIndex, int l, int u, Point sample[])
{
    // if(reqIndex < 0)
    // {
    //     cout<<"Illegal reqIndex"<<endl;
    //     exit(0);
    // }
    // if(reqIndex == 0)
    // {
    //     reqIndex += 1;
    // }
    // cout<<"Partioning "<<reqIndex<<" "<<l<<" "<<u<<endl;
    if(l<=u) // Safety check
    {
        int partitionIndex = partitioning(l,u,sample);
        // cout<<"PartIndex "<<partitionIndex<<endl;
        if (partitionIndex == reqIndex - 1)
        {
            // cout<<"Terminate"<<endl;
            return partitionIndex;
        }
        else if(partitionIndex < reqIndex - 1)
        {
            // cout<<"Upper"<<endl;
            return quickselect(reqIndex, partitionIndex + 1, u, sample);
        }
        // cout<<"Lower"<<endl;
        return quickselect(reqIndex, l, partitionIndex - 1, sample);
    }
    cout<< "WARNING : Illegal bounds for quickselect1"<< endl;
    cout<<reqIndex<<" "<<l<<" "<<u<<endl;
    exit(0);
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
    // if(reqIndex < 0)
    // {
    //     cout<<"Illegal reqIndex"<<endl;
    //     exit(0);
    // }
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
    cout<<reqIndex<<" "<<l<<" "<<u<<endl;
    return -1;
}

Pairing bridgeFinder(Point upperPoints[], int upperLine, int size)
{
    Point* candidates = new Point[size];
    int update = 0;
    if (size == 2)
    {
        Pairing tempPair = Pairing(upperPoints[0], upperPoints[1]);
        // cout<<"Sorting Start"<<endl;
        // cout<<tempPair.p.x<<endl;
        // cout<<tempPair.q.x;
        tempPair = sortPair(tempPair);
        // cout<<tempPair.p.x<<endl;
        // cout<<"Sorting Done"<<endl;
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
        pairs[i/2] = sortPair(pairs[i/2]);
        // cout<<"Points "<<pairs[i/2].p.x<<" "<<pairs[i/2].p.y<<" "<<pairs[i/2].q.x<<" "<<pairs[i/2].q.y<<endl;
    }

    // cout<<endl;
    // cout<<"Size is"<<size<<endl;
    // cout<<"NumPairs is"<<numPairs<<endl;
    // cout<<endl;

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
            // cout<<"Point's slopes "<<pairs[i].p.x<<" "<<pairs[i].p.y<<" "<<pairs[i].q.x<<" "<<pairs[i].q.y<<endl;
            slopes[slopeUpdate] = ((temp.p.y - temp.q.y) / (temp.p.x - temp.q.x));
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
        medianIndex = slopeUpdate - 1 /2;
    }

    double temp[numPairs];
    copyInitialization(temp, slopes, slopeUpdate);
    // cout<<"Slopeupdate is"<<slopeUpdate<<endl;
    double medianSlope = slopes[quickselect(medianIndex, 0, slopeUpdate -1, temp)];
    // cout<<"Slopeupdate is"<<slopeUpdate<<endl;
    // cout<< "MS"<<medianSlope<<" "<<slopes[0]<<endl;

    Pairing *small = new Pairing[slopeUpdate];
    Pairing *equal = new Pairing[slopeUpdate];
    Pairing *large = new Pairing[slopeUpdate];
    int smallCount=0, equalCount=0, largeCount=0;
    int skip = 0;
    for(i=0; i<numPairs;i++)
    {
        if(pairs[i].redact == 1)
        {
            skip++;
        }
        else
        {
            // Assign to small, equal and large
            if(slopes[i - skip] < medianSlope)
            {
                small[smallCount++] = pairs[i];
            }
            else if(slopes[i-skip] == medianSlope)
            {
                equal[equalCount++] = pairs[i];
            }
            else
            {
                large[largeCount++] = pairs[i];
            }
        }
    }
    // cout<<smallCount<<" "<<equalCount<<" "<<largeCount<<endl;

    // Get max slope
    double maxSlope = upperPoints[0].y - medianSlope * upperPoints[0].x;
    Point leftLargeSlopePoint = upperPoints[0];
    Point rightLargeSlopePoint = upperPoints[0];
    for(i=0; i<size; i++)
    {
        double newSlope  = upperPoints[i].y - medianSlope * upperPoints[i].x;
        if (newSlope > maxSlope)
        {
            maxSlope = newSlope;
            leftLargeSlopePoint = upperPoints[i];
            rightLargeSlopePoint = upperPoints[i];
        }
        else if(newSlope == maxSlope)
        {
            if(upperPoints[i].x < leftLargeSlopePoint.x)
            {
                leftLargeSlopePoint = upperPoints[i];
            }
            if(upperPoints[i].x > rightLargeSlopePoint.x)
            {
                rightLargeSlopePoint = upperPoints[i];
            }
        }
    }
    // cout<<maxSlope<<endl;
    // cout<<leftLargeSlopePoint.x<<" "<<leftLargeSlopePoint.y<<endl;
    // cout<<rightLargeSlopePoint.x<<" "<<rightLargeSlopePoint.y<<endl;
    if(leftLargeSlopePoint.x <= upperLine && rightLargeSlopePoint.x > upperLine)
    {
        Pairing tempPair = Pairing(leftLargeSlopePoint, rightLargeSlopePoint);
        tempPair = sortPair(tempPair);
        return tempPair;
    }
    if(rightLargeSlopePoint.x <= upperLine)
    {
        // Small
        for(i=0; i< smallCount;i++)
        {
            candidates[update++] = small[i].p;
            candidates[update++] = small[i].q;
        }
        // Medium
        for(i = 0; i < equalCount; i++)
        {
            candidates[update++] = equal[i].q;
        }
        //Large
        for(i = 0; i < largeCount; i++)
        {
            candidates[update++] = large[i].q;
        }
    }
    if(leftLargeSlopePoint.x > upperLine)
    {
        // Small
        for(i=0; i< smallCount; i++)
        {
            candidates[update++] = small[i].p;
        }
        // Medium
        for(i = 0; i < equalCount; i++)
        {
            candidates[update++] = equal[i].p;
        }
        //Large
        for(i = 0; i < largeCount; i++)
        {
            candidates[update++] = large[i].p;
            candidates[update++] = large[i].q;
        }
    }
    // cout<<update<<endl;
    // cout<<upperLine<<endl;
    delete [] small;
    delete [] equal;
    delete [] large;
    return bridgeFinder(candidates, upperLine, update);
}

void connect(Point minx, Point maxx, Point upperPoints[], Point result[], int lesserN, ofstream &visualiseOut)
{
    int i = 0;
    if (minx.x == maxx.x && minx.y == maxx.y)
    {
        result[pointTracker] = minx;
        pointTracker++;
        return;
    }
    Point *temp = new Point[lesserN];
    copyInitialization(temp, upperPoints, lesserN);
    Point max_left = temp[quickselect((lesserN)/2, 0, lesserN - 1, temp)];
    // cout<<"Max L "<<max_left.x<<" "<< max_left.y<<endl;
    copyInitialization(temp, upperPoints, lesserN);
    Point min_right = temp[quickselect(lesserN/2 + 1, 0, lesserN - 1, temp)];
    // cout<<"Min R "<<min_right.x<<" "<<min_right.y<<endl;
    Pairing leftright = bridgeFinder(upperPoints, (max_left.x + min_right.x)/2, lesserN);

    if(complexVisualiseFlag == 1)
    {
        visualiseOut<<leftright.p.x<<","<<leftright.p.y<<endl;
        visualiseOut<<leftright.q.x<<","<<leftright.q.y<<endl;
    }
    if(complexVisualiseFlag == 2)
    {
        visualiseOut<<-leftright.p.x<<","<<-leftright.p.y<<endl;
        visualiseOut<<-leftright.q.x<<","<<-leftright.q.y<<endl;
    }
    // cout<<"Smaller left"<<leftright.p.x<<" "<<leftright.p.y<<endl;
    // cout<<"Greater right"<<leftright.q.x<<" "<<leftright.q.y<<endl;
    // cout<<endl;
    Point *leftPoints = new Point[lesserN];
    int leftPointsIndex = 0;
    for(i=0; i < lesserN; i++)
    {
        if((upperPoints[i].x < leftright.p.x) || (upperPoints[i].x == leftright.p.x && upperPoints[i].y == leftright.p.y))
        {
            leftPoints[leftPointsIndex++] = upperPoints[i];
        }
    }
    Point *rightPoints = new Point[lesserN];
    int rightPointsIndex = 0;
    for(i=0; i < lesserN; i++)
    {
        if((upperPoints[i].x > leftright.q.x) || (upperPoints[i].x == leftright.q.x && upperPoints[i].y == leftright.q.y))
        {
            rightPoints[rightPointsIndex++] = upperPoints[i];
        }
    }
    // int leftIndex;
    // for(i=0; i < leftPointsIndex; i++)
    // {
    //     if(leftPoints[i].x == leftright.p.x && leftPoints[i].y == leftright.p.y)
    //     {
    //         leftIndex = i;
    //     }
    // }
    // int rightIndex;
    // for(i=0; i < rightPointsIndex; i++)
    // {
    //     if((rightPoints[i].x == leftright.q.x && rightPoints[i].y == leftright.q.y))
    //     {
    //         rightIndex = i;
    //     }
    // }
    // cout<<"**Left**"<<leftPointsIndex<<endl;
    delete [] temp;
    delete [] upperPoints;
    connect(minx, leftright.p, leftPoints, result, leftPointsIndex, visualiseOut);
    // cout<<endl;
    // cout<<"**Right**"<<rightPointsIndex<<endl;
    // cout<<"R is"<<leftright.q.x<<" "<<leftright.q.y<<endl;
    // cout<<"Max is"<<maxx.x<<" "<<maxx.y<<endl;
    connect(leftright.q, maxx, rightPoints, result, rightPointsIndex, visualiseOut);
}

void upperHull(Point input[],Point result[], int N, ofstream &visualiseOut)
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
    Point *upperPoints = new Point[lesserN]; // excluding the possible vertical edges of xmin and xmax
    for(i = 0; i < N; i++)
    {
        if((input[i].x > input[minxIndex].x && input[i].x < input[maxxIndex].x) || i == minxIndex || i == maxxIndex)
        {
            upperPoints[j++] = input[i];
        }
    }
    // printArray(upperPoints, lesserN);
    connect(input[minxIndex], input[maxxIndex], upperPoints, result, lesserN, visualiseOut);
    return;
}

int kpsHullCompute(Point input[],Point result[],int N)
{
    int i = 0;
    Point upper[N];
    copyInitialization(upper, input, N);
    Point lower[N];
    flipAll(input, lower, N);
    // cout<<"wababa"<<lower[0].x<<endl;
    Point resultUpper[N];
    int resultUpperIndex = 0;
    Point resultLower[N];
    int resultLowerIndex = 0;

    ofstream visualiseOut;

    if(complexVisualiseFlag != 0)
    {
        visualiseOut.open("/home/testsubjector/code/github_c++/CompGeom2/output/output_kpsbridge.ch");
    }

    upperHull(upper, resultUpper, N, visualiseOut);
    resultUpperIndex = pointTracker;

    if(complexVisualiseFlag != 0)
    {
        complexVisualiseFlag = 2;
    }

    pointTracker = 0;
    // cout<<"wababa"<<lower[0].x<<endl;
    upperHull(lower, resultLower, N, visualiseOut);
    resultLowerIndex = pointTracker;

    if(complexVisualiseFlag != 0)
    {
        visualiseOut.close();
    }
    // cout<<resultLowerIndex<<endl;
    // cout<<resultUpper[0].x<<endl;
    flipSelf(resultLower, resultLowerIndex);
    // cout<<resultUpper[0].x<<endl;

    //Merging
    if(resultLower[resultLowerIndex-1].x == resultUpper[0].x && resultLower[resultLowerIndex-1].y == resultUpper[0].y)
    {
        resultLowerIndex -= 1;
    }

    if(resultLower[0].x == resultUpper[resultUpperIndex-1].x && resultLower[0].y == resultUpper[resultUpperIndex-1].y)
    {
        resultUpperIndex -= 1;
    }

    for(i = 0;i < resultUpperIndex;i++)
	{
        result[i] = resultUpper[i];
    }

    for(i = resultUpperIndex; i<resultUpperIndex + resultLowerIndex;i++)
	{
        result[i] = resultLower[i-resultUpperIndex];
    }
    // for(i = 0; i < resultLowerIndex; i++)
    // {
    //     cout<<resultLower[i].x<<","<<resultLower[i].y<<endl;
    // }

    return resultUpperIndex + resultLowerIndex;
}