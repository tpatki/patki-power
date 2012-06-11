#ifndef Command_H
#define Command_H

/*------------------------------------------------------------------------------
- STRUCTURE
------------------------------------------------------------------------------*/

typedef struct Command_s {

  char *name;
  int arg;
  int (*proc)();
  int (*handler)(struct Command_s *);

} Command_t ;


/*------------------------------------------------------------------------------
- PROTOTYPES
------------------------------------------------------------------------------*/
extern Command_t * build_proc_name(char *struct_name, char *procedure_suffix, char *routine_name);
extern int sargs(Command_t *cp);
extern int sargse(Command_t *cp);
extern int zargs(Command_t *cp);
extern int zargse(Command_t *cp);
extern void rgst_print_function(Command_t *cp);

#endif

/*------------------------------------------------------------------------------
- GLOBAL VARS
------------------------------------------------------------------------------*/

/*******************************************************************************
* END OF FILE
*******************************************************************************/
