#include "PIDS&Motors&Vars.c"
#include "Drive PID.c"
#include "AtonVoids.c"
//#region Skills
 void Skills ()
{
  calwRequestedValue = 705;
  liftRRequestedValue = 1500;

}
//#endregion
//#region Ten Point AtonPrograms
void TenPoint ()
{
  liftRRequestedValue = 2600;          // PRESETS
	while(1==1)
	{
		droveStraight(900,true);
		liftRRequestedValue=2200;
		wait1Msec(2000);
		droveStraight(-900);
	liftRRequestedValue = 3000;
	wait1Msec(3000);
	}
}
//#endregion
