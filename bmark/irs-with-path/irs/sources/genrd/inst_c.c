#include "irs.h"
#include "irsgenrd.h"
#include "irsrgst.h"
#include "Command.h"
void inst_c(
       char       *cname,  int     (*cproc)(void),   int  (*chand)(Command_t  *), 
       int         carg,   HashTable_t *tab )
{
    Command_t *cp;
    cp = MALLOT(Command_t,1);
    cp->name = strsave(cname);
    cp->arg  = carg;
    cp->proc = cproc;
    cp->handler = chand;
    hash_add(cname, "Command_t", cp, tab);
    rgst_add(cname, "function", cp, NULL);
}
