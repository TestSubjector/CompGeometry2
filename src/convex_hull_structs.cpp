#include "convex_hull_structs.h"

/**
 * Shifts the origin and then converts to Polar format
 * @param  p      Point in cartesian that needs to be converted
 * @param  origin Point in cartesian that is treated as origin
 * @return        PolarPoint which is the conversion of the passed Point
 */
PolarPoint convertToPolar(Point p, Point origin)
{
	p.x -= origin.x;
	p.y -= origin.y;
	double r = sqrt(p.x*p.x + p.y*p.y);
	if(r == 0.0 || r == -0.0)
	{
		return PolarPoint(0.0,0.0,p.index);
	}
	double theta = atan(p.y/p.x);
	return PolarPoint(r,theta,p.index);
}

/**
 * Compares two PolarPoints based on which has lower theta
 * @param  p PolarPoint 1
 * @param  q PolarPoint 2
 * @return   0 for equal, -1 for p < q, 1 for p > q.
 */
int compareTheta(PolarPoint p, PolarPoint q)
{
	// abs() returns a rounded value. fabs() is for doubles
	double diff = fabs(p.theta - q.theta);
	if(diff < 0.000000000001)
	{
		// Equal theta. Margin to account for floating point error
		return 0;
	}
	else if(p.theta > q.theta)
	{
		//greater
		return 1;
	}
	else
	{
		//lesser
		return -1;
	}
}

//
// Stack methods
//

/**
 * Check if stack is empty or not
 * @param  root Node*
 * @return 1 if empty, else 0.
 */
int isEmpty(Node* root)
{
	return !root;
}

void push(Point p,Node** root)
{
	Node* temp = (Node*) malloc(sizeof(Node));
	temp->point = p;
	temp->next = *root;
	*root = temp;
}

Point pop(Node** root)
{
	//Stack is never empty in our usage, but check is kept. TODO think of better return here
	if(isEmpty(*root))
	{
		return Point(-1.0,-1.0);
	}
	Point p = (*root)->point;
	*root = (*root)->next;
	return p;
}

Point peek(Node** root)
{
	//Stack is never empty in our usage, but check is kept. TODO think of better return here
	if(isEmpty(*root))
	{
		return Point(-1.0,-1.0);
	}
	return (*root)->point;
}

void printStack(Node** root)
{
	Node* temp = *root;
	while(temp!=NULL)
	{
		printf("(%f,%f)\n",temp->point.x,temp->point.y);
		temp = temp->next;
	}
	printf("\n");
}

//
// Array methods
//

/**
 * Prints out all the elements in the array passed
 * @param p Array to be printed
 * @param n Length of the array
 */
void printArray(PolarPoint p[], int n)
{
	for (int i = 0; i < n; i++) {
		std::cout << p[i].r << ',' << p[i].theta << std::endl;
	}
}

/**
 * Prints out all the elements in the array passed
 * @param p Array to be printed
 * @param n Length of the array
 */
void printArray(Point p[], int n)
{
	for (int i = 0; i < n; i++) {
		printf("%f,%f\n",p[i].x,p[i].y );
	}
}

/**
 * Swaps the elements i and j in the inp array passed
 * @param i   integer index
 * @param j   integer index
 * @param inp PolarPoint array
 */
void swap(int i,int j, PolarPoint inp[])
{
	PolarPoint temp = inp[i];
	inp[i] = inp[j];
	inp[j] = temp;
	return;
}

/**
 * Swaps the elements i and j in the inp array passed
 * @param i   integer index
 * @param j   integer index
 * @param inp Point array
 */
void swap(int i,int j, Point inp[])
{
	Point temp = inp[i];
	inp[i] = inp[j];
	inp[j] = temp;
	return;
}

/**
 * Swaps the elements i and j in the inp array passed
 * @param i   integer index
 * @param j   integer index
 * @param inp Point array
 */
void swap(int i,int j, double inp[])
{
	double temp = inp[i];
	inp[i] = inp[j];
	inp[j] = temp;
	return;
}

/**
 * Reverses the elements in the inp array passed
 * @param inp Point array
 */
void swap_all(Point inp[])
{
    int size = *(&inp + 1) - inp;
    int i = 0;
    Point temp;
    for(i=0; i< size/2; i++)
    {
        swap(i, size-1-i, inp);
    }
	return;
}

/**
 * Changes the sign of all elements in the inp array passed
 * @param inp Point array
 * @param out Point array
 * @param size int
 * @return Point array with all elements having flipped sign compared to the input
 */
void flipAll(Point inp[], Point out[], int size)
{
    int i = 0;
    for(i=0; i < size; i++)
    {
        out[i].x = -1*inp[i].x;
		out[i].y = -1*inp[i].y;
		// out[i].index = inp[i].index;
    }
	return;
}

void flipSelf(Point inp[], int size)
{
    int i = 0;
    for(i=0; i < size; i++)
    {
        inp[i].x = -inp[i].x;
		inp[i].y = -inp[i].y;
		// out[i].index = inp[i].index;
    }
	return;
}

Pairing sortPair(Pairing z)
{
	if(z.p.x > z.q.x)
	{
		// printf("Reached here\n");
		Point temp;
		temp.x = z.p.x;
		temp.y = z.p.y;
		z.p.x = z.q.x;
		z.p.y = z.q.y;
		z.q.x = temp.x;
		z.q.y = temp.y;
	}
	return z;
}
