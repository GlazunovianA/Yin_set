
def text_save(filename, data1,data2):
    #filename为写入CSV文件的路径，data为要写入数据列表.
    file = open(filename,'a')
    for i in range(len(data1)):
        s = str(data1[i]).replace('[','').replace(']','')#去除[],这两行按数据不同，可以选择
        s = s.replace("'",'').replace(',','') +' '   #去除单引号，逗号，每行末尾追加换行符
        file.write(s)
        s = str(data2[i]).replace('[','').replace(']','')#去除[],这两行按数据不同，可以选择
        s = s.replace("'",'').replace(',','') +'\n'   #去除单引号，逗号，每行末尾追加换行符
        file.write(s)
    file.close()

def read_txt(args):
    import matplotlib.pyplot as plt
    import readline

    #argv="/mnt/hgfs/summer_program/data_2d/Shapes/beetle-7.txt"
    stri="./curve"+str(args)+".txt"
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
                dotx.append(float(lst[0]))
                doty.append(float(lst[1]))
            else:#break sign: another curve
                #print(lst)
                dot_nx=dotx[:];dot_ny=doty[:]
                dotx=[];doty=[]
                x_list.append(dot_nx);y_list.append(dot_ny)
                continue
    #print(len(x_list));print(len(inter_x))
    for i in range(0,len(x_list)):
        string="curve"+str(args)+str(i)+".txt"
        text_save(string,x_list[i],y_list[i])
    return 0

if __name__=="__main__":
    import sys
    #name=sys.args
    read_txt(0)
    read_txt(1)