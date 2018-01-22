#pragma config(Sensor, in1,    liftP,          sensorPotentiometer)
#pragma config(Sensor, in2,    chainP,         sensorPotentiometer)
#pragma config(Sensor, in3,    selectP,        sensorPotentiometer)
#pragma config(Sensor, in4,    Gyro,           sensorGyro)
#pragma config(Sensor, in5,    mobileP,        sensorPotentiometer)
#pragma config(Sensor, in6,    selecttwoP,     sensorPotentiometer)
#pragma config(Sensor, dgtl1,  rightEncoder,   sensorQuadEncoder)
#pragma config(Sensor, dgtl3,  leftEncoder,    sensorQuadEncoder)
#pragma config(Motor,  port1,           DriveR,        tmotorVex393_HBridge, openLoop)
#pragma config(Motor,  port2,           chain,         tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port3,           INtake,        tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port4,           liftL,         tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port5,           liftR,         tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port6,           MobileR,       tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port7,           MobileL,       tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port8,           RDrive,        tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port9,           LDrive,        tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port10,          DriveL,        tmotorVex393_HBridge, openLoop, reversed)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//
// This code is for the VEX cortex platform
#pragma platform(VEX2)
// Select Download method as "competition"
#pragma competitionControl(Competition)
//Main competition background code...do not modify!
#include "Vex_Competition_Includes.c"
//include both Void programs, and PID
#include "BackOver Functions 2017-18.c"
#include "AutonTasks.c"
#include "Drive PID.c"

int liftstillspeed;      //define the liftstillspeed
int chainstillspeed;      //define the chainstillspeed
int mobilestillspeed;    //define the mobilegoalstillspeed
int skillsVar;           //skills toggle variable
int usertoggle;          //usertoggle variable
int initalize=0;         //initializeing the toggle variable
/*---------------------------------------------------------------------------*/
/*                          Pre-Autonomous Functions                         */
/*                                                                           */
/*---------------------------------------------------------------------------*/
void pre_auton()
{
	SensorValue[rightEncoder] = 0;  ///
  SensorValue[leftEncoder] = 0;   ///  Making sure to clear all values
  bStopTasksBetweenModes = true;  ///
}
/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              Autonomous Task                              */
/*                                                                           */
/*---------------------------------------------------------------------------*/
task autonomous()
{
	//startTask(chainRController);
	startTask(liftRController);
	startTask(mobileRController);  //Start Mobile PID
	liftRSensorCurrentValue = SensorValue[ liftP ];
	//chainRRequestedValue = StraitUpChain;
	/*
	SensorType[Gyro] = sensorNone;
	wait1Msec(500);
	SensorType[Gyro] = sensorGyro;
	SensorScale[Gyro] = 125;
	SensorFullCount[Gyro] = 3600;
	wait1Msec(2000);
*/
	if (SensorValue[selecttwoP] < 2045) //=========== Score 10's ==========//
	{
			if (SensorValue[selectP] == 0) // Defensive - 1
			{
				Defensive();
			}
			if (SensorValue[selectP] > 1 && SensorValue[selectP] < 575) // Right Blue - 2
			{
				RightBlue();
			}
			if (SensorValue[selectP] > 575 && SensorValue[selectP] < 1185) //Left Blue - 3
			{
				LeftBlue();
			}
			if (SensorValue[selectP] > 1185 && SensorValue[selectP] < 1780)//Skils 1 - 4
			{
				SkillsOne();
			}
			if (SensorValue[selectP] > 1780 && SensorValue[selectP] < 2410)//Skills 2 - 5
			{
				SkillsTwo();
			}
			if (SensorValue[selectP] > 2410 && SensorValue[selectP] < 3110)//Left Red - 6
			{
				LeftRed();
			}
			if (SensorValue[selectP] > 3110 && SensorValue[selectP] < 4094)//Right Red - 7
			{
				RightRed();
			}
			if (SensorValue[selectP] == 4095)//Do Nothing - 8
			{
				DoNothing();
			}

	}
		if (SensorValue[selecttwoP] > 2045) //=========== Score 20's ==========//
	{
			if (SensorValue[selectP] == 0) // Defensive - 1
			{
				DefensiveTwo();
			}
			if (SensorValue[selectP] > 1 && SensorValue[selectP] < 575) // Right Blue - 2
			{
				RightBlueTwo();
			}
			if (SensorValue[selectP] > 575 && SensorValue[selectP] < 1185) //Left Blue - 3
			{
				LeftBlueTwo();
			}
			if (SensorValue[selectP] > 1185 && SensorValue[selectP] < 1780)//Skils 1 - 4
			{
				SkillsOne();
			}
			if (SensorValue[selectP] > 1780 && SensorValue[selectP] < 2410)//Skills 2 - 5
			{
				SkillsTwo();
			}
			if (SensorValue[selectP] > 2410 && SensorValue[selectP] < 3110)//Left Red - 6
			{
				LeftRedTwo();
			}
			if (SensorValue[selectP] > 3110 && SensorValue[selectP] < 4094)//Right Red - 7
			{
				RightRedTwo();
			}
			if (SensorValue[selectP] == 4095)//Do Nothing - 8
			{
				DoNothingTwo();
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

	while (3.1415926535897932384626433832795028841971==3.1415926535897932384626433832795028841971)
  //starting while loop to always run during userconroll
	{
		if (vexRT[Btn7L]==0)
		{
		usertoggle=1;
		}
		if (vexRT[Btn7L]==1 && skillsVar==1 && usertoggle==1)
		{
			skillsVar=0;
			usertoggle=0;
		}
		if (vexRT[Btn7L]==1 && skillsVar==0 && usertoggle==1)
		{
			skillsVar=1;
			usertoggle=0;
		}
	//=========================Normal Match Control===========================//
	if (skillsVar == 0)
	{
    if (initalize==0)
    {
      stopTask(liftRController);
    }
    initalize=1;

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
		else if( vexRT[Btn5DXmtr2] == 1)      // Setting Btn5D to lift Down
		{
			setLiftPower(-127);
			liftstillspeed=-15;
		}

		else if( vexRT[Btn5UXmtr2] == 1)      // Setting Btn5U to lift Up
		{
			setLiftPower(127);
			liftstillspeed=15;
		}
		else
		{
			setLiftPower(liftstillspeed);
		}

	//----------------------Intake Control------------------------//

		if( vexRT[Btn6U] == 1)      // Setting Btn 6U to Intake Cone
		{
			setIntakePower(127);
		}

		else if( vexRT[Btn6D] == 1)      // Setting Btn6D to Outtake Cone
		{
			setIntakePower(-127);
		}
		else if( vexRT[Btn6UXmtr2] == 1)      // Setting Btn 6U to Intake Cone
		{
			setIntakePower(127);
		}

		else if( vexRT[Btn6DXmtr2] == 1)      // Setting Btn6D to Outtake Cone
		{
			setIntakePower(-127);
		}
		else
		{
			setIntakePower(20);   // Else, set a intake still speed to hold cone in
		}

		//----------------------Moblie Goal Lift------------------------//
		if( vexRT[Btn7U] == 1)      // Setting Btn7U to Extend Goal
		{
			setMobilePower(127);
		}

		else if( vexRT[Btn7D] == 1)      // Setting Btn7D to Intake Goal
		{
			setMobilePower(-127);
		}
		else
		{
			setMobilePower(0);      // Else, stop mobile motors
		}

		//----------------------PIV Control ------------------------//
		if( vexRT[Btn8D] == 1)
		{
			setChainPower(127);
			chainstillspeed=20;
		}

		else if( vexRT[Btn8R] == 1)
		{
			setChainPower(-127);
			chainstillspeed=-20;
		}
		else if( vexRT[Btn8DXmtr2] == 1)
		{
			setChainPower(127);
			chainstillspeed=20;
		}

		else if( vexRT[Btn8RXmtr2] == 1)
		{
			setChainPower(-127);
			chainstillspeed=-20;
		}

		else
		{
			setChainPower(chainstillspeed);
		}
	}

//===========================================================================//

  if (skillsVar == 1)
  //--------------------------Specialties-Contol----------------------------//
  {
    if (initalize==1)
    {
      startTask(liftRController);
      liftRRequestedValue=2770;
      //chainRRequestedValue = StraitUpChain;
    }
    initalize=0;

    //---------------------PreLoad Task-----------------------------//
    if (vexRT[Btn7R] == 1)
    {
    	Preload();
    }
			//----------------------Moblie Goal Lift------------------------//
			if( vexRT[Btn6U] == 1)      // Setting Btn7U to Extend Goal
			{
				setMobilePower(127);
				mobilestillspeed=15;
			}

			else if( vexRT[Btn6D] == 1)      // Setting Btn7D to Intake Goal
			{
				setMobilePower(-127);
				mobilestillspeed=-15;
			}
			else
			{
				setMobilePower(mobilestillspeed);      // Else, stop mobile motors
			}

			//----------------------PIV Control with PID------------------------//
			if( vexRT[Btn8D] == 1)      // Setting Btn8D PID, to Strait Up
			{
				//chainRRequestedValue = StraitUpChain;
			}

			else if( vexRT[Btn8R] == 1)      // Setting Btn8R PID, to OutPosition
			{

				//chainRRequestedValue = OutPositionChain;
			}

			else if( vexRT[Btn8L] == 1)  // Setting Btn8L PID, to Stationary Position
			{
				//chainRRequestedValue = StationaryPositionChain;
			}
			else if( vexRT[Btn8U] == 1)      // Setting Btn8U PID, to In Position
			{
				//chainRRequestedValue = InPositionChain;
			}
    }
	}
}
