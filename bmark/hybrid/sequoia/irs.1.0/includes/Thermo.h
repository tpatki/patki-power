#ifndef Thermo_H
#define Thermo_H

/*------------------------------------------------------------------------------
- STRUCTURE
------------------------------------------------------------------------------*/

typedef struct {

  double *p       ; 
  double *dpdr    ;
  double *dpde    ; 
  double *dpdt    ; 

  double *pion    ;
  double *dpidr   ;
  double *dpidei  ; 
  double *dpidti  ; 

  double *dtdr    ;
  double *dtde    ; 

  double *dtidr   ;
  double *dtidei  ; 
  double *dtedei  ;

  double *drdp    ; 
  double *drde    ;
  double *drdt    ;
  double *drdti   ; 

  double *dedp    ; 
  double *dedr    ;
  double *dedt    ;
  double *dedti   ;
  double *dedt_v  ;

  double *deidp   ; 
  double *deidr   ; 
  double *deidti  ; 
  double *deidte  ; 
  double *deidt_v ; 

  double *den     ; 
  double *emat    ; 
  double *tmat    ; 

  double *eion    ; 
  double *tion    ; 

  double *p_cold  ; 
  double *e_cold  ; 
  double *dp_cdr  ; 
  double *cs      ;  
  double *cs2     ; 
  double *work3   ;  
  double *work1   ;  
  double *work2   ;

  double *abar    ; 
  double *zbar    ; 
  double *zstar   ; 

  double *tdedte  ; 
  double *tdedti  ; 
  double *tdedp   ; 
  double *tdeidte ; 
  double *tdeidti ; 
  double *tdeidp  ; 
  double *tdrdte  ; 
  double *tdrdti  ; 
  double *tdrdp   ; 

  double *dtlast  ;  
  double *delast  ; 
  double *deilast ; 
  double *drlast  ; 

  double *cdmin   ; 
  double *cdmax   ; 

  double *cpmin   ; 
  double *cpmax   ; 

  double *ceemin  ; 
  double *ceemax  ; 

  double *ctemin  ; 
  double *ctemax  ; 

  double *ceimin  ; 
  double *ceimax  ; 

  double *ctimin  ;  
  double *ctimax  ; 

} Thermo_t ;


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
