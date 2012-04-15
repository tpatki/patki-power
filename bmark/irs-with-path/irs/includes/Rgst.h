#ifndef Rgst_H
#define Rgst_H

/* RGST_START */

#include "irsdefs.h"
#include "Hash.h"

/* RGST_END */

/*------------------------------------------------------------------------------
- STRUCTURE
------------------------------------------------------------------------------*/

  /*----------------------------------------------------------------------------
  - This enumerated type specifes all the basic C data types that are known
  - to the registry.  The names of these types are fairly self-explanatory.
  -
  - I prefaced eachtype with "R_" to avoid name conflicts with other
  - libraries that may be linked with the code.
  -
  - Whenever more RGST enumerated datatypes are added, be sure to also
  - add string versions of the names to the rgst_datatype_strs[] and
  - rgst_datatype_sizes in rgst_init.c
  -----------------------------------------------------------------------------*/

/* RGST_START */

typedef enum { 
  GENERIC_ENUM_TYPE 
} GENERIC_ENUM_TYPEDEF;

typedef enum {

  R_CHAR,          R_UNSIGNED_CHAR,
  R_SHORT,         R_UNSIGNED_SHORT,
  R_SHORT_INT,     R_UNSIGNED_SHORT_INT,
  R_INT,           R_UNSIGNED_INT,
  R_LONG,          R_UNSIGNED_LONG,
  R_LONG_INT,      R_UNSIGNED_LONG_INT,
  R_LONG_LONG,     R_UNSIGNED_LONG_LONG,
  R_LONG_LONG_INT, R_UNSIGNED_LONG_LONG_INT,
  R_FLOAT,
  R_DOUBLE,
  R_VOID,
  R_STRUCT,
  R_CTYPE_TYPEDEF,
  R_ENUM_TYPEDEF,
  R_STRUCT_TYPEDEF,
  R_FUNCTION,
  R_INT_ARRAY,
  R_DOUBLE_ARRAY,
  NUM_RGST_Datatype_t

} RGST_Datatype_t;

  /*----------------------------------------------------------------------------
  - This enumerated type is used to specify the size of a dynamic array
  - in the registry.  That is, something that looks like
  -
  - double *myarray
  -
  - The actual length of this array can be either stored in another
  - field within the data structure that hold 'myarray', or it can be
  - stored in a global var, or it can be an absolute value given by
  - the call that adds this array to the registry.
  -----------------------------------------------------------------------------*/
typedef enum {

  FIELD_OFFSET, GLOBAL_VAR, ABSOLUTE_VALUE,
  NUM_ARRAY_SIZE_ENUM

} ARRAY_SIZE_ENUM;

  /*----------------------------------------------------------------------------
  - This enumerated type is used to speicify if an attribute is associated
  - with a typedef, a field within a structure, or with a registry object.
  -----------------------------------------------------------------------------*/
typedef enum {

  A_TYPE,
  A_FIELD,
  A_OBJECT,
  NUM_ATTR_Assoc_t

} ATTR_Assoc_t;

/* RGST_END */

/*------------------------------------------------------------------------------
- Forward declaration of typedefs and structures.
-
- These are used because of self-referential data structures.
-
- E.G. RGST_Attribute_t contains a ptr to  RGST_Object_t and
-      RGST_Object_t    contains a ptr to RGST_Attribute_t
-
-------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------
- This is used to hold a dynamically allocated array of attribute pointers.
-------------------------------------------------------------------------------*/

/* RGST_START */

struct RGST_Attribute_s ;

typedef struct {

  int num_attrs;                   /* Num of attrs in following attrs array */
  int size_attrs;                  /* Length of following attrs array */
  struct RGST_Attribute_s **attrs; /* Array full of attribute ptrs */

} AttrArray_t;

/* RGST_END */

/*------------------------------------------------------------------------------
- This defines a field of a structure for the registry
------------------------------------------------------------------------------*/
/* RGST_START */

typedef struct {

  char          name[R_MAXSTR_PLUS1];    /* Name of this field                */
  RGST_Datatype_t type;                  /* C Data type of this field         */
  int           type_size;               /* Size in bytes of this data type   */
  char          td_name[R_MAXSTR_PLUS1]; /* Name of structure or typedef of   */
                                         /*   this field.  Only used if above */
                                         /*   type is STRUCT, CTYPE_TYPEDEF,  */
                                         /*   ENUM_TYPEDEF, or STRUCT_TYPEDEF */
  long offset;                           /* Offset of this field from the     */
                                         /*   begining of the structure       */
  int  nptrs;                            /* Num of ptrs of this field         */
  int  ndims;                            /* Num of dimensions of this field   */
  int  dims[3];                          /* Dimensions of this field.         */
                                         /*   Only used if ndims > 0          */
  ARRAY_SIZE_ENUM array_size_type;       /* If this field is a ptr that will  */
                                         /* be used as an array, then the     */
                                         /* size of this array may be speci-  */
                                         /* fied by:                          */
                                         /*                                   */
                                         /* FIELD_OFFSET : Another field      */
                                         /*   within this data structure.     */
                                         /* GLOBAL_VAR : A global var placed  */
                                         /*   in the registry.                */
                                         /* ABSOLUTE_VALUE: An long spec-     */
                                         /*   fying the size of the array.    */
                                         /*                                   */
                                         /*                                   */
  int  array_size_field;                 /* If FIELD_OFFSET: the index of     */
                                         /*   another field in this struct    */
  long array_size_field_offset;          /* If FIELD_OFFSET: the offset of    */
                                         /*   another field in this struct    */
  char array_size_global_var[R_MAXSTR_PLUS1];
                                         /* If GLOBAL_VAR: the name of a      */
                                         /*   global var in the registry.     */
  long array_size_absolute_val;          /* If ABSOLUTE_VALUE: The size of    */
                                         /*   the ptr-array                   */
                                         /*                                   */
  int  str_array_size_field;             /* If this field is a ptr-to-ptr     */
                                         /* then the array-of-array sizes     */
                                         /* may be specified in another       */
                                         /* field within the structure.       */
                                         /* This is the index of this other   */
                                         /* field ...                         */
  long str_array_size_field_offset;      /* And this is the offset of the     */
                                         /* other field ...                   */
  AttrArray_t *attributes;               /* Attributes for this field */

} RGST_Field_t;

/* RGST_END */

/*------------------------------------------------------------------------------
- This defines a structure typedef for the registry
------------------------------------------------------------------------------*/
/* RGST_START */

typedef struct {

  char            name[R_MAXSTR_PLUS1]; /* Name of this structure definition  */
  RGST_Field_t   *fields;               /* Fields in this structure definition*/
  int             num_fields;           /* Number of fields                   */
  int             struct_size;          /* Size of entire structure in bytes  */
  AttrArray_t    *attributes;           /* Attributes for this typedef        */

} RGST_StructTypeDef_t;

/* RGST_END */

/*------------------------------------------------------------------------------
- This defines an enumerated typedef for the registry
------------------------------------------------------------------------------*/
/* RGST_START */

typedef struct {

  char            name[R_MAXSTR_PLUS1];
  int             num_entries;
  char **         entry_strings;        /* Pointer to array of strings which
                                           give the string names of each
                                           enumerated type entry */
  AttrArray_t    *attributes;           /* Attributes for this typedef */

} RGST_EnumTypeDef_t;

/* RGST_END */

/*------------------------------------------------------------------------------
- This defines a typedef of a 'C' type for the registry.
-------------------------------------------------------------------------------*/
/* RGST_START */

typedef struct {

  char            name[R_MAXSTR_PLUS1];
  RGST_Datatype_t type;
  int             type_size;
  int             nptrs;
  int             ndims;
  int             dims[3];
  AttrArray_t   *attributes;          /* Attributes for this typedef */

} RGST_CTypeDef_t;

/* RGST_END */

/*------------------------------------------------------------------------------
-
------------------------------------------------------------------------------*/
/* RGST_START */

typedef struct {

  RGST_Datatype_t type;
  int           type_size;

} RGST_BasicCTypeDef_t;

/* RGST_END */

/*------------------------------------------------------------------------------
-
------------------------------------------------------------------------------*/
/* RGST_START */

typedef struct {

  RGST_Datatype_t type;

} RGST_Function_t;

/* RGST_END */

/*------------------------------------------------------------------------------
- This defines a registry object.
------------------------------------------------------------------------------*/
/* RGST_START */

typedef struct {

  char           *name;         /* Unique name of this object */
  char           *usertype;     /* */
  RGST_Datatype_t datatype;     /* C data type of this object */
  int             nptrs;        /* eg. int **myint   would set nptrs to 2 */
  int             ndims;        /* eg. int myint[10] would set ndims to 1 */
  int             dims[3];      /* eg. int mying[10] would set dims[0] to 10 */
  void           *obj;          /* Pointer to the object */

  ARRAY_SIZE_ENUM array_size_type;
  int             array_size_field;
  long            array_size_field_offset;
  char            array_size_global_var[R_MAXSTR_PLUS1];
  long            array_size_absolute_val;

  AttrArray_t   *attributes;  /* Attributes for this typedef */

} RGST_Object_t;

/* RGST_END */

/*------------------------------------------------------------------------------
- Data structure of an element in the attributes hash table, and
- linked list.
-
- This stores the info for an object that has a given attribute.
-
- EG. The "zonal" attributes hash table and linked lists would be
-     comprised of many of these, one for each object, field, or
-     data structure that has the "zonal" attribute".
-
------------------------------------------------------------------------------*/

/* RGST_START */

typedef struct RGST_AttributeElem_s {


  char *name;                  /* Unique key which is either
                                    0) The name of a  structure
                                    1) The name of a  structure + field
                                    2) The name of an object */

  ATTR_Assoc_t assoc;            /* What this attribute is attached to
                                  A_TYPE   = typedef,
                                  A_FIELD  = field,
                                  A_OBJECT = registry object.  */

  RGST_Datatype_t rgst_datatype; /* If above assoc is A_TYPE or A_FIELD,
                                  then the type of the data structure.
                                  It may be one of the following types:

                                  RGST_STRUCT         if assoc is type or field
                                  RGST_STRUCT_TYPEDEF if assoc is type or field
                                  RGST_CTYPE_TYPEDEF  if assoc is type
                                  RGST_ENUM_TYPEDEF   if assoc is type */

  RGST_CTypeDef_t      *rgst_ctype_defn;  /* If assoc is type or field, one of */
  RGST_EnumTypeDef_t   *rgst_enum_defn;   /* these 3 will contain a ptr to the   */
  RGST_StructTypeDef_t *rgst_struct_defn; /* registry structure definition.      */

  RGST_Field_t *rgst_field;      /* If above type is field then ptr to registry
                                  field definition (which contains, among
                                  other things, the offset of this field
                                  within the data structure */

  RGST_Object_t *rgst_obj;       /* If above type is object, then ptr to registry
                                  object definition */

  struct RGST_AttributeElem_s     *next,
                                  *prev;

} RGST_AttributeElem_t;

/* RGST_END */

/*------------------------------------------------------------------------------
- Data structure for an attribute
-
- Note: This structure will be placed within the general hash table
-       for the code.  So the first thing to do when querying the
-       attribute, is to retrieve this data structure, with a unique
-       key such as "zonal", from the general hash table.
------------------------------------------------------------------------------*/

/* RGST_START */

typedef struct RGST_Attribute_s {

  char *attr_name;                    /* e.g. "zonal", Unique key */

  RGST_AttributeElem_t *obj_head,     /* linked list of objects with attr */
                       *type_head,    /* linked list of types   with attr */
                       *field_head;   /* linked list of fields  with attr */

  HashTable_t          *table;        /* Hash table, containing all objects,
                                         structs, and fields with this attr */

} RGST_Attribute_t;

/* RGST_END */


/*------------------------------------------------------------------------------
- PROTOTYPES
------------------------------------------------------------------------------*/

extern int  AttrArray_init(AttrArray_t *ptr);
extern int  RGST_Object_init(RGST_Object_t *ptr);
extern void AttrArray_add(RGST_Attribute_t *new_attr, AttrArray_t *ptr);
extern void AttrArray_del(char *attr_name, AttrArray_t *ptr);

extern RGST_AttributeElem_t * rgst_copy_attr_elm_list(RGST_AttributeElem_t *elm_list);
extern RGST_AttributeElem_t * rgst_create_RGST_AttributeElem_t(char *name, ATTR_Assoc_t assoc, RGST_Datatype_t datatype, void *v_ptr, RGST_Field_t *fld_ptr);
extern RGST_AttributeElem_t * rgst_free_RGST_AttributeElem_t(RGST_AttributeElem_t *ptr);
extern RGST_AttributeElem_t * rgst_free_attr_elm_list(RGST_AttributeElem_t *ptr);
extern RGST_Attribute_t     * rgst_free_RGST_Attribute_t(RGST_Attribute_t *ptr);
extern RGST_Attribute_t     * AttrArray_search(char *attr_name, AttrArray_t *ptr);
extern RGST_Object_t        * RGST_Object_construct(int num);
extern RGST_Object_t        * RGST_Object_create(char *name, char *type_str, RGST_Datatype_t datatype, int nptrs, int ndims, int *dims, void *obj, ARRAY_SIZE_ENUM array_size_type, int array_size_field, long array_size_field_offset, char *array_size_global_var, long array_size_absolute_val);
extern RGST_Object_t        * RGST_Object_destruct(RGST_Object_t *ptr);
extern AttrArray_t          * AttrArray_construct(int num);
extern AttrArray_t          * AttrArray_destruct(AttrArray_t *ptr);

#endif

/*------------------------------------------------------------------------------
- GLOBAL VARS
------------------------------------------------------------------------------*/

/*******************************************************************************
* END OF FILE
*******************************************************************************/
