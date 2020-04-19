#include <iostream>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <algorithm>
#include <math.h>
#include <vector>
#include <string>

using namespace std;
const int INF = 0x3f3f3f;
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
    double dot(Point p)
    {
        return
    }

};
typedef Point Vector;
int get_miniumnY_point_id(Vector *points,int size)
{
    int i,min_id = 0;
    double miny =INF;
    for(i = 0 ;i<size;i++)
    {
        if(points[i].ypos<miny)
        {
            miny = points[i].ypos;
            min_id =i;
        }
    }
    return min_id;
}
void get_cosine(Vector *points,double *mcos,int id,int size)
{
    int i ;
    double cosine;
    for(i = 0;i<size;i++)
    {
        if(i == id)
        {
            mcos[i]=2;
        } else{
            double deminator = (points[i].xpos-points[id].xpos)*(points[i].xpos-points[id].xpos)+(points[i].ypos-points[id].ypos)*(points[i].ypos-points[id].ypos);
            cosine =(points[i].xpos-points[id].xpos)/sqrt((deminator));
            mcos[i]= cosine;
        }
    }
}
void sort_points(Vector *points,double *mcos,int size)
{
    int i,j;
    double tempCosine;
    Vector tempPoint;
    for(i =0 ;i<size;i++)
    {
        for ( j = 0; j < size-i-1; j++)
        {
            //buble sort
            tempCosine=mcos[j];
            mcos[j]= mcos[j+1];
            mcos[j+1]= tempCosine;

            tempPoint= points[j];
            points[j]= points[j+1];
            points[j+1] = tempPoint;
        }
    }

}
int counterClockwise(Vector a,Vector b,Vector c)
{
    // judge if it is counter-clockwise
    double area2 = (b.xpos-a.xpos)*(c.ypos-a.ypos)-(b.ypos-a.ypos)*(c.xpos-a.xpos);
    if(area2<0)
    {
        return -1 ;//clockwise
    } else{
        if(area2>0)
        {
            return 1; // counterclosewise
        } else
        {
            return 0; //collinear;
        }
    }
}

void get_outpoint(Vector *points, int size){    //get points in stack
    int i, k;
    vector <Point>outpoint;
    outpoint.push_back(points[0]);
    outpoint.push_back(points[1]);
    i = 2;
    while(true){
        if(i == size){
            break;
        }
        if(counterClockwise(outpoint[outpoint.size() - 2], outpoint[outpoint.size() - 1], points[i]) > 0){
            outpoint.push_back(points[i]);
            i = i + 1;
        }
        else{
            outpoint.pop_back();
        }
    }
    cout << "The outpoints are: " << endl;
    for(k = 0; k < outpoint.size(); k++){
        cout << outpoint[k].xpos << " " << outpoint[k].ypos << endl;
    }
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
    for(int i = 0 ;i<verticles;i++)
    {
        int x = inputArray[2*i];
        int y = inputArray[2*i+1];
        Point temp(x,y);
        polygon.push_back(temp);
    }
    double *mcos = new double[verticles];
    Vector *points = new Vector[verticles];
    for(int i=0;i<verticles;i++)
    {
        points[i].xpos=polygon[i].xpos;
        points[i].ypos=polygon[i].ypos;
    }
    int minYPointId = get_miniumnY_point_id(points,verticles);
    get_cosine(points,mcos,minYPointId,verticles);
    sort_points(points,mcos,verticles);
    get_outpoint(points,verticles);
    delete []mcos;
    delete []points;

    return 0;
}
