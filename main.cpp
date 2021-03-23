#include <iostream>
#include <stack>
#include <stdlib.h>
using namespace std;

struct Point
{
    int x, y, value;
};

//used as first point
Point p0;

Point nextToTop(stack<Point> &S)
{
    Point p = S.top();
    S.pop();
    Point res = S.top();
    S.push(p);
    return res;
}

int swap(Point &p1, Point &p2)
{
    Point temp = p1;
    p1 = p2;
    p2 = temp;
}

//distance
int Distance(Point p1, Point p2)
{
    return (p1.x - p2.x)*(p1.x - p2.x) +
          (p1.y - p2.y)*(p1.y - p2.y);
}


int PointOrientation(Point p, Point q, Point r)
{
    int val = (q.y - p.y) * (r.x - q.x) -
              (q.x - p.x) * (r.y - q.y);

    if (val == 0)
        return 0;  // the same
    return (val > 0)? 1: 2; // < or >
}

//compare and sort
int ComparePoints(const void *vp1, const void *vp2)
{
   Point *p1 = (Point *)vp1;
   Point *p2 = (Point *)vp2;

   int o = PointOrientation(p0, *p1, *p2);
   if (o == 0)
     return (Distance(p0, *p2) >= Distance(p0, *p1))? -1 : 1;

   return (o == 2)? -1: 1;
}

// finds convex hull
void FindHull(Point points[], int n)
{
   // the lowest point
   int ymin = points[0].y, min = 0;
   for (int i = 1; i < n; i++)
   {
     int y = points[i].y;

     //chose a point
     if ((y < ymin) || (ymin == y &&
         points[i].x < points[min].x))
        ymin = points[i].y, min = i;
   }

   // places first point
   swap(points[0], points[min]);

    //sort
   p0 = points[0];
   qsort(&points[1], n-1, sizeof(Point), ComparePoints);


   int m = 1;
   for (int i=1; i<n; i++)
   {

       while (i < n-1 && PointOrientation(p0, points[i], points[i+1]) == 0)
          i++;


       points[m] = points[i];
            m++;
   }

   if (m < 3){
        cout<<endl<<"Convex hull not found"<<endl;
        return;
   }


   stack<Point> S;
   S.push(points[0]);
   S.push(points[1]);
   S.push(points[2]);

   for (int i = 3; i < m; i++)
   {

      while (PointOrientation(nextToTop(S), S.top(), points[i]) != 2)
         S.pop();
      S.push(points[i]);
   }


   while (!S.empty())
   {
       Point p = S.top();
       cout << "P"<<p.value<<" (" << p.x << ", " << p.y <<")" << endl;
       S.pop();
   }
}


int main()
{

    Point points[100];
    int n=8;

    cout<<"Number of points : ";
    cin>>n;
    cout<<endl;

    for(int i=0;i<n;i++){
        points[i].value = i;
        cout<<"Point "<<i<<".x = ";
        cin>>points[i].x;
        cout<<"Point "<<i<<".y = ";
        cin>>points[i].y;
        cout<<endl;
    }

    FindHull(points, n);

    return 0;

}
