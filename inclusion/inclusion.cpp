#include"newhead.hpp"

//when using the program you have to input N by hand
//if youre using this for other pixel data
//you may check if they are closed with function "closure"
//cout <<"inform us of the whereabouts of your data:"<<endl;
//assume that different curves are parsed into different txt files
int num_dir=19;
int inclusion(vector<Cubic>&x1,vector<Cubic>&y1,\
                vector<Cubic>&x2,vector<Cubic>&y2);
int point_inclusion(Point2d dot,\
                vector<Cubic>&x1,vector<Cubic>&y1);
int Curve_generate(int N,vector<Cubic>&curvex,\
vector<Cubic>&curvey,vector<Point2d>&polygon);
int isPointInsidePoly2(Point2d& p, vector<Point2d>& ptPolygon);
int inclusion_new(vector<Point2d>&poly1,vector<Point2d>&poly2);

int main(){

//pyread();

vector<string> sgn;
vector<Cubic>xvec;
vector<Cubic>yvec;
vector<Cubic>xvecj;
vector<Cubic>yvecj;
string strx;string stry;
int N=30;
vector<Point2d>polygon1;vector<Point2d>polygon2;
vector<vector<int>>inclusion_set={};
for (int i=0;i<num_dir;i++){
//string strx="Computer/mnt/hgfs/summer_program/curve_x"+std::to_string(i)+".txt";
    //std::cout << i << ": "<<" ";
    polygon1={};
    string ist = to_string(i); 
    strx ="./curve_x"+ ist +".txt";
    stry ="./curve_y"+ ist +".txt";
    //cout <<strx<<" ";
    //cout <<stry<<" ";
    xvec={};yvec={};
    
    readInToCubic(strx, xvec);
    readInToCubic(stry, yvec);
    int len_ind=xvec.size();
    vector<Point2d>xa(len_ind);
    
    for (int dd=0;dd<len_ind;dd++)
    {
        xa[dd].x=xvec[dd].a;xa[dd].y=yvec[dd].a;
    }
    //print orientation information
    float ori = orientation(xa);
    if (ori>0)
    {
        //std::cout <<  "+" << "   ";
        sgn.push_back("+");
    }
    else
    {
        //std::cout <<  "-" << "   ";
        sgn.push_back("-");
    }
    Curve_generate(N,xvec,yvec,polygon1);
    vector<int>inclusion_vec={};
    //output inclusion relations
    for (int j=0;j<num_dir;j++)
    {
        if (j!=i){
        polygon2={};
        string istj = to_string(j); 
        strx ="./curve_x"+ istj +".txt";
        stry ="./curve_y"+ istj +".txt";
        //std::cout << i <<" " <<j <<" ";
        xvecj={};yvecj={};
        readInToCubic(strx, xvecj);
        readInToCubic(stry, yvecj);
        Curve_generate(N,xvecj,yvecj,polygon2);
        int inc = inclusion_new(polygon1,polygon2);
        std::cout << inc <<" ";
        if (inc==1)
        {
            inclusion_vec.push_back(j);
        }
        }
        else
        {
            std::cout << "i" << " ";
        }
    }
inclusion_set.push_back(inclusion_vec);
std::cout << endl;
}

for (int inc=0;inc<num_dir;inc++)
{
    int len_single=inclusion_set[inc].size();
    std::cout<<inc<<":"<<endl;
    for (int ksi=0;ksi<len_single;ksi++)
    {
        std::cout<< inclusion_set[inc][ksi]<<" ";
    }
    std::cout<<endl;
}

std::cout << "the following is the orientation of each curve:" <<endl;
for (int k=0;k<num_dir;k++)
{
    std::cout << k << ": ";
    std::cout << sgn[k] << endl;
}

    //point_selection(strx,stry,xvec,yvec,N,i);
    //now the selected indexes are in  xvec yvec.

return 0;


}


int Curve_generate(int N,vector<Cubic>&curvex,\
vector<Cubic>&curvey,vector<Point2d>&polygon)
{
    vector<float>t_ind(N+1);
    //cout<<"up to here"<<endl;
    int phi = N;
    float interv = 1/N;
    for (float k=0;k<=phi;k++)
    {
        t_ind[k]=float(k/N);
    }
    //cout<<"up to here"<<endl;
    int len_ind = curvex.size();
    for (int j=0; j<len_ind; j++)
    {
        for (int f=0; f<phi+1;f++)
        {
        float addx = curvex[j].a+curvex[j].b*t_ind[f]+curvex[j].c\
        *pow((t_ind[f]),2) +curvex[j].d*pow((t_ind[f]),3);
        float addy = curvey[j].a+curvey[j].b*t_ind[f]+curvey[j].c\
        *pow((t_ind[f]),2) +curvey[j].d*pow((t_ind[f]),3);
        polygon.push_back({addx,addy});
        }
    }
return 0;
}

int inclusion_new(vector<Point2d>&poly1,vector<Point2d>&poly2)
{
    int len1=poly1.size();
    int len2=poly2.size();
    int flag_in=0;
    for (int i = 0; i<len2; i++)
    {
        flag_in=flag_in+isPointInsidePoly2(poly2[i],poly1);
    }
    if (float(flag_in/len2)>0.5)
    {
        return 1;
    }
    return 0;
}


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



/* return true if 2 in 1*/
int point_inclusion(Point2d dot,\
                vector<Cubic>&x1,vector<Cubic>&y1)
{

int nCross = 0; 
int nCount = x1.size();//number of curve pieces
vector<double> solution;
vector<int>solution_rec;
for (int i=0;i<nCount;i++)
{
    Cubic line = y1[i];vector<double>middle;
    cubic(line.d,line.c,line.b,line.a-dot.y,middle);
    vector<double>::iterator it;
    for (it=middle.begin();it!=middle.end();it++)
    {
        double decide=*it;int flag0=0;int flag1=0;
        if (decide>double(0))
        {
            flag0=1;
        }
        if (double(1)-decide>=0)
        {
            flag1=1;
        }
        if (flag0==1 && flag1==1)
        {
            //cout<<decide<<" ";
            solution.push_back(decide);
            solution_rec.push_back(i);
        }
    }
}
int sol_len=solution.size();
//cout<<endl;
for (int ind=0;ind<sol_len;ind++)
{
    Cubic xline=x1[solution_rec[ind]];
    double t = solution[ind];
        if (xline.a+xline.b*t+xline.c*pow(t,2)+xline.d*pow(t,3)>=dot.x)
        {nCross++;}
} 
//std::cout << nCross << endl;
if ((nCross % 2) == 1)
	    {
            return 1;
	    }
else
	    {
		    return 0;
	    }
}


int inclusion(vector<Cubic>&x1,vector<Cubic>&y1,\
                vector<Cubic>&x2,vector<Cubic>&y2)
{
int len1=x1.size();int len2=x2.size();
int flag=0;
for (int l=0;l<len1;l++)
{
    Point2d dot={x2[l].a,y2[l].a};
    flag=point_inclusion(dot,x1,y1)+flag;
}
if (float((flag)/len2)>float(0.5))
{
    return 1;
}
return 0;
}

int InputData_To_Vector(vector <float> *rt, string placement)
{     
    
    //cout << placement <<endl;
    *rt={};
    ifstream in (placement);
    if(!in)
 {
std::cout <<"no such file,please check the file name!"<< endl;
exit(0);
 }
    else{
        //cout << "Opened file." << endl;
        
    
    string line;
    while (getline(in,line))
    {
        //cout << line << endl;
        stringstream ss(line);
        float number;
        ss>>number;
        rt->push_back(number);
        //cout<< rt->size()<<" ";
        //pointer :-> variable: .
    }}
    return 0;
}


//based on the shoelace formula:
//return the orientated S of 2d shape.
//https://en.wikipedia.org/wiki/Shoelace_formula
float orientation(vector<float>* xs, vector<float>* ys)
{
    const int leng =xs->size()-1;
    vector<float> nx;vector<float> ny;
    float area = 0;
    vector<float>::iterator it;
	for (it= xs->begin(); it!=xs->end(); it++)
	{
        nx.push_back(*it);
	}{}
    for (it= ys->begin(); it!=ys->end(); it++)
	{
        ny.push_back(*it);
	}
    for (int i=0;i<leng;i++)
    {
        area=area+nx[i]*ny[i+1]-nx[i+1]*ny[i];
    }
    area=area+nx[leng]*ny[0]-nx[0]*ny[leng];

	return float(area);
}


