#ifndef Hash_H
#define Hash_H

/*------------------------------------------------------------------------------
- DEFINES AND MACROS
------------------------------------------------------------------------------*/

#define DEFAULT_HASHSIZE	31	/* Number of slots in a hash table */
#define GENERAL_HASHTBL_NAME	"general"

#define HASH(m_hv, m_ht, m_str)  {              \
    register int   my_hashval = 0;              \
    register char *my_hashstr = m_str;          \
    register char *my_savstr  = m_str;          \
    for (; *my_hashstr != '\0'; ) my_hashval = (my_hashval << 1) ^ (*my_hashstr++); \
    if (strlen(my_savstr) > 30) { for (; *my_savstr != '\0'; ) { my_hashval += *my_savstr++; } } \
    m_hv = abs(my_hashval) % m_ht->size;        \
  }

/*------------------------------------------------------------------------------
- STRUCTURE
------------------------------------------------------------------------------*/

/* RGST_START */

typedef struct HashElm_s {
  char *name;                           /* Unique string which identifies the
					   object in the hash table */
  char *type;				/* String which identifies the type
					   of data that *obj points to */
  void *obj;				/* Pointer to the object stored in the
					   hash table */	
  struct HashElm_s *next;		/* Pointer to next hash table element
					   within a specific slot of the 		
					   hash table.  All elements in this
					   chain have names that hash to the
					   same value */	
} HashElm_t;

typedef struct {                        /* A structure that holds an array */
                                        /* full of hash elements (slots) and */
                                        /* an int that specifies the number */
                                        /* of slots */

  char      *name;                      /* Optional unique name for this hash table */
                                        /*   Used to place hash table in registry */
  int       size;                       /* Numer of slots in the hash table */
  HashElm_t **tbl;                      /* RGST_LEN size */

  double d1,d2,d3,d4,d5,d6,d7,d8;       /* Scratch doubles and ints */
  int    i1,i2,i3;                      /* Used to store stuff identifiers */
                                        /* or other stuff in a thread-safe manner */
  
} HashTable_t;

/* RGST_END */


/*******************************************************************************
* PROTOTYPES
*******************************************************************************/

extern HashElm_t * * hash_get_elm_list(int *num_elms, char *type, HashTable_t *ht);
extern HashElm_t * hash_lookup_elm (char *name, HashTable_t *ht);
extern HashTable_t * hash_tbl_create(int size, char *name);
extern HashTable_t * hash_tbl_free(HashTable_t *ht, int free_obj_flag);
extern void * hash_lookup_obj (char *name, HashTable_t *ht);
extern void hash_add(char *name, char *type, void *obj, HashTable_t *ht);
extern void hash_cond_print_by_type(HashTable_t *ht, char *name);
extern void hash_del(char *name, HashTable_t *ht);
extern void hash_del2(char *name, char *type, HashTable_t *ht);
extern void hash_del_objs_of_type(HashTable_t *ht, char *type, void (*fn_ptr) ());
extern void hash_print        (HashTable_t *ht);
extern void hash_print_by_name(HashTable_t *ht);
extern void hash_print_by_type(HashTable_t *ht);
extern void hash_print_obj(HashElm_t *ptr);
extern void hash_print_structs_of_type(HashTable_t *ht, char *type);
extern void hash_sort_array(HashElm_t **hash_elm_array, int num_objs);
extern void hash_sort_array_by_type(HashElm_t **hash_elm_array, int num_objs);
extern void hash_analyze(HashTable_t *ht, int print_flag, FILE *fp, double *avg_chain, int *max_chain);
extern int get_num_elms_in_hashtable(HashTable_t *ht);
extern int hash_optimize(HashTable_t * *htp);
extern int hash_optimize_all(void);
extern int printhash(void);
extern char * strsave(char *ptr);


#endif

/*******************************************************************************
* GLOBALS
*******************************************************************************/

/*------------------------------------------------------------------------------
- gv_hash_tbl - free'd and reallocated by memclr  
- gv_perm_ht  - exists ALWAYS, used for getting wall time of main, which
-               should NOT be reset when a new silo file is read.
------------------------------------------------------------------------------*/

extern HashTable_t *gv_hash_tbl;          /* HH_INIT NULL */
extern HashTable_t *gv_perm_ht;           /* HH_INIT NULL */   
 
/*******************************************************************************
*                      E N D   O F   F I L E
*******************************************************************************/

