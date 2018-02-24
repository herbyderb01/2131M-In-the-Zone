#include "BackOver Functions 2017-18.c"
#include "Drive PID.c"
//#region Variables
//-------------Variables--------------//
// Random variable for turn and drive
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

void Atondrive(int ticks, int power)
{ //auton function to move forward by its self
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

void turnRight(int ticks) // void to turn the robot right as much as you want
{
	//Clear Gyro
	SensorValue[Gyro] = 0;

	while(abs(SensorValue[Gyro]) < ticks) //while the sensor value is less than the amount of turing
  {
		setDrivePower(75, -75); //set drive power to turn robot right
	}
	setDrivePower(-10,10); //then stop
	wait1Msec(100);
}

void turnLeft(int ticks) // void to turn the robot left as much as you want
{
	//Clear Gyro
	SensorValue[Gyro] = 0;

	while(abs(SensorValue[Gyro]) < ticks) //while the sensor value is less than the amount of turing
	{
		setDrivePower(-60, 60); //set drive power to turn robot right
	}
	setDrivePower(10,-10); //then stop}
	wait1Msec(50);
}

task drive() //Redirecting Drive into a task
{
	while(true)
	{
	setDrivePower(vexRT[Ch3],vexRT[Ch2]);
	}
	/*
	while (true)
	{
	if (abs(vexRT[Ch3])+ abs(vexRT[Ch2])>10)
	{
		setDrivePower(vexRT[Ch3],vexRT[Ch2]);
	}
  else
		{
			setDrivePower(vexRT[Ch3Xmtr2],vexRT[Ch2Xmtr2]);
		}
				//DrivePower(vexRT[Ch3Xmtr2], vexRT[Ch2Xmtr2]);
		}
				//setDrivePower(vexRT[Ch3]+vexRT[Ch3Xmtr2],vexRT[Ch2]+vexRT[Ch2Xmtr2]);

		wait1Msec(25); //dont hog cpu*/
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

		setChainPower(-127);
		wait1Msec(500);
		setChainPower(-10);

		liftRRequestedValue = SkillsLift + 400;

		setIntakePower(127);
		wait1Msec(400);
		setIntakePower(20);
		wait1Msec(100);

		liftRRequestedValue = ParallelLift;

		setChainPower(127);
		wait1Msec(750);
		setChainPower(20);

		liftRRequestedValue = SkillsLift + 500;
		wait1Msec(400);
		setIntakePower(-127);
		wait1Msec(200);
		liftRRequestedValue = ParallelLift;
		wait1Msec(300);
		setIntakePower(10);
	}

//_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_//
//#endregion
//#region AutoStack Teirs
/*//vars

//Toggle teirs var
int curentteir = 1;

//teirOne
int Stack Height 1
int GrabHeight

task StackNewCone() // button to stack new cone
{

  sequence in "if's" to stack new cone with variables to differentiate the different teirs
	- then changes currentteir varable to next teir 1-4

	if (vexRT[Btn7DXmtr2] == 1)
	{
		if(curentteir = 1)
		{
			startTask(liftRController);
		//run stack sequence with its specific teir
			stopTask(liftRController);
		}

		if(curentteir = 2)
		{
			startTask(liftRController);
		//run stack sequence with its specific teir
			stopTask(liftRController);
		}

		if(curentteir = 3)
		{
			startTask(liftRController);
		//run stack sequence with its specific teir
			stopTask(liftRController);
		}

		if(curentteir = 4)
		{
			startTask(liftRController);
		//run stack sequence with its specific teir
			stopTask(liftRController);
		}

		if(curentteir = 5)
		{
			startTask(liftRController);
		//run stack sequence with its specific teir
			stopTask(liftRController);
		}
	}

	else if (vexRT[Btn7LXmtr2] == 1)
	{
		curentteir+1;
	}

	else if (vexRT[Btn7RXmtr2] == 1)
	{
		curentteir-1;
	}
	else if (vexRT[Btn7UXmtr2] == 1)
	{
		curentteir = 1;
	}
}*/
//#endregion
//#region Special Auto Stack Voids
//--------------------Special Auto Stack Voids-----------------------//
void AutoStackUp()									// Simple Auto stack cone up
{
	liftRRequestedValue = ParallelLift;

	setChainPower(-127);
	wait1Msec(500);
	setChainPower(-10);

	liftRRequestedValue = SkillsLift + 400;

	setIntakePower(127);
	wait1Msec(1000);
	setIntakePower(20);
	wait1Msec(100);

	liftRRequestedValue = ParallelLift;

	setChainPower(127);
	wait1Msec(750);
	setChainPower(20);

	liftRRequestedValue = SkillsLift + 500;
	wait1Msec(400);
	setIntakePower(-127);
	wait1Msec(200);
	liftRRequestedValue = ParallelLift;
	wait1Msec(300);
	setIntakePower(10);
}
/*
void AutoStackDown()									// Simple Auto stack cone down
{
//	Atondrive(1000, -100);
}
*/
//_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_//
//#endregion
//--------------------Autonomous Programs----------------------------//
//#region Driver Program Programs
void Preload()
{
	setIntakePower(15);
	setChainPower(20);

	//chainRRequestedValue = StraitUpChain; //
	liftRRequestedValue = ParallelLift;           // PRESETS
	mobileRRequestedValue = mobileIn;     //

	mobileRRequestedValue = mobileOut;   // Open Mobile goal to grab 1st goal
	WaitieThing();											 // Wait for Mobile Goal
	setMobilePower(15);

	Atondrive(380, 127);								 // Drive forward for 380 encoder clicks

	wait1Msec(200);                      // Delay

	//chainRRequestedValue = OutPositionChain; //score pre-load

	mobileRRequestedValue = mobileIn;
	WaitieThing();											 // Wait for Mobile Goal

	liftRRequestedValue = BottomLift;

	setChainPower(127);
	wait1Msec(250);
	setChainPower(15);

	setIntakePower(-127);
	wait1Msec(500);
	setIntakePower(0);

	//chainRRequestedValue = StraitUpChain;// Set Chain to strait up

}
//#endregion
//#region Score 5's
void RightBlueFive()
{
	//--------------------------//
	setIntakePower(20);                   //
	liftRRequestedValue = 1880;           // PRESETS

	liftRRequestedValue = SkillsLift;

	mobileRRequestedValue = mobileOut;
	//WaitieThing();

	setChainPower(20);

	Atondrive(750, 127);

	wait1Msec(200);

	//chainRRequestedValue = StraitUpChain;
	liftRRequestedValue = ParallelLift;
	wait1Msec(1);
	mobileRRequestedValue = mobileIn;
	WaitieThing();

	liftRRequestedValue = SkillsLift + 350;
	wait1Msec(200);

	setIntakePower(-127);                   //
	wait1Msec(300);
	setIntakePower(0);                   //

	liftRRequestedValue = ParallelLift;

	setChainPower(127);
	wait1Msec(600);
	setChainPower(0);

	/*setDrivePower(30,70);
	wait1Msec(120);
	setDrivePower(0,0);
	Atondrive(100, 120);

	AutoStackUp(); 	*/										//Second Cone pickup

	Atondrive(-610, drivepower);

	turnPID(-NineP*1.575, true);

	setDrivePower(10,10);							  // Set drive still speed

	mobileRRequestedValue = mobileOut;  // Outake mobile goal
	WaitieThing();										  // Wait for Mobile Goal

	Atondrive(-675, drivepower);        // Drive backwards for 2nd Goal
	wait1Msec(100);
	Atondrive(100, drivepower);        // Drive backwards for 2nd Goal

	turnPID(-NineP*1.5, true);

	Atondrive(300, drivepower);         // Drive into Goal
}

void LeftBlueFive()
{
	//--------------------------//
	setIntakePower(20);                   //
	liftRRequestedValue = 1880;           // PRESETS

	liftRRequestedValue = SkillsLift;

	mobileRRequestedValue = mobileOut;
	//WaitieThing();

	setChainPower(20);

	Atondrive(750, 127);

	wait1Msec(200);

	//chainRRequestedValue = StraitUpChain;
	liftRRequestedValue = ParallelLift;
	wait1Msec(1);
	mobileRRequestedValue = mobileIn;
	WaitieThing();

	liftRRequestedValue = SkillsLift + 350;
	wait1Msec(200);

	setIntakePower(-127);                   //
	wait1Msec(300);
	setIntakePower(0);                   //

	liftRRequestedValue = ParallelLift;

	setChainPower(127);
	wait1Msec(600);
	setChainPower(0);

	/*setDrivePower(30,70);
	wait1Msec(120);
	setDrivePower(0,0);
	Atondrive(100, 120);

	AutoStackUp(); 	*/										//Second Cone pickup

	Atondrive(-610, drivepower);

	turnPID(NineP*1.575, true);

	setDrivePower(10,10);							  // Set drive still speed

	mobileRRequestedValue = mobileOut;  // Outake mobile goal
	WaitieThing();										  // Wait for Mobile Goal

	Atondrive(-700, drivepower);        // Drive backwards for 2nd Goal
	wait1Msec(100);
	Atondrive(100, drivepower);        // Drive backwards for 2nd Goal

	turnPID(NineP*1.5, true);

	Atondrive(300, drivepower);         // Drive into Goal
}

void RightRedFive()
{
	//--------------------------//
	setIntakePower(20);                   //
	liftRRequestedValue = 1880;           // PRESETS

	liftRRequestedValue = SkillsLift;

	mobileRRequestedValue = mobileOut;
	//WaitieThing();

	setChainPower(20);

	Atondrive(750, 127);

	wait1Msec(200);

	//chainRRequestedValue = StraitUpChain;
	liftRRequestedValue = ParallelLift;
	wait1Msec(1);
	mobileRRequestedValue = mobileIn;
	WaitieThing();

	liftRRequestedValue = SkillsLift + 350;
	wait1Msec(200);

	setIntakePower(-127);                   //
	wait1Msec(300);
	setIntakePower(0);                   //

	liftRRequestedValue = ParallelLift;

	setChainPower(127);
	wait1Msec(600);
	setChainPower(0);

	/*setDrivePower(30,70);
	wait1Msec(120);
	setDrivePower(0,0);
	Atondrive(100, 120);

	AutoStackUp(); 	*/										//Second Cone pickup

	Atondrive(-610, drivepower);

	turnPID(-NineP*1.575, true);

	setDrivePower(10,10);							  // Set drive still speed

	mobileRRequestedValue = mobileOut;  // Outake mobile goal
	WaitieThing();										  // Wait for Mobile Goal

	Atondrive(-675, drivepower);        // Drive backwards for 2nd Goal
	wait1Msec(100);
	Atondrive(100, drivepower);        // Drive backwards for 2nd Goal

	turnPID(-NineP*1.5, true);

	Atondrive(300, drivepower);         // Drive into Goal
}

void LeftRedFive()
{
	//--------------------------//
	setIntakePower(20);                   //
	liftRRequestedValue = 1880;           // PRESETS

	liftRRequestedValue = SkillsLift;

	mobileRRequestedValue = mobileOut;
	//WaitieThing();

	setChainPower(20);

	Atondrive(750, 127);

	wait1Msec(200);

	//chainRRequestedValue = StraitUpChain;
	liftRRequestedValue = ParallelLift;
	wait1Msec(1);
	mobileRRequestedValue = mobileIn;
	WaitieThing();

	liftRRequestedValue = SkillsLift + 350;
	wait1Msec(200);

	setIntakePower(-127);                   //
	wait1Msec(300);
	setIntakePower(0);                   //

	liftRRequestedValue = ParallelLift;

	setChainPower(127);
	wait1Msec(600);
	setChainPower(0);

	/*setDrivePower(30,70);
	wait1Msec(120);
	setDrivePower(0,0);
	Atondrive(100, 120);

	AutoStackUp(); 	*/										//Second Cone pickup

	Atondrive(-610, drivepower);

	turnPID(NineP*1.575, true);

	setDrivePower(10,10);							  // Set drive still speed

	mobileRRequestedValue = mobileOut;  // Outake mobile goal
	WaitieThing();										  // Wait for Mobile Goal

	Atondrive(-675, drivepower);        // Drive backwards for 2nd Goal
	wait1Msec(100);
	Atondrive(100, drivepower);        // Drive backwards for 2nd Goal

	turnPID(NineP*1.5, true);

	Atondrive(300, drivepower);         // Drive into Goal
}

//#endregion
//#region Score 10's
void RightBlueTen()
{
	//--------------------------//
	setIntakePower(20);                   //
	liftRRequestedValue = 1880;           // PRESETS

	liftRRequestedValue = SkillsLift;

	mobileRRequestedValue = mobileOut;
	//WaitieThing();

	setChainPower(20);

	Atondrive(750, 127);

	wait1Msec(200);

	//chainRRequestedValue = StraitUpChain;
	liftRRequestedValue = ParallelLift;
	wait1Msec(1);
	mobileRRequestedValue = mobileIn;
	WaitieThing();

	liftRRequestedValue = SkillsLift + 350;
	wait1Msec(200);

	setIntakePower(-127);                   //
	wait1Msec(300);
	setIntakePower(0);                   //

	liftRRequestedValue = ParallelLift;

	setChainPower(127);
	wait1Msec(600);
	setChainPower(0);

	setDrivePower(30,80);
	wait1Msec(120);
	setDrivePower(0,0);
	Atondrive(100, 120);

	AutoStackUp(); 											//Second Cone pickup

	//--------------------------//

	Atondrive(-825, 127);

	liftRRequestedValue = ParallelLift;

	turnPID(-NineP*1.75, true);

	setDrivePower(50,50);
	wait1Msec(600);
	setDrivePower(0,0);

	mobileRRequestedValue = mobileOut;
	WaitieThing();

	Atondrive(-120, drivepower);

	liftRRequestedValue = SkillsLift;

	//--------------------------//

	turnPID(-300, true);

	Atondrive(-300, drivepower);

	turnPID(300, true);

	setDrivePower(-127,-127);
	wait1Msec(500);

	setDrivePower(-80,-80);
	wait1Msec(1800);
	setDrivePower(0,0);

	turnPID(-NineP/2, true);

	/*setDrivePower(127,127);
	wait1Msec(1000);
	setDrivePower(0,0);*/
}

void LeftBlueTen()
{
	//--------------------------//
	setIntakePower(20);                   //
	liftRRequestedValue = 1880;           // PRESETS

	liftRRequestedValue = SkillsLift;
	wait1Msec(300);
	mobileRRequestedValue = mobileOut;
	//WaitieThing();

	setChainPower(20);

	Atondrive(750, 127);

	wait1Msec(200);

	//chainRRequestedValue = StraitUpChain;
	liftRRequestedValue = ParallelLift;
	wait1Msec(1);
	mobileRRequestedValue = mobileIn;
	WaitieThing();

	liftRRequestedValue = SkillsLift + 350;
	wait1Msec(200);

	setIntakePower(-127);                   //
	wait1Msec(300);
	setIntakePower(0);                   //

	liftRRequestedValue = ParallelLift;

	setChainPower(127);
	wait1Msec(600);
	setChainPower(0);

	setDrivePower(80,30);
	wait1Msec(120);
	setDrivePower(0,0);
	Atondrive(90, 120);

	AutoStackUp(); 											//Second Cone pickup

	//--------------------------//

	Atondrive(-825, 127);

	liftRRequestedValue = ParallelLift;

	turnPID(NineP*1.75, true);

	setDrivePower(50,50);
	wait1Msec(600);
	setDrivePower(0,0);

	mobileRRequestedValue = mobileOut;
	WaitieThing();

	Atondrive(-120, drivepower);

	liftRRequestedValue = SkillsLift;

	//--------------------------//

	turnPID(300, true);

	Atondrive(-300, drivepower);

	turnPID(-300, true);

	setDrivePower(-127,-127);
	wait1Msec(500);

	setDrivePower(-80,-80);
	wait1Msec(1800);
	setDrivePower(0,0);

	turnPID(NineP/2, true);

	/*setDrivePower(127,127);
	wait1Msec(1000);
	setDrivePower(0,0);*/
}

void RightRedTen()
{
	//--------------------------//
	setIntakePower(20);                   //
	liftRRequestedValue = 1880;           // PRESETS

	liftRRequestedValue = SkillsLift;

	mobileRRequestedValue = mobileOut;
	//WaitieThing();

	setChainPower(20);

	Atondrive(750, 127);

	wait1Msec(200);

	//chainRRequestedValue = StraitUpChain;
	liftRRequestedValue = ParallelLift;
	wait1Msec(1);
	mobileRRequestedValue = mobileIn;
	WaitieThing();

	liftRRequestedValue = SkillsLift + 350;
	wait1Msec(200);

	setIntakePower(-127);                   //
	wait1Msec(300);
	setIntakePower(0);                   //

	liftRRequestedValue = ParallelLift;

	setChainPower(127);
	wait1Msec(600);
	setChainPower(0);

	setDrivePower(30,80);
	wait1Msec(120);
	setDrivePower(0,0);
	Atondrive(100, 120);

	AutoStackUp(); 											//Second Cone pickup

	//--------------------------//

	Atondrive(-825, 127);

	liftRRequestedValue = ParallelLift;

	turnPID(-NineP*1.75, true);

	setDrivePower(50,50);
	wait1Msec(600);
	setDrivePower(0,0);

	mobileRRequestedValue = mobileOut;
	WaitieThing();

	Atondrive(-120, drivepower);

	liftRRequestedValue = SkillsLift;

	//--------------------------//

	turnPID(-300, true);

	Atondrive(-300, drivepower);

	turnPID(300, true);

	setDrivePower(-127,-127);
	wait1Msec(500);

	setDrivePower(-80,-80);
	wait1Msec(1800);
	setDrivePower(0,0);

	turnPID(-NineP/2, true);

	/*setDrivePower(127,127);
	wait1Msec(1000);
	setDrivePower(0,0);*/
}

void LeftRedTen()
{
	//--------------------------//
	setIntakePower(20);                   //
	liftRRequestedValue = 1880;           // PRESETS

	liftRRequestedValue = SkillsLift;
	wait1Msec(300);
	mobileRRequestedValue = mobileOut;
	//WaitieThing();

	setChainPower(20);

	Atondrive(750, 127);

	wait1Msec(200);

	//chainRRequestedValue = StraitUpChain;
	liftRRequestedValue = ParallelLift;
	wait1Msec(1);
	mobileRRequestedValue = mobileIn;
	WaitieThing();

	liftRRequestedValue = SkillsLift + 350;
	wait1Msec(200);

	setIntakePower(-127);                   //
	wait1Msec(300);
	setIntakePower(0);                   //

	liftRRequestedValue = ParallelLift;

	setChainPower(127);
	wait1Msec(600);
	setChainPower(0);

	setDrivePower(80,30);
	wait1Msec(120);
	setDrivePower(0,0);
	Atondrive(90, 120);

	AutoStackUp(); 											//Second Cone pickup

	//--------------------------//

	Atondrive(-825, 127);

	liftRRequestedValue = ParallelLift;

	turnPID(NineP*1.75, true);

	setDrivePower(50,50);
	wait1Msec(600);
	setDrivePower(0,0);

	mobileRRequestedValue = mobileOut;
	WaitieThing();

	Atondrive(-120, drivepower);

	liftRRequestedValue = SkillsLift;

	//--------------------------//

	turnPID(300, true);

	Atondrive(-300, drivepower);

	turnPID(-300, true);

	setDrivePower(-127,-127);
	wait1Msec(500);

	setDrivePower(-80,-80);
	wait1Msec(1800);
	setDrivePower(0,0);

	turnPID(NineP/2, true);

	/*setDrivePower(127,127);
	wait1Msec(1000);
	setDrivePower(0,0);*/
}

//#endregion
//#region Score 20's
void RightBlueTwenty() // Auton task to grab moble base on the right and score it
{
	//--------------------------//
	setIntakePower(20);                   //
	liftRRequestedValue = 1880;           // PRESETS

	liftRRequestedValue = SkillsLift;

	mobileRRequestedValue = mobileOut;
	//WaitieThing();

	setChainPower(20);

	Atondrive(650, 127);

	wait1Msec(200);

	//chainRRequestedValue = StraitUpChain;
	liftRRequestedValue = ParallelLift;
	wait1Msec(1);
	mobileRRequestedValue = mobileIn;
	WaitieThing();

	liftRRequestedValue = SkillsLift + 350;
	wait1Msec(200);

	setIntakePower(-127);                   //
	wait1Msec(300);
	setIntakePower(0);                   //

	liftRRequestedValue = ParallelLift;

	setChainPower(127);
	wait1Msec(600);
	setChainPower(0);

	setDrivePower(30,80);
	wait1Msec(120);
	setDrivePower(0,0);
	Atondrive(100, 120);

	AutoStackUp(); 											//Second Cone pickup
/*
	setDrivePower(50,50);
	wait1Msec(120);
	setDrivePower(0,0);
	Atondrive(100, 120);

	AutoStackUp(); 											//Second Cone pickup

	setChainPower(-127);
	wait1Msec(700);
	setChainPower(-15);

	liftRRequestedValue = 2200;
	wait1Msec(500);
	setLiftPower(-20);

	setDrivePower(50,50);
	wait1Msec(120);
	setDrivePower(0,0);
	Atondrive(100, 120);

	AutoStackUp(); 											//Second Cone pickup*/


			Atondrive(-650, 127);
			wait1Msec(200);

			TurnPID(-NineP/2, true);
			setIntakePower(0);                   //

			Atondrive(-400, 127);

			liftRRequestedValue = 2000;

			TurnPID(-NineP-30, true);

			Atondrive(285, 127);

			setDrivePower(40,40);

			mobileRRequestedValue = mobileOut;
			WaitieThing();

			mobileRRequestedValue = mobileIn;

			Atondrive(-230, drivepower);
}

void LeftBlueTwenty()
{
	//--------------------------//
	setIntakePower(20);                   //
	//liftRRequestedValue = 1880;    We don't need this       // PRESETS

	liftRRequestedValue = SkillsLift;
	wait1Msec(250);
	mobileRRequestedValue = mobileOut;
	//WaitieThing();

	setChainPower(20);

	Atondrive(650, 127);

	wait1Msec(200);

	//chainRRequestedValue = StraitUpChain;
	liftRRequestedValue = ParallelLift;
	wait1Msec(1);
	mobileRRequestedValue = mobileIn;
	WaitieThing();

	liftRRequestedValue = SkillsLift + 350;
	wait1Msec(200);

	setIntakePower(-127);                   //
	wait1Msec(300);
	setIntakePower(0);                   //

	liftRRequestedValue = ParallelLift;

	setChainPower(127);
	wait1Msec(600);
	setChainPower(0);

	setDrivePower(70,30);
	wait1Msec(120);
	setDrivePower(0,0);
	Atondrive(100, 120);

	AutoStackUp(); 											//Second Cone pickup
/*
	setDrivePower(50,50);
	wait1Msec(120);
	setDrivePower(0,0);
	Atondrive(100, 120);

	AutoStackUp(); 											//Second Cone pickup

	setChainPower(-127);
	wait1Msec(700);
	setChainPower(-15);

	liftRRequestedValue = 2200;
	wait1Msec(500);
	setLiftPower(-20);

	setDrivePower(50,50);
	wait1Msec(120);
	setDrivePower(0,0);
	Atondrive(100, 120);

	AutoStackUp(); 											//Second Cone pickup*/


			Atondrive(-650, 127);
			wait1Msec(200);

			TurnPID(NineP/2, true);
			setIntakePower(0);                   //

			Atondrive(-300, 127);

			liftRRequestedValue = 2000;

			TurnPID(NineP+30, true);

			Atondrive(285, 127);

			setDrivePower(40,40);

			mobileRRequestedValue = mobileOut;
			WaitieThing();

			mobileRRequestedValue = mobileIn;

			Atondrive(-230, drivepower);
}

void RightRedTwenty()
{
	//--------------------------//
	setIntakePower(20);                   //
	liftRRequestedValue = 1880;           // PRESETS

	liftRRequestedValue = SkillsLift;

	mobileRRequestedValue = mobileOut;
	//WaitieThing();

	setChainPower(20);

	Atondrive(650, 127);

	wait1Msec(200);

	//chainRRequestedValue = StraitUpChain;
	liftRRequestedValue = ParallelLift;
	wait1Msec(1);
	mobileRRequestedValue = mobileIn;
	WaitieThing();

	liftRRequestedValue = SkillsLift + 350;
	wait1Msec(200);

	setIntakePower(-127);                   //
	wait1Msec(300);
	setIntakePower(0);                   //

	liftRRequestedValue = ParallelLift;

	setChainPower(127);
	wait1Msec(600);
	setChainPower(0);

	setDrivePower(30,80);
	wait1Msec(120);
	setDrivePower(0,0);
	Atondrive(100, 120);

	AutoStackUp(); 											//Second Cone pickup
/*
	setDrivePower(50,50);
	wait1Msec(120);
	setDrivePower(0,0);
	Atondrive(100, 120);

	AutoStackUp(); 											//Second Cone pickup

	setChainPower(-127);
	wait1Msec(700);
	setChainPower(-15);

	liftRRequestedValue = 2200;
	wait1Msec(500);
	setLiftPower(-20);

	setDrivePower(50,50);
	wait1Msec(120);
	setDrivePower(0,0);
	Atondrive(100, 120);

	AutoStackUp(); 											//Second Cone pickup*/


			Atondrive(-650, 127);
			wait1Msec(200);

			TurnPID(-NineP/2, true);
			setIntakePower(0);                   //

			Atondrive(-310, 127);

			liftRRequestedValue = 2000;

			TurnPID(-NineP-30, true);

			Atondrive(285, 127);

			setDrivePower(40,40);

			mobileRRequestedValue = mobileOut;
			WaitieThing();

			mobileRRequestedValue = mobileIn;

			Atondrive(-230, drivepower);
}

void LeftRedTwenty()
{
	//--------------------------//
	setIntakePower(20);                   //
	liftRRequestedValue = 1880;           // PRESETS

	liftRRequestedValue = SkillsLift;

	mobileRRequestedValue = mobileOut;
	//WaitieThing();

	setChainPower(20);

	Atondrive(650, 127);

	wait1Msec(200);

	//chainRRequestedValue = StraitUpChain;
	liftRRequestedValue = ParallelLift;
	wait1Msec(1);
	mobileRRequestedValue = mobileIn;
	WaitieThing();

	liftRRequestedValue = SkillsLift + 350;
	wait1Msec(200);

	setIntakePower(-127);                   //
	wait1Msec(300);
	setIntakePower(0);                   //

	liftRRequestedValue = ParallelLift;

	setChainPower(127);
	wait1Msec(600);
	setChainPower(0);

	setDrivePower(70,30);
	wait1Msec(120);
	setDrivePower(0,0);
	Atondrive(100, 120);

	AutoStackUp(); 											//Second Cone pickup
/*
	setDrivePower(50,50);
	wait1Msec(120);
	setDrivePower(0,0);
	Atondrive(100, 120);

	AutoStackUp(); 											//Second Cone pickup

	setChainPower(-127);
	wait1Msec(700);
	setChainPower(-15);

	liftRRequestedValue = 2200;
	wait1Msec(500);
	setLiftPower(-20);

	setDrivePower(50,50);
	wait1Msec(120);
	setDrivePower(0,0);
	Atondrive(100, 120);

	AutoStackUp(); 											//Second Cone pickup*/


			Atondrive(-750, 127);
			wait1Msec(200);

			TurnPID(NineP/2, true);
			setIntakePower(0);                   //

			Atondrive(-310, 127);

			liftRRequestedValue = 2000;

			TurnPID(NineP+30, true);

			Atondrive(285, 127);

			setDrivePower(40,40);

			mobileRRequestedValue = mobileOut;
			WaitieThing();

			mobileRRequestedValue = mobileIn;

			Atondrive(-230, drivepower);
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

			setChainPower(20);

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

			Atondrive(160, drivepower);

			mobileRRequestedValue = mobileOut;

			TurnPID(-NineP, true);

			//mobileRRequestedValue = mobileOut;
			//WaitieThing();

			/*setDrivePower(-30,-30);
			wait1Msec(1200);*/

			Atondrive(320, drivepower);

			mobileRRequestedValue = mobileIn;
			wait1Msec(400);
			Atondrive(-260, drivepower);

			TurnPID(-FullP+30, true);

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

			Atondrive(448, drivepower);

			mobileRRequestedValue = mobileIn;
			wait1Msec(500);

			TurnPID(-NineP-10, true);

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
			TurnPID(FullP+25, true);

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
			Atondrive(-530, drivepower);

			mobileRRequestedValue = mobileMid;

			TurnPID(NineP-10, true);

			mobileRRequestedValue = mobileOut;
			WaitieThing();

			Atondrive(460, drivepower);

			mobileRRequestedValue = mobileIn;
			wait1Msec(500);

			TurnPID(-NineP-35, true);

			Atondrive(580, drivepower);
			//setDrivePower(20,20);

			mobileRRequestedValue = mobileOut;
			WaitieThing();
			Atondrive(-120, drivepower);
			//------------------------------------------- Place 6th
			TurnPID(1305 , true);

			Atondrive(605, 127);

			mobileRRequestedValue = mobileIn;
			wait1Msec(200);

			Atondrive(-570, 127);

			TurnPID(-NineP/2, true);
			setIntakePower(0);                   //

			Atondrive(-255, 127);

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
	//------------------------------------------------------------//
			setIntakePower(15);                   //
			liftRRequestedValue = 2000;
			wait1Msec(700);
			mobileRRequestedValue = mobileOut;

			setChainPower(20);

			Atondrive(770, 127);

			mobileRRequestedValue = mobileIn;
			wait1Msec(200);

			Atondrive(-750, 127);
			liftRRequestedValue = 2600;
			wait1Msec(300);
			setIntakePower(-127);                   //
			liftRRequestedValue = 2000;

			TurnPID(-1110, true);
			setIntakePower(0);                   //

			Atondrive(285, 127);

			setDrivePower(40,40);

			mobileRRequestedValue = mobileOut;
			WaitieThing();

			mobileRRequestedValue = mobileIn;
			//------------------------------------------- Place 2nd
			Atondrive(-230, drivepower);

			mobileRRequestedValue = mobileOut;
			TurnPID(-1191, true);

			Atondrive(857, drivepower);

			mobileRRequestedValue = mobileIn;
			wait1Msec(600);

			Atondrive(-730, drivepower);

			/// // / // / //


			//------------------------------------------- Place 3rd
			Atondrive(-10, drivepower);

			TurnPID(-NineP, true);

			Atondrive(180, drivepower);

			mobileRRequestedValue = mobileOut;

			TurnPID(-NineP, true);

			//mobileRRequestedValue = mobileOut;
			//WaitieThing();

			/*setDrivePower(-30,-30);
			wait1Msec(1200);*/

			Atondrive(300, drivepower);

			mobileRRequestedValue = mobileIn;
			wait1Msec(400);
			Atondrive(-250, drivepower);

			TurnPID(-FullP+30, true);

			Atondrive(105, 127);

			//setDrivePower(40,40);

			mobileRRequestedValue = mobileOut;
			WaitieThing();
			//------------------------------------------- Place 4th
			Atondrive(-530, drivepower);

			mobileRRequestedValue = mobileMid;

			TurnPID(NineP-10, true);

			mobileRRequestedValue = mobileOut;
			WaitieThing();

			Atondrive(470, drivepower);

			mobileRRequestedValue = mobileIn;
			wait1Msec(500);

			TurnPID(-NineP-20, true);

			Atondrive(580, drivepower);
			//setDrivePower(40,40);

			mobileRRequestedValue = mobileOut;
			WaitieThing();
			Atondrive(-100, drivepower);
			mobileRRequestedValue = mobileMid-100;
			//setDrivePower(40,40);
			wait1Msec(300);

			//Atondrive(-170, drivepower);

			//------------------------------------------- Place 5rd
			TurnPID(FullP+50, true);

			mobileRRequestedValue = mobileOut;

			//////////////
			//setDrivePower(-80,-80);
			//wait1Msec(2000);
			//////////////

			Atondrive(760, drivepower);

			mobileRRequestedValue = mobileMid;

			Atondrive(670, drivepower);

			mobileRRequestedValue = mobileOut;
			WaitieThing();
			//------------------------------------------- Place 6th
			Atondrive(-530, drivepower);

			mobileRRequestedValue = mobileMid;

			TurnPID(NineP-10, true);

			mobileRRequestedValue = mobileOut;
			WaitieThing();

			Atondrive(470, drivepower);

			mobileRRequestedValue = mobileIn;
			wait1Msec(500);

			TurnPID(-NineP-20, true);

			Atondrive(580, drivepower);
			//setDrivePower(40,40);

			mobileRRequestedValue = mobileOut;
			WaitieThing();
			Atondrive(-100, drivepower);
			//------------------------------------------- Place 7th
			TurnPID(1315 , true);

			Atondrive(595, 127);

			mobileRRequestedValue = mobileIn;
			wait1Msec(200);

			Atondrive(-560, 127);

			TurnPID(-NineP/2, true);
			setIntakePower(0);                   //

			Atondrive(-265, 127);

			TurnPID(-NineP-30, true);

			Atondrive(285, 127);

			setDrivePower(40,40);

			mobileRRequestedValue = mobileOut;
			WaitieThing();

			Atondrive(-10, 127);

			mobileRRequestedValue = mobileIn;
			//------------------------------------------- Place 8th
			Atondrive(-230, drivepower);

			mobileRRequestedValue = mobileOut;
			TurnPID(-1191, true);

			Atondrive(857, drivepower);

			mobileRRequestedValue = mobileIn;
			wait1Msec(600);

			Atondrive(-730, drivepower);

			TurnPID(FullP, true);

			//Atondrive(-210, drivepower);

			//TurnPID(-NineP-10, true);

			setDrivePower(60,60);

			mobileRRequestedValue = mobileOut;
			WaitieThing();

			Atondrive(-150, drivepower);

			TurnPID(200, true);

			Atondrive(-800, drivepower);
}
//#endregion
//#region Other Programs
void Defensive ()
{
	setIntakePower(15);                   //
	liftRRequestedValue = 2000;
	wait1Msec(700);
	mobileRRequestedValue = mobileIn;

	setChainPower(20);

	Atondrive(100, drivepower);

	TurnPID(NineP/2,true);

//	mobileRRequestedValue = mobileOut;

	Atondrive(600*1.25, drivepower);

	Atondrive(-150*1.25 , drivepower);
	mobileRRequestedValue = mobileOut;
	TurnPID(NineP/2-50,true);
	wait1Msec(250);

	Atondrive(300, drivepower);

	mobileRRequestedValue = mobileIn;
	WaitieThing();
	liftRRequestedValue = SkillsLift + 350;
	wait1Msec(200);

	setIntakePower(-127);                   //
	wait1Msec(300);
	setIntakePower(0);
	liftRRequestedValue = 2000;                //

}

void DoNothing ()
{
	setIntakePower(15);                   //
	liftRRequestedValue = 1500;
	wait1Msec(100);

	Atondrive(1000000000, 127);
	Atondrive(-1000000000, 127);

}

void DefensiveTwo ()
{

		setIntakePower(15);                   //
		liftRRequestedValue = 2000;
		wait1Msec(700);
		mobileRRequestedValue = mobileIn;

		setChainPower(20);

		Atondrive(140, drivepower);

		TurnPID(-NineP/2,true);

	//	mobileRRequestedValue = mobileOut;

		Atondrive(600*1.25, drivepower);

		Atondrive(-150*1.25 , drivepower);
		mobileRRequestedValue = mobileOut;
		TurnPID(-NineP/2+100,true);
		wait1Msec(250);

		Atondrive(300, drivepower);

		mobileRRequestedValue = mobileIn;
		WaitieThing();
		liftRRequestedValue = SkillsLift + 350;
		wait1Msec(200);

		setIntakePower(-127);                   //
		wait1Msec(300);
		setIntakePower(0);                   //
		liftRRequestedValue = 2000;
}

void DoNothingTwo ()
{
}
void SpecialAton()
{
	setDrivePower(127 , 127);
	wait1Msec(5000);
	setDrivePower(0 , 0);
}
//_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_//
//#endregion
//<editor-fold


//</editor-fold>
