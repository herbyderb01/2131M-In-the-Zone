#include "PIDS&Motors&Vars.c"
#include "Drive PID.c"
#include "AtonVoids.c"
//#region Skills
 void Skills ()
{
  setClawTo(1222,true);
  LiftTo(2180,true);

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
  setClawTo(1222,true);

  LiftTo(2180,true);
  wait1Msec(2000);
  LiftTo(1500,true);

//  Turn(rightTurn);

}
//#endregion
