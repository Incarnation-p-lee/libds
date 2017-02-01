#ifndef HAVE_DEFINED_SET_DEFINE_H
#define HAVE_DEFINED_SET_DEFINE_H

#define DISJOINT_TOP          -1
#define DISJOINT_ZERO_SIZE    0

#if defined DEBUG
    #define DISJOINT_SET_LEGAL_P(set)   disjoint_set_structure_legal_p(set)
    #define DISJOINT_SET_ILLEGAL_P(set) disjoint_set_structure_illegal_p(set)
#else
    #define DISJOINT_SET_LEGAL_P(set)   NON_NULL_PTR_P(set)
    #define DISJOINT_SET_ILLEGAL_P(set) NULL_PTR_P(set)
#endif

#endif

