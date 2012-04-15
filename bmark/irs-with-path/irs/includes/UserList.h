#ifndef UserList_H
#define UserList_H

/*------------------------------------------------------------------------------
- STRUCTURE
------------------------------------------------------------------------------*/

/* RGST_START */

struct UserList_ {

   char name[32];
   struct UserList_ *next;

};

typedef struct UserList_ UserList_t;

/* RGST_END */


/*------------------------------------------------------------------------------
- PROTOTYPES
------------------------------------------------------------------------------*/
#ifdef SILO
struct DBfile ;
extern void UserList_wtsilo( struct DBfile *idbid ) ;
extern void UserList_rdsilo( struct DBfile *idbid ) ;
#endif

extern UserList_t *UserList_find(char *attr) ;

extern int     UserList_input( void ) ;
extern int     UserList_parse( char *listname ) ;
extern int     UserList_print( void ) ;

extern void    UserList_add(char *name, char *attr) ;
extern void    UserList_del(char *attr) ;
extern void    UserList_remove(char *name, char *attr) ;
extern void    UserList_free( void ) ;


#endif

/*------------------------------------------------------------------------------
- GLOBAL VARS
------------------------------------------------------------------------------*/

/*******************************************************************************
* END OF FILE
*******************************************************************************/
