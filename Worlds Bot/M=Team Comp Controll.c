#pragma config(Sensor, in1,    mobileP,        sensorPotentiometer)
#pragma config(Sensor, in2,    liftP,          sensorPotentiometer)
#pragma config(Sensor, in3,    selectP,        sensorPotentiometer)
#pragma config(Sensor, in4,    Gyro,           sensorGyro)
#pragma config(Sensor, in5,    selecttwoP,     sensorPotentiometer)
#pragma config(Sensor, dgtl1,  rightEncoder,   sensorQuadEncoder)
#pragma config(Sensor, dgtl3,  leftEncoder,    sensorQuadEncoder)
#pragma config(Sensor, dgtl5,  Sonar,          sensorSONAR_raw)
#pragma config(Motor,  port1,           MobileR,       tmotorVex393_HBridge, openLoop, reversed)
#pragma config(Motor,  port2,           FourBar,       tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port3,           INtake,        tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port4,           UliftL,        tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port5,           UliftR,        tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port6,           DliftL,        tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port7,           DliftR,        tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port8,           RDrive,        tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port9,           LDrive,        tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port10,          MobileL,       tmotorVex393_HBridge, openLoop)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

// This code is for the VEX cortex platform
#pragma platform(VEX2)
// Select Download method as "competition"
#pragma competitionControl(Competition)
//Main competition .background code...do not modify!
#include "Vex_Competition_Includes.c"
//include both Void programs, and PID
#include "BackOver Functions 2017-18.c"
#include "AutonTasks.c"
#include "Turn PID.c"
/*---------------------------------------------------------------------------*/
/*                          Pre-Autonomous Functions                         */
/*                                                                           */
/*---------------------------------------------------------------------------*/
void pre_auton()
{
	SensorValue[rightEncoder] = 0;  ///
  SensorValue[leftEncoder] = 0;   ///  Making sure to clear all values
	SensorValue[Gyro] = 0;					///
	/*SensorType[Gyro] = sensorNone;
	wait1Msec(1000);										//
	SensorType[Gyro] = sensorGyro;      // To correct Gyro Drift
	wait1Msec(1000);										//
  bStopTasksBetweenModes = true;  		//

SensorType[Gyro] = sensorNone;

	for(int i = 0; i<2000; i++)
	{
		cumBias += (float)(SensorValue[Gyro]);

		wait1Msec(1);
	}

	debug = cumBias / 2000;
*/
}
/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              Autonomous Task                              */
/*                                                                           */
/*---------------------------------------------------------------------------*/
task autonomous()
{
	startTask(killmeplz);
	SensorBias[Gyro] = 1862;
	wait1Msec(250);
	SensorScale[Gyro] = 134;
	wait1Msec(250);

	startTask(liftRController);    //Start Lift PID
	startTask(mobileRController);  //Start Mobile PID
  mobileRRequestedValue = mobileIn;
  liftRequest(SkillsLift+100,false);


	 //=========== Score 5's ==========//
	if (SensorValue[selecttwoP] > 300 && SensorValue[selecttwoP] < 1795)
	{
			if (SensorValue[selectP] < 15)
			{
				LeftFive();
			}
			if (SensorValue[selectP] > 420 && SensorValue[selectP] < 1053)
			{
			}
			if (SensorValue[selectP] > 1053 && SensorValue[selectP] < 1768)
			{
			}
			if (SensorValue[selectP] > 1768 && SensorValue[selectP] < 2735)
			{
			}
			if (SensorValue[selectP] > 2735 && SensorValue[selectP] < 3642)
			{
			}
			if (SensorValue[selectP] > 4000)
			{
				RightFive();
			}

	}

	 //=========== Score 10's ==========//
	if (SensorValue[selecttwoP] > 1795 && SensorValue[selecttwoP] < 3530)
	{
			if (SensorValue[selectP] < 15)
			{
				LeftTen();
			}
			if (SensorValue[selectP] > 420 && SensorValue[selectP] < 1053)
			{
				LeftTenConesOne();
			}
			if (SensorValue[selectP] > 1053 && SensorValue[selectP] < 1768)
			{
				LeftTenConesTwo();
			}
			if (SensorValue[selectP] > 1768 && SensorValue[selectP] < 2735)
			{
				RightTenConesTwo();
			}
			if (SensorValue[selectP] > 2735 && SensorValue[selectP] < 3642)
			{
				RightTenConesOne();
			}
			if (SensorValue[selectP] > 4000)
			{
				RightTen();
			}

	}

	 //=========== Score 20's ==========//
	if (SensorValue[selecttwoP] > 3530)
	{
			if (SensorValue[selectP] < 15)
			{
				LeftTwenty();
			}
			if (SensorValue[selectP] > 420 && SensorValue[selectP] < 1053)
			{
			}
			if (SensorValue[selectP] > 1053 && SensorValue[selectP] < 1768)
			{
			}
			if (SensorValue[selectP] > 1768 && SensorValue[selectP] < 2735)
			{
			}
			if (SensorValue[selectP] > 2735 && SensorValue[selectP] < 3642)
			{
			}
			if (SensorValue[selectP] > 4000)
			{
				RightTwenty();
			}

	}

	 //=========== Score Special's ==========//
	if (SensorValue[selecttwoP] < 300)
	{
			if (SensorValue[selectP] < 15)
			{
				SkillsOne();
			}
			if (SensorValue[selectP] > 420 && SensorValue[selectP] < 1053)
			{
				StationaryLeft();
			}
			if (SensorValue[selectP] > 1053 && SensorValue[selectP] < 1768)
			{

			}
			if (SensorValue[selectP] > 1768 && SensorValue[selectP] < 2735)
			{
				TestingAton();
			}
			if (SensorValue[selectP] > 2735 && SensorValue[selectP] < 3642)
			{
				StationaryRight();
			}
			if (SensorValue[selectP] > 4000)
			{
				Defensive();
			}
	}
}
/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              User Control Task                            */
/*                                                                           */
/*---------------------------------------------------------------------------*/
task usercontrol()
{
startTask(drive);
setFourBarPower(20);

	while (3.1415926535897932384626433832795028841971==3.1415926535897932384626433832795028841971)
  //starting while loop to always run during userconroll
	{

		if (vexRT[Btn7L]==0)																	//
		{																											//
			usertoggle=1;																				//
		}																											//
		if (vexRT[Btn7L]==1 && skillsVar==1 && usertoggle==1) //
		{																											//  USER CONTROL TOGGLE
			skillsVar=0;																				//		- To switch between
			usertoggle=0;																				//			our two different
		}																											//			modes
		if (vexRT[Btn7L]==1 && skillsVar==0 && usertoggle==1)	//
		{																											//
			skillsVar=1;																				//
			usertoggle=0;																				//
		}																											//

	//=========================Normal Match Control===========================//
	if (skillsVar == 0)
	{
    if (initalize==0)																			// To Initalize Normal
    {																											// match Code
      stopTask(liftRController);
      setFourBarPower(20);
    }
    initalize=1;

		  if (vexRT[Btn8L]==1)
		  {
		  	startTask(drivelock);
		  }

		  if (vexRT[Btn8U]==1)
		  {
		  	stopTask(drivelock);
		  }
		//----------------------Moblie Goal------------------------//

		if( vexRT[Btn7U] == 1)      // Setting Btn7U to Extend Goal
		{
				setMobilePower(127);
		}
		else if( vexRT[Btn7D] == 1)      // Setting Btn7D to Intake Goal
		{
				setMobilePower(-127);
		}
		else if( vexRT[Btn7R] == 1)      // Setting Btn7R to brake
		{
				setMobilePower(-10);
		}
		else
		{
			if (abs(vexRT[Ch3]) + abs(vexRT[Ch2])>10)
	  	{
				motor[MobileR] = (vexRT[Ch2])*1.2;
				motor[MobileL] = (vexRT[Ch3])*1.2;
			}
		  else
			{
				motor[MobileR] = (vexRT[Ch2Xmtr2])*1.2;
				motor[MobileL] = (vexRT[Ch3Xmtr2])*1.2;
			}
		}


	//----------------------Lift Controll------------------------//

		if( vexRT[Btn5D] == 1)      // Setting Btn5D to lift Down
		{
			setLiftPower(-127);
			liftstillspeed=-15;
		}

		else if( vexRT[Btn5U] == 1)      // Setting Btn5U to lift Up
		{
			setLiftPower(127);
			liftstillspeed=15;
		}

		/*else if( vexRT[Btn5DXmtr2] == 1)      // Setting Btn5D on Secondary to lift Down
		{
			setLiftPower(-127);
			liftstillspeed=-15;
		}

		else if( vexRT[Btn5UXmtr2] == 1)      // Setting Btn5U on Secondary to lift Up
		{
			setLiftPower(127);
			liftstillspeed=15;
		}*/

		else
		{
			setLiftPower(liftstillspeed);	// Setting the Still Speed when no commands
		}

	//----------------------Intake Control------------------------//

		if( vexRT[Btn6U] == 1)      // Setting Btn 6U to Intake Cone
		{
			startTask(IntakeCone);
		}

		else if( vexRT[Btn6D] == 1)      // Setting Btn6D to Outtake Cone
		{
			startTask(OutakeCone);
		}
		/*else if( vexRT[Btn8LXmtr2] == 1)      // Setting Btn 6U to Intake Cone
		{
			startTask(IntakeCone);
		}
		else if( vexRT[Btn8DXmtr2] == 1)      // Setting Btn6D to Outtake Cone
		{
			startTask(OutakeCone);
		}*/

		//----------------------Four Bar Control ------------------------//

		if( vexRT[Btn8D] == 1)      // Setting Btn8D to Extend Four Bar
		{
			setFourBarPower(127);
			FourBarstillspeed=20;
		}

		else if( vexRT[Btn8R] == 1)      // Setting Btn8R to bring in Four Bar
		{
			setFourBarPower(-127);
			FourBarstillspeed=-20;
		}
		/*else if( vexRT[Btn6DXmtr2] == 1) // Setting Btn8D on 2nd to Extend Four Bar
		{
			setFourBarPower(127);
			FourBarstillspeed=20;
		}

		else if( vexRT[Btn6UXmtr2] == 1)// Setting Btn8D on 2nd to bring in Four Bar
		{
			setFourBarPower(-127);
			FourBarstillspeed=-20;
		}*/
		else
		{
			setFourBarPower(FourBarstillspeed);// Setting the Still Speed when no commands
		}
	}
//-=-=-=-==-=-=-=--=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=//
//===========================================================================//

  if (skillsVar == 1)
  //--------------------------Specialties-Contol----------------------------//
  {
    if (initalize==1)															//
    {																							//
      startTask(liftRController);									//   SPECIALTIES CONTOLL
      liftRRequestedValue=SkillsLift;							//		TOGGLE
     	setFourBarPower(127);												//
			wait1Msec(200);															//
			setFourBarPower(15);												//
    }
    initalize=0;																	// initalize for toggle
    //---------------------PreLoad Task-----------------------------//
    if (vexRT[Btn5U] == 1)
    {
    	startTask(OutakePreload);
    }
    //--------------------Simple Auto Stack-------------------------//
    if (vexRT[Btn5D] == 1)
    {
    	startTask(StackAtonOneTask);
    }

		//----------------------Moblie Goal Lift------------------------//
		if( vexRT[Btn6U] == 1)      // Setting Btn6U to Extend Goal
		{
			setMobilePower(127);
		}

		else if( vexRT[Btn6D] == 1)      // Setting Btn6D to Intake Goal
		{
			setMobilePower(-127);
		}
		else if( vexRT[Btn6UXmtr2] == 1)      // Setting Btn6U to Extend Goal
		{
			setMobilePower(127);
		}

		else if( vexRT[Btn6DXmtr2] == 1)      // Setting Btn6D to Intake Goal
		{
			setMobilePower(-127);
		}
		else
		{
			if (abs(vexRT[Ch3]) + abs(vexRT[Ch2])>10)
	  	{
				motor[MobileR] = vexRT[Ch2]*1.2;
				motor[MobileL] = vexRT[Ch3]*1.2;
			}
		  else
			{
				motor[MobileR] = vexRT[Ch2Xmtr2]*1.2;
				motor[MobileL] = vexRT[Ch3Xmtr2]*1.2;
			}
		}
  }
 }
}
