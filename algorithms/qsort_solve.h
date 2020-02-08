//
// Created by allvphx on 2020/2/6.
//

#ifndef QSORT_SOLVE_H
#define QSORT_SOLVE_H

#include <iostream>
#include "../data_structures/area.h"
#define debug(x) std::cout << #x << " = " << x << std::endl

namespace quick_sort {
    Partition *a;
    int n;
}

void p_swap(int *x,int *y)
{
    int tmp = *x;
    *x = *y;
    *y = tmp;
}

void q_sort(Partition_iter s, Partition_iter t, int l, int r) {
    //use the time to exchange for memory
    if(l >= r) return;
    int cnt = (r-l+1)/2, val;

    Partition_iter nt = s;
    for(int i=0;i<cnt;i++) nt++;
    val = *nt.curr();
    p_swap(nt.curr(), s.curr());

    Partition_iter it = s, jt = s;
    int j=l;
    it++;
    for(int i=l+1;i<=r;i++)
    {
        if(*it.curr() <= val) {
            jt++;
            p_swap(jt.curr(), it.curr());
            j++;
        }
        it++;
    }
    p_swap(jt.curr(), s.curr());
    if(l<j-1) {
        jt--;
        q_sort(s, jt, l, j - 1);
        jt++;
    }
    if(j+1<r) {
        jt++;
        q_sort(jt, t, j + 1, r);
    }
}

void q_solve(Partition * _a, int _n, bool test_print= false) {
    quick_sort::a = _a;
    quick_sort::n = _n;
    int total = quick_sort::a[0].total_len;
    for(int i=1;i<quick_sort::n;i++) {  //build links between partitions.
        total += quick_sort::a[i].total_len;
        quick_sort::a[i-1].end->next = quick_sort::a[i].head;
        quick_sort::a[i].head->pre = quick_sort::a[i-1].end;
    }

    q_sort(init_iter(quick_sort::a,0,0), init_iter(quick_sort::a,quick_sort::n-1,1), 1, total);
    puts("<--- quick data_block sort done --->");
    Partition_iter it = init_iter(quick_sort::a,0,0);
    int tmp = -1e9;
    while(it.curr()) {
        if(tmp > *it.curr()) {
            puts("!<--- error: unsorted --->");
        }
        if(test_print) printf("%d ",tmp = *it.curr());
        it++;
    }
    puts("<--- result check done --->");
    if(test_print) printf("\n");

    for(int i=1;i<quick_sort::n;i++) {  // break the links
        quick_sort::a[i-1].end->next = nullptr;
        quick_sort::a[i].head->pre = nullptr;
    }
}

#endif //QSORT_SOLVE_H