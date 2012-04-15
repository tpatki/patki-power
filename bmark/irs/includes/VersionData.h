#ifndef VersionData_H
#define VersionData_H

/*------------------------------------------------------------------------------
- STRUCTURE
------------------------------------------------------------------------------*/

/* RGST_START */

typedef struct {
   char *node_compiled;
   char *date_compiled;
   char *time_compiled;
   char *os_compiled;
   char *opt_compiled;
   char *dump_version;
   char *person;
} VersionData_t ;

/* RGST_END */


/*------------------------------------------------------------------------------
- PROTOTYPES
------------------------------------------------------------------------------*/
extern VersionData_t * VersionData_destruct(VersionData_t *ptr);

#endif

/*------------------------------------------------------------------------------
- GLOBAL VARS
------------------------------------------------------------------------------*/

extern VersionData_t gv_ver;            /* global version data structure */

/*******************************************************************************
* END OF FILE
*******************************************************************************/
