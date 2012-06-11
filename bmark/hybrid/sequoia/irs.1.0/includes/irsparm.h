#ifndef IRSPARM_H
#define IRSPARM_H

/*******************************************************************************
* DEFINES
*******************************************************************************/

#define NEWPARMI(myname,myparm,myinit)	\
  myparm = myinit;			\
  newparm(myname,&myparm,R_INT,0);

#define NEWPARMF(myname,myparm,myinit)	\
  myparm = myinit;			\
  newparm(myname,&myparm,R_DOUBLE,0);

#define NEWPARMC(myname,myparm,myinit,mylen)	\
  strncpy(myparm,myinit,mylen);			\
  newparm(myname,&myparm,R_CHAR,mylen);

/*******************************************************************************
* PROTOTYPES
*******************************************************************************/
extern int boxid(void);
extern int create_temp_pa(void);
extern int free_temp_pa(void);
extern int memclr_input(int mode);
extern int ndset(void);
extern int newparm(char *name, void *parm, RGST_Datatype_t type, int len);
extern int set(void);
extern int setparmc(char *name, char *cval);
extern int setparmf(char *name, double dval);
extern int setparmi(char *name, int ival);
extern void memclr(void);
extern void memexp(void);
extern void parminit(void);
extern void parmsanity(void);

#endif
/*******************************************************************************
* GLOBALS
*******************************************************************************/

/*******************************************************************************
* END OF FILE
*******************************************************************************/
