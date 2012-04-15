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
int boxid(void);
int create_temp_pa(void);
int free_temp_pa(void);
int memclr_input(int mode);
int ndset(void);
int newparm(char *name, void *parm, RGST_Datatype_t type, int len);
int set(void);
int setparmc(char *name, char *cval);
int setparmf(char *name, double dval);
int setparmi(char *name, int ival);
void memclr(void);
void memexp(void);
void parminit(void);
void parmsanity(void);

#endif
/*******************************************************************************
* GLOBALS
*******************************************************************************/

/*******************************************************************************
* END OF FILE
*******************************************************************************/
