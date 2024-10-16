#include <iostream>
#include <fstream>
using namespace std;
#include <vector>
#include <string>
#include <cmath>
#include <math.h>
#include <fstream>
#include <sstream>
#include <dirent.h>
#include <cstdlib>
#include <Eigen/Core>
#include <Eigen/LU>
#include "python3.8/Python.h"
#include <vector>
#include <algorithm>

using std::vector;
using std::count;
using std::cout;
using std::endl;

struct Point2d
{
    double x=0;
    double y=0;
};

/*PointWithPos records the relative position 
along with the x y axis of points:
in = 0:not inside the other yin set
in = 1:inside yin set
in = 2:intersect*/
struct PointWithPos
{
    double x=0;
    double y=0;
    int in = 0;
    
};

struct line {
    double x1;
    double y1;
    double x2;
    double y2;
};


/*pointinfo records the position of interrsection points,
along with the index of the two polygons that are intersected*/
struct PointInfo {
    Point2d pt;
    //line l1;//from polygon1
    //line l2;//from polygon2
    int pol1;
    int pol2;
    //int ind1;int ind2;
};
struct int_tuple {
    int int1;
    int int2;
};


int Py_plot();

void intersect_trace(vector<Point2d>&dot1,vector<Point2d>&dot2,vector<PointWithPos>&in_1,
    vector<PointWithPos>&in_2,vector<PointInfo>&intersect_info,int indpoly1,int indpoly2);

void yin_trace(vector<Point2d>&dot,vector<PointWithPos>&new_dot, \
vector<vector<Point2d>>&yin);

bool overlap(vector<vector<Point2d>>& route_group,vector<Point2d>&route);

int Point_walk(vector<PointInfo>& intersect_info,vector<vector<PointWithPos>>&yin1,\
vector<vector<PointWithPos>>&yin2,vector<vector<Point2d>>& route_group);
int road_finding_inPoly(vector<vector<PointWithPos>> &yin1,vector<vector<PointWithPos>> \
&yin2,PointInfo &begin_inf,vector<Point2d>&route,vector<PointInfo> &intersect_info);
void line_order(vector<PointInfo> &intersect_info,vector<PointWithPos>&in_1,
vector<PointWithPos>&new_in1,int poly_ind,int yin_ind);
float dist(PointWithPos a,PointWithPos b);
bool intersection(const line &l1, const line &l2);
int intersection_position(const line &l1, const line &l2, Point2d &dot);
float orientation(vector<Point2d>&dtv);
int isPointInsideYin(Point2d& P,std::vector<vector<Point2d>>& polyVertices);
int findPointInPoly(Point2d dot,vector<PointWithPos> &poly);

int dblcmp(double a,double b);double dot(double x1,double y1,double x2,double y2);
int point_on_line(Point2d a,Point2d b,Point2d c);
double cross(double x1,double y1,double x2,double y2);
double ab_cross_ac(Point2d a,Point2d b,Point2d c);
int intersection_position(const line &l1,const line &l2,Point2d&p);

int isPointInsidePoly2(Point2d& p, vector<Point2d>& ptPolygon);
bool isPointOnLine(Point2d end1,Point2d end2,Point2d point);
int InputData_To_Vector(vector <Point2d> &rt, string placement);

int save_txt(vector<Point2d>& xt, string location,string condition);
void readInToPointVec(string FilePath, vector<Point2d>&dot_set);



int Py_plot()
{

	Py_Initialize();

	if (!Py_IsInitialized())
	{
		return -1;
	}
	
	PyRun_SimpleString("import sys");

    wchar_t **argv_tmp;
    wchar_t *tmp = (wchar_t *)"xxx";
    argv_tmp = &tmp;
    
    PySys_SetArgv(0, argv_tmp);
	
	if (PyRun_SimpleString("exec(open('./plot.py').read())") == 0)
	{
		return -1;
	}
	
	Py_Finalize();
	return 0;
}

/************/
/*this function return whereabout of all intersections for two polygons
and save the information of intersection point in intersect_info*/
/************/
void intersect_trace(vector<Point2d>&dot1,vector<Point2d>&dot2,vector<PointWithPos>&in_1,
    vector<PointWithPos>&in_2,vector<PointInfo>&intersect_info,int indpoly1,int indpoly2)
{
    
    vector<int_tuple>point_info1;vector<int_tuple>point_info2;
    int len_poly2 = dot2.size();
    int len_poly1 = dot1.size();
    //vector<PointWithPos> in_1;vector<PointWithPos> in_2;
    
    int b_i = isPointInsidePoly2(dot1[0],dot2);
    //std::cout << b_i <<std::endl;
    PointWithPos p_i = {dot1[0].x,dot1[0].y,b_i};
    in_1.push_back(p_i);

    PointWithPos last;
    int_tuple v1;int_tuple v2;
    for (int i=1;i<=len_poly1;i++)
    {
        b_i=isPointInsidePoly2(dot1[i%len_poly1],dot2);
        //std::cout << b_i <<std::endl;
        last=in_1.back();
        if (b_i!=last.in)
        {
            v1 = {(i-1)%len_poly1,i%len_poly1};
            //std::cout << v1.int1 <<" "<<v1.int2<<std::endl;
            point_info1.push_back(v1);
            //point_info1.push_back(v2);
        }
        p_i = {dot1[i%len_poly1].x,dot1[i%len_poly1].y,b_i};
        in_1.push_back(p_i);
    }

    b_i = isPointInsidePoly2(dot2[0],dot1);
    p_i = {dot2[0].x,dot2[0].y,b_i};
    in_2.push_back(p_i);
    //std::cout << b_i <<std::endl;
    for (int i=1;i<=len_poly2;i++)
    {
        b_i=isPointInsidePoly2(dot2[i%len_poly2],dot1);
        //std::cout << b_i <<std::endl;
        last=in_2.back();
        if (b_i!=last.in)
        {
            v1 = {(i-1)%len_poly2,i%len_poly2};
            //v2 = {i,b_i};
            std::cout << v1.int1 <<" "<<v1.int2<<std::endl;
            point_info2.push_back(v1);
            //point_info2.push_back(v2);
        }
        p_i = {dot2[i%len_poly2].x,dot2[i%len_poly2].y,b_i};
        in_2.push_back(p_i);
    }
    // point_info: (index,in/out)
    // contain only 0-1 points; intersecting point=2 in=1 out=0
    // point_info is increasing on index
    //vector<PointInfo> intersect_info;

    int l0=(point_info1.size());int l1=(point_info2.size());
    for (int i=0;i<l0;i=i+1)
    {
        int ind1 = point_info1[i].int1;        
        //int ind2 = point_info1[(i+1)%l0].int1;
        int ind2 = point_info1[i].int2; 
        Point2d d11 = dot1[ind1]; Point2d d12 = dot1[ind2];
        line line1;
        line1.x1=d11.x;line1.y1=d11.y;line1.x2=d12.x;line1.y2=d12.y;
        for (int j=0;j<len_poly2;j=j+1)
        {
            int ind3=j;int ind4=(j+1)%len_poly2;
            Point2d d21 = dot2[ind3]; Point2d d22 = dot2[ind4];            
            line line2;
            line2.x1=d21.x;line2.y1=d21.y;line2.x2=d22.x;line2.y2=d22.y;
            if (intersection(line1,line2))
            {
                Point2d dot;
                intersection_position(line1,line2,dot);
                intersect_info.push_back({dot,indpoly1,indpoly2});
                std::cout << dot.x<<" "<<dot.y<<" "<<indpoly1<<" "<<indpoly2<<endl;
            }
        }
    }
    for (int i=0;i<l1;i=i+1)
    {
        int ind3 = point_info2[i].int1;        
        //int ind2 = point_info1[(i+1)%l0].int1;
        int ind4 = point_info2[i].int2; 
        Point2d d11 = dot2[ind3]; Point2d d12 = dot2[ind4];
        line line1;
        line1.x1=d11.x;line1.y1=d11.y;line1.x2=d12.x;line1.y2=d12.y;
        for (int j=0;j<len_poly1;j=j+1)
        {
            int ind1=j;int ind2=(j+1)%len_poly1;
            Point2d d21 = dot1[ind1]; Point2d d22 = dot1[ind2];            
            line line2;
            line2.x1=d21.x;line2.y1=d21.y;line2.x2=d22.x;line2.y2=d22.y;
            if (intersection(line1,line2))
            {
                Point2d dot;
                intersection_position(line1,line2,dot);
                intersect_info.push_back({dot,indpoly1,indpoly2});
                std::cout << dot.x<<" "<<dot.y<<" "<<indpoly1<<" "<<indpoly2<<endl;
            }
        }
    }
    
    //vector<PointInfo> intersect_copy=intersect_info;
}


 
//float CalculatePointToLineDistance(float point[2], const float p1[2], const float p2[2])
float CalculatePointToLineDistance(Point2d point, Point2d p1 , Point2d p2)
{
    float dis = 0.f;
 
    float dx = p2.x - p1.x;
    float dy = p2.y - p1.y;
 
    float k = -((p1.x - point.x)*dx + (p1.y - point.y)*dy) / ( dx*dx + dy*dy);
    float footX = k*dx + p1.x;
    float footY = k*dy + p1.y;
 
    if( footY >= min(p1.y, p2.y) && footY <=max(p1.y, p2.y)
        && footX >= min(p1.x, p2.x) && footX <=max(p1.x, p2.x ) )
    {
        dis = sqrtf((footX-point.x)*(footX-point.x) + \
        (footY-point.x)*(footY-point.x));
    }
    else 
    {
        float dis1 = sqrtf((p1.x-point.x)*(p1.x-point.x) + \
        (p1.y-point.y)*(p1.y-point.y));
        float dis2 = sqrtf((p2.x-point.x)*(p2.x-point.x) + \
        (p2.y-point.y)*(p2.y-point.y));
 
        dis = ( dis1 < dis2 ? dis1 : dis2 );
    }
 
    return dis;
}


//this is for yin sets
//return dots according to its relation to yin set
void yin_trace(vector<Point2d>&dot,vector<PointWithPos>&new_dot, \
vector<vector<Point2d>>&yin)
{
    int len_poly = dot.size();
    //vector<PointWithPos> in_1;vector<PointWithPos> in_2;
    int b_i;PointWithPos p_i;
    PointWithPos last;
    int_tuple v1;int_tuple v2;
    for (int i=0;i<len_poly;i++)
    {
        b_i=isPointInsideYin(dot[i%len_poly],yin);
        //std::cout << b_i <<std::endl;
        p_i = {dot[i].x,dot[i].y,b_i};
        new_dot.push_back(p_i);
    }
}

//if multiple intersections were on one line
//it may create confusion
//this function produce vector of ordered dots including all intersects
void line_order(vector<PointInfo> &intersect_info,vector<PointWithPos>&in_1,
vector<PointWithPos>&new_in1,int poly_ind,int yin_ind)
{
    //vector<PointWithPos>::iterator it;
    int length1=in_1.size();//int length2=in_2.size();
    int size_info = intersect_info.size();
    //vector<PointInfo>::iterator is;
    for(int i=0;i<length1;i++)
    {
        PointWithPos dot0=in_1[i];
        if (dot0.x!=0 || dot0.y!=0)
        {
        //PointWithPos dot0=in_1[i%(length1)];PointWithPos dot1=in_1[(i+1)%(length1)];
        new_in1.push_back(dot0);
        //if (dot0.in != dot1.in)
        //this is not the only way to have intersection!!!
        //intersection
        vector<PointWithPos> intersect_pt={};
        for (int j=0;j<size_info;j++)
        {
            int flag_online;
            Point2d pti = intersect_info[j].pt;
            vector<int> poly_have = {intersect_info[j].pol1,intersect_info[j].pol2};
            Point2d dot1={in_1[(i+1)%length1].x,in_1[(i+1)%length1].y};
            if (poly_have[yin_ind]!=poly_ind){continue;}
            if ((dot0.x<=pti.x<=dot1.x || dot1.x<=pti.x<=dot0.x) && \
                (dot0.y<=pti.y<=dot1.y || dot1.y<=pti.y<=dot0.y) ) //&&\
                //CalculatePointToLineDistance(pti,{dot0.x,dot0.y},dot1)<1)
                {flag_online=1;}
            if ((point_on_line(pti,{dot0.x,dot0.y},dot1)<=0) && flag_online==1)
            {
                PointWithPos pt_add = {pti.x,pti.y,2};
                intersect_pt.push_back(pt_add);
                std::cout <<dist(pt_add,dot0)<<"=distance"<<std::endl;
    //             if (((dot0.x<=pt_add.x<=in_1[(i+1)%length1].x)or\
    //             (dot0.x>=pt_add.x>=in_1[(i+1)%length1].x)) and\
    //     ((dot0.y<=pt_add.y<=in_1[(i+1)%length1].y) or (dot0.y>=pt_add.y>=in_1[(i+1)%length1].y)))
    // {
    // float eps = 1e-10;Point2d end1={dot0.x,dot0.y};Point2d end2={in_1[(i+1)%length1].x,in_1[(i+1)%length1].y};
    // float k0=(pt_add.x-end1.x)*(end2.y-end1.y);
    // float k1=(pt_add.y-end1.y)*(end2.x-end1.x);
    // if (abs(k0-k1)==0)
    // {
    //     std::cout <<dist(pt_add,dot0)<<"=real distance"<<std::endl;
    //     std::cout <<dot0.x<<pt_add.x<<in_1[(i+1)%length1].x<<"=real axis"<<std::endl;
    //     std::cout <<dot0.y<<pt_add.y<<in_1[(i+1)%length1].y<<"=real axis"<<std::endl;
    // }
    // }
                std::cout <<point_on_line(pti,{dot0.x,dot0.y},{in_1[(i+1)%length1].x,\
            in_1[(i+1)%length1].y})<<"=point"<<std::endl;
            }
        } 
        //rank intersection on the line
        int len_int = intersect_pt.size();
        int k;int l;PointWithPos temp;
        if (len_int>0)
        {
            if (len_int>1)
        {
            for (k=0;k<len_int-1;k++)
            {
                for (l=0;l<len_int-k;l++)
                {
                    if (dist(intersect_pt[k],dot0)>dist(intersect_pt[k+1],dot0))
                    {
                            temp=intersect_pt[k];
                            intersect_pt[k]=intersect_pt[k+1];
                            intersect_pt[k+1]=temp;
                        }
                }
                    
            }
        }

            //std::cout << dot0.x <<" "<<dot0.y<<std::endl;
            for (k=0;k<len_int;k++)
            {
                new_in1.push_back(intersect_pt[k]);
                int len_new=new_in1.size();
                //std::cout <<"position:"<< len_new <<std::endl;

            }
        }
        }
    }
    int size0=in_1.size();int size1=new_in1.size();
    std::cout << size0<<"size change="<<size1 << endl;
}




int findPointInPoly(Point2d dot,vector<PointWithPos> &poly)
{
    vector<PointWithPos>::iterator it;
    PointWithPos tobe;int k=0;int ret=-1;
    std::cout<< "finding point"<<endl;
    for (it=poly.begin();it!=poly.end();it++)
    {
        tobe=*it;
        if (abs(tobe.x-dot.x)<1e-6 && abs(tobe.y-dot.y)<1e-6)
        {
            ret=k;
            break;
        }
        //std::cout<< k<<endl;
        k++;
    }
    return ret;
}



//see if two routes are overlapping
bool overlap(vector<vector<Point2d>>& route_group,vector<Point2d>&route)
{
    vector<vector<Point2d>>::iterator it;
    int flag=0;int size_route=route.size();
    for (it=route_group.begin();it!=route_group.end();it++)
    {
        vector<Point2d> route_in=*it;
        vector<Point2d>::iterator it_route;
        vector<Point2d>::iterator it0;
        for (it_route=route.begin();it_route!=route.end();it_route++)
        {
            Point2d dot_inspect=*it_route;
            for (it0=route_in.begin();it0!=route_in.end();it0++)
            {
                Point2d dot = *it0;
                if (abs(dot.x-dot_inspect.x)<1e-6 && abs(dot.y-dot_inspect.y)<1e-6)
                {
                    flag++;
                }
            }
        }
    }
    
    if (float((size_route-flag)/size_route)<1e-2)
    {
        return true;
    }
    return false;
}



float dist(PointWithPos a,PointWithPos b)
{
    return (pow(a.x-b.x,2)+pow(a.y-b.y,2));
}

bool intersection(const line &l1, const line &l2)
{
    //quick rejection
    if ((l1.x1 > l1.x2 ? l1.x1 : l1.x2) < (l2.x1 < l2.x2 ? l2.x1 : l2.x2) ||
        (l1.y1 > l1.y2 ? l1.y1 : l1.y2) < (l2.y1 < l2.y2 ? l2.y1 : l2.y2) ||
        (l2.x1 > l2.x2 ? l2.x1 : l2.x2) < (l1.x1 < l1.x2 ? l1.x1 : l1.x2) ||
        (l2.y1 > l2.y2 ? l2.y1 : l2.y2) < (l1.y1 < l1.y2 ? l1.y1 : l1.y2))
    {
        return false;
    }
    //cross by vector dot() multiplication
    if ((((l1.x1 - l2.x1)*(l2.y2 - l2.y1) - (l1.y1 - l2.y1)*(l2.x2 - l2.x1))*
        ((l1.x2 - l2.x1)*(l2.y2 - l2.y1) - (l1.y2 - l2.y1)*(l2.x2 - l2.x1))) > 0 ||
        (((l2.x1 - l1.x1)*(l1.y2 - l1.y1) - (l2.y1 - l1.y1)*(l1.x2 - l1.x1))*
        ((l2.x2 - l1.x1)*(l1.y2 - l1.y1) - (l2.y2 - l1.y1)*(l1.x2 - l1.x1))) > 0)
    {
        return false;
    }
    return true;
}



int dblcmp(double a,double b)
{
    if (fabs(a-b)<=1e-10) return 0;
    if (a>b) return 1;
    else return -1;
}
//***************vector dot multiplication***************
double dot(double x1,double y1,double x2,double y2) //点积
{
    return x1*x2+y1*y2;
}
 
// if a on line bc
int point_on_line(Point2d a,Point2d b,Point2d c) 
{
    return dblcmp(sqrt(dot(b.x-a.x,b.y-a.y,c.x-a.x,c.y-a.y)),0);
}
//**************************************************
double cross(double x1,double y1,double x2,double y2)
{
    return x1*y2-x2*y1;
}
double ab_cross_ac(Point2d a,Point2d b,Point2d c) //vector ab x vector ac
{
    return cross(b.x-a.x,b.y-a.y,c.x-a.x,c.y-a.y);
}

int intersection_position(const line &l1,const line &l2,Point2d&p)
{
    Point2d a = {l1.x1,l1.y1};Point2d b = {l1.x2,l1.y2};
    Point2d c = {l2.x1,l2.y1};Point2d d = {l2.x2,l2.y2};
    double s1,s2,s3,s4;
    int d1,d2,d3,d4;
    d1=dblcmp(s1=ab_cross_ac(a,b,c),0);
    d2=dblcmp(s2=ab_cross_ac(a,b,d),0);
    d3=dblcmp(s3=ab_cross_ac(c,d,a),0);
    d4=dblcmp(s4=ab_cross_ac(c,d,b),0);
 
//if regularly intersect, derive intersection position
    if ((d1^d2)==-2 && (d3^d4)==-2)
    {
        p.x=(c.x*s2-d.x*s1)/(s2-s1);
        p.y=(c.y*s2-d.y*s1)/(s2-s1);
        return 1;
    }
 
//if not regularly intersect
    if (d1==0 && point_on_line(c,a,b)<=0)
    {
        p=c;
        return 0;
    }
    if (d2==0 && point_on_line(d,a,b)<=0)
    {
        p=d;
        return 0;
    }
    if (d3==0 && point_on_line(a,c,d)<=0)
    {
        p=a;
        return 0;
    }
    if (d4==0 && point_on_line(b,c,d)<=0)
    {
        p=b;
        return 0;
    }
return -1;
}


float orientation(vector<Point2d>&dtv)
{
    const int leng =dtv.size()-1;
    float area = 0;
    for (int i=0;i<leng;i++)
    {
        //area=area+xs[i]*ys[i+1]-xs[i+1]*ys[i];
        area=area+(dtv[i].x)*(dtv[i+1].y)-(dtv[i+1].x)*(dtv[i].y);
    }
    area=area+(dtv[leng].x)*(dtv[0].y)-(dtv[0].x)*(dtv[leng].y);
    //xs[leng]*ys[0]-xs[0]*ys[leng];
	return float(area);
}


int isPointInsideYin(Point2d& P,\
vector<vector<Point2d>>& yinVertices)
{
    int flag_positive=0;int flag_negative=0;
    vector<vector<Point2d>>::iterator it;
    for (it=yinVertices.begin();it!=yinVertices.end();it++)
    {
        vector<Point2d> poly=*it;
        if (orientation(poly)>0)
        {
            flag_positive=isPointInsidePoly2(P, poly)+flag_positive;
        }
        else{flag_negative=isPointInsidePoly2(P, poly)+flag_negative;}
    }
    if (flag_positive>flag_negative)
        {
            return 1;
        }
    return 0;
}

//decide if point is in polygon by the intersection number of line with polygon
int isPointInsidePoly2(Point2d& p, vector<Point2d>& ptPolygon)  
{  
	// 
	int nCross = 0; int nOverlap=0; 
    int nCount = ptPolygon.size();
	for (int i = 0; i < nCount; i++)   
	{  
		Point2d p1 = ptPolygon[i];  
		Point2d p2 = ptPolygon[(i + 1) % nCount];// line segment p1-p2  
 
		if ( p1.y == p2.y )  
			continue;  
		if ( p.y < min(p1.y, p2.y) )  
			continue;  
		if ( p.y >= max(p1.y, p2.y) )  
			continue;  
		// x-axis of intersection pt   
 
		double x = (double)(p.y - p1.y) * (double)(p2.x - p1.x) / (double)(p2.y - p1.y) + p1.x;  
 
		// only take into account the intersection on right hand side of the dot  
		if ( x >= p.x )  
		{  
			nCross++;  
		}
        //if (x = p.x)
        //{
        //    nOverlap++;
        //}
 
	}  
 
	// ncross even: point outside polygon  
	// ncross odd: point inside polygon
    //if (nOverlap==0)
    //{
	    if ((nCross % 2) == 1)
	    {
            return 1;
	    }
	    else
	    {
		    return 0;
	    }
    //}
    //else {return -1;}
} 


bool isPointOnLine(Point2d end1,Point2d end2,Point2d point)
{
    if (((end1.x<=point.x<=end2.x)||(end2.x<=point.x<=end1.x))&&\
        ((end1.y<=point.y<=end2.y)||(end2.y<=point.y<=end1.y)))
    {
    float eps = 1e-10;
    float k0=(point.x-end1.x)*(end2.y-end1.y);
    float k1=(point.y-end1.y)*(end2.x-end1.x);
    if (abs(k0-k1)==0)
    {
        return true;
    }
    }
    return false;
}


void readInToPointVec(string FilePath, vector<Point2d>&dot_set) {
    dot_set={};
    ifstream in(FilePath);
    //in.open(FilePath, ios::in);//opening file
	if (!in) {
		cout << "Can not find " << FilePath << endl;
		system("pause");
	}
	string buff;
	int i = 0;//line number i
	while (getline(in, buff)) {
		vector<double> nums;
		// string->char *
		char *s_input = (char *)buff.c_str();
		const char * split = " ";
		// 以‘ ’为分隔符拆分字符串
		char *p = strtok(s_input, split);
		double a;
		while (p != NULL) {
			// char * -> int
			a = atof(p);
			//cout << a << endl;
			nums.push_back(a);
			p = strtok(NULL, split);
		}//end while
		Point2d dot_add;
        dot_add.x = nums[0];
        dot_add.y = nums[1];
        dot_set.push_back(dot_add);
        //std::cout << dot_add.x <<std::endl;
		//end for
		i++;
	}//end while
	//in.close();
    std::cout << "read  data" << std::endl;
}

int save_txt(vector<Point2d>& xt, string location,string condition)
{
    ofstream location_out;
    
    location_out.open(location, std::ios::out | std::ios::app);  
       if (!location_out.is_open())
        return 0;
    vector<Point2d>::iterator it;
    for (it=xt.begin();it!=xt.end();it++)
    {
        Point2d dot=*it;
        location_out << dot.x <<" "<<dot.y << std::endl;
    }
    location_out <<"#" <<" "<<condition<<std::endl;
    location_out.close();
    std::cout<< "saved successfully."<<std::endl;
    return 0;
}