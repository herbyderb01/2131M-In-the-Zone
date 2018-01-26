#include "PIDS&Motors&Vars.c"
#include "Drive PID.c"
#include "AtonVoids.c"
//#region Skills
 void Skills ()
{
  LiftTo(1240);
  setClawTo(1222);

  droveStraight(900,true);

  calwRequestedValue = 880;
  wait1Msec(1000);

  LiftTo(2100,true);

  droveStraight(1000,true);

  wait1Msec(100);

  droveStraight(1280,true);
                                    //end of pushing
  droveStraight(-370,true);

  Turn(leftTurn/2,true);

  droveStraight(600,true);

  Turn(rightTurn/2,true);

  liftRRequestedValue = 1680;

  droveStraight(460,true);

  calwRequestedValue = 1220;
  wait1Msec(200);

//  droveStraight(-,true);

}
//#endregion
//#region Ten Point AtonPrograms
void TenPoint ()
{
  LiftTo(1300,true);

  Turn(rightTurn/2,true);

  Turn(leftTurn/2,true);

  droveStraight(370,true);
  droveStraight(-370,true);
  /*
  setClawTo(1222,true);

  LiftTo(1600);
  wait1Msec(6000);
  LiftTo(2800,true);

//  Turn(rightTurn);
*/
}
//#endregion
