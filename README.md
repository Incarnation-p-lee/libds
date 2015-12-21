[![Build Status](https://travis-ci.org/Incarnation-p-lee/libds.svg?branch=trunk)](https://travis-ci.org/Incarnation-p-lee/libds)

UNIFIED DATA STRUCTURE IMPLEMENTATION LIB OF C LANGUAGE

    1. sh src/script/build.sh [options]
       DEBUG=0/1
       PROFILE=0/1
       CODE_COVERAGE=0/1
       LIB=0/1
       X86_64=0/1
       STATIC=0/1
       OPT_HOT=0/1
    2. Output obj_out/out/ds.elf
              obj_out/out/ds.h
              obj_out/out/libds.a
              obj_out/out/libds.so

[Design]:
---------
This project export sorts of API of data structure with libds.so or libds.a.
Some convention should notify for operation of exported APIs.
   1. remove operation never free the memory allocated of one element, just strip out of data structure.
   2. destroy operation will free the memory.
   3. contains operation operates on pointers of element exist in data structure or not.
   4. find operation operates on sorted data structure who has priority of node/element of data structure.
   5. To be continue...

[Convention]:
-------------
For all data structures, it has nice(priority) of node, or do not has nice.
   For nice data structures. API should be looks like this:
       1. xxx_xx_insert(*head, *node)
       2. xxx_xx_remove(*head, nice)
       3. xxx_xx_remove_and_destroy(*head, nice)
       4. xxx_xx_contains_p(*head, *node)
       5. xxx_xx_find(*head, nice)
       6. implemented:
           a. skip linked list.
           b. binary search tree
           c. avl tree
           d. splay tree
   For no-niced data structure. API should be looked like:
       1. xxx_xx_insert(*head, *node)
       2. xxx_xx_remove(*head, *node)
       3. xxx_xx_remove_and_destroy(*head, *node)
       4. xxx_xx_contains_p(*head, *node)
       5. implemented:
           a. single linked list
           a. doubly linked list
   For nice or no-niced data structure with out node concept.
       1. some data sturcture organized without node concept.
       2. these API has no conventions, case by case.
       3. implemented:
           a. minimal heap
           b. maximal heap
           b. array stack
           c. linked stack
           d. array queue
           e. stacked queue
           f. doubly end queue
           g. separate chain hash
           h. open addressing hash
       
[list]:
-------
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

END
