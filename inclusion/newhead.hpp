#include <iostream>
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
//#include "gnuplot_i.hpp"
#include "python3.8/Python.h"
#include <vector>
#include <algorithm>

struct Point2d
{
    double x=0;
    double y=0;
};

struct Cubic
{
    double a;
    double b;
    double c;
    double d;
};

//"/mnt/hgfs/summer_program/curve_x.txt"

void readInToCubic(string FilePath, vector<Cubic>&dot_set);
int InputData_To_Vector(vector <float>& rt, string placement);

bool neighbor(int x0,int x1,int y0,int y1);
int closure(vector<float>& xvec,vector<float>& yvec);
float orientation(vector<float>& xs, vector<float>& ys);
// int inclusion(vector<float>& x1, vector<float>& y1, vector<float>& x2, vector<float>& y2);
// int inclusion2(vector<float>& x1, vector<float>& y1, vector<float>& x2, vector<float>& y2);


int point_selection(vector<float>&xdot,\
vector<float>&ydot,vector<float>&p1,vector<float>&p2,int N);
int interp_simple(vector<float>&dotx,vector<float>&aind,vector<float>&bind,\
    vector<float>&cind,vector<float>&dind);
int curve_interp(vector<float> &xdot,\
vector<float> &ydot,vector<float> &xa,\
    vector<float> &xb,vector<float> &xc,\
    vector<float> &xd,vector<float> &ya,vector<float> &yb,\
    vector<float> &yc,\
    vector<float> &yd,int N);
int interp_gen(vector<float> &xls,vector<float>&vec);
int interp_simple(vector<float>&dotx,\
vector<float>&aind,\
vector<float>&bind,vector<float>&cind,v\
ector<float>&dind);


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

/***************************************/
/*based on the shoelace formula:
//return the orientated S of 2d shape.
//https://en.wikipedia.org/wiki/Shoelace_formula*/
/***************************************/
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

int pyread()//,wchar_t **argv_tmp)
{

	Py_Initialize();

	if (!Py_IsInitialized())
	{
		return -1;
	}
	
	PyRun_SimpleString("import sys");

    wchar_t **argv_tmp;
	wchar_t *tmp = (wchar_t *)"";
	argv_tmp = &tmp;
    
    PySys_SetArgv(0, argv_tmp);
	
	if (PyRun_SimpleString("exec(open('./read_txt.py').read())") == 0)
	{
		return -1;
	}
	
	Py_Finalize();
	return 0;
}


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


void readInToCubic(string FilePath, vector<Cubic>&dot_set) {
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
		Cubic nums={};
        vector<double>num_ind={};
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
			num_ind.push_back(a);
			p = strtok(NULL, split);
		}//end while
        nums.a=num_ind[0];nums.b=num_ind[1];
        nums.c=num_ind[2];nums.d=num_ind[3];
        dot_set.push_back(nums);
        //std::cout << dot_add.x <<std::endl;
		//end for
		i++;
	}//end while
	//in.close();
    //std::cout << "read  data" << std::endl;
}


/************************************************************************/
	/* Shengjin formula for cubic equation
	    delta(f)=B^2-4AC
	*/
/************************************************************************/
void cubic(double a,double b,double c,double d,vector<double> &X123)
{
	
	double A=b*b-3*a*c;
	double B=b*c-9*a*d;
	double C=c*c-3*b*d;
	double f=B*B-4*A*C;
	double i_value;
	double Y1,Y2;
	if (fabs(A)<1e-6 && fabs(B)<1e-6)//公式1
	{
		X123.push_back(-b/(3*a));
		X123.push_back(-b/(3*a));
		X123.push_back(-b/(3*a));
	}
	else if (fabs(f)<1e-6)   //公式3
	{
		double K=B/A;
		X123.push_back(-b/a+K);
		X123.push_back(-K/2);
		X123.push_back(-K/2);
	}
	else if (f>1e-6)      //公式2
	{
		Y1=A*b+3*a*(-B+sqrt(f))/2;
		Y2=A*b+3*a*(-B-sqrt(f))/2;
		double Y1_value=(Y1/fabs(Y1))*pow((double)fabs(Y1),1.0/3);
		double Y2_value=(Y2/fabs(Y2))*pow((double)fabs(Y2),1.0/3);
		X123.push_back((-b-Y1_value-Y2_value)/(3*a));
		i_value=sqrt(3.0)/2*(Y1_value-Y2_value)/(3*a);
		if (fabs(i_value)<1e-1)
		{
			X123.push_back((-b+0.5*(Y1_value+Y2_value))/(3*a));
		}
	}
	else if (f<-1e-6)   //公式4
	{
		double T=(2*A*b-3*a*B)/(2*A*sqrt(A));
		double S=acos(T);
		X123.push_back((-b-2*sqrt(A)*cos(S/3))/(3*a));
		X123.push_back((-b+sqrt(A)*(cos(S/3)+sqrt(3.0)*sin(S/3)))/(3*a));
		X123.push_back((-b+sqrt(A)*(cos(S/3)-sqrt(3.0)*sin(S/3)))/(3*a));
	}
}
