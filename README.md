[![Build Status](https://travis-ci.org/Incarnation-p-lee/libds.svg?branch=trunk)](https://travis-ci.org/Incarnation-p-lee/libds)

##UNIFIED DATA STRUCTURE IMPLEMENTATION LIB OF C LANGUAGE

### build
    1. sh src/script/build.sh [options]
       DEBUG=0/1
       PROFILE=0/1
       CODE_COVERAGE=0/1
       LIB=0/1
       X86_64=0/1
       STATIC=0/1
    2. Output obj_out/out/ds.elf
              obj_out/out/ds.h
              obj_out/out/libds.a
              obj_out/out/libds.so

### Design

    This project export sorts of API of data structure with libds.so or libds.a. Some convention should notify for operation of exported APIs.
    1. remove operation never free the memory allocated of one element, just strip out of data structure.
    2. remove and destroy operation will free the memory.
    3. contains operation operates on pointers of element exist in data structure or not.
    4. find operation operates on sorted data structure who has priority of node/element of data structure.
    5. distinguish node and data structure itself only if necessary.
    6. No head node for all linked list linked data structure.
    7. To be continue...

### list

    The following data structure implemented in this project.
    1. linked_list
        a. single linked list
        b. doubly linked list
        c. skip linked list.
    2. stack
        a. array stack
        b. linked stack
    3. queue
        a. array queue
        b. stacked queue
        c. doubly end queue
    4. tree
        a. binary search tree
        b. avl tree
        c. splay tree
    5. hash
        a. separate chain hash
        b. open addressing hash
    6. heap
        a. minimal heap
        b. maximal heap
        c. min_max heap
        d. leftist_heap

