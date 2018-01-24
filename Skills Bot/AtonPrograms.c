#include "PIDS&Motors&Vars.c"
#include "Drive PID.c"
#include "AtonVoids.c"
//#region Skills
 task Skills ()
{
  calwRequestedValue = 705;
  liftRRequestedValue = 1500;

  drivePID(1000);
}
//#endregion
//#region Ten Point AtonPrograms
task TenPoint ()
{
  liftRRequestedValue = 1500;

}
//#endregion
