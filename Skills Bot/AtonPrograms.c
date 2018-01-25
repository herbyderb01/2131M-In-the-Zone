#include "PIDS&Motors&Vars.c"
#include "Drive PID.c"
#include "AtonVoids.c"
//#region Skills
 void Skills ()
{
  calwRequestedValue = 1266;
  liftRRequestedValue = 2100;

  droveStraight(800,true);

  calwRequestedValue = 880;
  wait1Msec(1000);

  liftRRequestedValue = 1000;

  droveStraight(2300,true);

}
//#endregion
//#region Ten Point AtonPrograms
void TenPoint ()
{
  liftRRequestedValue = 1800;          // PRESETS

  droveStraight(900);
  wait1Msec(200);

//  Turn(rightTurn);

}
//#endregion
