#include "BackOver Functions 2017-18.c"
#include "Turn PID.c"
//#region Variables
//-------------Variables--------------//
int liftstillspeed;      //define the liftstillspeed

int skillsVar;           //skills toggle variable
int usertoggle;          //usertoggle variable
int initalize=0;         //initializing the toggle variable

//Variables for turn and drive
int drivepower = 127;
int NineP = 900;
int FullP = 1800;

// PID Mobile Variables
int mobileIn = 940;
int mobileMid = 1815;
int mobileSMid = 2500;
int mobileLow = 3000;
int mobileOut = 3300;

// PID Lift variables
int BottomLift = 1350;
int TopLift = 2900;
int ParallelLift = 1850;
int SkillsLift = 1540;

// Auto Stack variables
int SonarsThreshold = 500;

//Fourbar and roller void vars
int Up = 1;
int In = 1;
int Down = 0;
int Out = 0;

//converts and other vars
float wheelDiameter = 4;
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
 // Creating a function to make sure the robot drives forward.
{
	int direction = sgn(distance);
	distance = abs(distance);

 // telling it to do this while you are driving to the disired distance
	while(abs(SensorValue[rightEncoder]) < distance)
	{
		 // Checking if the right drive is faster than the left drive
		if (abs(SensorValue[rightEncoder]) > abs(SensorValue[leftEncoder]))
		{
			setDrivePowerAton(direction * (power + 8), direction * (power - 15));
		}
		// Checking if the left drive is faster than the right drive
		else if (abs(SensorValue[leftEncoder]) > abs(SensorValue[rightEncoder]))
		{
			setDrivePowerAton(direction * (power - 15), direction * power + 4);
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
  stopTask(TPIDDriveController);
	int ticks = InchesToCounts(inches);
	  //Clear Encoders
  SensorValue[rightEncoder] = 0;
  SensorValue[leftEncoder] = 0;
		///forward
	AutoStrait(ticks, power);
//sudden stop to correct overshooting the value
	motor[LDrive] = -15 * sgn(ticks);
  motor[RDrive] = -15 * sgn(ticks);
	wait1Msec(100);
}
//#endregion
//#region User Control Tasks
task drive() //Redirecting Drive into a task
{
  while (true)
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
  }
}

task killmeplz()
{ // tuning task to stop aton at 15 sec
	wait1Msec(15000);
	stopAllTasks();
	allMotorsOff();
}

void ClearAllSensors()
{// void to quickly clear all sensors
SensorValue[rightEncoder] = 0;  ///
SensorValue[leftEncoder] = 0;   ///  Making sure to clear all values
SensorValue[Gyro] = 0;					///
}

task IntakeCone()
{// task for user controll to intake cone
	setIntakePower (127);
	wait1Msec (50);
	setIntakePower (20);
}

task OutakeCone()
{// task for user controll to outake cone
  wait1Msec (50);
  setIntakePower(-127);
  wait1Msec(1000);
  setIntakePower(20);
}

task FourBarIn()
{// task to bring the fourbar in
  setFourBarPower(127);
  wait1Msec(200);
  setFourBarPower(20);
}

task FourBarOut()
{// task to bring the fourbar in
  setFourBarPower(-127);
  wait1Msec(200);
  setFourBarPower(-20);
}

task OutakePreload()
{// task to outake the preload at the begining of skills
	liftRRequestedValue = SkillsLift - 500;
	wait1Msec(100);
	setIntakePower (-127);
	wait1Msec(300);
	setIntakePower (20);
	liftRRequestedValue=SkillsLift;
}

task drivelock()
{// task to keep the drive locked during driver loads
ClearAllSensors();
while(true)
{
setDrivePower(SensorValue[leftEncoder]*-1.25, SensorValue[rightEncoder]*-1.25);
}
}

void QuickPickUP(int power, int delay)
{// quick sequence to pick up a mobile goal during aton
  goalRequest(mobileIn+100, false);
  setDrivePower(power,power);
  wait1Msec(delay);
  setDrivePower(power*0.1,power*0.1);
}

void QuickOffLoad(int power, int delay)
{// quick sequence to offload mobile goal during aton
  goalRequest(mobileOut, false);
  setDrivePower(-power,-power);
  wait1Msec(delay);
  setDrivePower(power*0.1,power*0.1);
}

void ScoreGoal()
{// quick void to score a high stack safely during the match
  startTask(mobileRController);
  setLiftPower(15);
  setFourBarPower(-50);
  goalRequest(mobileOut,true);

  RollerMode(Out,0);
  FourBarPosition(Up,500,127);
  stopTask(mobileRController);
  setIntakePower(20);
}
//#endregion
//#region Auto Stack Voids and Tasks
task StackAtonOneTask()									// Simple Auto stack task cone up aton
{
  liftRequest(SkillsLift,false);
  FourBarPosition(Down,500,127);
  RollerMode(In,0);
  setFourBarPower(-20);
  liftRequest(BottomLift-120,true);
  RollerMode(In,250);
  setIntakePower(100);

  liftRequest(SkillsLift+210,false);
  FourBarPosition(Up,700,127);
  liftRequest((SkillsLift-500)/2,false);
  liftRequest(SkillsLift-500,false);
  setFourBarPower(10);
	wait1Msec(200);
  RollerMode(Out,0);

  wait1Msec(100);
  liftRequest(SkillsLift,false);
}

void StackAtonOne()									// Simple Auto stack void cone up aton
{
  liftRequest(SkillsLift,true);
  FourBarPosition(Down,500,127);
  RollerMode(In,0);
  liftRequest(BottomLift-120,true);
  RollerMode(In,250);
  liftRequest(SkillsLift+100,false);
  // wait1Msec(300);
  FourBarPosition(Up,600,127);

  liftRequest(SkillsLift-500,false);
	wait1Msec(300);
  RollerMode(Out,0);

  wait1Msec(100);
  liftRequest(SkillsLift,false);
  liftRequest(SkillsLift,false);
  FourBarPosition(Down,500,127);
  RollerMode(In,0);
  setFourBarPower(-20);
  liftRequest(BottomLift-120,true);
  RollerMode(In,250);

  liftRequest(SkillsLift+210,false);
  FourBarPosition(Up,700,127);
  liftRequest((SkillsLift-500)/2,false);
  liftRequest(SkillsLift-500,false);
  setFourBarPower(10);
  wait1Msec(200);
  RollerMode(Out,0);

  wait1Msec(100);
  liftRequest(SkillsLift,false);
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
// programs that corilate with M=Team Comp Controll.c to run our autonomous
//#region Score 5's
void RightFive()
{
  liftRequest(SkillsLift+100,false);
  goalRequest(mobileIn,true);
  setFourBarPower(20);
  setIntakePower(15);

  goalRequest(mobileOut,true);
  Atondrive(44, drivepower);

  QuickPickUP(75, 310);
  wait1Msec(310);

  liftRequest(BottomLift,true);
  RollerMode(Out,0);
  startTask(StackAtonOneTask);
  wait1Msec(1000);
  liftRequest(ParallelLift,false);

  Atondrive(-36, drivepower);
  TurnPID(-1400, true);

  liftRequest(SkillsLift,false);
  Atondrive(0.01, drivepower);
  goalRequest(mobileOut,true);
  Atondrive(-35, drivepower);
  goalRequest(mobileIn,true);
  TurnPID(150);
  Atondrive(-40, drivepower);
  TurnPID(-900,true);
  goalRequest(mobileOut,false);
}
void RightFiveCones()
{
  liftRequest(SkillsLift+100,false);
  goalRequest(mobileIn,true);
  setFourBarPower(20);
  setIntakePower(15);

  goalRequest(mobileOut,true);
  Atondrive(44, drivepower);

  QuickPickUP(75, 300);
  wait1Msec(200);
  goalRequest(mobileIn,true);

  liftRequest(BottomLift,true);
  RollerMode(Out,0);
  startTask(StackAtonOneTask);
  wait1Msec(1220);
  Atondrive(7, drivepower);
  wait1Msec(800);
  startTask(StackAtonOneTask);
  wait1Msec(1220);
  Atondrive(9, drivepower);
  wait1Msec(800);
  startTask(StackAtonOneTask);
  wait1Msec(1000);
  RollerMode(In,0);
  liftRequest(ParallelLift,false);

  Atondrive(-59, drivepower);
  liftRequest(ParallelLift,true);
  TurnPID(-1000, true);
  Atondrive(0.01, drivepower);
  setFourBarPower(20);

  liftRequest(ParallelLift,true);
  QuickOffLoad(127, 500);
  wait1Msec(175);
  Atondrive(-15, drivepower);
}
void LeftFive()
{
  liftRequest(SkillsLift+100,false);
  goalRequest(mobileIn,true);
  setFourBarPower(20);
  setIntakePower(15);

  goalRequest(mobileOut,true);
  Atondrive(44, drivepower);

  QuickPickUP(75, 310);
  wait1Msec(310);

  liftRequest(BottomLift,true);
  RollerMode(Out,0);
  startTask(StackAtonOneTask);
  wait1Msec(1000);
  liftRequest(ParallelLift,false);

  Atondrive(-40, drivepower);
  TurnPID(-2000, true);

  liftRequest(SkillsLift,false);
  Atondrive(0.01, drivepower);
  QuickOffLoad(127, 500);
  wait1Msec(200);
  Atondrive(-35, drivepower);
  goalRequest(mobileIn,true);
  TurnPID(-150);
  Atondrive(-5, drivepower);
  TurnPID(900,true);
  goalRequest(mobileOut,false);
}

void LeftFiveCones()
{
  liftRequest(SkillsLift+100,false);
  goalRequest(mobileIn,true);
  setFourBarPower(20);
  setIntakePower(15);

  goalRequest(mobileOut,true);
  Atondrive(44, drivepower);

  QuickPickUP(75, 300);
  wait1Msec(200);
  goalRequest(mobileIn,true);

  liftRequest(BottomLift,true);
  RollerMode(Out,0);
  startTask(StackAtonOneTask);
  wait1Msec(1220);
  Atondrive(7, drivepower);
  wait1Msec(800);
  startTask(StackAtonOneTask);
  wait1Msec(1220);
  Atondrive(8, drivepower); //mark was here
  wait1Msec(800);
  startTask(StackAtonOneTask);
  wait1Msec(1000);
  RollerMode(In,0);
  liftRequest(ParallelLift,false);

  Atondrive(-59, drivepower);
  liftRequest(ParallelLift,true);
  TurnPID(-2000, true);
  Atondrive(0.01, drivepower);
  setFourBarPower(20);

  liftRequest(ParallelLift,true);
  QuickOffLoad(127, 500);
  wait1Msec(175);
  Atondrive(-15, drivepower);
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
  Atondrive(56, drivepower);
  QuickPickUP(75, 310);
  wait1Msec(350);
  liftRequest(BottomLift,false);

  Atondrive(-60, drivepower);
  setIntakePower(-127);
  TurnPID(FullP+210, true);
  setIntakePower(0);
  liftRequest(SkillsLift,false);
  Atondrive(0.01, drivepower);
  goalRequest(mobileOut,true);
  Atondrive(-35, drivepower);
  goalRequest(mobileIn,true);
  TurnPID(150);
  Atondrive(-40, drivepower);
  TurnPID(-900,true);
  goalRequest(mobileOut,false);
}

void RightTenConesOne()
{
  liftRequest(SkillsLift+100,false);
  goalRequest(mobileIn,true);
  setFourBarPower(20);
  setIntakePower(15);

  goalRequest(mobileOut,true);
  Atondrive(44, drivepower);

  QuickPickUP(75, 310);
  wait1Msec(300);

  liftRequest(BottomLift,true);
  RollerMode(Out,0);
  startTask(StackAtonOneTask);
  wait1Msec(1000);
  liftRequest(ParallelLift,false);

  Atondrive(-50, drivepower);
  TurnPID(-450, true);
  Atondrive(-5, drivepower);
  TurnPID(-NineP+80, true);
  liftRequest(ParallelLift,false);
  Atondrive(2, drivepower);
  goalRequest(mobileOut,true);
  liftRequest(SkillsLift, false);
  Atondrive(-10, drivepower);

  wait1Msec(300);
  TurnPID(-NineP/2);
  Atondrive(-21, drivepower);
  TurnPID(NineP/2);
  goalRequest(mobileMid,false);
  Atondrive(-38, drivepower);
}

void RightTenConesTwo()
{
  liftRequest(SkillsLift+100,false);
  goalRequest(mobileIn,true);
  setFourBarPower(20);
  setIntakePower(15);

  goalRequest(mobileOut,true);
  Atondrive(44, drivepower);

  QuickPickUP(75, 300);
  wait1Msec(200);
  goalRequest(mobileIn,true);

  liftRequest(BottomLift,true);
  RollerMode(Out,0);
  startTask(StackAtonOneTask);
  wait1Msec(1220);
  Atondrive(7, drivepower);
  wait1Msec(800);
  startTask(StackAtonOneTask);
  wait1Msec(1000);
  liftRequest(ParallelLift,false);


  Atondrive(-50, drivepower);
  TurnPID(-450, true);
  Atondrive(-7, drivepower);
  TurnPID(-NineP+110, true);
  liftRequest(ParallelLift,false);
  Atondrive(4, drivepower);
  goalRequest(mobileOut,true);
  liftRequest(SkillsLift, false);
  Atondrive(-30, drivepower);
}

void LeftTen()
{
  liftRequest(SkillsLift+100,false);
  goalRequest(mobileIn,true);
  setFourBarPower(20);
  setIntakePower(15);

  goalRequest(mobileOut,true);
  Atondrive(56, drivepower);
  QuickPickUP(75, 310);
  wait1Msec(350);
  liftRequest(BottomLift,false);

  Atondrive(-60, drivepower);
  setIntakePower(-127);
  TurnPID(-FullP-210, true);
  setIntakePower(0);
  liftRequest(SkillsLift,false);
  Atondrive(0.01, drivepower);
  goalRequest(mobileOut,true);
  Atondrive(-35, drivepower);
  goalRequest(mobileIn,true);
  TurnPID(-150);
  Atondrive(-40, drivepower);
  TurnPID(900,true);
  goalRequest(mobileOut,false);
}

void LeftTenConesOne()
{
  liftRequest(SkillsLift+100,false);
  goalRequest(mobileIn,true);
  setFourBarPower(20);
  setIntakePower(15);

  goalRequest(mobileOut,true);
  Atondrive(44, drivepower);

  QuickPickUP(75, 310);
  wait1Msec(300);

  liftRequest(BottomLift,true);
  RollerMode(Out,0);
  startTask(StackAtonOneTask);
  wait1Msec(1000);
  liftRequest(ParallelLift,false);

  Atondrive(-47, drivepower);
  TurnPID(450, true);
  Atondrive(-5, drivepower);
  TurnPID(NineP-80, true);
  liftRequest(ParallelLift,false);
  Atondrive(2, drivepower);
  goalRequest(mobileOut,true);
  liftRequest(SkillsLift, false);
  Atondrive(-10, drivepower);

  wait1Msec(300);
  TurnPID(NineP/2);
  Atondrive(-21, drivepower);
  TurnPID(-NineP/2);
  goalRequest(mobileMid,false);
  Atondrive(-38, drivepower);
}

void LeftTenConesTwo()
{
  liftRequest(SkillsLift+100,false);
  goalRequest(mobileIn,true);
  setFourBarPower(20);
  setIntakePower(15);

  goalRequest(mobileOut,true);
  Atondrive(44, drivepower);

  QuickPickUP(75, 300);
  wait1Msec(200);
  goalRequest(mobileIn,true);

  liftRequest(BottomLift,true);
  RollerMode(Out,0);
  startTask(StackAtonOneTask);
  wait1Msec(1220);
  Atondrive(7, drivepower);
  wait1Msec(800);
  startTask(StackAtonOneTask);
  wait1Msec(1000);
  liftRequest(ParallelLift,false);

  Atondrive(-50, drivepower);
  TurnPID(450, true);
  Atondrive(-7, drivepower);
  TurnPID(NineP-110, true);
  liftRequest(ParallelLift,false);
  Atondrive(4, drivepower);
  goalRequest(mobileOut,true);
  liftRequest(SkillsLift, false);
  Atondrive(-30, drivepower);
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
  Atondrive(43, drivepower);

  QuickPickUP(75, 300);
  wait1Msec(200);

  liftRequest(BottomLift,true);
  RollerMode(Out,0);
  startTask(StackAtonOneTask);
  wait1Msec(1220);
  Atondrive(8, drivepower);
  wait1Msec(800);
  startTask(StackAtonOneTask);
  wait1Msec(1000);
  RollerMode(In,0);
  liftRequest(ParallelLift,false);

  Atondrive(-58, drivepower);
  RollerMode(In,0);
  liftRequest(1488,false);
  TurnPID(-300, true);
  RollerMode(In,1);
  Atondrive(-17, drivepower);
  TurnPID(-850, true);
  setFourBarPower(20);

  Atondrive(19, drivepower);
  setDrivePower(15,15);
  RollerMode(Out,0);
  liftRequest(ParallelLift,false);
  wait1Msec(100);

  waitMobliERerror = 150;
  goalRequest(mobileLow,true);
  Atondrive(-21, drivepower);
}

void LeftTwenty()
{
  liftRequest(SkillsLift+100,false);
  goalRequest(mobileIn,true);
  setFourBarPower(20);
  setIntakePower(15);

  goalRequest(mobileOut,true);
  Atondrive(43, drivepower);

  QuickPickUP(75, 300);
  wait1Msec(200);

  liftRequest(BottomLift,true);
  RollerMode(Out,0);
  startTask(StackAtonOneTask);
  wait1Msec(1220);
  Atondrive(8, drivepower);
  wait1Msec(800);
  startTask(StackAtonOneTask);
  wait1Msec(1000);
  RollerMode(In,0);
  liftRequest(ParallelLift,false);

  Atondrive(-58, drivepower);
  RollerMode(In,0);
  liftRequest(1488,false);
  TurnPID(-1250, true);
  RollerMode(In,1);
  Atondrive(17, drivepower);
  TurnPID(-850, true);
  setFourBarPower(20);

  Atondrive(19, drivepower);
  setDrivePower(15,15);
  RollerMode(Out,0);
  liftRequest(ParallelLift,false);
  wait1Msec(100);

  waitMobliERerror = 150;
  goalRequest(mobileLow,true);
  Atondrive(-21, drivepower);
}
//#endregion
//#region Skills
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
  setIntakePower(15);

  goalRequest(mobileOut,true);
  Atondrive(43, drivepower);

  QuickPickUP(75, 300);
  wait1Msec(200);

  liftRequest(BottomLift,true);
  RollerMode(Out,0);
  startTask(StackAtonOneTask);
  wait1Msec(1220);
  Atondrive(8, drivepower);
  wait1Msec(800);
  startTask(StackAtonOneTask);
  wait1Msec(1000);
  RollerMode(In,0);
  liftRequest(ParallelLift,false);

  Atondrive(-58, drivepower);
  RollerMode(In,0);
  liftRequest(1488,false);
  TurnPID(-300, true);
  RollerMode(In,1);
  Atondrive(-17, drivepower);
  TurnPID(-850, true);
  setFourBarPower(20);

  Atondrive(19, drivepower);
  setDrivePower(15,15);
  RollerMode(Out,0);
  liftRequest(ParallelLift,false);
  wait1Msec(100);

  waitMobliERerror = 150;
  goalRequest(mobileLow,true);
  Atondrive(-24, drivepower);


  //End of twenty point portion
  liftRequest(SkillsLift,false)
  TurnPID(-900, true);
  Atondrive(18, drivepower);
  TurnPID(-450, true);
  //End of Patch

  liftRequest(SkillsLift+100,false);
  goalRequest(mobileIn,true);
  setFourBarPower(20);
  setIntakePower(15);

  goalRequest(mobileOut,true);
  Atondrive(43, drivepower);

  QuickPickUP(75, 300);
  wait1Msec(200);

  liftRequest(BottomLift,true);
  RollerMode(Out,0);
  startTask(StackAtonOneTask);
  wait1Msec(1220);
  Atondrive(8, drivepower);
  wait1Msec(800);
  startTask(StackAtonOneTask);
  wait1Msec(1000);
  RollerMode(In,0);
  liftRequest(ParallelLift,false);

  Atondrive(-58, drivepower);
  RollerMode(In,0);
  liftRequest(1488,false);
  TurnPID(-1250, true);
  RollerMode(In,1);
  Atondrive(17, drivepower);
  TurnPID(-850, true);
  setFourBarPower(20);
  Atondrive(4, drivepower)

  RollerMode(Out,0);
  liftRequest(ParallelLift,false);
  wait1Msec(100);

  waitMobliERerror = 150;
  goalRequest(mobileOut,true);
  Atondrive(-4, drivepower);
//End of second goal
  TurnPID(900, true);
  Atondrive(6, drivepower);
  TurnPID(900, true);
  Atondrive(18, drivepower);

  QuickPickUP(75, 300);
  wait1Msec(200);

  TurnPID(-1800, true);
  Atondrive(20, drivepower);
  goalRequest(mobileOut,true);
  Atondrive(-4, drivepower);
  goalRequest(mobileMid, false);
  TurnPID(1800, true);
  goalRequest(mobileOut, true);
  Atondrive(18, true);

  QuickPickUP(75, 300);
  wait1Msec(200);

  TurnPID(900, true);
  Atondrive(18, drivepower);
  goalRequest(mobileOut, true);
  Atondrive(-6, drivepower);
  TurnPID(-1800);
  //On to other side of feild

  Atondrive(36, drivepower);

  QuickPickUP(75, 300);
  wait1Msec(200);

  Atondrive(18, drivepower);
  TurnPID(-900, true);
  Atondrive(12, drivepower);
  TurnPID(900, true);

  Atondrive(19, drivepower);
  setDrivePower(15,15);
  RollerMode(Out,0);
  liftRequest(ParallelLift,false);
  wait1Msec(100);

  waitMobliERerror = 150;
  goalRequest(mobileLow,true);
  Atondrive(-24, drivepower);
}
//#endregion
//#region Other Programs
void Defensive ()
{
  liftRequest(ParallelLift,true);
  // QuickPickUP(200);
  liftRequest(BottomLift,true);
  RollerMode(Out,0);
  startTask(StackAtonOneTask);
  wait1Msec(1200);
  Atondrive(6, drivepower);
  wait1Msec(800);
  startTask(StackAtonOneTask);
  wait1Msec(1200);
  Atondrive(6, drivepower);
  wait1Msec(800);

  startTask(StackAtonOneTask);
  wait1Msec(1000);
  Atondrive(-12, drivepower);
}

void TestingAton ()
{
  liftRequest(1830,false);
  goalRequest(mobileIn, true);
  goalRequest(mobileOut, true);
  goalRequest(mobileIn, true);
  goalRequest(mobileOut, true);

}

void StationaryLeft()
{
  liftRequest(1830,false);

  Atondrive(18, drivepower);
  FourBarPosition(Down,500,127);
  RollerMode(Out,0);
  FourBarPosition(Up,500,127);
  liftRequest(SkillsLift,false);
  TurnPID(NineP-80, true);
  Atondrive(19, drivepower);
  TurnPID(-NineP/2, true);
  Atondrive(36, drivepower);
  wait1Msec(300);
  Atondrive(-12, drivepower);
  TurnPID(-880/2, true);
  wait1Msec(300);
  goalRequest(mobileOut,true);
  Atondrive(20, drivepower);
}

void StationaryRight()
{
  liftRequest(1830,false);

  Atondrive(18, drivepower);
  FourBarPosition(Down,500,127);
  RollerMode(Out,0);
  FourBarPosition(Up,500,127);
  liftRequest(SkillsLift,false);
  TurnPID(-NineP+80, true);
  Atondrive(19, drivepower);
  TurnPID(NineP/2, true);
  Atondrive(36, drivepower);
  wait1Msec(300);
  Atondrive(-12, drivepower);
  TurnPID(880/2, true);
  wait1Msec(300);
  goalRequest(mobileOut,true);
  Atondrive(20, drivepower);
}

//#endregion
//</editor-fold>
