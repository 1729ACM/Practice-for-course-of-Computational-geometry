#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <algorithm>
#include <math.h>
#include <vector>
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

};
typedef Point Vector;


struct Line
{
    Point s,e;
    double k;
    Line(){}
    Line(Point _s,Point _e)
    {
        s = _s;e = _e;
        k = atan2(e.ypos - s.ypos,e.xpos - s.xpos);
    }
    //computation the intersection of two line
    //the first value is 0 meaning two line are same,1 is paraleel ,2 is interseection

    pair<int,Point> operator &(const Line &b)const
    {
        Point res = s;
        if(sgn((s-e)^(b.s-b.e)) == 0)
        {
            if(sgn((s-b.e)^(b.s-b.e)) == 0)
                return make_pair(0,res);//intersection
            else return make_pair(1,res);//parallel
        }
        double t = ((s-b.s)^(b.s-b.e))/((s-e)^(b.s-b.e));
        res.xpos += (e.xpos-s.xpos)*t;
        res.ypos += (e.ypos-s.ypos)*t;
        return make_pair(2,res);
    }
};

//check whehter point is on the segment
bool OnSeg(Point p,Line L)
{
   bool condtion = (sgn((L.s-p)^(L.e-p))==0&&
                    sgn((p.xpos-L.s.xpos)*(p.xpos-L.e.xpos))<=0&&
                    sgn((p.ypos-L.s.ypos)*(p.ypos-L.e.ypos))<=0);
   return condtion;
}
//check whehter two lines are intersected with each other
bool inter(Line l1,Line l2)
{
    bool condition = ( max(l1.s.xpos,l1.e.xpos) >= min(l2.s.xpos,l2.e.xpos) &&
                       max(l2.s.xpos,l2.e.xpos) >= min(l1.s.xpos,l1.e.xpos) &&
                       max(l1.s.ypos,l1.e.ypos) >= min(l2.s.ypos,l2.e.ypos) &&
                       max(l2.s.ypos,l2.e.ypos) >= min(l1.s.ypos,l1.e.ypos) &&
                       sgn((l2.s-l1.s)^(l1.e-l1.s))*sgn((l2.e-l1.s)^(l1.e-l1.s)) <= 0 &&
                       sgn((l1.s-l2.s)^(l2.e-l1.s))*sgn((l1.e-l2.s)^(l2.e-l2.s)) <= 0);
    return condition;

}

//check the point is in the polygon or not
//Ray method, the number of vertices of poly [] should be greater than or equal to 3, and the number of points: 0 ~ n-1
//return value
//-1：outside the polygon
//0：in the boundary of polygon
//1：inside the polygon
int inPoly(Point p,vector<Point>&triangle, int n)
{
    int cnt=0;
    Line ray,side;
    ray.s=p;
    ray.s.ypos=p.ypos;
    ray.e.xpos=-100000000000.0;//-INF,in order to not overflow

    for(int i=0;i<n;i++)
    {
        side.s=triangle[i];
        int endIndex = (i+1)%n;
        Point end(triangle[endIndex]);
        int endX = end.xpos;
        int endY = end.ypos;
        side.e.xpos=endX;
        side.e.ypos = endY;
        if(OnSeg(p,side))   return 0;
        //Not considered if parallel axis
        if(sgn(side.s.ypos-side.e.ypos)==0)
            continue;
        if(OnSeg(side.s,ray)){
            if(sgn(side.s.ypos-side.e.ypos)>0)
                cnt++;
        }
        else if(OnSeg(side.e,ray)){
            if(sgn(side.e.ypos-side.s.ypos)>0)
                cnt++;
        }
        else if(inter(ray,side))
            cnt++;
    }
    if(cnt%2==1)
        return 1;
    else
        return -1;
}
int main() {
    int Ax,Ay,Bx,By,Cx,Cy;
    vector<Point>triangle;
    scanf("%d%d%d%d%d%d",&Ax,&Ay,&Bx,&By,&Cx,&Cy);
    Point A(Ax,Ay);
    Point B(Bx,By);
    Point C(Cx,Cy);
    triangle.push_back(A);
    triangle.push_back(B);
    triangle.push_back(C);
    int tc=0;
    scanf("%d",&tc);
    for(int i =0;i<tc;i++)
    {
        int tx,ty;
        scanf("%d%d",&tx,&ty);
        Point t(tx,ty);

        int returnValue = inPoly(t,triangle,3);

        switch (returnValue)
        {
            case -1:
                printf("OUTSIDE\n");
                break;
            case 0:
                printf("BORDER\n");
                break;
            case 1:
                printf("INSIDE\n");
                break;
        }
    }
    return 0;
}