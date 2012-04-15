#ifndef ProblemArray_H 
#define ProblemArray_H 


/* RGST_START */

#include "irsdefs.h"
#include "Hash.h"
#include "Rgst.h"

/* RGST_END */

/*------------------------------------------------------------------------------
- STRUCTURE
------------------------------------------------------------------------------*/

/* RGST_START */

typedef struct {

   char             name[MAXWORD];	/* name of problem array */
   void            *ptr;   		/* pointer to data */
   int              len;   		/* length of data */
   HashTable_t     *hash;  		/* hash table */
   RGST_Datatype_t  type;  		/* type of data */

} ProblemArray_t;

/* RGST_END */

/*------------------------------------------------------------------------------
- PROTOTYPES
------------------------------------------------------------------------------*/
 
extern ProblemArray_t * ProblemArray_find(char *name, HashTable_t *hash);  
extern ProblemArray_t * ProblemArray_setblk(char *name);

extern HashTable_t * ProblemArray_GetHash(char *name, HashTable_t *hash);

extern void ProblemArray_add(char *name, void *ptr, int len, RGST_Datatype_t type,  HashTable_t *hash); 
extern void ProblemArray_del(char *name, HashTable_t *hash); 
extern void ProblemArray_del_all(HashTable_t* hash) ; 
extern void ProblemArray_free(char *name);
extern void ProblemArray_FreeHash(char *name, HashTable_t *hash);
extern void ProblemArray_CreateHash(char *name, HashTable_t *hash, int size);
  
extern void * ProblemArray_allotptr(char *name, HashTable_t *hash);
extern void * ProblemArray_ptr(char *name, HashTable_t *hash);  

#endif  

/*------------------------------------------------------------------------------
- GLOBAL VARS
------------------------------------------------------------------------------*/

/*******************************************************************************
* END OF FILE
*******************************************************************************/
