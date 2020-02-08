//
// Created by allvphx on 2020/2/8.
//

#ifndef SORT_MERGE_SOLVE_H
#define SORT_MERGE_SOLVE_H

#include "../data_structures/area.h"
#include <iostream>
#include <cassert>

namespace merge_sort {
    Partition *a;
    int n, block_size;
}

void free_block(data_block *cur, int *at, int &st, int &ed) {
    for(int i=0;i<cur->block_size;i++) {
        cur->head[i] = at[st];
        st = (st+1)%(2*merge_sort::block_size+1);
    }
}

void print(Partition_iter it) {
    while(it.cur) {
        printf("%d ",*it.curr());
        it++;
    }
    printf("\n");
}

Partition_iter merge(Partition_iter s1, Partition_iter s2) {
    Partition_iter res;
    res.i_cur = -1;
    data_block *endp = nullptr;
    int size = 2*merge_sort::block_size+1;
    int temp[size], st = 1, ed = 0;
    while(s1.cur!= nullptr || s2.cur!= nullptr) {
        if((s2.cur== nullptr) || (s1.cur!= nullptr && *s1.curr() <= *s2.curr())) {
            ed = (ed+1)%size;
            temp[ed] = *s1.curr();
            if(s1.i_cur == s1.cur->block_size-1) {
                free_block(s1.cur, temp, st, ed);
                if(endp != nullptr) {
                    endp->next = s1.cur;
                    s1.cur->pre = endp;
                    endp = s1.cur;
                } else {
                    res = s1; res.i_cur = 0;
                    endp = s1.cur;
                }
            }
            s1++;
        } else {
            ed = (ed+1)%size;
            temp[ed] = *s2.curr();
            if(s2.i_cur == s2.cur->block_size-1) {
                free_block(s2.cur, temp, st, ed);
                if(endp != nullptr) {
                    endp->next = s2.cur;
                    s2.cur->pre = endp;
                    endp = s2.cur;
                } else {
                    res = s2; res.i_cur = 0;
                    endp = s2.cur;
                }
            }
            s2++;
        }
    }
    assert(st==(ed+1)%(2*merge_sort::block_size+1));
    return res;
}

Partition_iter m_sort(int l,int r) {
    if(l == r) return init_iter(merge_sort::a,l,0);
    int mid = (l+r)/2;
    Partition_iter s1 = m_sort(l,mid);
    Partition_iter s2 = m_sort(mid+1,r);
    return merge(s1,s2);
}

void merge_solve(Partition * _a, int _n, int _max_block_size, bool test_print= false) {
    merge_sort::a = _a, merge_sort::n = _n, merge_sort::block_size = _max_block_size;
    Partition_iter it = m_sort(0,merge_sort::n-1);
    puts("<--- merge data_block sort done --->");

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
}

#endif //SORT_MERGE_SOLVE_H
