#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <algorithm>
#include <math.h>
#include <vector>
#include <string>
#include <sstream>

const int maxn=1e3;
using namespace std;
const double eps = 1e-8;
int sgn(double x)
{
    if(fabs(x)<eps) return 0;
    if(x<0) return -1;
    else return 1;
}
struct  Point
{
    double xpos,ypos;
    Point(){}
    // copy constructor
    Point(const Point &pt)
    {
        xpos =pt.xpos;
        ypos =pt.ypos;
    }
    Point(double xpos,double ypos):xpos(xpos),ypos(ypos){}
    Point operator+(const Point &B)const
    {
        return Point(xpos+B.xpos,ypos+B.ypos);
    }
    Point operator-(const Point &B)const
    {
        return Point(xpos-B.xpos,ypos-B.ypos);
    }

    double operator ^(const Point &b)const
    {
        return xpos*b.ypos - ypos*b.xpos;
    }
    //dot product
    double operator *(const Point &b)const
    {
        return xpos*b.xpos + ypos*b.ypos;
    }
    void transXY(double B)
    {
        double tx = xpos,ty = ypos;
        xpos = tx*cos(B) - ty*sin(B);
        ypos = tx*sin(B) + ty*cos(B);
    }

}p[maxn];
typedef Point Vector;

int get(int i,int j,int k)
{
    int a,b;
    a=(p[j].xpos-p[i].xpos)*(p[k].ypos-p[i].ypos);
    b=(p[j].ypos-p[i].ypos)*(p[k].xpos-p[i].xpos);
    return a-b;
}

int main() {
    int verticles=0;
    cin>>verticles;
    int inputArray[verticles*2];
    int i = 0;
    cin>>inputArray[i++];
    while(getchar()!='\n')
    {
        cin>>inputArray[i++];
    }
    vector<Point>polygon;
    for(int index = 0 ;index<verticles;index++)
    {
        int x = inputArray[2*index];
        int y = inputArray[2*index+1];
        Point temp(x,y);
        polygon.push_back(temp);
    }
    for(int index= 1;index<=verticles;index++)
    {
        p[index].xpos =polygon[index-1].xpos;
        p[index].ypos=polygon[index-1].ypos;
    }
    for(int index = 1;index<=verticles;index++)
    {
        int x = p[index].xpos;
        int y =p[index].ypos;
     //   printf("%d %d",x,y);
    }
    p[verticles+1]=p[1];
    p[verticles+2]=p[2];
    int flag = get(1,2,3);
    bool isConvex = true;
    for(int index = 2 ;index<=verticles;index++)
    {
        int ans = flag*get(index,index+1,index+2);
        if(ans<0)
        {
            isConvex = false;
            break;
        }

    }
    if(isConvex)
    {
        printf("CONVEX");
    }
    else
    {
        printf("NOT_CONVEX");
    }

    return 0;
}
