#include "irs.h"
#include "irsdefs.h"
#include "Hash.h"
#include "irsdefs.h"
 #include "Hash.h"
char *strsave(char *ptr)	
{
  char *me = "strsave";
  char *return_ptr;
  if (ptr == NULL) { return (NULL); }
  return_ptr = malloc(strlen(ptr) + 2);
  if (return_ptr == NULL) {
    fprintf(stderr,"%s: out of memory\n",me);
    exit(EXIT_FAILURE);
  }
  memset(return_ptr,'\0',strlen(ptr) + 2);
  strcpy(return_ptr,ptr);
  return(return_ptr);
}
