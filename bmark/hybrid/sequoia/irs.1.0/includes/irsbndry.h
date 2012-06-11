#ifndef irsbndry_H
#define irsbndry_H

/*******************************************************************************
* DEFINES
*******************************************************************************/

/*******************************************************************************
* PROTOTYPES
*******************************************************************************/
struct Domain_s ;
struct BlockMapping_s ;
struct Boundary_s ;

extern int MatchFourNodes(int node1, int node2, int node3, int node4, int *NodeList, int len);
extern int bcin(void);
extern int bcin0(int len, int *ndx, int ibc, char *op, struct Domain_s *domain);
extern int bcnorm(double *norm, int len, int *ndx, struct Domain_s *domain);
extern int bndin(void);
extern int bndry_findcrn(struct BlockMapping_s *map, int nmap);
extern int bndrydev(void);
extern int vsamein0(int len, int *ndx, int ibc, struct Domain_s *domain);
extern void bndcopy(struct Domain_s *domain1, int *mapin, struct Domain_s *domain2, int *mapout, int lenmap, int irep);
extern void bndry_init(void);
extern void bndry_setgbnd(void);
extern void bndry_setmomflx(void);
extern void bndry_zdxneighbor(void);
extern void bndzonelist(struct Domain_s *domain);
extern void genradreflst(struct Domain_s *domain);
extern void genreflst(struct Domain_s *domain);
extern void getbcname(char *op, int ibc, struct Domain_s *domain);
extern void initbc(struct Domain_s *domain);
extern void irefzq(int *zq, struct Domain_s *domain);
extern void orient_ublks(void);
extern void refadv2d(struct Domain_s *domain);
extern void refadv3d(struct Domain_s *domain);
extern void refnd2d(double *x, double *y, struct Domain_s *domain);
extern void refnd3d(double *x, double *y, double *z, struct Domain_s *domain);
extern void refnd3ds(double *a, struct Domain_s *domain);
extern void refradnq(double *ndq, struct Domain_s *domain);
extern void refzq(double *zq, struct Domain_s *domain);
extern void setbndry(double *v, double s, struct Domain_s *domain);
extern void setcrnlst(int len, int *ndx, int *nflg, int nstr, struct Boundary_s *bnd, struct Domain_s *domain);
extern void setphony(double *v, double s, struct Domain_s *domain);
extern void setphony2(double *v, double s, struct Domain_s *domain);
extern void sewbndry(void);
extern void vsameorg(void);

#endif
/*******************************************************************************
* GLOBALS
*******************************************************************************/

/*******************************************************************************
* END OF FILE
*******************************************************************************/
