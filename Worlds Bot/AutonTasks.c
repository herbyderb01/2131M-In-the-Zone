#include "BackOver Functions 2017-18.c"
#include "Turn PID.c"
//#region Variables
//-------------Variables--------------//
int liftstillspeed;      //define the liftstillspeed
int FourBarstillspeed;      //define the FourBarstillspeed
int mobilestillspeed;    //define the mobilegoalstillspeed
int skillsVar;           //skills toggle variable
int usertoggle;          //usertoggle variable
int initalize=0;         //initializing the toggle variable

//Variables for turn and drive
int drivepower = 127;
int NineP = 900;
int FullP = 1800;

// PID Mobile Variables
int mobileIn = 2600;
int mobileMid = 1920;
int mobileSMid = 1438;
int mobileLow = 700;
int mobileOut = 460;

// PID Lift variables
int BottomLift = 1350;
int TopLift = 2900;
int ParallelLift = 1850;
int SkillsLift = 1600;

// Auto Stack variables
int SonarsThreshold = 500;

float wheelDiameter = 6.5;
float cumBias;
float debug;

int InchesToCounts(float value) //converts drive encoder counts into inches
{
  return (value * 360)/(PI * wheelDiameter);
}
//#endregion
//#region Autonomous Drive Voids
//--------------------Autonomous Voids-----------------------//
void AutoStrait(int distance, int power)
 // Creating a function to make sure the robot drives forward
{
	int direction = sgn(distance);
	distance = abs(distance);

 // telling it to do this while you are driving to the disired distance
	while(abs(SensorValue[rightEncoder]) < distance)
	{
		 // Checking if the right drive is faster than the left drive
		if (abs(SensorValue[rightEncoder]) > abs(SensorValue[leftEncoder]))
		{
			setDrivePowerAton(direction * (power + 4), direction * (power - 10));
		}
		// Checking if the left drive is faster than the right drive
		else if (abs(SensorValue[leftEncoder]) > abs(SensorValue[rightEncoder]))
		{
			setDrivePowerAton(direction * (power - 2), direction * power);
		}
		else //if the values are the same, keeps motor powers equall
		{
			setDrivePowerAton(direction * power, direction * power);
		}
	}
		motor[LDrive] = 0; // stops motors when finished with function
		motor[RDrive] = 0;
}

void Atondrive(float inches, int power)
{ //Aton function to move forward by its self
	int ticks = InchesToCounts(inches);
	  //Clear Encoders
  SensorValue[rightEncoder] = 0;
  SensorValue[leftEncoder] = 0;
		///forward
	/*AutoStrait(ticks*0.6, power);
	AutoStrait(ticks*0.8, power/2);*/
	AutoStrait(ticks, power/*/3*/);
//sudden stop to correct overshooting the value
	motor[LDrive] = -15 * sgn(ticks);
  motor[RDrive] = -15 * sgn(ticks);
	wait1Msec(100);
}
//#endregion
//#region User Control Tasks
task drive() //Redirecting Drive into a task
{
	while(true)
	{
	setDrivePower(vexRT[Ch3],vexRT[Ch2]);
  motor[MobileR] = vexRT[Ch2];
	motor[MobileL] = vexRT[Ch3];
}
  /*while (true)
  {
  	if (abs(vexRT[Ch3]) + abs(vexRT[Ch2])>10)
  	{
  		setDrivePower(vexRT[Ch3],vexRT[Ch2]);
  	}
    else
		{
			setDrivePower(vexRT[Ch3Xmtr2],vexRT[Ch2Xmtr2]);
		}
		wait1Msec(25); //dont hog cpu
  }*/
}
void ClearAllSensors()
{
SensorValue[rightEncoder] = 0;  ///
SensorValue[leftEncoder] = 0;   ///  Making sure to clear all values
SensorValue[Gyro] = 0;					///
}
task IntakeCone()
{
	setIntakePower (127);
	wait1Msec (25);
	setIntakePower (20);
}

task OutakeCone()
{
setIntakePower (-127);
wait1Msec (1000);
setIntakePower (20);
}

task OutakePreload()
{
	liftRRequestedValue = SkillsLift - 500;
	wait1Msec(100);
	setIntakePower (-127);
	wait1Msec(300);
	setIntakePower (20);
	liftRRequestedValue=SkillsLift;
}


task drivelock()
{
  ClearAllSensors();
while(true)
{
setDrivePower(SensorValue[leftEncoder]*-1.25, SensorValue[rightEncoder]*-1.25);
}
}

//#endregion
//#region Auto Stack Voids and Tasks
task AutoStackUpSimple()									// Simple Auto stack cone up
{
	liftRRequestedValue = ParallelLift;

	setFourBarPower(-127);
	wait1Msec(500);
	setFourBarPower(-10);

	liftRRequestedValue = SkillsLift - 400;

	setIntakePower(127);
	wait1Msec(600);
	setIntakePower(20);
	wait1Msec(100);

	liftRRequestedValue = ParallelLift;

	setFourBarPower(127);
	wait1Msec(750);
	setFourBarPower(20);

	liftRRequestedValue = SkillsLift - 500;
	wait1Msec(400);
	setIntakePower(-127);
	wait1Msec(200);
	liftRRequestedValue = SkillsLift;
	wait1Msec(300);
	setIntakePower(10);
}

void StackAtonOne()									// Simple Auto stack cone up aton
{
  //liftRequest(ParallelLift,true);
	setFourBarPower(-127);
	wait1Msec(400);
	setFourBarPower(-10);

  liftRequest(1450,false);

	setIntakePower(127);
	wait1Msec(350);
	setIntakePower(20);
	wait1Msec(100);

  liftRequest(ParallelLift-50,false);
  wait1Msec(300);
	setFourBarPower(127);
	wait1Msec(500);
	setFourBarPower(20);

  liftRequest(SkillsLift-500,false);
	wait1Msec(300);
	setIntakePower(-127);
	wait1Msec(100);
  liftRequest(SkillsLift,false);
	wait1Msec(300);
	setIntakePower(10);
}

task StackAton()									// Simple Auto stack cone up aton
{
  //liftRequest(ParallelLift,true);
	setFourBarPower(-127);
	wait1Msec(400);
	setFourBarPower(-10);

  liftRequest(1450,false);

	setIntakePower(127);
	wait1Msec(900);
	setIntakePower(20);
	wait1Msec(100);

  liftRequest(ParallelLift-50,false);
  wait1Msec(300);
	setFourBarPower(127);
	wait1Msec(1000);
	setFourBarPower(20);

  liftRequest(SkillsLift-500,false);
	wait1Msec(300);
	setIntakePower(-127);
	wait1Msec(100);
  liftRequest(SkillsLift,false);
	wait1Msec(300);
	setIntakePower(10);
}
//#endregion
//#region Sonar Auto Stacking
/*task SonarAutoStack()
{
stopTask(liftRController);
int test = 0;
set roller power to intake

for half a seconed lower lift with power to grab cone

set roller still speed

set lift power to start comming up

	while(test < 6)
	{
    if(SensorValue[Sonar] < SonarsThreshold && SensorValue[Sonar] != -1)
    {
        test = 0;
    }
    if (SensorValue[Sonar] > SonarsThreshold)
    {

        test += 1;
    }
	}
set a lift still speed

bring four bar up

bring lift down
while(test < 6)
{
  if(SensorValue[Sonar] < SonarsThreshold && SensorValue[Sonar] != -1)
  {
      test += 1;
  }
  if (SensorValue[Sonar] > SonarsThreshold)
  {

      test = 0;
  }
}
get rid of the cone with lift comming up

four bar out

starTask(liftRController);

set pid to the grab height
}*/
//#endregion
//<editor-fold Autonomous Programs
//--------------------Autonomous Programs----------------------------//
//#region Score 5's
void RightFive()
{
  liftRequest(SkillsLift+100,false);
  goalRequest(mobileIn,true);
  setFourBarPower(20);
  setIntakePower(15);

  goalRequest(mobileOut,true);
  Atondrive(46, drivepower);
  goalRequest(mobileIn,true);
  liftRequest(BottomLift,false);
  wait1Msec(300);
  setIntakePower(-127);
  Atondrive(10.5, drivepower);
  setIntakePower(0);
  startTask(StackAton);
  wait1Msec(1000);
  Atondrive(-44, drivepower);
  TurnPID(-1350, true);
  goalRequest(mobileOut,true);
  Atondrive(-75, drivepower);
  goalRequest(mobileIn,true);
  TurnPID(-900, true);
  goalRequest(mobileOut,true);
  Atondrive(25, drivepower);
}

void LeftFive()
{
  liftRequest(SkillsLift+100,false);
  goalRequest(mobileIn,true);
  setFourBarPower(20);
  setIntakePower(15);

  goalRequest(mobileOut,true);
  Atondrive(46, drivepower);
  goalRequest(mobileIn,true);
  liftRequest(BottomLift,false);
  wait1Msec(300);
  setIntakePower(-127);
  Atondrive(8, drivepower); //20 points are good, and I started the 5 points but I couldn't get it to pick up the 2nd and 3rd cones. Otherwise it should be good. I haven't updated the right 5 point though
  setIntakePower(0);
  startTask(StackAton);
  wait1Msec(1000);
  liftRequest(BottomLift,false);
  wait1Msec(300);
  setIntakePower(-127);
  Atondrive(9, drivepower);
  setIntakePower(0);
  startTask(StackAton);
  wait1Msec(1000);
  Atondrive(-50, drivepower);
  TurnPID(1350, true);
  goalRequest(mobileOut,true);
  Atondrive(-60, drivepower);
  goalRequest(mobileIn,true);
  TurnPID(900, true);
  goalRequest(mobileOut,true);
  Atondrive(25, drivepower);
}
//#endregion
//#region Score 10's
void RightTen()
{
  liftRequest(SkillsLift+100,false);
  goalRequest(mobileIn,true);
  setFourBarPower(20);
  setIntakePower(15);

  goalRequest(mobileOut,true);
  Atondrive(46, drivepower);
  goalRequest(mobileIn,true);
  liftRequest(BottomLift,false);
  wait1Msec(300);
  Atondrive(-44, drivepower);
  setIntakePower(-127);
  TurnPID(-NineP/2, true);
  liftRequest(SkillsLift,false);
  setIntakePower(0);
  Atondrive(-13.5, drivepower);
  TurnPID(-NineP-50, true);
  Atondrive(5, drivepower);
  goalRequest(mobileOut,true);

  Atondrive(-5, drivepower);
  goalRequest(mobileLow,true);
  Atondrive(-10, drivepower);
  goalRequest(mobileIn,false);
  TurnPID(-NineP/2, true);
  Atondrive(-10, drivepower);
  TurnPID(NineP/2, true);
  Atondrive(-50, drivepower);
  goalRequest(mobileOut,true);
  setDrivePower(-10,-127);
  wait1Msec(2000);
  setDrivePower(0,0);
  Atondrive(20, drivepower);
}

void RightTenCones()
{
  liftRequest(SkillsLift+100,false);
  goalRequest(mobileIn,true);
  setFourBarPower(20);
  setIntakePower(15);

  goalRequest(mobileOut,true);
  Atondrive(46, drivepower);
  goalRequest(mobileIn,true);
  liftRequest(BottomLift,false);
  wait1Msec(300);
  setIntakePower(-127);

  Atondrive(8.5, drivepower);
  setFourBarPower(-20);
  setIntakePower(0);
  StackAtonOne();
  Atondrive(6, drivepower);
  startTask(StackAton);
  wait1Msec(800);

  Atondrive(-50, drivepower);
  TurnPID(-NineP/2, true);
  Atondrive(-15, drivepower);
  TurnPID(-NineP-50, true);
  Atondrive(8, drivepower);
  goalRequest(mobileOut,true);

  Atondrive(-5, drivepower);
  goalRequest(mobileLow,true);
  Atondrive(-10, drivepower);
}

void LeftTen()
{
  liftRequest(SkillsLift+100,false);
  goalRequest(mobileIn,true);
  setFourBarPower(20);
  setIntakePower(15);

  goalRequest(mobileOut,true);
  Atondrive(46, drivepower);
  goalRequest(mobileIn,true);
  liftRequest(BottomLift,false);
  wait1Msec(300);

  Atondrive(-43, drivepower);
  setIntakePower(-127);
  TurnPID(NineP/2, true);
  liftRequest(SkillsLift,false);
  setIntakePower(0);
  Atondrive(-13.5, drivepower);
  TurnPID(NineP-50, true);
  Atondrive(5, drivepower);
  goalRequest(mobileOut,true);

  Atondrive(-5, drivepower);
  goalRequest(mobileLow,true);
  Atondrive(-10, drivepower);
  goalRequest(mobileIn,false);
  TurnPID(NineP/2, true);
  Atondrive(-10, drivepower);
  TurnPID(-NineP/2, true);
  Atondrive(-50, drivepower);
  goalRequest(mobileOut,true);
  setDrivePower(-10,-127);
  wait1Msec(2000);
  setDrivePower(0,0);
  Atondrive(20, drivepower);
}

void LeftTenCones()
{
  liftRequest(SkillsLift+100,false);
  goalRequest(mobileIn,true);
  setFourBarPower(20);
  setIntakePower(15);

  goalRequest(mobileOut,true);
  Atondrive(46, drivepower);
  goalRequest(mobileIn,true);
  liftRequest(BottomLift,false);
  wait1Msec(300);
  setIntakePower(-127);

  Atondrive(8.5, drivepower);
  setFourBarPower(-20);
  setIntakePower(0);
  StackAtonOne();
  Atondrive(6, drivepower);
  startTask(StackAton);
  wait1Msec(800);

  Atondrive(-50, drivepower);
  TurnPID(NineP/2, true);
  Atondrive(-15, drivepower);
  TurnPID(NineP-50, true);
  Atondrive(8, drivepower);
  goalRequest(mobileOut,true);

  Atondrive(-5, drivepower);
  goalRequest(mobileLow,true);
  Atondrive(-10, drivepower);
}
//#endregion
//#region Score 20's
void RightTwenty()
{
  liftRequest(SkillsLift+100,false);
  goalRequest(mobileIn,true);
  setFourBarPower(20);
  setIntakePower(15);

  goalRequest(mobileOut,true);
  Atondrive(46, drivepower);
  goalRequest(mobileIn,true);
  liftRequest(BottomLift,false);
  wait1Msec(300);
  setIntakePower(-127);
  Atondrive(10.5, drivepower);
  setIntakePower(0);
  startTask(StackAton);
  wait1Msec(1000);

  Atondrive(-45, drivepower);
  TurnPID(-NineP/2, true);
  Atondrive(-26, drivepower);
  TurnPID(-NineP, true);
  Atondrive(21, drivepower);
  goalRequest(mobileOut,true);
  Atondrive(-6, drivepower);
  goalRequest(mobileMid, true);
  Atondrive(-12, drivepower);

}

void LeftTwenty()
{
  liftRequest(SkillsLift+100,false);
  goalRequest(mobileIn,true);
  setFourBarPower(20);
  setIntakePower(15);

  goalRequest(mobileOut,true);
  Atondrive(46, drivepower);
  goalRequest(mobileIn,true);
  liftRequest(BottomLift,false);
  wait1Msec(300);
  setIntakePower(-127);
  Atondrive(10.5, drivepower);
  setIntakePower(0);
  startTask(StackAton);
  wait1Msec(1000);

  Atondrive(-44, drivepower);
  TurnPID(NineP/2, true);
  Atondrive(-26, drivepower);
  TurnPID(NineP, true);
  Atondrive(21, drivepower);
  goalRequest(mobileOut,true);
  Atondrive(-6, drivepower);
  goalRequest(mobileMid, true);
  Atondrive(-12, drivepower);

}
//#endregion
//#region Score Special's
void SkillsOne ()
{
	//------------------------------------------------------------//
			setIntakePower(15);                   //
			liftRRequestedValue = SkillsLift;
			wait1Msec(550);
			mobileRRequestedValue = mobileOut;
      wait1Msec(300);
			setFourBarPower(20);

			Atondrive(610, 127);

			mobileRRequestedValue = mobileIn;
			wait1Msec(200);

			Atondrive(-550, 127);
			wait1Msec(300);
			setIntakePower(-127);                   //

			TurnPID(-NineP/2, true);
			setIntakePower(0);                   //

			Atondrive(-300, 127);

			TurnPID(-NineP-30, true);

			Atondrive(250, 127);

			setDrivePower(40,40);

			mobileRRequestedValue = mobileOut;
			//WaitieThing();

      Atondrive(-75, drivepower);

			mobileRRequestedValue = mobileIn;
			//------------------------------------------- Place 2nd
			Atondrive(-300, drivepower);

			TurnPID(-NineP, true);

			Atondrive(145, drivepower);

			mobileRRequestedValue = mobileOut;

			TurnPID(-NineP, true);
      stopTask(TPIDDriveController);
      wait1Msec(450);

			Atondrive(320, drivepower);

			mobileRRequestedValue = mobileIn;
			wait1Msec(400);
			Atondrive(-260, drivepower);

			TurnPID(-FullP+5, true);

			Atondrive(115, 127);

			//setDrivePower(40,40);

			mobileRRequestedValue = mobileOut;
			//WaitieThing();
			//------------------------------------------- Place 3rd
			Atondrive(-530, drivepower);

			mobileRRequestedValue = mobileMid;

			TurnPID(NineP-5, true);

			mobileRRequestedValue = mobileOut;
			//WaitieThing();

			Atondrive(390, drivepower);

			mobileRRequestedValue = mobileIn;
			wait1Msec(500);

			TurnPID(-NineP-10, true);

			Atondrive(590, drivepower);
			//setDrivePower(40,40);

			mobileRRequestedValue = mobileOut;
			//WaitieThing();
			Atondrive(-100, drivepower);
			mobileRRequestedValue = mobileMid-100;
			//setDrivePower(40,40);
			wait1Msec(300);

			//Atondrive(-170, drivepower);

			//------------------------------------------- Place 4rd
			TurnPID(FullP+35, true);

			mobileRRequestedValue = mobileOut;

			//////////////
			//setDrivePower(-80,-80);
			//wait1Msec(2000);
			//////////////

			Atondrive(760, drivepower);

			mobileRRequestedValue = mobileMid;

			Atondrive(675, drivepower);

			mobileRRequestedValue = mobileOut;
			setDrivePower(20,20);
			//WaitieThing();
			//------------------------------------------- Place 5th
			Atondrive(-545, drivepower);

			mobileRRequestedValue = mobileMid;

			TurnPID(NineP-10, true);

			mobileRRequestedValue = mobileOut;
			//WaitieThing();

			Atondrive(460, drivepower);

			mobileRRequestedValue = mobileIn;
			wait1Msec(500);

			TurnPID(-NineP-42, true);

			Atondrive(565, drivepower);
			//setDrivePower(20,20);

			mobileRRequestedValue = mobileOut;
			//WaitieThing();
			Atondrive(-120, drivepower);
			//------------------------------------------- Place 6th
			TurnPID(1320 , true);

			Atondrive(620, 127);

			mobileRRequestedValue = mobileIn;
			wait1Msec(200);

			Atondrive(-585, 127);

			TurnPID(-NineP/2, true);
			setIntakePower(0);                   //

			Atondrive(-250, 127);

			TurnPID(-NineP-30, true);

			Atondrive(285, 127);

			setDrivePower(40,40);

			mobileRRequestedValue = mobileOut;
			//WaitieThing();

			Atondrive(-10, 127);

			mobileRRequestedValue = mobileIn;

			Atondrive(-230, drivepower);
			//------------------------------------------- Place 7th
			mobileRRequestedValue = mobileOut;
			TurnPID(-1220, true);

			Atondrive(857, drivepower);

			mobileRRequestedValue = mobileIn;
			wait1Msec(600);

			Atondrive(-730, drivepower);

			TurnPID(FullP-200, true);

			//Atondrive(-210, drivepower);

			//TurnPID(-NineP-10, true);

			setDrivePower(60,60);

			mobileRRequestedValue = mobileOut;
			//WaitieThing();

			Atondrive(-200, drivepower);

}

void SkillsTwo ()
{
  liftRequest(SkillsLift+100,false);
  goalRequest(mobileIn,true);
  setFourBarPower(20);

  Atondrive(36, drivepower);
  //startTask(TPIDDriveController);

  /*TurnPID(NineP,true);
  wait1Msec(1000);
  TurnPID(NineP,true);
  wait1Msec(1000);
  TurnPID(NineP,true);
  wait1Msec(1000);
  TurnPID(NineP,true);*/

}
//#endregion
//#region Other Programs
void Defensive ()
{
  liftRequest(2000,false);
  goalRequest(mobileOut,true);
  Atondrive(12, 127);
  goalRequest(mobileIn,true);
  //Atondrive(-12, 127);
}

void DoNothing ()
{
  liftRequest(2000,false);

  TurnPID(NineP, true);
  TurnPID(NineP, true);
  TurnPID(NineP, true);
  TurnPID(NineP, true);

}

void DefensiveTwo ()
{
}

void DoNothingTwo ()
{
}

void SpecialAton()
{
}
//#endregion
//</editor-fold>
