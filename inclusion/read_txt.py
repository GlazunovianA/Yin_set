def text_save(filename, data1):#,data2):
    #filename为写入CSV文件的路径，data为要写入数据列表.
    file = open(filename,'a')
    for i in range(len(data1)):
        for j in range(4):
            s = str(data1[i][j]).replace('[','').replace(']','')#去除[],这两行按数据不同，可以选择
            s = s.replace("'",'').replace(',','') +' '   #去除单引号，逗号，每行末尾追加换行符
            file.write(s)
        file.write("\n")
    file.close()

def read_txt():
    import matplotlib.pyplot as plt
    import readline

    #argv="/mnt/hgfs/summer_program/data_2d/Shapes/beetle-7.txt"
    stri="./result"+".txt"
    f=open(stri)
    line = f.readline().strip() # 读取第一行
    txt=[]
    txt.append(line)
    while line:  # 直到读取完文件
        line = f.readline().strip() # 读取一行文件，包括换行符
        txt.append(line)
    f.close()  # 关闭文件
    dotx=[];doty=[]
    x_list=[];y_list=[]
    
    for stri in txt:
        lst=stri.split(' ')
    #print(lst)
        if stri:
            if lst[0]!="#":
                dotx.append([float(lst[0]),float(lst[1]),float(lst[2]),float(lst[3])])
                doty.append([float(lst[4]),float(lst[5]),float(lst[6]),float(lst[7])])
            else:#break sign: another curve
                #print(lst)
                dot_nx=dotx[:];dot_ny=doty[:]
                dotx=[];doty=[]
                x_list.append(dot_nx);y_list.append(dot_ny)
                continue
    #print(len(x_list));print(len(inter_x))
    for i in range(0,len(x_list)):
        stringx="curve_x"+str(i)+".txt"
        stringy="curve_y"+str(i)+".txt"
        text_save(stringx,x_list[i])
        text_save(stringy,y_list[i])
    return 0

if __name__=="__main__":
    import sys
    #name=sys.args
    read_txt()