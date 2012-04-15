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

int MatchFourNodes(int node1, int node2, int node3, int node4, int *NodeList, int len);
int bcin(void);
int bcin0(int len, int *ndx, int ibc, char *op, struct Domain_s *domain);
int bcnorm(double *norm, int len, int *ndx, struct Domain_s *domain);
int bndin(void);
int bndry_findcrn(struct BlockMapping_s *map, int nmap);
int bndrydev(void);
int vsamein0(int len, int *ndx, int ibc, struct Domain_s *domain);
void bndcopy(struct Domain_s *domain1, int *mapin, struct Domain_s *domain2, int *mapout, int lenmap, int irep);
void bndry_init(void);
void bndry_setgbnd(void);
void bndry_setmomflx(void);
void bndry_zdxneighbor(void);
void bndzonelist(struct Domain_s *domain);
void genradreflst(struct Domain_s *domain);
void genreflst(struct Domain_s *domain);
void getbcname(char *op, int ibc, struct Domain_s *domain);
void initbc(struct Domain_s *domain);
void irefzq(int *zq, struct Domain_s *domain);
void orient_ublks(void);
void refadv2d(struct Domain_s *domain);
void refadv3d(struct Domain_s *domain);
void refnd2d(double *x, double *y, struct Domain_s *domain);
void refnd3d(double *x, double *y, double *z, struct Domain_s *domain);
void refnd3ds(double *a, struct Domain_s *domain);
void refradnq(double *ndq, struct Domain_s *domain);
void refzq(double *zq, struct Domain_s *domain);
void setbndry(double *v, double s, struct Domain_s *domain);
void setcrnlst(int len, int *ndx, int *nflg, int nstr, struct Boundary_s *bnd, struct Domain_s *domain);
void setphony(double *v, double s, struct Domain_s *domain);
void setphony2(double *v, double s, struct Domain_s *domain);
void sewbndry(void);
void vsameorg(void);

#endif
/*******************************************************************************
* GLOBALS
*******************************************************************************/

/*******************************************************************************
* END OF FILE
*******************************************************************************/
