

# def txt_plot(stringx,stringy):
#     def txt_read(string):   
#         f=open(string)
#         line = f.readline().strip() #读取第一行
#         txt=[]
#         txt.append(line)
#         while line.strip():  # 直到读取完文件
#             line = f.readline().strip(" ")  # 读取一行文件，包括换行符
#             txt.append(line)
#         f.close()  # 关闭文件
#         txt_num=[]
#         for string in txt:
#             if string!="" and string != "\n" and string:
#                 txt_num.append(float(string))
#         return txt_num
#     dotx=txt_read(stringx);doty=txt_read(stringy)
#     return dotx,doty

def plot_txt(argv):
    import matplotlib.pyplot as plt
    import readline
    import sys
    #argv="/mnt/hgfs/summer_program/data_2d/Shapes/beetle-7.txt"
    f=open(argv)
    line = f.readline().strip() #读取第一行
    txt=[]
    txt.append(line)
    while line:  # 直到读取完文件
        line = f.readline().strip()  # 读取一行文件，包括换行符
        txt.append(line)
    f.close()  # 关闭文件
    dotx=[];doty=[]
    x_list=[];y_list=[]
    inter_x=[];inter_y=[]
    x_hollow=[];y_hollow=[]
    for string in txt:
        lst=string.split(' ')
    #print(lst)
        if string:
            if lst[0]!="#":
                dotx.append(float(lst[0]))
                doty.append(float(lst[1]))
            else:#break sign: another curve
                print(lst)
                dot_nx=dotx[:];dot_ny=doty[:]
                if lst[1].strip()=="intersect":
                    inter_x.append(dot_nx)
                    inter_y.append(dot_ny)
                    x_list.append(dot_nx);y_list.append(dot_ny)
                if lst[1].strip()=="border":
                    x_list.append(dot_nx);y_list.append(dot_ny)
                if lst[1].strip()=="hollow":
                    x_list.append(dot_nx);y_list.append(dot_ny)
                    x_hollow.append(dot_nx);y_hollow.append(dot_ny)
                dotx=[];doty=[]
                continue
    #print(len(x_list));print(len(inter_x))
    for i in range(0,len(x_list)):
        plt.plot(x_list[i],y_list[i])
        if (x_list[i] in inter_x) and (y_list[i] in inter_y):
        #for j in range(0,len(inter_x)):
            plt.fill(x_list[i],y_list[i])
            plt.plot(x_list[i],y_list[i])
        elif (x_list[i] in x_hollow) and (y_list[i] in y_hollow):
        #for j in range(0,len(x_hollow)):
            plt.fill(x_list[i],y_list[i],"w")
            plt.plot(x_list[i],y_list[i])
    plt.pause(2)
    plt.show()
    return 0

if __name__=="__main__":
    plot_txt("./result.txt")
