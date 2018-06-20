#include "topo.h"
#include <ctime>
#include <cstdlib>
#include <iostream>
using namespace std;

int nodenum, edgenum, original; //点，边，起点
Edge edge[MAX_EDGE];
int dis[N+1], pre[N+1];
int A[N+1][N+1];
void generate_random_graph(int size, int avg_degree, bool isdigraph, bool is_neg){//生成随机图

    if(!isdigraph && is_neg){
        cout << "undigraph with negative edge!" << endl;//有负边的无向图没办法算最短路
        exit(-1);
    }

    if(size <= 0)
        return;
    if(size > N)
        size = N;

    srand(time(NULL)); //初始化随机数种子

    nodenum = size;
    original = rand() % nodenum + 1;

    //avg_degree 每个点的平均度数
    if(avg_degree < 2) avg_degree = 2; //最小度数为2
    if(avg_degree > nodenum-1) avg_degree = nodenum-1; //最大度数为全连通图

    edgenum = avg_degree * nodenum / 2; //平均度数乘以点数除以2等于边数

    if(!isdigraph){
        edgenum *= 2;
    }

    if(edgenum > MAX_EDGE){
        edgenum = MAX_EDGE;
    }


    for(int i = 1; i <= nodenum; ++i){ //初始化dis数组
        dis[i] = (i == original ? 0 : MAX);
    }

    for(int i = 1; i <= nodenum; ++i){//初始化邻接矩阵
        for(int j = 1; j <= nodenum; ++j){
            A[i][j] = MAX;
        }
    }
    int node1, node2;
    int dist;

    for(int i = 0; i < edgenum; ){//初始化邻接表
        do{//随机选择两个点来连边
            node1 = rand()%nodenum+1;
            node2 = rand()%nodenum+1;
        }while(node1 == node2 || A[node1][node2] != MAX);// 避免自环或重复赋值
    
        dist = rand()%10+1; //随机边长为1~10之间的数
        
        if(is_neg){//如果有负边
            //以10%的概率产生负边，避免太多负边造成负环
            if( rand()%10 == 0){
                dist = -dist;
            }
        }
        if(isdigraph){//有向图
            A[node1][node2] = dist;
            i += 1;
        }else{//无向图
            A[node1][node2] = dist;
            A[node2][node1] = dist;
            i += 2;
        }
    }

    int edgeidx = 1;
    for(int i = 1; i <= nodenum; ++ i){//根据邻接表初始化边表
        for(int j = 1; j <= nodenum; ++ j){
            if(A[i][j] != MAX){//已经初始化的边
                edge[edgeidx].u = i;
                edge[edgeidx].v = j;
                edge[edgeidx].cost = A[i][j];
                ++ edgeidx;
            }
        }
    }
}
void print_graph(){

    cout << "nodenum:" << nodenum << endl;
    cout << "edgenum:" << edgenum << endl;
    cout << "original:" << original << endl;

    cout << "print adjacent matrix" << endl;
    for(int i = 1; i <= nodenum; ++ i){
        for(int j = 1; j <= nodenum; ++ j){
            if(A[i][j] != MAX)
                cout << A[i][j] << ' ';
            else
                cout << 0 << ' ';
        }
        cout  << endl;
    }

    cout << "print edge table" << endl;
    for(int i = 1; i <= edgenum; ++ i){
        cout << edge[i].u << "->" << edge[i].v << ":" << edge[i].cost << endl;
    }
}
