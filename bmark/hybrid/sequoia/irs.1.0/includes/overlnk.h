#ifndef overlnk_H
#define overlnk_H


#define BC_FREE     -1
#define BC_REFLECT  -2

#define NUM_ATTRS 5

#define CENTERING  0
#define SCALING    1
#define DEPENDENCY 2
#define DATA_TYPE  3
#define LINKING    4

#define ATTR_NODAL        0  /* Centering */
#define ATTR_ZONAL        1
#define ATTR_FACE         2
#define ATTR_EDGE         3

#define ATTR_INTENSIVE    0  /* Scaling */
#define ATTR_EXTENSIVE    1

#define ATTR_DEPENDENT    0  /* Dependency */
#define ATTR_INDEPENDENT  1

#define ATTR_INTEGER      0  /* Data type */
#define ATTR_FLOAT        1

#define ATTR_FIRST_ORDER  0   /* Linking */
#define ATTR_SECOND_ORDER 1

#endif

