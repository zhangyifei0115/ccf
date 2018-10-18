import numpy as np
import h5py
L0 = np.loadtxt(open(".\category0.csv","rb"),delimiter=",",skiprows=0)
L1 = np.loadtxt(open(".\category1.csv","rb"),delimiter=",",skiprows=0)
L2 = np.loadtxt(open(".\category2.csv","rb"),delimiter=",",skiprows=0)
L3 = np.loadtxt(open(".\category3.csv","rb"),delimiter=",",skiprows=0)
L4 = np.loadtxt(open(".\category4.csv","rb"),delimiter=",",skiprows=0)
L5 = np.loadtxt(open(".\category5.csv","rb"),delimiter=",",skiprows=0)
L6 = np.loadtxt(open(".\category6.csv","rb"),delimiter=",",skiprows=0)
L7 = np.loadtxt(open(".\category7.csv","rb"),delimiter=",",skiprows=0)

L0 = L0[0:(len(L0)//2048*2048)]#就要2048列
L0 = np.reshape(L0,(-1,2048))
L1 = L1[0:(len(L1)//2048*2048)]#就要2048列
L1 = np.reshape(L1,(-1,2048))
L2 = L2[0:(len(L2)//2048*2048)]#就要2048列
L2 = np.reshape(L2,(-1,2048))
L3 = L3[0:(len(L3)//2048*2048)]#就要2048列
L3 = np.reshape(L3,(-1,2048))
L4 = L4[0:(len(L4)//2048*2048)]#就要2048列
L4 = np.reshape(L4,(-1,2048))
L5 = L5[0:(len(L5)//2048*2048)]#就要2048列
L5 = np.reshape(L5,(-1,2048))
L6 = L6[0:(len(L6)//2048*2048)]#就要2048列
L6 = np.reshape(L6,(-1,2048))
L7 = L7[0:(len(L7)//2048*2048)]#就要2048列
L7 = np.reshape(L7,(-1,2048))

L = np.r_[L0,L1]
L = np.r_[L,L2]
L = np.r_[L,L3]
L = np.r_[L,L4]
L = np.r_[L,L5]
L = np.r_[L,L6]
L = np.r_[L,L7]


f = h5py.File('allpts.h5','w') #创建h5文件，文件指针f
f['data'] = [i[0:3] for i in L]
f['labels'] = [i[3] for i in L]
f.close()
print('end')
