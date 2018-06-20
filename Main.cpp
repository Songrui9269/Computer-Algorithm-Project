#include <iostream>
#include <cstdio>
#include <ctime>
#include <cstdlib>
using namespace std;
#include "bellman_ford.h"
#include "dijkstra.h"
#include "topo.h"

void _run_test(int node_num, int avg_degree, bool isdigraph, bool is_neg){
    clock_t start, cur;
    double max_time = 1.0;
    if(node_num > 300){
        max_time = 2.0;
    }else if(node_num > 500){
        max_time = 5.0;
    }else if(node_num > 800){
        max_time = 10.0;
    }
    start = clock();
    cur = start;
    double total_bf = 0.0, total_dij = 0.0, bf = 0.0, dij = 0.0;
    int test_times = 0;

    cout << "node_num:" << node_num << ",avg_degree:" << avg_degree 
         << ",isdigraph:" << boolalpha << isdigraph
         << ",is_neg:" << boolalpha << is_neg << endl;

    while( (double)(cur - start) / CLOCKS_PER_SEC < max_time && test_times < 10000){

        generate_random_graph(node_num, avg_degree, isdigraph, is_neg);

        Bellman_Ford(bf); 
        total_bf += bf;

        Dijkstra(dij);
        total_dij += dij;

        cur = clock(); 
        ++ test_times;
    }
    cout.precision(10);
    cout << "test_times:" << test_times << endl;
    cout << "avg bel time:" << total_bf / (double)test_times << endl;
    cout << "avg dij time:" << total_dij / (double)test_times << endl;
    cout << "***************************************" << endl;
}

void run_test(){
    int node_num = 10;

    int idx;
    /*
    while(node_num <= 1000){//有向无负边
        idx = 0;
        for(int avg_degree = 2; avg_degree <= 20 && avg_degree < node_num; avg_degree ++){
            _run_test(node_num, avg_degree, true, false);
        }
        if(node_num < 100) node_num += 10;
        else node_num += 100;
    }
    */

    while(node_num <= 1000){//无向无负边
        idx = 0;
        for(int avg_degree = 2; avg_degree <= 20 && avg_degree < node_num; avg_degree ++){
            _run_test(node_num, avg_degree, false, false);
        }
        if(node_num < 100) node_num += 10;
        else node_num += 100;
    }
}


void mixed_algorithm(double& time_spend){
    bool contains_negative = false;
    for(int i = 1; i <= edgenum; ++i ){
        if(edge[i].cost <= 0){
            contains_negative = true;
            break;
        }
    }
    if(contains_negative){
        Bellman_Ford(time_spend);
        return;
    }

    int avg_degree = edgenum * 2 / nodenum;
    if(nodenum <= 100){
        if(avg_degree <= 2){
            Bellman_Ford(time_spend);
        }else{
            Dijkstra(time_spend);
        }
    }else{
        if(avg_degree <= 4){
            Bellman_Ford(time_spend);
        }else{
            Dijkstra(time_spend);
        }
    }
}

void run_sparse_test(){//稀疏图
    clock_t start, cur;
    double max_time = 300.0;
    start = clock();
    cur = start;
    double total_bf = 0.0, total_dij = 0.0, total_mix = 0.0, bf = 0.0, dij = 0.0, mix = 0.0;
    int test_times = 0;

    int node_num = rand()%900+101;
    int avg_degree = rand()%2+2;

    while( (double)(cur - start) / CLOCKS_PER_SEC < max_time){

        generate_random_graph(node_num, avg_degree, true, false);

        Bellman_Ford(bf); 
        total_bf += bf;

        Dijkstra(dij);
        total_dij += dij;

        mixed_algorithm(mix);
        total_mix += mix;

        cur = clock(); 
        ++ test_times;
    }

    cout.precision(10);
    cout << "test times:" << test_times << endl;
    cout << "total bel time:" << total_bf  << endl;
    cout << "total dij time:" << total_dij << endl;
    cout << "total mix time:" << total_mix << endl;
    cout << "***************************************" << endl;

}

void run_dense_test(){//稀疏图
    clock_t start, cur;
    double max_time = 300.0;
    start = clock();
    cur = start;
    double total_bf = 0.0, total_dij = 0.0, total_mix = 0.0, bf = 0.0, dij = 0.0, mix = 0.0;
    int test_times = 0;

    int node_num = rand()%900+101;
    int avg_degree = rand()%2+8;

    while( (double)(cur - start) / CLOCKS_PER_SEC < max_time){

        generate_random_graph(node_num, avg_degree, true, false);

        Bellman_Ford(bf); 
        total_bf += bf;

        Dijkstra(dij);
        total_dij += dij;

        mixed_algorithm(mix);
        total_mix += mix;

        cur = clock(); 
        ++ test_times;
    }

    cout.precision(10);
    cout << "test times:" << test_times << endl;
    cout << "total bel time:" << total_bf  << endl;
    cout << "total dij time:" << total_dij << endl;
    cout << "total mix time:" << total_mix << endl;
    cout << "***************************************" << endl;

}
int main(){
    run_sparse_test();
    run_dense_test();
    return 0;
}
