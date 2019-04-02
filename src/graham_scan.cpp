#include "graham_scan.h"

/**
* Computes whether the next point is to the left or to the right or in the same direction.
 * @param  p The previous point
 * @param  q The point common to both segments, i.e. current point
 * @param  r The next point
 * @return   0 for same direction, positive value for left turn and negative value for right turn
 */
double nextDirection(Point p,Point q,Point r)
{
    // A positive cross product indicates left, while a negative one indicates right.
    return (q.x - p.x)*(r.y - q.y) - (r.x - q.x)*(q.y - p.y);
}

/**
 * @brief Finds the leftmost point and then brings it to index 0.
 * @param p Array of Point objects
 * @param n length of the array
 * @returns index of leftmost point
 */
int getLeftmostPoint(Point p[], int n)
{
    int index_ref = 0;
    for (int i = 1; i < n; i++)
    {
        if(p[i].x < p[index_ref].x)
        {
            index_ref = i;
        }
        else if(p[i].x == p[index_ref].x)
        {
            if(p[i].y < p[index_ref].y)
            {
                index_ref = i;
            }
        }
    }
    return index_ref;
}

/**
 * If multiple points have the same angle, then only the one with largest radius remains in the out array
 * @param  inp Array of points in Polar form. This MUST be sorted before being passed
 * @param  n   Length of array
 * @param  out an array of valid points.
 * @return     the length of the out array
 */
int removeThetaCollinear(PolarPoint inp[],int n,PolarPoint out[])
{
    int newlen = 0;
    out[newlen++] = inp[0]; //maintaining origin first
    for(int i = 1; i < n-1 ; i++)
    {
        if(compareTheta(inp[i],inp[i+1]) == 0)
        {
            continue;
        }
        else
        {
            out[newlen++] = inp[i];
        }
    }
    out[newlen++] = inp[n-1]; // no further item to check with. Is always added.
    return newlen;
}

/**
 * @brief A in-place sort of all points
 * @details Points are sorted according to increasing angle, then radius.
 * The leftmost point is not passed to the function to ensure that inp[0] is the origin (0.0,0.0).
 * If this is not done, the points below origin (theta < 0) are before it in the array, which is not our desired traversal path.
 * O(n^2) complexity. Can be brought to O(nlogn) by using a QuickSort or other appropriate algorithm
 * @param inp Array of points in polar representation
 * @param n Length of the array
 */
void sortPoints(PolarPoint inp[], int n)
{
    //Bubble sort
    for(int k=0; k < n-1; k++)
    {
        for(int i = 0; i < n-k-1; i++)
        {
            if(inp[i].theta > inp[i+1].theta)
            {
                //swap since angle
                swap(i,i+1,inp);
            }
            else if(inp[i].theta == inp[i+1].theta)
            {
                if(inp[i].r > inp[i+1].r)
                {
                    //swap since radius
                    swap(i,i+1,inp);
                }
            }
        }
    }
}

/**
 * Adds the points that are the vertices of the convex hull into the passed stack
 * @param inp  Array of all points in cartesian form; sorted
 * @param n  length of the array
 * @param root pointer to the root node pointer of a stack
 * @return     number of points on the hull
 */
int computeHull(Point inp[],int n,Node **root)
{
    int size = 0;
    //Add the origin and next point to the Hull
    push(inp[size++], root); // 0->1
    push(inp[size++], root); // 1->2

    for(int i = 2; i < n-1; i++ )
    {
        // cout << "(" << peek(root).x << " " << peek(root).y << ") ";
        // cout << "(" << inp[i].x << " " << inp[i].y << ") ";
        // cout << "(" << inp[i+1].x << " " << inp[i+1].y << ") ";
        // cout << nextDirection(peek(root),inp[i],inp[i+1]) << endl;
        if(nextDirection(peek(root),inp[i],inp[i+1]) < 0)
        {
            //The code below running means occurence of a right turn. If collinear point not to be taken, make <=
            Point popped = pop(root);
            size--;
            // Keep popping till left turn arises
            while (nextDirection(popped, peek(root), inp[i+1]) >= 0 && !isEmpty(*root))
            {
                // cout << "while: popped" <<endl;
                popped = pop(root);
                size--;
            }
            push(popped,root);
            size++;
        }
        else
        {
            push(inp[i],root);
            // cout << "pushed" << endl;
            size++;
        }
    }
    push(inp[n-1],root);
    size++;
    delete inp;
    return size;
}

/**
 * The single function that needs to be called in order to get the vertices of the convex hull using Graham's Scan algo
 * @param input  Input array of Points
 * @param len    Length of array
 * @param root   Stack root node to which vertices will be pushed
 * @return       Number of points on the hull
 */
int getHull(Point input[],int len,Node **root)
{
    // Get the leftmost point
    int ind = getLeftmostPoint(input,len);
    Point origin = input[ind];
    PolarPoint* input_pol= new PolarPoint[len];

    for(int i = 0; i < len; i++)
    {
        input_pol[i] = convertToPolar(input[i],origin);
    }
    // If an array is defined as <type>* <arrayname> = new <type>[len] (Basically using the new operator), then the delete [] <arrayName> method can be safely used
    // The arrays of form <type> <arrayName>[len] are called statically allocated arrays. Their memory cannot be freed

    // printf("%s\n","Printing unsorted polar array" );
    // printArray(input_pol,len);

    swap(0, ind, input_pol); // Origin is now at index0 in input_pol
    sortPoints(input_pol+ 1, len-1); // input_pol[1:]
    // printf("%s\n","Printing sorted polar array" );
    // printArray(input_pol,len);

    // Remove Collinear Points
    PolarPoint* intermediate_pol = new PolarPoint[len];
    int newlen = 0;
    newlen = removeThetaCollinear(input_pol,len,intermediate_pol);
    // printf("%s\n","Printing intermediate polar array");
    // printArray(intermediate_pol,newlen);

    if(newlen < 3)
    {
        printf("%s\n", "Convex hull not possible");
        return -1;
    }

    Point* intermediate_cart = new Point[newlen];
    for(int i = 0; i < newlen; i++)
    {
        intermediate_cart[i] = input[intermediate_pol[i].index];
    }
    delete [] intermediate_pol;
    delete [] input_pol;

    // printf("%s\n","Printing intermediate cart array");
    // printArray(intermediate_cart,newlen);

    return computeHull(intermediate_cart,newlen,root);
}
