//first give the negatively oriented square brackets of curve position
//reverse all curves and fill them
//give a background color same as bracket


//note:the brackets can be on the same position if add function"overlap"
//save bracket as curve00/10 for use in union.


#include"header.hpp"
using std::cout;
//args=0/1
//decides which txt to read

int f=1; //index of shape
int num=11; //number of curves in the shape
int deviate=0;

vector<vector <Point2d>> Set={};
string str;
vector<Point2d>polygon1={};vector<Point2d>polygon2={};


int main()
{
for (int j=deviate;j<num+deviate;j++)
	{
	str= "./curve"+to_string(f)+to_string(j)+".txt";
	polygon1={};
	readInToPointVec(str, polygon1);int manage=polygon1.size();
    for (int phi=0;phi<manage;phi++)
    {
        polygon1[phi].x=polygon1[phi].x*100;
        polygon1[phi].y=polygon1[phi].y*100;}
    reverse(polygon1.begin(),polygon1.end());
	//save_txt(polygon1, "./result.txt","border");
	Set.push_back(polygon1);}

vector<int>inside_count={};
int count=0;
for (int i=0;i<num;i++)
{
    count=0;
    for (int j=0;j<num;j++)
    {
        if (isPointInsidePoly2(Set[i][0],Set[j]))// i in j
        {
            count ++;
        }
    }
    inside_count.push_back(count);
}
int max_layer=*max_element(inside_count.begin(),inside_count.end());
vector<string>condition={"intersect","hollow"};int flagging;
for (int layer=0;layer<=max_layer;layer++)
{
    for (int pol_id=0;pol_id<num;pol_id++)
    {
        if (inside_count[pol_id]==layer)
        {
            if (orientation(Set[pol_id])>0)
            {
                flagging=0;
            }
            else
            {
                flagging=1;
            }
            save_txt(Set[pol_id], "./result.txt", condition[flagging]);
        }
    }
}
Py_plot();
return 0;
}
