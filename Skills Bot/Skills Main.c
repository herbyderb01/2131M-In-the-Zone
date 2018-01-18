#pragma config(Sensor, in1,    clawp,          sensorPotentiometer)
#pragma config(Sensor, in2,    liftPot,        sensorPotentiometer)
#pragma config(Sensor, in3,    selectpot,      sensorPotentiometer)
#pragma config(Sensor, in4,    Gyro,           sensorGyro)
#pragma config(Sensor, dgtl1,  rightEncoder,   sensorQuadEncoder)
#pragma config(Sensor, dgtl3,  leftEncoder,    sensorQuadEncoder)
#pragma config(Motor,  port1,           Claw,          tmotorVex393_HBridge, openLoop)
#pragma config(Motor,  port2,           LexDrive,      tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port3,           RexDrive,      tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port4,           LDriveOne,     tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port5,           LDriveTwo,     tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port6,           RDriveOne,     tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port7,           RDriveTwo,     tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port8,           LOne,          tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port9,           LTwo,          tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port10,          LThree,        tmotorVex393_HBridge, openLoop, reversed)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#pragma platform(VEX2)
#pragma competitionControl(Competition)

#include "Vex_Competition_Includes.c"
#include "PIDS&Motors&Vars.c"
#include "AtonPrograms.c"
#include "AtonVoids.c"

task drive() //Redirecting Drive into a task
{
	while (true)
	{
		setDrivePower(vexRT[Ch3], vexRT[Ch2]);
	}
wait1Msec(25);
}
///*/*/*/*//*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*/*//**/*/*/*/*/*/*/

/*---------------------------------------------------------------------------*/
/*                          Pre-Autonomous Functions                         */
/*---------------------------------------------------------------------------*/

void pre_auton()
{
}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              Autonomous Task                              */
/*                                                                           */
/*---------------------------------------------------------------------------*/

task autonomous()
{

	startTask(calwController);
	startTask(liftRController);
	startTask(DriveController);

	if (SensorValue[selectpot] < 2045)
	{
		startTask(Skills);
	}
	if (SensorValue[selectpot] > 2045)
	{
		startTask(TenPoint);
	}


}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              User Control Task                            */
/*                                                                           */
/*---------------------------------------------------------------------------*/

task usercontrol()
{
	startTask(calwController);
	calwRequestedValue = 605;
	startTask(drive);

  while (true)
  {
  	//----------------------Claw------------------------//
		if( vexRT[Btn6U] == 1)      // Setting Btn7U to Extend Goal
		{
			calwRequestedValue = 850;
		}

		else if( vexRT[Btn6D] == 1)      // Setting Btn7D to Intake Goal
		{
			calwRequestedValue = 1290;
		}
		else if( vexRT[Btn8D] == 1)      // Setting Btn7U to Extend Goal
		{
			calwRequestedValue = 655;
		}


		  	//----------------------Lift------------------------//
		if( vexRT[Btn5U] == 1)      // Setting Btn7U to Extend Goal
		{
			setLiftPower(-127);
			liftStillSpeed = -15;
		}

		else if( vexRT[Btn5D] == 1)      // Setting Btn7D to Intake Goal
		{
			setLiftPower(127);
			liftStillSpeed = 10;
		}
		else
		{
			if(SensorValue[liftPot] > 2470)
			{
				setLiftPower(15);      // Else, stop mobile motors
			}
			else
			{
				setLiftPower(liftStillSpeed);      // Else, stop mobile motors
			}
		}
  }
}
