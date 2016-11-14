#ifndef HAVE_TYPES_H
#define HAVE_TYPES_H

enum log_level {
    INFO,
    WARN,
    DBUG,
    ERRR,
};

typedef signed char            sint8;
typedef unsigned char          uint8;
typedef unsigned int           bool;
typedef unsigned long          native_wide_t;

#if defined X86_32
    typedef signed short       sint16;
    typedef unsigned short     uint16;
    typedef signed int         sint32;
    typedef unsigned int       uint32;
    typedef signed long long   sint64;
    typedef unsigned long long uint64;
    typedef unsigned int       ptr_t;
    #define M32
#endif

#if defined X86_64
    typedef signed short       sint16;
    typedef unsigned short     uint16;
    typedef signed int         sint32;
    typedef unsigned int       uint32;
    typedef signed long        sint64;
    typedef unsigned long      uint64;
    typedef unsigned long      ptr_t;
    #define M64
#endif


#endif

