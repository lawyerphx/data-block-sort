//
// Created by allvphx on 2020/2/7.
//

#include <cstdlib>
#include <ctime>
#include <algorithm>
#include "data_structures/area.h"
#include "algorithms/qsort_solve.h"

void generator(int *&a, int &n,int max_n) {
    n = rand()%max_n + 1;
    a = (int *)(malloc(sizeof(int) * n));
    for(int i=0;i<n;i++) a[i] = rand();
    std::sort(a,a+n);
}

void quick_sort_tester(int cnt_part,int block_per_part,int max_block_size) {
    srand(time(nullptr));
    Partition a[cnt_part];
    int *at, nt;
    for(int t=0;t<cnt_part;t++) {
        for(int i=0;i<block_per_part;i++) {
            generator(at, nt, max_block_size);
            a[t].add_data_block(at, nt);
        }
    }
    puts("<--- block build done --->");
    q_solve(a, cnt_part);
    for(int t=0;t<cnt_part;t++) {
        a[t].clear();
    }
    puts("<-- block memory free done -->");
}

int main() {
    quick_sort_tester(10,10,100);
    return 0;
}