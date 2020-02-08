//
// Created by allvphx on 2020/2/6.
//

#ifndef QSORT_SOLVE_H
#define QSORT_SOLVE_H

#include <iostream>
#include "../data_structures/area.h"
#define debug(x) std::cout << #x << " = " << x << std::endl

Partition* a;
int n;

void p_swap(int *x,int *y)
{
    int tmp = *x;
    *x = *y;
    *y = tmp;
}

Partition_iter init_iter(int i, int cmd)
//initialize a iterator for the i-th partition
//cmd = 0: from head
//cmd = 1: from end
{
    Partition_iter res;
    res.init_iter(cmd, a+i);
    return res;
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

void q_solve(Partition * _a, int _n) {
    a = _a;
    n = _n;
    int total = a[0].total_len;
    for(int i=1;i<n;i++) {  //build links between partitions.
        total += a[i].total_len;
        a[i-1].end->next = a[i].head;
        a[i].head->pre = a[i-1].end;
    }

    q_sort(init_iter(0,0), init_iter(n-1,1), 1, total);
    puts("<--- quick data_block_sort done --->");
    Partition_iter it = init_iter(0,0);
    int tmp = -1e9;
    while(it.curr()) {
        if(tmp > *it.curr()) {
            puts("!<--- error: unsorted --->");
        }
     //   printf("%d ",tmp = *it.curr());
        it++;
    }
    puts("<--- result check done --->");
//    printf("\n");

    for(int i=1;i<n;i++) {  // break the links
        a[i-1].end->next = nullptr;
        a[i].head->pre = nullptr;
    }
}

#endif //QSORT_SOLVE_H