#ifndef IRSOBJECTS_H
#define IRSOBJECTS_H

/*******************************************************************************
* DEFINES
*******************************************************************************/

/*******************************************************************************
* PROTOTYPES
*******************************************************************************/

extern void GlobalArrays_register( void );
extern void GlobalArrays_free( HashTable_t *hash );
extern void GlobalArrays_allot( HashTable_t *hash );
extern int ObjectName_input(void );
extern char *ObjectName_get(void);
extern int SubMesh_parse( void );

#ifdef SILO
extern void SubMesh_wtroot ( DBfile *idbid, DBoptlist *ioptnod, char **rootnames ) ;
extern void SubMesh_wtdomain ( DBfile *idbid, Domain_t *domain) ;
#endif

extern void SubMesh_free ( void );
extern int printtimer(void);
 


#endif
/*******************************************************************************
* GLOBALS
*******************************************************************************/

/*******************************************************************************
* END OF FILE
*******************************************************************************/

