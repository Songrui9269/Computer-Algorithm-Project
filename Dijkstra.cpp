#include "topo.h"
#include "dijkstra.h"
#include <ctime>
void Dijkstra(double& time_spend)
{   
    clock_t start, end;
    start = clock();//计时开始

    for(int i = 1; i <= nodenum; ++i){ //初始化dis数组
        dis[i] = (i == original ? 0 : MAX);
    }
    
    bool S[nodenum];                                  // 判断是否已存入该点到S集合中
    int n = nodenum;
    for(int i = 1; i <= n; ++i){
        dis[i] = A[original][i];
        S[i] = false;                                   // 初始都未用过该点
        if(dis[i] == MAX)    
            pre[i] = -1;
        else 
            pre[i] = original;
    }
    dis[original] = 0;
    S[original] = true;
    for(int i=2; i<=n; i++){
        int mindist = MAX;
        int u = original;                               // 找出当前未使用的点j的dis[j]最小值
        for(int j=1; j<=n; ++j){
            if((!S[j]) && dis[j]<mindist){
                u = j;                                      // u保存当前邻接点中距离最小的点的号码 
                mindist = dis[j];
            }
        }
        S[u] = true; 
        for(int j=1; j<=n; j++){
            if((!S[j]) && A[u][j]<MAX){
                if(dis[u] + A[u][j] < dis[j]){            //在通过新加入的u点路径找到离original点更短的路径  
                    dis[j] = dis[u] + A[u][j];              //更新dist 
                    pre[j] = u;                              //记录前驱顶点 
                }
            }
        }
    }
    end = clock();//计时结束
    time_spend = (double)(end - start) / CLOCKS_PER_SEC;
}
