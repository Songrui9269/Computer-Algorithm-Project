#ifndef TOPO_H
#define TOPO_H

#define MAX 0x3f3f3f3f
#define N 1010
#define MAX_EDGE 101000
extern int nodenum, edgenum, original; //点，边，起点
typedef struct Edge{ //边
    int u, v;
    int cost;
}Edge;
extern Edge edge[MAX_EDGE];
extern int dis[N+1], pre[N+1];
extern int A[N+1][N+1];
void generate_random_graph(int size, int avg_degree, bool is_digraph, bool is_neg);
void print_graph();
#endif
