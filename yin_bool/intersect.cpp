#include"header.hpp"
using std::cout;
//args=0/1
//decides which txt to read

int num1=6;int num2=10;
//if point relation is strongly affected by small distance:
//1. fix condition of point_on_line function
//2. multiply all points by a parameter of 100 etc.
int deviate=1;
vector<int>num={num1,num2};
//the number of curves in 2 polygon

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

//road_finding_inPoly(yin1,yin2,dt,route);
//begin_inf is the information of beginning point
//starting in YIn1






// int intersect_function(vector<Point2d>&polygon1,vector<Point2d>&polygon2)
// {
// int flag=0;
// if (orientation(polygon1)>0 && orientation(polygon2)>0)
// //positive intersection
// {
// 	flag=1;}
// else //hollow
// { 	if ((orientation(polygon1)<0 && orientation(polygon2)>0)\
// 		|| (orientation(polygon1)>0 && orientation(polygon2)<0))
// 	{
// 		vector<Point2d> temp={};
// 		vector<Point2d>::reverse_iterator riter;
// 		for (riter=polygon1.rbegin();riter!=polygon1.rend();riter++)
// 		{
// 			temp.push_back(*riter);}
// 		polygon1=temp;
// 	}
// }
// std::cout <<"___________flag_____________"<< flag<<endl;
// vector<PointWithPos> inside1;
// vector<PointWithPos> inside2;
// vector<PointInfo> intersect_inf;

// intersect_trace(polygon1,polygon2,inside1,inside2,intersect_inf);
// //std::cout<< "intersection trace found."<<std::endl;


// // vector<Point2d>inter_poly;
// // int len_in =inside1.size();
// // for (int i=0;i<len_in;i++)
// // {
// //     if (inside1[i].in>1)
// //     {
// //         Point2d pt_add;
// //         pt_add.x=inside1[i].x;pt_add.y=inside1[i].y;
// //         inter_poly.push_back(pt_add);
// //         std::cout<<pt_add.x <<pt_add.y <<std::endl;
// //     }

// // }

// vector<vector<Point2d>> poly_group = {polygon1,polygon2};//inter_poly};

// for (int i=0;i<2;i++)
// {
//      string savex ="./result.txt";
//      save_txt(poly_group[i], savex,"border");
// }
// // Py_plot();


// vector<vector<Point2d>> route_group;

// Point_walk(intersect_inf,inside1,inside2,route_group);
// //std::cout<< "intersection 2."<<std::endl;
// int len_route=route_group.size();

// for (int i=0;i<len_route;i++)
// {
//     string savex ="./result.txt";
// 	if (flag==1)
//     {	save_txt(route_group[i], savex,"intersect");}
// 	else
// 	{	save_txt(route_group[i], savex,"hollow");}
// }
// return 0;
// }



int save_txt_pos(vector<PointWithPos>& xt, string location,string condition)
{
    ofstream location_out;
    
    location_out.open(location, std::ios::out | std::ios::app);  
    //write into txts in a continuual manner
    //if txt not existent then create new txt
       if (!location_out.is_open())
        return 0;
    vector<PointWithPos>::iterator it;
    for (it=xt.begin();it!=xt.end();it++)
    {
        PointWithPos dot=*it;
        location_out << dot.x <<" "<<dot.y << std::endl;
    }
    location_out <<"#" <<" "<<condition<<std::endl;
    location_out.close();
    std::cout<< "saved successfully."<<std::endl;
    return 0;
}

//decide if point is an intersection

bool in_info(vector<PointInfo>&inter_info,Point2d dot)
{
    vector<PointInfo>::iterator inter;
    for (inter=inter_info.begin();inter!=inter_info.end();inter++)
    {
        PointInfo ift= *inter;
        if (abs(ift.pt.x-dot.x)<1e-6 && abs(ift.pt.y-dot.y)<1e-6)
        {
            return true;
        }
    }
    return false;
}

int main()
{

//pyread();

//first make out all intersection point position with intersect_trace

vector<vector <Point2d>> Set1={};vector<vector <Point2d>> Set2={};
vector<vector<vector<Point2d>>> Shape={Set1,Set2};
string str;
vector<Point2d>polygon1={};vector<Point2d>polygon2={};

for (int f=0;f<2;f++)
{
	for (int j=deviate;j<num[f]+deviate;j++)
	{
	str= "./curve"+to_string(f)+to_string(j)+".txt";
	polygon1={};
	readInToPointVec(str, polygon1);int manage=polygon1.size();
    for (int phi=0;phi<manage;phi++)
    {
        polygon1[phi].x=polygon1[phi].x*100;
        polygon1[phi].y=polygon1[phi].y*100;}
	save_txt(polygon1, "./result.txt","border");
	Shape[f].push_back(polygon1);}
}
	//cout << endl;
int len0=Shape[0].size();int len1=Shape[1].size();
vector<int>len={len0,len1};
vector<Point2d>curve0;vector<Point2d>curve1;

vector<PointInfo>intersect_info={};
vector<vector<PointWithPos>> yin1(num[0]);
vector<vector<PointWithPos>> yin2(num[1]);
vector<vector<vector<PointWithPos>>> Yin={yin1,yin2};
vector<PointWithPos>in1={};vector<PointWithPos>in0={};
for (int i=0;i<len0;i++)
{
	curve0=Shape[0][i];
	for(int j=0;j<len1;j++)
	{
		curve1=Shape[1][j];
		intersect_trace(curve0,curve1,in0,in1,intersect_info,i,j);
		in0={};in1={};
	}
}
for (int f=0;f<2;f++)
{
	//curve0=Shape[0][i];
	for(int j=0;j<num[f];j++)
	{
		vector<PointWithPos>in1={};
		curve1=Shape[f][j];
		yin_trace(curve1,in1, Shape[1-f]);
		Yin[f][j]=in1; int ret1=curve1.size();int ret2=in1.size();
		std::cout << ret1<< " "<< ret2 <<" "<<"size"<<endl;
		//save_txt_pos(in1,"./result.txt","border");
	}
}
//vector<vector<vector<Point2d>>>().swap(Shape);

vector<vector<Point2d>>().swap(Set1);vector<vector<Point2d>>().swap(Set2);
int len_info=intersect_info.size();
    for (int i=0;i<len_info-1;i++)
    {
        for (int j=i+1;j<len_info;j++)
        {
            if (abs(intersect_info[i].pt.x-intersect_info[j].pt.x)<1e-6 && \
            abs(intersect_info[i].pt.y-intersect_info[j].pt.y)<1e-6)
            {
                //repeating pts
                Point2d idot = {0,0};
                intersect_info[i].pt=idot;
            }
        }

    }
vector<PointInfo>intersect_bridge={};
vector<PointInfo>:: iterator bridge;
for (bridge=intersect_info.begin();bridge!=intersect_info.end();bridge++)
{
    PointInfo bridgedot=*bridge;
    if (bridgedot.pt.x!=0 || bridgedot.pt.y!=0)
    {
        intersect_bridge.push_back(bridgedot);
    }
}
intersect_info=intersect_bridge;

//vector<vector<vector<PointWithPos>>> Yin={yin1,yin2};
std::vector<std::vector<Point2d>> route_group;
//again do point walk
vector<PointWithPos> new_in;
for (int f=0;f<2;f++)
{
	for (int j=0;j<num[f];j++)
	{
		line_order(intersect_info,Yin[f][j],new_in,j,f);
		Yin[f][j]=new_in;
        save_txt_pos(new_in,"./result.txt","border");
		new_in={};
	}
}

vector<vector<Point2d>> seg_set={};

vector<vector<int>> num_dir(2);//indicate number of polygon dots
    for (int f=0;f<2;f++){
        vector<vector<PointWithPos>> set = Yin[f];
        vector<int>num_dot={};
        int num_pol=set.size();
        for (int j=0;j<num_pol;j++)
        {
            int num_append=set[j].size();
            num_dot.push_back(num_append);
            std::cout <<num_append<<std::endl;
        }
        num_dir[f]=num_dot;
    }

//int len_info=intersect_info.size();
for (int info_ind=0;info_ind<len_info;info_ind++)
{
    for (int f=0;f<2;f++)
    {
    PointInfo begin_inf=intersect_info[info_ind];
	int repeat=0;
    int yin_ind=f;
	int i;
	vector<Point2d> route={};
    //vector<vector<vector<PointWithPos>>> Yin={yin1,yin2};
    //vector<int>len={p1l,p2l};
    Point2d begin_xy = begin_inf.pt;
    int poly_ind;
    vector<int> poly_ind_vec={begin_inf.pol1,begin_inf.pol2};
    poly_ind=poly_ind_vec[f];
    int begin_ind = findPointInPoly(begin_xy,Yin[yin_ind][poly_ind]);
    std::cout << begin_ind <<" " << Yin[yin_ind][poly_ind][begin_ind].in<<std::endl;
    
    
    std::cout << "don't panic"<<std::endl;
    PointWithPos begin_pt=Yin[yin_ind][poly_ind][begin_ind];

    
    //note:do not forget vector initialization
     
    i=begin_ind;//%len[poly_ind-1];
    cout<<"i="<<i<<endl;
    //poly_ind!
    int route_record=route.size();
    // std::cout << "i=" <<i<<std::endl;
    // std::cout <<"poly=" << poly_ind <<std::endl;
    route.push_back({Yin[yin_ind][poly_ind][i%num_dir[yin_ind][poly_ind]].x,\
    Yin[yin_ind][poly_ind][i%num_dir[yin_ind][poly_ind]].y}); 
    std::cout << "2. don't panic"<<std::endl;
    // if next point is inside
    if (Yin[yin_ind][poly_ind][(i+1)%num_dir[yin_ind][poly_ind]].in>=1)
    {
        i++;
        std::cout <<"i="<< i<<std::endl;
        while (Yin[yin_ind][poly_ind][i%num_dir[yin_ind][poly_ind]].in>=1)
        {   
            Point2d new_pt;
            std::cout <<"i="<< i<<std::endl;
            new_pt.x=Yin[yin_ind][poly_ind][i%num_dir[yin_ind][poly_ind]].x;
            new_pt.y=Yin[yin_ind][poly_ind][i%num_dir[yin_ind][poly_ind]].y;
            
            route.push_back(new_pt);
            if (abs(new_pt.x-begin_xy.x)<1e-6 && \
            abs(new_pt.y-begin_xy.y)<1e-6)
            {break;}
            if (Yin[yin_ind][poly_ind][i%num_dir[yin_ind][poly_ind]].in>1)
            {break;}
            //std::cout << i << " " << poly_ind <<std::endl;
            //poly[poly_ind][i%len[poly_ind]].in=0;
            i++;
            //go on until meeting intersection points
        }
    }
    int flag_2=0;
    int route_length=route.size();
    for (int route_it=0;route_it<route_length-1;route_it++)
    {
        Point2d pta=route[route_it];Point2d ptb=route[route_it+1];
        if (in_info(intersect_info,pta) && in_info(intersect_info,ptb))
        //two consecutive intersection
        //there are possibility that the intersection segment
        //would not stay inside the yin set
        {
            Point2d middle={(pta.x+ptb.x)/2,(pta.y+ptb.y)/2};
            if (isPointInsideYin(middle,Shape[1-f])==0)
            {
                flag_2++;
            }
        }
    }


    if (route.size()>1 && flag_2==0)
    {
        seg_set.push_back(route);}

    }
}




//then connect the line segments to make out intersection region
//make out routes
vector<vector<Point2d>> segment_set={};
int seg_len=seg_set.size();
for (int i=0;i<seg_len;i++)
{
    vector<Point2d>seg_to_check = seg_set[i];
    Point2d seg_head=seg_to_check.front();
    Point2d seg_end=seg_to_check.back();
    
    int flag_head=0; int flag_end=0; int flag_repeat=0;
    vector<PointInfo>:: iterator info_seg;
    for (info_seg=intersect_info.begin();info_seg!=intersect_info.end();\
    info_seg++)
    {
        PointInfo new_info=*info_seg;
        if (abs(new_info.pt.x-seg_head.x)<1e-6 && \
        abs(new_info.pt.y-seg_head.y)<1e-6)
        {   flag_head=1;} 
        if (abs(new_info.pt.x-seg_end.x)<1e-6 && \
        abs(new_info.pt.y-seg_end.y)<1e-6)
        {   flag_end=1;}
        
    }
    // int seg_len_tobe = segment_set.size();
    // vector<int>flag_rec={};
    // for (int seg_indi=0;seg_indi<seg_len_tobe;seg_indi++)
    //     {
    //         int ing_repeat=0;
    //         vector<Point2d> seg_check=segment_set[seg_indi];
    //         vector<Point2d>::iterator it_check;
    //         vector<Point2d>::iterator it_to_check;
    //         for (it_to_check=seg_to_check.begin();it_to_check!=seg_to_check.end();\
    //         it_to_check++)
    //         {
    //             Point2d process = *it_to_check;
    //             for (it_check=seg_check.begin();it_check!=seg_check.end();\
    //         it_check++)
    //         {
    //             Point2d process_tobe=*it_check;
    //             if (abs(process_tobe.x-process.x)<1e-6 && \
    //             abs(process_tobe.y-process.y)<1e-6)
    //             {
    //                 ing_repeat++;
    //             }
                
    //         }
    //         }
    //         if (ing_repeat>1)
    //             {ing_repeat=1;}
    //         flag_rec.push_back(ing_repeat);
    //     }
    // int equa = *max_element(flag_rec.begin(),flag_rec.end());
    // int size_check=seg_to_check.size();
    // if (equa >=size_check){flag_repeat=1;}
    if (flag_head==1 && flag_end==1)// && flag_repeat==0)//both end is intersect point
    {
        segment_set.push_back(seg_set[i]);
        //save_txt(seg_set[i], "./result.txt","border");
    }
}

int repeat_flag=0;vector<Point2d>back_seg={};
int segment_len=segment_set.size();
std::cout<<segment_len<<endl;
vector<vector<Point2d>> route_set={};
for (int i=0;i<segment_len;i++)
{	// if (!route_set.empty())
	// {
	// 	vector<vector<Point2d>>::iterator itr;
	// 	for (itr=route_set.begin();itr!=route_set.end();itr++)
	// 	{
	// 		vector<Point2d> route=*itr;
	// 		vector<Point2d>::iterator itl;
	// 		for (itl=route.begin();itl!=route.end())
	// 		{
				
	// 		}
	// 	}
	// }
		vector<Point2d> route={};
		vector<Point2d> began=segment_set[i];
		//vector<int>been_to={i};
		route.insert(route.end(),began.begin(),began.end());
		while (1)
		{	
			Point2d endpt=route.back();
            
            int flag_push=0;
            for (int j=0;j<segment_len;j++)
			{
				//if 	(!(std::find(been_to.begin(),been_to.end(),j)\
				!=been_to.end()))
				//{
					vector<Point2d>conti=segment_set[j];
					//std::cout<<"Don't Panic."<<std::endl;
					if (abs(endpt.x-conti[0].x)<1e-6 && \
					abs(endpt.y-conti[0].y)<1e-6 )//connected
					{
					route.insert(route.end(),conti.begin(),conti.end());
					//been_to.push_back(j);
                    flag_push++;
                    endpt=route.back();
					std::cout<<flag_push<<std::endl;
                    if (abs(endpt.x-route[0].x)<1e-6 && abs(endpt.y-route[0].y)<1e-6)
			{
				std::cout<<"route found."<<std::endl;
				break;
                break;
			}
					}
				//}
			}
            if (flag_push==0)//cannot connect
            {
                std::cout<<"failed to connect."<<endl;
                break;
            }
            endpt=route.back();
			if (abs(endpt.x-route[0].x)<1e-6 && abs(endpt.y-route[0].y)<1e-6)
			{
				std::cout<<"route found."<<std::endl;
				break;
			}
			
            // if (std::find(been_to.begin(),been_to.end(),j)\
			// 	!=been_to.end())
            // {break;}
		}
	if (!overlap(route_set,route))
	{
		route_set.push_back(route);
		save_txt(route, "./result.txt","intersect");
	}	
}

//deal with all-included curves

vector<PointInfo>::iterator check;
vector<int> poly_rec1={};vector<int>poly_rec2={};
vector<vector<int>>poly_rec={poly_rec1,poly_rec2};
for (check=intersect_info.begin();check!=intersect_info.end();check++)
{
    PointInfo dti=*check;int poly_1=dti.pol1;int poly_2=dti.pol2;
    if \
    (std::find(poly_rec[0].begin(),poly_rec[0].end(),poly_1)==poly_rec[0].end())
    {poly_rec[0].push_back(poly_1);}
    if \
    (std::find(poly_rec[1].begin(),poly_rec[1].end(),poly_2)==poly_rec[1].end())
    {poly_rec[1].push_back(poly_2);}
}
//std::cout<<"up to here"<<endl;
vector<vector<Point2d>> inside_layer={};
for (int f=0;f<2;f++)
{
    for (int pj =0; pj<num[f];pj++)
    {
        if (!std::count(poly_rec[f].begin(),poly_rec[f].end(),pj) &&\
            Yin[f][pj][0].in==1)
        //it contain no intersection pt
        //if all inside then fill according to orientation
        {
            inside_layer.push_back(Shape[f][pj]);
        }
    }
}

int layer_count=inside_layer.size();
vector<vector<int>> in_count={};
vector<int> how_many_outside={};
vector<int>counting={};
for (int d=0;d<layer_count;d++)
{
    counting={};
    for (int e=0;e<layer_count;e++)
    {
        if (e!=d && isPointInsidePoly2(inside_layer[d][0],\
        inside_layer[e])==1)//d is in e
        counting.push_back(e);
    }
    in_count.push_back(counting);
    int count_size=counting.size();
    how_many_outside.push_back(count_size);
}

int layer_max=*max_element(how_many_outside.begin(),how_many_outside.end());
vector<string>condition={"intersect","hollow"};int flagging;
for (int rank=0;rank<=layer_max;rank++)
{
    for (int psi=0;psi<layer_count;psi++)
    {
        if (how_many_outside[psi]==rank)
        {
            if (orientation(inside_layer[psi])>0)
            {
                flagging=0;
            }
            else
            {
                flagging=1;
            }
            save_txt(inside_layer[psi], "./result.txt", condition[flagging]);
        }
    }
}
Py_plot();
return 0;
}

//str= "./curve"+to_string(f)+to_string(j)+".txt";
//	readInToPointVec(str, polygon1);



// vector<Point2d>polygon2;
// //InputData_To_Vector(polygon1, "./apple.txt");
// //InputData_To_Vector(polygon2, "./beetle.txt");
// //readInToPointVec("./curve0.txt", polygon1);
// //readInToPointVec("./curve1.txt", polygon2);

// vector<PointWithPos> inside1;
// vector<PointWithPos> inside2;
// vector<PointInfo> intersect_inf;

// intersect_trace(polygon1,polygon2,inside1,inside2,intersect_inf);
// std::cout<< "intersection trace found."<<std::endl;

// // int length1=inside1.size();
// // std::cout<< length1 << std::endl;
// // for (int i=0;i<length1;i++)
// // {
// //     std::cout<< inside1[i].in << std::endl;
// // }

// // vector<Point2d>inter_poly;
// // int len_in =inside1.size();
// // for (int i=0;i<len_in;i++)
// // {
// //     if (inside1[i].in>1)
// //     {
// //         Point2d pt_add;
// //         pt_add.x=inside1[i].x;pt_add.y=inside1[i].y;
// //         inter_poly.push_back(pt_add);
// //         std::cout<<pt_add.x <<pt_add.y <<std::endl;
// //     }

// // }

// vector<vector<Point2d>> poly_group = {polygon1,polygon2};//inter_poly};

// for (int i=0;i<2;i++)
// {
//      string savex ="./result.txt";
//      save_txt(poly_group[i], savex,"border");
// }
// // Py_plot();


// vector<vector<Point2d>> route_group;

// Point_walk(intersect_inf,inside1,inside2,route_group);
// //std::cout<< "intersection 2."<<std::endl;
// int len_route=route_group.size();
// for (int i=0;i<len_route;i++)
// {
//     string savex ="./result.txt";
//     save_txt(route_group[i], savex,"intersect");
// }
// Py_plot();