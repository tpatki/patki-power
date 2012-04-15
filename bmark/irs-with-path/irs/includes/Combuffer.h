#ifndef Combuffer_H
#define Combuffer_H

#include "FunctionTimer.h"

/*------------------------------------------------------------------------------
- DEFINES AND MACROS
------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------
- STRUCTURE
------------------------------------------------------------------------------*/

typedef struct {

   int bufnum;              /* number of this communications buffer */

   char bufname[MAXWORD];   /* name of this communications buffer */

   int *proc;               /* mapping of processor number to individual
                                    buffer number */

   int size;                /* number of individual buffers */

   int *len_sendi;          /* length of the integer send buffers */
   int *len_sendd;          /* length of the double send buffers  */
   int *len_recvi;          /* length of the integer recv buffers */
   int *len_recvd;          /* length of the double recv buffers  */

   int **sendi_buf;         /* pointer to integer send buffer     */
   int **sendi_ptr;         /* pointer into integer send buffer   */
   int **recvi_buf;         /* pointer to integer recv buffer     */
   int **recvi_ptr;         /* pointer into integer recv buffer   */


   double **sendd_buf;      /* pointer to double send buffer      */
   double **sendd_ptr;      /* pointer into double send buffer    */
   double **recvd_buf;      /* pointer to double recv buffer      */
   double **recvd_ptr;      /* pointer into double recv buffer    */

   int **blk_order;         /* pointer to block order of buffer packing */
   int **tag_order;         /* pointer to bc order of buffer packing    */
   int  *len_order;         /* length of order arrays                   */
   int  len_order_send;     /* length of send portion of order arrays   */

   double starttime;        /* start timer                    */
   double *comtimer;        /* accumulated time for each call */

   int mesgtag;             /* message tag for messages sent with this buffer */
   MPI_Request* send_request;  /* array of requests for sends  */
   MPI_Request* recv_request;  /* array of requests for recv's */

   MPI_Status* send_status;    /* array of status (or stati) for sends  */
   MPI_Status* recv_status;    /* array of status (or stati) for recv'c */

   MPI_Comm* comm;              /* communicator used with this buffer    */

} Combuffer_t;

/*------------------------------------------------------------------------------
- PROTOTYPES
------------------------------------------------------------------------------*/

#endif
/*------------------------------------------------------------------------------
- GLOBAL VARS
------------------------------------------------------------------------------*/

/*******************************************************************************
* END OF FILE
*******************************************************************************/
