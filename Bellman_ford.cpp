#include <iostream>
#include <cstdio>
#include <ctime>
using namespace std;
#include "topo.h"
#include "bellman_ford.h"

bool Bellman_Ford(double& time_spend){
    clock_t start, end;
    start = clock();//计时开始

    for(int i = 1; i <= nodenum; ++i){ //初始化dis数组
        dis[i] = (i == original ? 0 : MAX);
    }
    for(int i = 1; i <= nodenum - 1; ++i){
        for(int j = 1; j <= edgenum; ++j){
            if(dis[edge[j].v] > dis[edge[j].u] + edge[j].cost){ //松弛
                dis[edge[j].v] = dis[edge[j].u] + edge[j].cost;
                pre[edge[j].v] = edge[j].u;
            }
        }
    }
    bool flag = 1; //判断是否含有负权回路
    for(int i = 1; i <= edgenum; ++i){
        if(dis[edge[i].v] > dis[edge[i].u] + edge[i].cost){
            flag = 0;
            break;
        }
    }
    end = clock();//计时结束
    time_spend = (double)(end - start) / CLOCKS_PER_SEC;
    return flag;    
}

void print_path(int root){ //打印最短路的路径（反向）
    while(root != pre[root]){ //前驱
        printf("%d-->", root);
        root = pre[root];
    }
    if(root == pre[root]){
        printf("%d\n", root);
    }
}
/*
int main(){
    scanf("%d%d%d", &nodenum, &edgenum, &original);
    pre[original] = original;
    for(int i = 1; i <= edgenum; ++i){
        scanf("%d%d%d", &edge[i].u, &edge[i].v, &edge[i].cost);
    }
    if(Bellman_Ford()){
        for(int i = 1; i <= nodenum; ++i){ //每个点最短路
            printf("%d\n", dis[i]);
            printf("Path:");
            print_path(i);
        }
    }
    else{
        printf("have negative circle\n");
    }
    return 0;
}
*/
