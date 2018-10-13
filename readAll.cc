#include<bits/stdc++.h>
#include<io.h>
using namespace std;
struct Pts{//三维坐标
    double x;
    double y;
    double z;
    bool operator < (const Pts& a) const
    {
        return x < a.x;
    }
};
struct Pairs{//坐标对应类别
    Pts pts;
    int label;
    bool operator < (const Pairs& a) const
    {
        if(label == a.label)
        {
            return pts.x < a.pts.x;
        }
        return label < a.label;
    }
};

vector<Pts> Vecpts;//三维坐标
vector<int> Veccat;//类别
set<Pairs> Set;//存数据和标签对
map<int,vector<Pts> > Map;//类别对应所有的坐标

vector<string> ptsfiles,categoryfiles;//所有文件的名字
char* ptsfilepath = ".\\pts";
char* categorypath = ".\\category";

// 数字转成字符串
string Dig2Alp(int a)
{
    //将数字转成字符串,这种用法比stringstream用法效率高
    string str="";
    string str_dig="";
    if(a==0)
        str+="0";
    if(a>0)
    {
        while(a)
        {
            str_dig="";
            str_dig+=(a%10+'0');
            str=str_dig+str;
            a/=10;
        }
    }
    if(a<0)
    {
        a = -a;
        while(a)
        {
            str_dig="";
            str_dig+=(a%10+'0');
            str=str_dig+str;
            a/=10;
        }
        str = "-"+str;
    }
    return str;
}

//读取文件夹下所有文件
void getFiles(string path,vector<string>& files)
{
    //文件句柄
    long hFile = 0;
    //文件信息
    struct _finddata_t fileinfo;
    string p;
    if((hFile = _findfirst(p.assign(path).append("\\*").c_str(),&fileinfo)) != -1)
    {
        do{
            //如果是目录则迭代
            //如果不是，加入列表
            if((fileinfo.attrib & _A_SUBDIR))
            {
                if(strcmp(fileinfo.name,".") != 0 && strcmp(fileinfo.name,"..") != 0)
                    getFiles(p.assign(path).append("\\").append(fileinfo.name),files);
            }
            else
            {
                files.push_back(p.assign(path).append("\\").append(fileinfo.name));
            }
        }while(_findnext(hFile,&fileinfo) == 0);
        _findclose(hFile);
    }
}

//读取所有文件中内容
void readAllFile()
{
    FILE* fp;
    Pts pts;
    int category;

    for(int i=0;i<ptsfiles.size();i++)
    {
        if((fp=fopen(ptsfiles[i].c_str(),"r")) == NULL)
        {
            cout<<"open file "<<ptsfiles[i]<<" error"<<endl;
            exit(0);
        }
        while(!feof(fp))
        {
            int res;
            res = fscanf(fp,"%lf,%lf,%lf",&pts.x,&pts.y,&pts.z);
            if(res == -1)
                break;
            Vecpts.push_back(pts);
        }
        fclose(fp);

        if((fp=fopen(categoryfiles[i].c_str(),"r")) == NULL)
        {
            cout<<"open file "<<categoryfiles[i]<<" error"<<endl;
            exit(0);
        }
        while(!feof(fp))
        {
            int res;
            res = fscanf(fp,"%d",&category);
            if(res == -1)
                break;
            Veccat.push_back(category);
        }
        fclose(fp);
    }

}

//把读出的data和label值存到set中
void saveToSet(vector<Pts> Vecpts,vector<int> Veccat,set<Pairs>& Set)
{
    Pairs mpair;
    for(long i=0;i<Vecpts.size();i++)
    {
        mpair.pts = Vecpts[i];
        mpair.label = Veccat[i];
        //cout<<mpair.label<<"----"<<mpair.pts.x<<","<<mpair.pts.y<<","<<mpair.pts.z<<endl;
        Set.insert(mpair);
    }
    //cout<<"set size "<<Set.size()<<endl;
}
//set中的数据存到map中
void saveToMap(set<Pairs> Set,map<int,vector<Pts> >& Map)
{
    Pairs mpair;
    set<Pairs>::iterator it;
    //cout<<"set size "<<Set.size()<<endl;
    for(it=Set.begin();it!=Set.end();it++)
    {
        mpair = (*it);
        //**************************************************
        //cout<<mpair.label<<"---"<<mpair.pts.x<<endl;
        Map[mpair.label].push_back(mpair.pts);
    }
}
//遍历map把不同类别写入不同文件
void searchAndWrite(map<int,vector<Pts> > Map)
{
    FILE* fp;
    vector<Pts> Vec;
    map<int,vector<Pts> >::iterator it;
    string filename = "label";
    for(it=Map.begin();it!=Map.end();it++)
    {
        filename += Dig2Alp(it->first);
        filename += ".csv";
        Vec = it->second;
        //*********************************************************
        //cout<<it->first<<"size is "<<Vec.size()<<endl;
        if((fp = fopen(filename.c_str(),"w")) == NULL)
        {
            cout<<"write file error"<<endl;
            exit(0);
        }
        for(long i=0;i<Vec.size();i++)
        {
            fprintf(fp,"%lf,%lf,%lf\n",Vec[i].x,Vec[i].y,Vec[i].z);
        }
        fclose(fp);
        filename = "label";
    }
}

int main()
{
    getFiles(ptsfilepath,ptsfiles);//文件名放到files中
    getFiles(categorypath,categoryfiles);
    readAllFile();
    //cout<<"Vecpts.size = "<<Vecpts.size()<<endl;
    //cout<<"Veccat.size = "<<Veccat.size()<<endl;
    //上面已经读取文件中的内容了
    if(Veccat.size()!=Vecpts.size())
    {
        cout<<"data size not equal label size"<<endl;
        exit(0);
    }
    saveToSet(Vecpts,Veccat,Set);
    saveToMap(Set,Map);
    searchAndWrite(Map);

    return 0;
}
