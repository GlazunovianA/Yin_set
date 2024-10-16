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

//"/mnt/hgfs/summer_program/curve_x.txt"

int num_dir=19;

int InputData_To_Vector(vector <float> *rt, string placement);

bool neighbor(int x0,int x1,int y0,int y1);
int closure(vector<float>* xvec,vector<float>* yvec);
float orientation(vector<float>* xs, vector<float>* ys);
int inclusion(vector<float>* x1, vector<float>* y1, vector<float>* x2, vector<float>* y2);
int inclusion2(vector<float>* x1, vector<float>* y1, vector<float>* x2, vector<float>* y2);


int point_selection(string strx,string stry,vector<float>*p1,vector<float>*p2,int N);
int save_txt(vector<float>* xt, string location);
int interp_simple(vector<float>*dotx,vector<float>*aind,vector<float>*bind,\
    vector<float>*cind,vector<float>*dind);
int curve_interp(vector<float>*xdot,\
vector<float>*ydot,vector<float> *xa,\
    vector<float> *xb,vector<float> *xc,\
    vector<float> *xd,vector<float> *ya,vector<float> *yb,vector<float> *yc,\
    vector<float> *yd,int N);
int interp_gen(vector<float> *xls,vector<float>*vec);
int interp_simple(vector<float>*dotx,\
vector<float>*aind,\
vector<float>*bind,vector<float>*cind,v\
ector<float>*dind);