#include "BackOver Functions 2017-18.c"
#include "Drive PID.c"
//#region Variables
//-------------Variables--------------//
// Random variable for turn and drive
int Nine = 750;
int full = 1750;
int drivepower = 127;
int NineP = 930;
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

	setDrivePower(80,30);
	wait1Msec(120);
	setDrivePower(0,0);
	Atondrive(100, 120);

	AutoStackUp(); 											//Second Cone pickup

	Atondrive(-600, drivepower);

	turnRight(1175);

	setDrivePower(10,10);							  // Set drive still speed

	mobileRRequestedValue = mobileOut;  // Outake mobile goal
	WaitieThing();										  // Wait for Mobile Goal

	Atondrive(-475, drivepower);        // Drive backwards for 2nd Goal

	turnRight(1200);										// Turn to Goal

	Atondrive(250, drivepower);         // Drive into Goal

	mobileRRequestedValue = mobileIn;
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

	setDrivePower(80,30);
	wait1Msec(120);
	setDrivePower(0,0);
	Atondrive(100, 120);

	AutoStackUp(); 											//Second Cone pickup

	Atondrive(-620, drivepower);

	turnLeft(1200);

	setDrivePower(10,10);							  // Set drive still speed

	mobileRRequestedValue = mobileOut;  // Outake mobile goal
	WaitieThing();										  // Wait for Mobile Goal

	Atondrive(-550, drivepower);        // Drive backwards for 2nd Goal

	turnLeft(1175);											// Turn to Goal

	Atondrive(220, drivepower);         // Drive into Goal

	mobileRRequestedValue = mobileIn;
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

	setDrivePower(90,30);
	wait1Msec(120);
	setDrivePower(0,0);
	Atondrive(100, 120);

	AutoStackUp(); 											//Second Cone pickup

	Atondrive(-620, drivepower);

	turnRight(1175);

	setDrivePower(10,10);							  // Set drive still speed

	mobileRRequestedValue = mobileOut;  // Outake mobile goal
	WaitieThing();										  // Wait for Mobile Goal

	Atondrive(-500, drivepower);        // Drive backwards for 2nd Goal

	turnRight(1125);										// Turn to Goal

	Atondrive(250, drivepower);         // Drive into Goal

	mobileRRequestedValue = mobileIn;
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

	setDrivePower(80,30);
	wait1Msec(120);
	setDrivePower(0,0);
	Atondrive(100, 120);

	AutoStackUp(); 											//Second Cone pickup

	Atondrive(-600, drivepower);

	turnLeft(1200);

	setDrivePower(10,10);							  // Set drive still speed

	mobileRRequestedValue = mobileOut;  // Outake mobile goal
	WaitieThing();										  // Wait for Mobile Goal

	Atondrive(-550, drivepower);        // Drive backwards for 2nd Goal

	turnLeft(1150);											// Turn to Goal

	Atondrive(220, drivepower);         // Drive into Goal

	mobileRRequestedValue = mobileIn;
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

	setDrivePower(80,30);
	wait1Msec(120);
	setDrivePower(0,0);
	Atondrive(100, 120);

	AutoStackUp(); 											//Second Cone pickup

	//--------------------------//

	Atondrive(-650, 127);

	liftRRequestedValue = ParallelLift;

	turnRight(Nine+250);

	setDrivePower(80,80);
	wait1Msec(200);
	setDrivePower(0,0);

	mobileRRequestedValue = mobileOut;
	WaitieThing();

	Atondrive(-120, drivepower);

	liftRRequestedValue = SkillsLift;

	//--------------------------//

	turnRight(110);

	Atondrive(-300, drivepower);

	turnLeft(150);

	setDrivePower(-127,-127);
	wait1Msec(500);

	setDrivePower(-80,-80);
	wait1Msec(1800);
	setDrivePower(0,0);
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

	Atondrive(-650, 127);

	liftRRequestedValue = ParallelLift;

	turnLeft(full-410);

	Atondrive(75, 127);

	mobileRRequestedValue = mobileOut;
	WaitieThing();

	Atondrive(-200, drivepower);

	liftRRequestedValue = SkillsLift;

	//--------------------------//

	turnLeft(110);

	Atondrive(-250, drivepower);

	turnRight(150);

	setDrivePower(-127,-127);
	wait1Msec(500);

	setDrivePower(-80,-80);
	wait1Msec(1800);
	setDrivePower(0,0);
}

void RightRedTen()
{
	//--------------------------//
	setIntakePower(20);                   //
	liftRRequestedValue = 1880;           // PRESETS

	liftRRequestedValue = SkillsLift;
	wait1Msec(300);
	mobileRRequestedValue = mobileOut;
	//WaitieThing();

	setChainPower(20);

	Atondrive(730, 127);

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
	Atondrive(100, 120);

	AutoStackUp(); 											//Second Cone pickup

	//--------------------------//

	Atondrive(-625, 127);

	liftRRequestedValue = ParallelLift;

	turnRight(full-500);

	Atondrive(110, 127);

	mobileRRequestedValue = mobileOut;
	WaitieThing();

	Atondrive(-120, drivepower);

	liftRRequestedValue = SkillsLift;

	//--------------------------//

	turnRight(110);

	Atondrive(-300, drivepower);

	turnLeft(150);

	setDrivePower(-127,-127);
	wait1Msec(500);

	setDrivePower(-80,-80);
	wait1Msec(1800);
	setDrivePower(0,0);
}

void LeftRedTen()
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

	setDrivePower(80,30);
	wait1Msec(120);
	setDrivePower(0,0);
	Atondrive(100, 120);

	AutoStackUp(); 											//Second Cone pickup

	//--------------------------//

	Atondrive(-675, 127);

	liftRRequestedValue = ParallelLift;

	turnLeft(full-500);

	setDrivePower(100,100);
	wait1Msec(260);
	setDrivePower(0,0);

	mobileRRequestedValue = mobileOut;
	WaitieThing();

	Atondrive(-120, drivepower);

	liftRRequestedValue = SkillsLift;

	//--------------------------//

	turnLeft(110);

	Atondrive(-300, drivepower);

	turnRight(150);

	setDrivePower(-127,-127);
	wait1Msec(500);

	setDrivePower(-80,-80);
	wait1Msec(1800);
	setDrivePower(0,0);
}

//#endregion
//#region Score 20's
void RightBlueTwenty() // Auton task to grab moble base on the right and score it
{
	//------------------------------------------------------------//
			setIntakePower(15);                   //
			liftRRequestedValue = 2000;
			wait1Msec(500);
			mobileRRequestedValue = mobileOut;

			setChainPower(20);

			Atondrive(750, 127);				//Drive to Mobile Goal

			mobileRRequestedValue = mobileIn;
			wait1Msec(150);

			Atondrive(-610, 100);       //Drive Back to Start
			liftRRequestedValue = 2600; //Deposit Cone
			wait1Msec(200);
			setIntakePower(-127);                   //

			TurnPID(-NineP/2, true);
			setIntakePower(0);                   //
 
			Atondrive(-300, 127);				//Drive to Middle

			liftRRequestedValue = 2100;

			TurnPID(-NineP+10, true);

			Atondrive(285, 127);

			setDrivePower(40,40);

			mobileRRequestedValue = mobileOut;
			WaitieThing();

			Atondrive(-70, drivepower);         // Drive 175 encoder clicks

			mobileRRequestedValue = mobileIn;
			WaitieThing();											 // Wait for Mobile Goal

			Atondrive(-190, drivepower);
}

void LeftBlueTwenty()
{
	//------------------------------------------------------------//
			setIntakePower(15);                   //
			liftRRequestedValue = 2000;
			wait1Msec(500);
			mobileRRequestedValue = mobileOut;

			setChainPower(20);

			Atondrive(650, 127);				//Drive to Mobile Goal

			mobileRRequestedValue = mobileIn;
			wait1Msec(100);

			Atondrive(-600, 127);       //Drive Back to Start
			liftRRequestedValue = 2600; //Deposit Cone
			wait1Msec(200);
			setIntakePower(-127);                   //

			TurnPID(NineP/2, true);
			setIntakePower(0);                   //

			Atondrive(-275, 127);				//Drive to Middle

			liftRRequestedValue = 2100;

			TurnPID(NineP+10, true);

			Atondrive(285, 127);

			setDrivePower(40,40);

			mobileRRequestedValue = mobileOut;
			WaitieThing();

			Atondrive(-75, drivepower);         // Drive 175 encoder clicks

			mobileRRequestedValue = mobileIn;
			WaitieThing();											 // Wait for Mobile Goal

			Atondrive(-190, drivepower);
}

void RightRedTwenty()
{
<<<<<<< HEAD
	//--------------------------//
	liftRRequestedValue = ParallelLift;           // PRESETS
	mobileRRequestedValue = mobileIn;     //

	mobileRRequestedValue = mobileOut;
	WaitieThing();

	setChainPower(20);

	Atondrive(660, 127);

	wait1Msec(200);

	liftRRequestedValue = SkillsLift;
	//chainRRequestedValue = OutPositionChain; //score pre-load

	//chainRRequestedValue = StraitUpChain;
	liftRRequestedValue = ParallelLift;
	wait1Msec(1);
	mobileRRequestedValue = mobileIn;
	WaityThing();

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
	Atondrive(100, 120);

	AutoStackUp(); 											//Second Cone pickup

	//--------------------------//

	Atondrive(-580, 127);

	liftRRequestedValue = SkillsLift;
	wait1Msec(200);
=======
	//------------------------------------------------------------//
			setIntakePower(15);                   //
			liftRRequestedValue = 2000;
			wait1Msec(500);
			mobileRRequestedValue = mobileOut;
>>>>>>> 7a5e5fcee9b806fa2305c7d632b9bc97d8b957ea

			setChainPower(20);

			Atondrive(650, 127);				//Drive to Mobile Goal

			mobileRRequestedValue = mobileIn;
			wait1Msec(100);

			Atondrive(-600, 127);       //Drive Back to Start
			liftRRequestedValue = 2600; //Deposit Cone
			wait1Msec(200);
			setIntakePower(-127);                   //

			TurnPID(-NineP/2, true);
			setIntakePower(0);                   //

			Atondrive(-275, 127);				//Drive to Middle

			liftRRequestedValue = 2100;

			TurnPID(-NineP+10, true);

			Atondrive(285, 127);

			setDrivePower(40,40);

			mobileRRequestedValue = mobileOut;
			WaitieThing();

			Atondrive(-75, drivepower);         // Drive 175 encoder clicks

			mobileRRequestedValue = mobileIn;
			WaitieThing();											 // Wait for Mobile Goal

			Atondrive(-190, drivepower);
}

void LeftRedTwenty()
{
	//------------------------------------------------------------//
			setIntakePower(15);                   //
			liftRRequestedValue = 2000;
			wait1Msec(500);
			mobileRRequestedValue = mobileOut;

			setChainPower(20);

			Atondrive(750, 127);				//Drive to Mobile Goal

			mobileRRequestedValue = mobileIn;
			wait1Msec(150);

			Atondrive(-610, 100);       //Drive Back to Start
			liftRRequestedValue = 2600; //Deposit Cone
			wait1Msec(200);
			setIntakePower(-127);                   //

			TurnPID(NineP/2, true);
			setIntakePower(0);                   //

			Atondrive(-300, 127);				//Drive to Middle

			liftRRequestedValue = 2100;

			TurnPID(NineP+10, true);

			Atondrive(285, 127);

			setDrivePower(40,40);

			mobileRRequestedValue = mobileOut;
			WaitieThing();

			Atondrive(-70, drivepower);         // Drive 175 encoder clicks

			mobileRRequestedValue = mobileIn;
			WaitieThing();											 // Wait for Mobile Goal

			Atondrive(-190, drivepower);
}
//#endregion
//#region Score Special's
void SkillsOne ()
{
	Preload();
//////////////////////////////////Section 1 -score first mobile goal
	liftRRequestedValue = SkillsLift;           // PRESETS

	mobileRRequestedValue = mobileIn;    // Intake mobile goal
	WaitieThing();											 // Wait for Mobile Goal

	Atondrive(-265, drivepower);         // Drive back 265 encoder clicks

	turnLeft(Nine+50);

	Atondrive(200, drivepower);         // Drive 175 encoder clicks

	turnLeft(Nine+100);

	Atondrive(300, drivepower);         // Drive 300 encoder clicks

	setDrivePower(20,20);							  // Set drive still speed

	mobileRRequestedValue = mobileOut;  // Outake mobile goal
	WaitieThing();										  // Wait for Mobile Goal

	Atondrive(-75, drivepower);         // Drive 175 encoder clicks

	mobileRRequestedValue = mobileIn;
	WaitieThing();											 // Wait for Mobile Goal

/////////////////////////////////////////Section 2 - Grab mobile goal 2
	Atondrive(-190, drivepower);         // Drive back 190 encoder clicks

	turnLeft(Nine+50);

	Atondrive(210, drivepower);         // Drive 190 encoder clicks

	turnLeft(Nine+50);

	setDrivePower(-40, -40);            // Dead Recon to bar for accuracy
	wait1Msec(800);
	setDrivePower(-20, -30);
	wait1Msec(600);

	mobileRRequestedValue = mobileOut;  // Set mobile postion to OUT

	Atondrive(860, drivepower);         // Drive 850 encoder clicks

	mobileRRequestedValue = mobileMid;  // Mobile to go half up to save time
	WaitieThing();											 // Wait for Mobile Goal

	Atondrive(650, drivepower);         // Drive 550 encoder clicks

	turnLeft(Nine);

	Atondrive(200, drivepower);         // Drive 180 encoder clicks

	turnRight(Nine);

	Atondrive(320, drivepower);         // Drive 250 encoder clicks

	setDrivePower(110, 110);              // Dead Recon to bar for accuracy
	wait1Msec(300);
	setDrivePower(15, 15);

	mobileRRequestedValue = mobileOut;  // Set Mobile goal out
	WaitieThing();                      // Wait until mobile is out

	Atondrive(-100, drivepower);         // Drive back 50 encoder clicks

	mobileRRequestedValue = mobileMid;  // Set Mobile goal to middle position
	WaitieThing();                      // Wait untill mobile is in postion

	Atondrive(-150, drivepower);         // Drive back 150 encoder clicks

	//////////////////////////////////////////////// Score 3rd

	turnLeft(Nine);

	Atondrive(220, drivepower);         // Drive 220 encoder clicks

	turnLeft(Nine+120);

	mobileRRequestedValue = mobileOut+10;  // Set Mobile goal Out
	WaitieThing();                      // Wait until mobile goal is out

	setDrivePower(-30, -40);            // Dead Recon to bar for accuracy
	wait1Msec(1000);
	setDrivePower(0, 0);

	Atondrive(550, drivepower);         // Drive 420 encoder clicks

	mobileRRequestedValue = mobileMid;  // Set mobile goal OUT
	WaitieThing();                      // Wait until mobile goal is out

	turnRight(full);

	Atondrive(520, drivepower);         // Drive 450 encoder clicks

	mobileRRequestedValue = mobileOut;  // Set Mobile goal Out
	WaitieThing();                      // Wait until mobile goal is out

	Atondrive(-50, drivepower);         // Drive back 40 encoder clicks

	mobileRRequestedValue = mobileMid;  // Set mobile goal to middle position
	Atondrive(-50, drivepower);         // Drive back 50 encoder clicks
/////////////////////////////////////////////// Score 4th

	turnLeft(full+50);

	mobileRRequestedValue = mobileOut;  // Set mobile goal out

	setDrivePower(-30, -40);            // Dead recon to bar for accuacy
	wait1Msec(1600);
	setDrivePower(0, 0);

	setMobilePower(20);

	Atondrive(850, drivepower);         // Drive 800 encoder clicks

	mobileRRequestedValue = mobileMid;  // Pick up final Mobile goal

	Atondrive(800, drivepower);         // Drive 600 encoder clicks

	mobileRRequestedValue = mobileOut;  // Set Mobile goal Out to place in 10pt
	WaitieThing();                      // Wait until mobile goal is out

	Atondrive(-100, 100);        			  // Drive back 20 encoder clicks

///////////////////////////////////////// 5th

	mobileRRequestedValue = mobileMid;  // Bring lift in so it can turn around
	WaitieThing();											// Wait until it does so

	mobileRRequestedValue = mobileOut;  // Multi task to save time/outtake

	turnRight(Nine+360);

	Atondrive(600, drivepower);         // Drive 600 encoder clicks

	mobileRRequestedValue = mobileMid;  // Pick up Mobile goal
	WaitieThing();                      // Wait until picked up

	Atondrive(-600, drivepower);         // Drive 600 backwards encoder clicks

	turnLeft(full+300);

	Atondrive(350, drivepower);         // Drive 100 encoder clicks

	turnRight(Nine);

	Atondrive(100, drivepower);

	mobileRRequestedValue = mobileOut;  // Set Mobile goal Out to place in 10pt
	WaitieThing();
////////////////////////////////////////////////

	Atondrive(-100, drivepower);

	mobileRRequestedValue = mobileMid;  // Bring lift in so it can turn around
	WaitieThing();											// Wait until it does so

	turnLeft(Nine+300);

	mobileRRequestedValue = mobileOut;  // Set Mobile goal Out to place in 10pt
	WaitieThing();

	Atondrive(900, drivepower);

	mobileRRequestedValue = mobileMid;  // Bring lift in so it can turn around
	WaitieThing();											// Wait until it does so

	Atondrive(-600, drivepower);

	turnRight(Nine+250);

	Atondrive(100, drivepower);

	mobileRRequestedValue = mobileOut;  // Bring lift in so it can turn around
}

void SkillsTwo ()
{
	//------------------------------------------------------------//
			setIntakePower(15);                   //
			liftRRequestedValue = 2000;
			wait1Msec(500);
			mobileRRequestedValue = mobileOut;

			setChainPower(20);

			Atondrive(650, 127);

			mobileRRequestedValue = mobileIn;
			wait1Msec(100);

			Atondrive(-600, 127);
			liftRRequestedValue = 2600;
			wait1Msec(200);
			setIntakePower(-127);                   //

			TurnPID(-NineP/2, true);
			setIntakePower(0);                   //

			Atondrive(-260, 127);

			liftRRequestedValue = 2000;

			TurnPID(-NineP+10, true);

			Atondrive(285, 127);

			setDrivePower(40,40);

			mobileRRequestedValue = mobileOut;
			WaitieThing();

			mobileRRequestedValue = mobileIn;
			//------------------------------------------- Place 2nd
			Atondrive(-230, drivepower);

			TurnPID(-NineP, true);

			Atondrive(185, drivepower);

			TurnPID(-NineP, true);

			mobileRRequestedValue = mobileOut;
			WaitieThing();

			Atondrive(400, drivepower);

			mobileRRequestedValue = mobileIn;
			wait1Msec(150);
			Atondrive(-250, drivepower);

			TurnPID(FullP+40, true);

			Atondrive(90, 127);

			setDrivePower(40,40);

			mobileRRequestedValue = mobileOut;
			WaitieThing();
			//------------------------------------------- Place 3rd
			Atondrive(-500, drivepower);

			mobileRRequestedValue = mobileMid;

			TurnPID(NineP-10, true);

			mobileRRequestedValue = mobileOut;
			WaitieThing();

			Atondrive(460, drivepower);

			mobileRRequestedValue = mobileIn;

			TurnPID(-NineP-50, true);

			Atondrive(600, drivepower);
			setDrivePower(40,40);

			mobileRRequestedValue = mobileOut;
			WaitieThing();

			Atondrive(-250, drivepower);

			mobileRRequestedValue = mobileMid;

			//------------------------------------------- Place 4rd
			TurnPID(FullP, true);

			mobileRRequestedValue = mobileOut;

			//////////////
			setDrivePower(-100,-100);
			wait1Msec(2000);
			//////////////

			Atondrive(700, drivepower);

			mobileRRequestedValue = mobileIn;

			Atondrive(485, drivepower);

			TurnPID(NineP, true)

			Atondrive(200, drivepower);

			TurnPID(-NineP, true)

			Atondrive(275, 127);

			setDrivePower(110,110);
			wait1Msec(1000);
			setDrivePower(40,40);

			mobileRRequestedValue = mobileOut;
			WaitieThing();

			mobileRRequestedValue = mobileIn;
			//------------------------------------------- Place 5nd
			Atondrive(-175, drivepower);



/*
			//chainRRequestedValue = StraitUpChain;
			liftRRequestedValue = ParallelLift;
			wait1Msec(1);
			mobileRRequestedValue = mobileIn;
			WaityThing();

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
			Atondrive(100, 120);

			AutoStackUp(); 											//Second Cone pickup

			//--------------------------//

			Atondrive(-600, 127);

			liftRRequestedValue = SkillsLift;
			wait1Msec(200);


			setIntakePower(-127);                   //
			wait1Msec(250);
			setIntakePower(0);                   //

			liftRRequestedValue = ParallelLift;

			turnRight(Nine/2-100);

			Atondrive(-200, 127);

			turnRight(Nine);

			Atondrive(300, drivepower);         // Drive 300 encoder clicks

			setDrivePower(20,20);							  // Set drive still speed

			mobileRRequestedValue = mobileOut;  // Outake mobile goal
			WaitieThing();										  // Wait for Mobile Goal

			Atondrive(-75, drivepower);         // Drive 175 encoder clicks

			mobileRRequestedValue = mobileIn;
			WaitieThing();											 // Wait for Mobile Goal

			Atondrive(-190, drivepower);         // Drive back 190 encoder clicks*/
	//------------------------------------------------------------//
}
//#endregion
//#region Other Programs
void Defensive ()
{
	mobileRRequestedValue = mobileIn;     //
	liftRRequestedValue = ParallelLift;           // PRESETS

	Atondrive(500,127);
}

void DoNothing ()
{
	mobileRRequestedValue = mobileIn;     //
	liftRRequestedValue = ParallelLift;           // PRESETS

	wait1Msec(1000);

	AutoStackUp();
}

void DefensiveTwo ()
{
	setDrivePower(127 , 127);
	wait1Msec(5000);
	setDrivePower(0 , 0);
}

void DoNothingTwo ()
{
}
void SpecialAton()
{
}
//_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_//
//#endregion
//<editor-fold


//</editor-fold>
