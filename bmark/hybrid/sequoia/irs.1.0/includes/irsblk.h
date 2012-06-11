#ifndef irsblk_H
#define irsblk_H

#include "Extents.h"

/*******************************************************************************
* PROTOTYPES
*******************************************************************************/
struct Domain_s ;

extern int Blocks_match(void);
extern int Blocks_parse(void);
extern int blkdiv(void);
extern int blkdivin(int mode);
extern int blkgen(struct Domain_s *domain);
extern int blockin0(int type);
extern int domain_allot_arrays1(struct Domain_s *domain);
extern int domain_allot_arrays2(struct Domain_s *domain);
extern int reblkdiv(void);
extern void domain_allot(struct Domain_s *domain, int imax, int jmax, int kmax);
extern void domain_allot_fields(struct Domain_s *domain);
extern void domain_attr(void);
extern void domain_free(struct Domain_s *domain);
extern void domain_free_attr(void);
extern void domain_setlimits(struct Domain_s *domain, int imax, int jmax, int kmax);
extern void domain_setpa(struct Domain_s *domain);
extern void domaincopy(struct Domain_s *domain1, Extents_t *ext1, struct Domain_s *domain2, Extents_t *ext2);
extern void initblk(int iblk, struct Domain_s *domain);

#endif
/*******************************************************************************
* GLOBALS
*******************************************************************************/

/*******************************************************************************
* END OF FILE
*******************************************************************************/
