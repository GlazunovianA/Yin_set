#include"newhead.hpp"

//when using the program you have to input N by hand
//if youre using this for other pixel data
//you may check if they are closed with function "closure"
//cout <<"inform us of the whereabouts of your data:"<<endl;
//assume that different curves are parsed into different txt files


int num_dir=19;

int save_txt_4(vector<float>& at,vector<float>&bt,\
vector<float>&ct,vector<float>&dt,vector<float>& aty,\
vector<float>&bty,\
vector<float>&cty,vector<float>&dty,
 string location,string condition)
{
    ofstream location_out;
    
    location_out.open(location, std::ios::out | std::ios::app);  
       if (!location_out.is_open())
        return 0;
    int len_save=at.size();
    for (int it=0;it<len_save;it++)
    {
        location_out << at[it] <<" "<<bt[it] \
        <<" "<<ct[it]<<" "<<dt[it]<<" "<<aty[it] \
        <<" "<<bty[it]<<" "<<cty[it]<<" "<<dty[it]<< std::endl;
    }
    location_out <<"#" <<" "<<condition<<std::endl;
    location_out.close();
    std::cout<< "saved successfully."<<std::endl;
    return 0;
}


int main(){


//std::cout << "how many curves are to be interpolated?"<<endl;
//cin >> num_dir;
    
int N=0;
std::cout << "input the pixel intervals for interpolation:"<<" ";
cin >> N;

//vector <vector<int>*>* x_ind =  new vector <vector<int>*>;
//vector <vector<int>*>* y_ind =  new vector <vector<int>*>;
//container for all indexes
//vector<float> *aidx;vector<float> *aidy;
//vector<float> *bidx;vector<float> *bidy;
//vector<float> *cidx;vector<float> *cidy;
//vector<float> *didx;vector<float> *didy;

pyread();

vector<float> x_t;vector<float> y_t;

for (int i=0;i<num_dir;i++){
//string strx="Computer/mnt/hgfs/summer_program/curve_x"+std::to_string(i)+".txt";
    //std::cout << i << ": "<<" ";
     
    string ist = to_string(i); 
    // string strx ="./curve_data/curve_x"+ ist +".txt";
    // string stry ="./curve_data/curve_y"+ ist +".txt";
    string strx ="./curve_x"+ ist +".txt";
    string stry ="./curve_y"+ ist +".txt";
    //cout <<strx<<" ";
    //cout <<stry<<" ";
    vector<float> xvec;
    vector<float> yvec;
    
    InputData_To_Vector(xvec, strx);
    InputData_To_Vector(yvec, stry);
    
    vector<float>aindx;vector<float>aindy;
    vector<float>bindx;vector<float>bindy;
    vector<float>cindx;vector<float>cindy;
    vector<float>dindx;vector<float>dindy;
    


    curve_interp(xvec,yvec,aindx,bindx,cindx,dindx,aindy,bindy,cindy,dindy,N);
    //aidx->insert(aidx->end(),aindx->begin(),aindx->end());
    //bidx->insert(bidx->end(),bindx->begin(),bindx->end());
    //cidx->insert(cidx->end(),cindx->begin(),cindx->end());
    //didx->insert(didx->end(),dindx->begin(),dindx->end());
    //aidy->insert(aidy->end(),aindy->begin(),aindy->end());
    //bidy->insert(bidy->end(),bindy->begin(),bindy->end());
    //cidy->insert(cidy->end(),cindy->begin(),cindy->end());
    //didy->insert(didy->end(),dindy->begin(),dindy->end());
    
    
    // vector<Point2d> xy;
    // //vector<float>av = *aindx;vector<float>avy = *aindy;
    // //vector<float>bv = *bindx;vector<float>bvy = *bindy;
    // //vector<float>cv = *cindx;vector<float>cvy = *cindy;
    // //vector<float>dv = *dindx;vector<float>dvy = *dindy;

    // //aindx->resize(0);bindx->resize(0);cindx->resize(0);dindx->resize(0);

    // vector<float>t_ind(N+1);
    // cout<<"up to here"<<endl;
    // int phi = N;
    // float interv = 1/N;
    // for (float k=0;k<=phi;k++)
    // {
    //     t_ind[k]=float(k/N);
    // }
    // cout<<"up to here"<<endl;
    // int len_ind = aindx.size();
    // for (int j=0; j<len_ind; j++)
    // {
    //     for (int f=0; f<phi+1;f++)
    //     {
    //     float addx = aindx[j]+bindx[j]*t_ind[f]+cindx[j]*pow((t_ind[f]),2) +dindx[j]*pow((t_ind[f]),3);
    
    //     float addy = aindy[j]+bindy[j]*t_ind[f]+cindy[j]*pow((t_ind[f]),2) +dindy[j]*pow((t_ind[f]),3);
    //     xy.push_back({addx,addy});
    //     }
    // }
    cout<<"up to here"<<endl;
    string savexy ="./result.txt";
    //string savey ="/mnt/hgfs/summer_program/interp_data/curve_y"+ ist +".txt";
    //vector<string>condition={"hollow","intersect"};int flag_save=0;
    save_txt_4(aindx,bindx,cindx,dindx,aindy,bindy,cindy,dindy, \
    savexy," ");
    // if (orientation(xy)>0)//positive
    // {   flag_save=1;}
    // else{   flag_save=0;}
    //     save_txt(xy, savexy,condition[flag_save]);
    //save_txt(y_i, savey);
    //vector<float>().swap(x_i);
    //vector<float>().swap(y_i);
    vector<float>().swap(aindx);
    vector<float>().swap(bindx);
    vector<float>().swap(cindx);
    vector<float>().swap(dindx);
    vector<float>().swap(aindy);
    vector<float>().swap(bindy);
    vector<float>().swap(cindy);
    vector<float>().swap(dindy);
    //vector<Point2d>().swap(xy);
}


Py_plot();


return 0;
}



int InputData_To_Vector(vector <float> &rt, string placement)
{     
    
    //cout << placement <<endl;
    rt={};
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
        rt.push_back(number);
        //cout<< rt->size()<<" ";
        //pointer :-> variable: .
    }}
    return 0;
}


int point_selection(vector<float>&xdo,\
vector<float>&ydo,vector<float>&p1,vector<float>&p2,int N)//int rank)
{
    int add1=0; int add2=0;
    vector<float>::iterator it;
    vector<float>::iterator it0;
    
    //xvec.assign(InputData_To_Vector(strx).begin(),InputData_To_Vector(strx).end());
    
    int Xdot= xdo.size();
    int Ydot= ydo.size();
    cout<<"0000000000000"<<" ";
    //for(it= xdo->begin(); it!=xdo->end(); it++)
    //{
    //    std::cout<< *it <<std::endl;
    //}

    //p1->reserve(100);p2->reserve(100);

    
    cout<< "select1"<<endl;
    for(it0= ydo.begin(); it0!=ydo.end(); it0++)
    {
        int dec = Ydot-add2;
        if  (int(add2%N)==0 and (double(dec)>10))
        {
            p2.push_back(*it0);
        }
        add2++;  
        //cout<< *it <<" ";
    }

    for(it= xdo.begin(); it!=xdo.end(); it++)
    {
        int dec = Xdot-add1;
        if  (int(add1%N)==0 and (double(dec)>10))
        {
        p1.push_back(*it);
        //std::cout<< *it <<endl;
        }
        add1++;
    }
    
    cout<< "select2"<<endl;
    return 0;

}


int curve_interp(vector<float> &xdt,\
vector<float> &ydt,vector<float> &xa,\
vector<float> &xb,vector<float> & xc,\
vector<float> &xd,vector<float> &ya,vector<float> &yb,\
vector<float> &yc,vector<float> &yd,int N)
{
    vector<float>ptx;vector<float>pty;
    int bottom = (xdt.size())/4;
    int interval = min(N,bottom);
    point_selection(xdt,ydt,ptx,pty,interval);
   
    //ptx pty
    
    //vector<float>::iterator it;
    //vector<float> t_pt;
    //int k=0;
	//for (it= ptx->begin(); it!=ptx->end(); it++)
	//{   
    //    t_pt.push_back(k);
    //    k++;
	//}
    
    interp_simple(ptx,xa,xb,xc,xd);
    interp_simple(pty,ya,yb,yc,yd);
return 0;
}

//vec should be empty
int interp_gen(vector<float> &nx,vector<float> &vec)
{
    
    
    const int leng = nx.size();
    for (int i=1;i<(leng-1);i++)
    {
        float ad = nx[i+1]-2*nx[i]+nx[i-1];
        vec.push_back(ad);
    }
    vec.insert(vec.begin(),nx[1]-2*nx[0]+nx[leng-1]);
    float ad = nx[0]-2*nx[leng-1]+nx[leng-2];
    vec.push_back(ad);
    return 0;
}


int interp_simple(vector<float>&nx,vector<float>&aind,vector<float>&bind,\
    vector<float>&cind,vector<float>&dind)
{
    //vector<float> nx;
    
    //vector<float>::iterator it;
	//for (it= dotx->begin(); it!=dotx->end(); it++)
	//{
    //    nx.push_back(*it);
	//}
    const int leng = nx.size();
    
    Eigen::MatrixXd A0 (leng,leng);
    A0  = Eigen::MatrixXd::Identity(leng,leng);
    std::cout <<"matrix 0"<<endl;
    Eigen::MatrixXd A1(leng,leng);
    A1.topRightCorner(leng-1,leng-1)= Eigen::MatrixXd::Identity(leng-1,leng-1);
    A1.topLeftCorner(leng-1,1) = Eigen::MatrixXd::Zero(leng-1,1);
    A1.bottomLeftCorner(1,1)=Eigen::MatrixXd::Zero(1,1);
    A1.bottomRightCorner(1,leng-1)=Eigen::MatrixXd::Zero(1,leng-1);
    Eigen::MatrixXd A2(leng,leng);
    A2.topRightCorner(1,1).setZero();
    A2.topLeftCorner(1,leng-1).setZero();
    A2.bottomLeftCorner(leng-1,leng-1).setIdentity();
    A2.bottomRightCorner(leng-1,1).setZero();
    Eigen::MatrixXd A = A0*4 +A1 +A2;
    A(0,leng-1)=1;A(leng-1,0)=1;
    
    Eigen::MatrixXd B= A.inverse();
    B=B*6;
    
    vector<float>vec;
    interp_gen(nx,vec);
    
    vector<float>::iterator it0;
    Eigen::RowVectorXd m0 (leng);
    int k=0;

    for (it0= vec.begin(); it0!=vec.end(); it0++)
	{
        m0(k)=float(*it0);
        k++;
	}
    
    std::cout <<"matrix 1"<<endl;
    Eigen::MatrixXd m_vec=B*(m0.transpose());
    std::cout <<"matrix 2"<<endl;
    
    for (it0=nx.begin();it0!=nx.end();it0++)
    {
        aind.push_back(*it0);
    }
    std::cout <<"matrix 3"<<endl;
    for (int i=0;i<(leng-1);i++)
    {
        dind.push_back(float((m_vec(i+1)-m_vec(i))/6));
    }
    dind.push_back(float((m_vec(0)-m_vec(leng-1))/6));
    std::cout <<"matrix 4"<<endl;
    for (int j=0;j<leng;j++)
    {
        cind.push_back(float(m_vec(j)/2));
    }
    std::cout <<"matrix 5"<<endl;
    // vector<float> dind_v;
    // //vector<float>::iterator itt;
    // for (it0=dind.begin();it0!=dind.end();it0++)
    // {
    //     dind_v.push_back(*it0);
    // }
    for (int k=0;k<(leng-1);k++)
    {
        bind.push_back(float(nx[k+1]-nx[k]-(0.5)*m_vec(k)-dind[k]));
    }
    bind.push_back(float(nx[0]-nx[leng-1]-(0.5)*m_vec(leng-1)-dind[leng-1]));
    //std::cout <<"matrix 6"<<endl;
    
    // cout << aind.size()<<" ";cout <<bind.size()<<" ";
    // cout << cind.size()<<" ";cout <<dind.size()<<" ";
    //cout << dind[1] <<endl;
    return 0;
}