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
int curentteir = 1;      //initializing a variable to keep track of teir number
bool stackReadyAdd = true;
bool stackReadySubtract = true;

//Variables for turn and drive
int Nine = 750;
int full = 1750;
int drivepower = 127;
int NineP = 933;
int FullP = 1860;

// PID Mobile Variables
int mobileIn = 1051;
int mobileOut = 3340;
int mobileMid = 2456;
int mobileSMid = 2770;

// PID Lift variables
int BottomLift = 2290;
int TopLift = 855;
int ParallelLift = 1880;
int SkillsLift = 2140;

// Auto Stack teir variables
int teirHeightOneTwo = 2138;
int teirHeightThree = 2020;
int teirHeightFour = 1902;
int teirHeightFive = 1720;
int teirHeightSix = 1596;
int teirHeightSeven = 1540;
int teirHeightEight = 1460;
int teirHeightNine = 1340;
int teirHeightTen = 1210;
int teirHeightEleven = 1110;
int teirHeightTwelve = 940;
int teirHeightThirteen = 940;
int teirHeightFourteen = 940;
int teirHeightFifteen = 940;

float wheelDiameter = 3;
int cumBias;
int debug;

int InchesToCounts(float value) //converts drive encoder counts into inches
{
  return (value * 360)/(PI * wheelDiameter);
}
//#endregion
//#region Autonomous Voids
//--------------------Autonomous Voids-----------------------//
void AutoStrait(int distance, int power)
 // Creating a function to make sure the robot drives forward
{
	int direction = sgn(distance);
	distance = abs(distance);

 // telling it to do this while you are driving to the disired distance
	while((abs(SensorValue[rightEncoder])/2) < distance)
	{
		 // Checking if the right drive is faster than the left drive
		if (abs(SensorValue[rightEncoder]) > abs(SensorValue[leftEncoder]))
		{
			setDrivePower(direction * (power + 4), direction * (power - 10));
		}
		// Checking if the left drive is faster than the right drive
		else if (abs(SensorValue[leftEncoder]) > abs(SensorValue[rightEncoder]))
		{
			setDrivePower(direction * (power - 2), direction * power);
		}
		else //if the values are the same, keeps motor powers equall
		{
			setDrivePower(direction * power, direction * power);
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
	AutoStrait(ticks*0.6, power);
	AutoStrait(ticks*0.8, power/2);
	AutoStrait(ticks, power/3);
//sudden stop to correct overshooting the value
	motor[LDrive] = -20 * sgn(ticks);
	motor[RDrive] = -20 * sgn(ticks);
	wait1Msec(100);
}
//#endregion
//#region User Contoll Tasks
task drive() //Redirecting Drive into a task
{
	while(true)
	{
	setDrivePower(vexRT[Ch3],vexRT[Ch2]);
	}
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
	liftRRequestedValue = SkillsLift + 500;
	wait1Msec(100);
	setIntakePower (-127);
	wait1Msec(300);
	setIntakePower (20);
	liftRRequestedValue=2000;
}

task AutoStackUpSimple()									// Simple Auto stack cone up
{
	liftRRequestedValue = ParallelLift;

	setFourBarPower(-127);
	wait1Msec(500);
	setFourBarPower(-10);

	liftRRequestedValue = SkillsLift + 400;

	setIntakePower(127);
	wait1Msec(400);
	setIntakePower(20);
	wait1Msec(100);

	liftRRequestedValue = ParallelLift;

	setFourBarPower(127);
	wait1Msec(750);
	setFourBarPower(20);

	liftRRequestedValue = SkillsLift + 500;
	wait1Msec(400);
	setIntakePower(-127);
	wait1Msec(200);
	liftRRequestedValue = ParallelLift;
	wait1Msec(300);
	setIntakePower(10);
}
//#endregion
//#region Special Auto Stack Voids
//--------------------Special Auto Stack Voids-----------------------//
void AutoStackUp()									// Simple Auto stack cone up
{
}
//#endregion
//--------------------Autonomous Programs----------------------------//
//#region Driver Program Programs
void Preload()
{
}
//#endregion
//#region Score 5's
void RightFive()
{
}

void LeftFive()
{
}
//#endregion
//#region Score 10's
void RightTen()
{
}

void LeftTen()
{
}
//#endregion
//#region Score 20's
void RightTwenty()
{
}

void LeftTwenty()
{
}
//#endregion
//#region Score Special's
void SkillsOne ()
{
	//------------------------------------------------------------//
			setIntakePower(15);                   //
			liftRRequestedValue = 2000;
			wait1Msec(700);
			mobileRRequestedValue = mobileOut;

			setFourBarPower(20);

			Atondrive(610, 127);

			mobileRRequestedValue = mobileIn;
			wait1Msec(200);

			Atondrive(-550, 127);
			liftRRequestedValue = 2600;
			wait1Msec(300);
			setIntakePower(-127);                   //
			liftRRequestedValue = 2000;

			TurnPID(-NineP/2, true);
			setIntakePower(0);                   //

			Atondrive(-290, 127);

			TurnPID(-NineP-30, true);

			Atondrive(285, 127);

			setDrivePower(40,40);

			mobileRRequestedValue = mobileOut;
			WaitieThing();

			mobileRRequestedValue = mobileIn;
			//------------------------------------------- Place 2nd
			Atondrive(-230, drivepower);

			TurnPID(-NineP, true);

			Atondrive(170, drivepower);

			mobileRRequestedValue = mobileOut;

			TurnPID(-NineP-15, true);

			//mobileRRequestedValue = mobileOut;
			//WaitieThing();

			/*setDrivePower(-30,-30);
			wait1Msec(1200);*/

			Atondrive(320, drivepower);

			mobileRRequestedValue = mobileIn;
			wait1Msec(400);
			Atondrive(-260, drivepower);

			TurnPID(-FullP+5, true);

			Atondrive(115, 127);

			//setDrivePower(40,40);

			mobileRRequestedValue = mobileOut;
			WaitieThing();
			//------------------------------------------- Place 3rd
			Atondrive(-535, drivepower);

			mobileRRequestedValue = mobileMid;

			TurnPID(NineP-5, true);

			mobileRRequestedValue = mobileOut;
			WaitieThing();

			Atondrive(420, drivepower);

			mobileRRequestedValue = mobileIn;
			wait1Msec(500);

			TurnPID(-NineP-30, true);

			Atondrive(590, drivepower);
			//setDrivePower(40,40);

			mobileRRequestedValue = mobileOut;
			WaitieThing();
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
			WaitieThing();
			//------------------------------------------- Place 5th
			Atondrive(-545, drivepower);

			mobileRRequestedValue = mobileMid;

			TurnPID(NineP-10, true);

			mobileRRequestedValue = mobileOut;
			WaitieThing();

			Atondrive(460, drivepower);

			mobileRRequestedValue = mobileIn;
			wait1Msec(500);

			TurnPID(-NineP-42, true);

			Atondrive(565, drivepower);
			//setDrivePower(20,20);

			mobileRRequestedValue = mobileOut;
			WaitieThing();
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
			WaitieThing();

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
			WaitieThing();

			Atondrive(-200, drivepower);

}

void SkillsTwo ()
{
}
//#endregion
//#region Other Programs
void Defensive ()
{
}

void DoNothing ()
{
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
//<editor-fold


//</editor-fold>
