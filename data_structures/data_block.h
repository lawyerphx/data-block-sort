//
// Created by allvphx on 2020/2/6.
//

#ifndef SORT_DATA_BLOCK_H
#define SORT_DATA_BLOCK_H


#include <cstdio>
#include <cstdlib>
#include <cstring>

struct data_block {
    int block_size = 0; //the size of sequence
    int *head = nullptr;    //the head of sequence
    data_block* next = nullptr; //next block in Partition
    data_block* pre = nullptr;  //previous block in Partition

    data_block(int* a, int n, data_block* prev) {
        block_size = n;
        head = a;
        next = nullptr;
        if (prev != nullptr)
        {
            prev->next = this;
            this->pre = prev;
        }
    }

    int* ips (int x) {
    //get the pointer of i-th element
        if (x < block_size) return head + x;
        else
        {
            puts("Error : data_block access error");
            return nullptr;
        }
    }

    void block_free() {
        //remove the elements in  the head[block_size]
        free(head);
    }
};

#endif //SORT_DATA_BLOCK_H
