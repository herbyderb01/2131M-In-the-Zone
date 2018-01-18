#include "PIDS&Motors&Vars.c"
#include "AtonVoids.c"

 task Skills ()
{
  calwRequestedValue = 705;
  liftRRequestedValue = 1500;

  drivePID(1000);
}

task TenPoint ()
{
  liftRRequestedValue = 1500;

}
