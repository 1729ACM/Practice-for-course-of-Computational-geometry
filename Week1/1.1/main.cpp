#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <algorithm>
using namespace std;
struct  Point
{
    int xpos,ypos;
    Point(){}
    Point(int xpos,int ypos):xpos(xpos),ypos(ypos){}
    Point operator+(Point B)
    {
        return Point(xpos+B.xpos,ypos+B.ypos);
    }
    Point operator-(Point B)
    {
        return Point(xpos-B.xpos,ypos-B.ypos);
    }


};
typedef Point Vector;
int Cross(Vector A,Vector B)
{
    return A.xpos*B.ypos-A.ypos*B.xpos;
}
struct Line
{
    Point p1,p2;
    Line(){}
    Line(Point p1,Point p2):p1(p1),p2(p2){}
};
typedef Line Segment;
enum Output
{
    ON_SEGMENT = 0,
    ON_LINE=1,
    LEFT =2,
    RIGHT = 3
};
int Point_Segment_relation(Point p,Segment v)
{
    int c = Cross(p-v.p1,v.p2-v.p1);
    int returnValue =0;
    if(c == 0)
    {
        int xLeft = min(v.p1.xpos,v.p2.xpos);
        int xRight = max(v.p1.xpos,v.p2.xpos);
        int yBottom = min(v.p1.ypos,v.p2.ypos);
        int yUp = max(v.p1.ypos,v.p2.ypos);;

        int xposP = p.xpos;
        int yposP = p.ypos;
        if((xposP>=xLeft)&&(xposP<=xRight)&&(yposP>=yBottom)&&(yposP<=yUp))
        {
            returnValue =ON_SEGMENT;
        }
        else
        {
            returnValue= ON_LINE;
        }
    }
    if(c<0)
    {
        returnValue =LEFT;
    }
    if(c>0)
    {
        returnValue =RIGHT;
    }
    return returnValue;
}
int main() {
    int Ax,Ay,Bx,By;
    scanf("%d%d%d%d",&Ax,&Ay,&Bx,&By);
    Point A(Ax,Ay);
    Point B(Bx,By);
    Segment AB(A,B);
    int number;
    scanf("%d",&number);
    for(int i =0 ;i<number;i++)
    {
        int targetX=0,targetY=0;
        scanf("%d%d",&targetX,&targetY);
        Point target(targetX,targetY);
        int result = Point_Segment_relation(target,AB);

        switch (result)
        {
            case ON_SEGMENT:
                printf("ON_SEGMENT\n");
                break;
            case ON_LINE:
                printf("ON_LINE\n");
                break;
            case LEFT:
                printf("LEFT\n");
                break;
            case RIGHT:
                printf("RIGHT\n");
                break;
        }
    }

    return 0;
}