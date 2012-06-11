#include "irs.h"
#include "irsrgst.h"
#include "Conditional.h"
#include "FunctionTimer.h"
#include "FreqMesg.h"
#include "Gparm.h"
#include "Region.h"
#include "Source.h"
#include "Spline.h"
#include "Transform.h"
#include "TimePlot.h"
void setup_attrs(void) 
{
  char *me = "setup_attrs";
  int ierr = 0;
  TimePlotCurve_setup_attrs();
  TimePlot_setup_attrs();
  BoundaryCondition_setup_attrs();
  Boundary_setup_attrs();
  Conditional_setup_attrs();
  Database_setup_attrs();
  Domain_setup_attrs();
  EosGroup_setup_attrs();
  FunctionTimer_setup_attrs();
  OpacityGroup_setup_attrs();
  Region_setup_attrs();
  Source_setup_attrs();
  Species_setup_attrs();
  Spline_setup_attrs();
  SourceNew_setup_attrs();
  Transform_setup_attrs();
  ierr += RGST_ADD_ATTR_TO_FIELDS("FreqMesg_t",        "dump");
  ierr += RGST_ADD_ATTR_TO_FIELDS("CycleMesg_t",       "dump");
  ierr += RGST_ADD_ATTR_TO_FIELDS("Gparm_t",           "dump");
  ierr += RGST_ADD_ATTR_TO_FIELDS("VersionData_t",     "dump");
  ierr += RGST_ADD_ATTR_TO_FIELDS("Component_t",       "dump");
  ierr += RGST_ADD_ATTR_TO_FIELDS("TimeStepControl_t", "dump");
  if (ierr != 0) ctlerror(me,gv_errmsg_rgst_add_attrs_to_fields);
}
