import numpy as np
import pandas as pd
import h5py
import os
rootdir = '.\\training\\pts'
categorydir = '.\\training\\category'
list = os.listdir(rootdir)#得到路径下文件名
pstList = [] #坐标数据集
categoryList = [] #标签数据集
for i in range (0,len(list)):  #for i in range(0,len(list)): #所有文件名字
        path = os.path.join(rootdir,list[i]) #pts加上文件名
        categorypath = os.path.join(categorydir,list[i])#类别的路径
        if os.path.isfile(path):
            tup = pd.read_csv(path,header=None) #读取一个存三维坐标的csv文件
            if len(pstList) == 0:
                pstList = tup.values
            else:
                pstList = np.r_[pstList,tup.values] #增加行
                
            categorytup = pd.read_csv(categorypath,header=None)#读取标识类别的csv文件
            if len(categoryList) == 0:
                categoryList = categorytup.values
            else:
                categoryList = np.r_[categoryList,categorytup.values]
List = np.c_[pstList,categoryList] #把数据和标签合起来，最后一列是标签
L0 = []
L1 = []
L2 = []
L3 = []
L4 = []
L5 = []
L6 = []
L7 = []
for i in range(0,len(List)):
    if List[i][3] == 0:
        L0 = L0 + [List[i]]
    elif List[i][3] == 1:
        L1 = L1 + [List[i]]
    elif List[i][3] == 2:
        L2 = L2 + [List[i]]
    elif List[i][3] == 3:
        L3 = L3 + [List[i]]
    elif List[i][3] == 4:
        L4 = L4 + [List[i]]
    elif List[i][3] == 5:
        L5 = L5 + [List[i]]
    elif List[i][3] == 6:
        L6 = L6 + [List[i]]
    elif List[i][3] == 7:
        L7 = L7 + [List[i]]
if len(L0)>0:
    np.savetxt('category0.csv',L0,delimiter=',') 
if len(L1)>0:
    np.savetxt('category1.csv',L1,delimiter=',') 
if len(L2)>0:
    np.savetxt('category2.csv',L2,delimiter=',') 
if len(L3)>0:
    np.savetxt('category3.csv',L3,delimiter=',') 
if len(L4)>0:
    np.savetxt('category4.csv',L4,delimiter=',') 
if len(L5)>0:
    np.savetxt('category5.csv',L5,delimiter=',')
if len(L6)>0:
    np.savetxt('category6.csv',L6,delimiter=',')
if len(L7)>0:
    np.savetxt('category7.csv',L7,delimiter=',') 
print('end')