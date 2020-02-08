//
// Created by allvphx on 2020/2/6.
//

#ifndef SORT_AREA_H
#define SORT_AREA_H

#include "data_block.h"
#include <iostream>

struct Partition {
    data_block* head = nullptr; //the head and the end pointer of the data_block list
    data_block* end = nullptr;
    int block_cnt = 0;  //the count of data blocks
    int total_len = 0;  //the total length of sequence

    void add_data_block(int* a, int n) {
        //add a[0..n-1] to this area as a new data block
        end = new data_block(a,n,end);
        if(head == nullptr) head = end;
        block_cnt ++;
        total_len += n;
    }

    void clear() {
        //free all the resources occupied
        data_block *cur = head, *tmp;
        while(cur) {
            tmp = cur->next;
            cur->block_free();
            delete cur;
            cur = tmp;
        }
    }
};

struct Partition_iter {
    //the iterator used to help traversal all the elements in this Partition
    data_block* cur{};
    int i_cur{};
    //help find the Partition

    void init_iter(int cmd, Partition *tmp) {
        //initialize the iterator
        if(cmd == 0) {  //begin
            cur = tmp->head;
            i_cur = 0;
        } else {    //end
            cur = tmp->end;
            i_cur = cur->block_size-1;
        }
    }

    void operator++(int) {
        //go to the next one
        if(cur!= nullptr) {
            i_cur++;
            if (i_cur == cur->block_size) {
                cur = cur->next;
                i_cur = 0;
            }
        } else {
            i_cur = 0;
            cur = nullptr;
        }
    }

    void operator--(int) {
        //go to the previous one
        if(cur!= nullptr) {
            i_cur--;
            if (i_cur == -1)
            {
                cur = cur->pre;
                if(cur != nullptr) i_cur = cur->block_size-1;
            }
        } else {
            i_cur = 0;
            cur = nullptr;
        }
    }

    int *curr() {
        //get the pointer of current element
        if(cur!= nullptr) return cur->ips(i_cur);
        else return nullptr;
    }
};

Partition_iter init_iter(Partition* a, int i, int cmd)
//initialize a iterator for the i-th partition
//cmd = 0: from head
//cmd = 1: from end
{
    Partition_iter res;
    res.init_iter(cmd, a+i);
    return res;
}

#endif //SORT_AREA_H
