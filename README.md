[![Build Status](https://travis-ci.org/Incarnation-p-lee/libds.svg?branch=trunk)](https://travis-ci.org/Incarnation-p-lee/libds)

[ ![Codeship Status for Incarnation-p-lee/libds](https://app.codeship.com/projects/2cba2150-2287-0134-4afd-4ef69db363d6/status?branch=master)](https://app.codeship.com/projects/161167)

[![codecov](https://codecov.io/gh/Incarnation-p-lee/libds/branch/trunk/graph/badge.svg)](https://codecov.io/gh/Incarnation-p-lee/libds)

[![Open Source Love](https://badges.frapsoft.com/os/v1/open-source.svg?v=103)](https://github.com/Incarnation-p-lee/libds/) 

[![GPL Licence](https://badges.frapsoft.com/os/gpl/gpl.svg?v=103)](https://opensource.org/licenses/GPL-3.0/) 

[![star this repo](http://githubbadges.com/star.svg?user=Incarnation-p-lee&repo=libds&style=default)](https://github.com/Incarnation-p-lee/libds)

[![fork this repo](http://githubbadges.com/fork.svg?user=Incarnation-p-lee&repo=libds&style=default)](https://github.com/Incarnation-p-lee/libds/fork)


## UNIFIED DATA STRUCTURE IMPLEMENTATION LIB OF C LANGUAGE

### build
```
  make            :Default debug build
  make RELEASE=1  :Release build
  make V=1        :Verbose build
  make COVERAGE=1 :Coverage build
```

### Output
```
  bin/ds.elf
  bin/libds.a
  bin/libds.so
  src/inc/data_structure_interface.h
```

### Design

    This project export sorts of API of data structure with libds.so or libds.a.

### List

    The following data structure implemented in this project.
    1. Linked list
        a. single linked list
        b. doubly linked list
        c. skip linked list
    2. Stack
        a. array stack
        b. linked stack
    3. Queue
        a. array queue
        b. stacked queue
        c. doubly end queue
    4. Tree
        a. binary search tree
        b. avl tree
        c. splay tree
        d. binary indexed tree
        e. trie tree
    5. Hash
        a. separate chain hash
        b. open addressing hash
        c. bitmap
    6. Heap
        a. minimal heap
        b. maximal heap
        c. min-max heap
        d. leftist heap
    7. Sort
        a. insertion sort
        b. shell sort
        c. heap sort
        d. merge sort
        e. quick sort
    8. Set
        a. disjoint set
    9. Graph
        a. directed graph           [in process]
        b. indirected graph         [in process]
    10. Lock
        a. spin lock
        b. semaphore
        c. mutex
        
----- to be continue -----

