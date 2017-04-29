[![Build Status](https://travis-ci.org/Incarnation-p-lee/libds.svg?branch=trunk)](https://travis-ci.org/Incarnation-p-lee/libds)

[![Codeclimate Test Coverage](https://codeclimate.com/github/Incarnation-p-lee/libds/badges/coverage.svg)](https://codeclimate.com/github/Incarnation-p-lee/libds/coverage)

[![Codeclimate Issue Count](https://codeclimate.com/github/Incarnation-p-lee/libds/badges/issue_count.svg)](https://codeclimate.com/github/Incarnation-p-lee/libds)

[![Code Climate GPA](https://codeclimate.com/github/Incarnation-p-lee/libds/badges/gpa.svg)](https://codeclimate.com/github/Incarnation-p-lee/libds)

[![codecov](https://codecov.io/gh/Incarnation-p-lee/libds/branch/trunk/graph/badge.svg)](https://codecov.io/gh/Incarnation-p-lee/libds)


[![Open Source Love](https://badges.frapsoft.com/os/v1/open-source.svg?v=103)](https://github.com/Incarnation-p-lee/libds/) 

[![GPL Licence](https://badges.frapsoft.com/os/gpl/gpl.svg?v=103)](https://opensource.org/licenses/GPL-3.0/) 

[![star this repo](http://githubbadges.com/star.svg?user=Incarnation-p-lee&repo=libds&style=default)](https://github.com/Incarnation-p-lee/libds)

[![fork this repo](http://githubbadges.com/fork.svg?user=Incarnation-p-lee&repo=libds&style=default)](https://github.com/Incarnation-p-lee/libds/fork)


##UNIFIED DATA STRUCTURE IMPLEMENTATION LIB OF C LANGUAGE

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

### list

    The following data structure implemented in this project.
    1. linked list
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
        d. binary indexed tree
        e. trie tree
    5. hash
        a. separate chain hash
        b. open addressing hash
        c. bitmap
    6. heap
        a. minimal heap
        b. maximal heap
        c. min-max heap
        d. leftist heap
    7. sort
        a. insertion sort
        b. shell sort
        c. heap sort
        d. merge sort
        e. quick sort
    8. set
        a. disjoint set
        
----- to be continue -----

