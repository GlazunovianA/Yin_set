#include"head.h"

//when using the program you have to input N by hand
//if youre using this for other pixel data
//you may check if they are closed with function "closure"
//cout <<"inform us of the whereabouts of your data:"<<endl;
//assume that different curves are parsed into different txt files
int main(){
std::cout << "how many curves are to be interpolated?"<<endl;
cin >> num_dir;
    
//int N=0;
//std::cout << "input the pixel intervals for interpolation:"<<" ";
//cin >> N;

//vector <vector<int>*>* x_ind =  new vector <vector<int>*>;
//vector <vector<int>*>* y_ind =  new vector <vector<int>*>;
//container for all indexes
//vector<float> *aidx;vector<float> *aidy;
//vector<float> *bidx;vector<float> *bidy;
//vector<float> *cidx;vector<float> *cidy;
//vector<float> *didx;vector<float> *didy;

vector<string> sgn;

for (int i=0;i<num_dir;i++){
//string strx="Computer/mnt/hgfs/summer_program/curve_x"+std::to_string(i)+".txt";
    //std::cout << i << ": "<<" ";
    
    string ist = to_string(i); 
    string strx ="/mnt/hgfs/summer_program/curve_data/curve_x"+ ist +".txt";
    string stry ="/mnt/hgfs/summer_program/curve_data/curve_y"+ ist +".txt";
    //cout <<strx<<" ";
    //cout <<stry<<" ";
    vector<float>* xvec=new vector<float>;
    vector<float>* yvec=new vector<float>;
    
    InputData_To_Vector(xvec, strx);
    InputData_To_Vector(yvec, stry);
    
    //print orientation information
    float ori = orientation(xvec, yvec);
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
    //output inclusion relations
    for (int j=0;j<num_dir;j++)
    {
        if (j!=i){
        string istj = to_string(j); 
        string strx ="/mnt/hgfs/summer_program/curve_data/curve_x"+ istj +".txt";
        string stry ="/mnt/hgfs/summer_program/curve_data/curve_y"+ istj +".txt";
        vector<float>* xvecj=new vector<float>;
        vector<float>* yvecj=new vector<float>;
        InputData_To_Vector(xvecj, strx);
        InputData_To_Vector(yvecj, stry);
        int inc = inclusion2(xvec,yvec,xvecj,yvecj);
        std::cout << inc <<" ";
        }
        else
        {
            std::cout << "i" << " ";
        }
    }
std::cout<< " " << endl;
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



int inclusion2(vector<float>* x1, vector<float>* y1, vector<float>* x2, vector<float>* y2)
{
    if (inclusion(x1,y1,x2,y2) and inclusion(x2,y2,x1,y1))
    {
        return 4;
        //std::cout << "mistake occured(invalid data)."<<endl;
    }
    else if (inclusion(x1,y1,x2,y2) and not inclusion(x2,y2,x1,y1))
    {
        return 2;
        // 1 is in 2
    }
    else if (not inclusion(x1,y1,x2,y2) and inclusion(x2,y2,x1,y1))
    {
        return 1;
        // 2 is in 1
    }
    //else if (not inclusion(x1,y1,x2,y2) and not inclusion(x2,y2,x1,y1))
    //{
        //return 0;
        // the two is separated
    //}

//std::cout<< "warning: mistake occured when confirming inclusion."<<endl;
return 0; }

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


bool neighbor(float x0,float x1,float y0,float y1){
    if (abs(x0-x1)<2 and abs(y0-y1)<2)
    {
        return true;
    }
    return false;
}

//return true if curve (pixel) ends meet
int closure(vector<float>* xvec,vector<float>* yvec)
{
    float x0 = xvec->front();float y0 = yvec->front();
    float xd = xvec->back();float yd = yvec->back();
    return neighbor(x0,xd,y0,yd);
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

//only work when no intersection exists 
//returns whether (x1,y1) is included in (x2,y2)
//x2,y2 should be closed
int inclusion(vector<float>* x1, vector<float>* y1, vector<float>* x2, vector<float>* y2)
{
    //if (not closure(x1,y1) or not closure(x2,y2))
    //{
    //    std::cout<< "fallacy!"<<endl;
    //}
    //else {std::cout<<"closed!"<<endl;}
    const int len1 =x1->size()-1;
    
    const int len2 =x2->size()-1;
    vector<float> nx1;vector<float> ny1;vector<float> nx2;vector<float> ny2;
    vector<float>::iterator it;
    vector<float>::iterator it2;
    vector<float>::iterator it3;
    vector<float>::iterator it4;
	for (it= x1->begin(); it!=x1->end(); it++)
	{
        nx1.push_back(*it);
	}
    for (it2= y1->begin(); it2!=y1->end(); it2++)
	{
        ny1.push_back(*it2);
	}
	for (it3= x2->begin(); it3!=x2->end(); it3++)
	{
        nx2.push_back(*it3);
	}
    for (it4= y2->begin(); it4!=y2->end(); it4++)
	{
        ny2.push_back(*it4);
	}
    
    
    vector<float>*k1;vector<float>*k2;
    for (int f=0;f<=len1;f++)
    {
        float x_1=nx1[f];float y_1=ny1[f];
        int flag1=0; int flag2=0; int flag3=0; int flag4=0; int flag5=0;
    for (int i=0;i<=len2;i++)
    {
        if (abs(nx2[i]-x_1)<1 and ny2[i]<y_1)
        {
            flag1=1;
        }
        if (abs(nx2[i]-x_1)<1 and ny2[i]>y_1)
        {
            flag2=1;
        }
        if (nx2[i]>x_1 and abs(ny2[i]-y_1)<1)
        {
            flag3=1;
        }
        if (nx2[i]<x_1 and (ny2[i]-y_1)<1)
        {
            flag4=1;
        }
        if (flag1==1 and flag2==1 and flag3==1 and flag4==1)
    {
        return true;
    }
        //if (nx2[i]==x_1 and ny2[i]==y_1)
        //{
        //    flag5=1;
        //}
    }
    }
    
    //if (flag5==1)
    //{
    //    std::cout << "mistake occured(intersection)." << endl;
    //}
    return false;
}

