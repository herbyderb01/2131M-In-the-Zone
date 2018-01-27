#include "BackOver Functions 2017-18.c"
//#include "Drive PID.c"
//#region Variables
//-------------Variables--------------//
// Random variable for turn and drive
int Nine = 750;
int full = 1750;
int drivepower = 127;
float  liftRSensorCurrentValue;																																//GO LINE TRACK YOURSELF.

// PID Mobile Variables
int mobileIn = 955;
int mobileOut = 3260;
int mobileMid = 1860;
int mobileSMid = 2770;
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
{/*
	while(true)
	{
	setDrivePower(vexRT[Ch3],vexRT[Ch2]);
	}
	*/
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

		wait1Msec(25); //dont hog cpu
	}


//_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_//
//#endregion
//#region Special Auto Stack Voids
//--------------------Special Auto Stack Voids-----------------------//
/*
void AutoStackUp()									// Simple Auto stack cone up
{
	//Atondrive(1000, 100);
}

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
	liftRRequestedValue = 2600;           // PRESETS
	mobileRRequestedValue = mobileIn;     //

	mobileRRequestedValue = mobileOut;   // Open Mobile goal to grab 1st goal
	WaitieThing();											 // Wait for Mobile Goal
	setMobilePower(15);

	Atondrive(380, 127);								 // Drive forward for 380 encoder clicks

	wait1Msec(200);                      // Delay

	//chainRRequestedValue = OutPositionChain; //score pre-load

	mobileRRequestedValue = mobileIn;
	WaitieThing();											 // Wait for Mobile Goal

	liftRRequestedValue = 3000;

	setChainPower(127);
	wait1Msec(250);
	setChainPower(15);

	setIntakePower(-127);
	wait1Msec(500);
	setIntakePower(0);

	//chainRRequestedValue = StraitUpChain;// Set Chain to strait up

}
//#endregion
//#region Blue Aton Programs
void RightBlue () // Auton task to grab moble base on the right and score it
{
	//--------------------------//
	setIntakePower(15);                   //
	liftRRequestedValue = 2600;           // PRESETS
	mobileRRequestedValue = mobileIn;     //

	mobileRRequestedValue = mobileOut;
	WaitieThing();

	liftRRequestedValue = 3000;

	setChainPower(20);

	Atondrive(750, 127);

	wait1Msec(200);

	liftRRequestedValue = 2910;
	//chainRRequestedValue = OutPositionChain; //score pre-load

	wait1Msec(1);

	//chainRRequestedValue = StraitUpChain;
	liftRRequestedValue = 2600;
	wait1Msec(1);
	mobileRRequestedValue = mobileIn;
	wait1Msec(600);

	//--------------------------//

	Atondrive(-550, 127);

	liftRRequestedValue = 3000;
	wait1Msec(200);


	setIntakePower(-127);                   //
	wait1Msec(250);
	setIntakePower(0);                   //

	liftRRequestedValue = 2600;

	turnRight(full-400);

	Atondrive(130, 127);

	mobileRRequestedValue = mobileOut;
	WaitieThing();

	Atondrive(-120, drivepower);

	mobileRRequestedValue = mobileIn;
	WaitieThing();

	liftRRequestedValue = 3000;

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

void LeftBlue ()
{
	//--------------------------//
	liftRRequestedValue = 2600;           // PRESETS
	mobileRRequestedValue = mobileIn;     //

	mobileRRequestedValue = mobileOut;
	WaitieThing();

	liftRRequestedValue = 3000;

	setChainPower(20);

	Atondrive(650, 127);

	wait1Msec(200);

	liftRRequestedValue = 2910;
	//chainRRequestedValue = OutPositionChain; //score pre-load

	wait1Msec(540);

	//chainRRequestedValue = StraitUpChain;
	liftRRequestedValue = 2600;
	wait1Msec(1);
	mobileRRequestedValue = mobileIn;
	wait1Msec(500);

	//--------------------------//

	Atondrive(-580, 127);

	liftRRequestedValue = 3000;
	wait1Msec(200);


	setIntakePower(-127);                   //
	wait1Msec(250);
	setIntakePower(0);                   //

	liftRRequestedValue = 2600;


	turnLeft(full-360);

	setDrivePower(60,60);
	wait1Msec(500);
	setDrivePower(0,0);

	mobileRRequestedValue = mobileOut;
	WaitieThing();

	Atondrive(-120, drivepower);

	mobileRRequestedValue = mobileIn;
	WaitieThing();

	//--------------------------//

	turnLeft(150);

	setDrivePower(-127,-127);
	wait1Msec(1500);
	setDrivePower(0,0);

	setDrivePower(40,40);
	wait1Msec(300);
	setDrivePower(0,0);

	turnLeft(Nine+100);
}

void RightBlueTwo () // Auton task to grab moble base on the right and score it
{
	//--------------------------//
	setIntakePower(15);                   //
	liftRRequestedValue = 2600;           // PRESETS
	mobileRRequestedValue = mobileIn;     //

	mobileRRequestedValue = mobileOut;
	WaitieThing();

	liftRRequestedValue = 3000;

	setChainPower(20);

	Atondrive(750, 127);

	wait1Msec(200);

	liftRRequestedValue = 2910;
	//chainRRequestedValue = OutPositionChain; //score pre-load

	wait1Msec(1);

	//chainRRequestedValue = StraitUpChain;
	liftRRequestedValue = 2600;
	wait1Msec(1);
	mobileRRequestedValue = mobileIn;
	wait1Msec(600);

	//--------------------------//

	Atondrive(-600, 127);

	liftRRequestedValue = 3000;
	wait1Msec(200);


	setIntakePower(-127);                   //
	wait1Msec(250);
	setIntakePower(0);                   //

	liftRRequestedValue = 2600;

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

	Atondrive(-190, drivepower);         // Drive back 190 encoder clicks
}

void LeftBlueTwo ()
{
	//--------------------------//
	liftRRequestedValue = 2600;           // PRESETS
	mobileRRequestedValue = mobileIn;     //

	mobileRRequestedValue = mobileOut;
	WaitieThing();

	liftRRequestedValue = 3000;

	setChainPower(20);

	Atondrive(650, 127);

	wait1Msec(200);

	liftRRequestedValue = 2910;
	//chainRRequestedValue = OutPositionChain; //score pre-load

	wait1Msec(540);

	//chainRRequestedValue = StraitUpChain;
	liftRRequestedValue = 2600;
	wait1Msec(1);
	mobileRRequestedValue = mobileIn;
	wait1Msec(500);

	//--------------------------//

	Atondrive(-580, 127);

	liftRRequestedValue = 3000;
	wait1Msec(200);

	setIntakePower(-127);                   //
	wait1Msec(250);
	setIntakePower(0);                   //

	liftRRequestedValue = 2600;

	turnLeft((Nine/2)-100);

	Atondrive(-250, 127);

	turnLeft(Nine);

	Atondrive(300, drivepower);         // Drive 300 encoder clicks

	setDrivePower(20,20);							  // Set drive still speed

	mobileRRequestedValue = mobileOut;  // Outake mobile goal
	WaitieThing();										  // Wait for Mobile Goal

	Atondrive(-75, drivepower);         // Drive 175 encoder clicks

	mobileRRequestedValue = mobileIn;
	WaitieThing();											 // Wait for Mobile Goal

	Atondrive(-190, drivepower);         // Drive back 190 encoder clicks
}

//#endregion
//#region Skills
void SkillsOne ()
{
	Preload();
//////////////////////////////////Section 1 -score first mobile goal
	liftRRequestedValue = 2600;           // PRESETS

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
}
//#endregion
//#region Red Aton Programs
void LeftRed ()
{
	//--------------------------//
	setIntakePower(15);                   //
	liftRRequestedValue = 2600;           // PRESETS
	mobileRRequestedValue = mobileIn;     //

	mobileRRequestedValue = mobileOut;
	WaitieThing();

	liftRRequestedValue = 3000;

	setChainPower(20);

	Atondrive(850, 127);

	wait1Msec(200);

	liftRRequestedValue = 2910;
	//chainRRequestedValue = OutPositionChain; //score pre-load

	wait1Msec(1);

	//chainRRequestedValue = StraitUpChain;
	liftRRequestedValue = 2600;
	wait1Msec(1);
	mobileRRequestedValue = mobileIn;
	wait1Msec(600);

	//--------------------------//

	Atondrive(-800, 127);

	liftRRequestedValue = 3000;
	wait1Msec(200);


	setIntakePower(-127);                   //
	wait1Msec(250);
	setIntakePower(0);                   //

	liftRRequestedValue = 2600;

	turnLeft(full-400);

	Atondrive(130, 127);

	mobileRRequestedValue = mobileOut;
	WaitieThing();

	Atondrive(-200, drivepower);

	mobileRRequestedValue = mobileIn;
	WaitieThing();

	//--------------------------//

	turnLeft(110);

	Atondrive(-300, drivepower);

	turnRight(190);

	setDrivePower(-127,-127);
	wait1Msec(500);

	setDrivePower(-80,-80);
	wait1Msec(2000);
	setDrivePower(0,0);
}
void RightRed ()
{
	//--------------------------//
	liftRRequestedValue = 2600;           // PRESETS
	mobileRRequestedValue = mobileIn;     //

	mobileRRequestedValue = mobileOut;
	WaitieThing();

	liftRRequestedValue = 3000;

	setChainPower(20);

	Atondrive(650, 127);

	wait1Msec(200);

	liftRRequestedValue = 2910;
	//chainRRequestedValue = OutPositionChain; //score pre-load

	wait1Msec(540);

	//chainRRequestedValue = StraitUpChain;
	liftRRequestedValue = 2600;
	wait1Msec(1);
	mobileRRequestedValue = mobileIn;
	wait1Msec(500);

	//--------------------------//

	Atondrive(-580, 127);

	liftRRequestedValue = 3000;
	wait1Msec(200);


	setIntakePower(-127);                   //
	wait1Msec(250);
	setIntakePower(0);                   //

	liftRRequestedValue = 2600;


	turnRight(full-400);

	Atondrive(80, drivepower);

	mobileRRequestedValue = mobileOut;
	WaitieThing();

	Atondrive(-120, drivepower);

	mobileRRequestedValue = mobileIn;
	WaitieThing();

	//--------------------------//

	turnRight(150);

	setDrivePower(-127,-127);
	wait1Msec(1500);
	setDrivePower(0,0);

	setDrivePower(40,40);
	wait1Msec(300);
	setDrivePower(0,0);

	turnRight(Nine+100);
}

void LeftRedTwo ()
{
	//--------------------------//
	liftRRequestedValue = 2600;           // PRESETS
	mobileRRequestedValue = mobileIn;     //

	mobileRRequestedValue = mobileOut;
	WaitieThing();

	liftRRequestedValue = 3000;

	setChainPower(20);

	Atondrive(780, 127);

	wait1Msec(200);

	liftRRequestedValue = 2910;
	//chainRRequestedValue = OutPositionChain; //score pre-load

	wait1Msec(540);

	//chainRRequestedValue = StraitUpChain;
	liftRRequestedValue = 2600;
	wait1Msec(1);
	mobileRRequestedValue = mobileIn;
	wait1Msec(500);

	//--------------------------//

	Atondrive(-650, 127);

	liftRRequestedValue = 3000;
	wait1Msec(200);


	setIntakePower(-127);                   //
	wait1Msec(250);
	setIntakePower(0);                   //

	liftRRequestedValue = 2600;

	turnLeft((Nine/2)-100);

	Atondrive(-200, 127);

	turnLeft(Nine);

	Atondrive(300, drivepower);         // Drive 300 encoder clicks

	setDrivePower(20,20);							  // Set drive still speed

	mobileRRequestedValue = mobileOut;  // Outake mobile goal
	WaitieThing();										  // Wait for Mobile Goal

	Atondrive(-75, drivepower);         // Drive 175 encoder clicks

	mobileRRequestedValue = mobileIn;
	WaitieThing();											 // Wait for Mobile Goal

	Atondrive(-190, drivepower);         // Drive back 190 encoder clicks


}

void RightRedTwo ()
{
	//--------------------------//
	liftRRequestedValue = 2600;           // PRESETS
	mobileRRequestedValue = mobileIn;     //

	mobileRRequestedValue = mobileOut;
	WaitieThing();

	liftRRequestedValue = 3000;

	setChainPower(20);

	Atondrive(650, 127);

	wait1Msec(200);

	liftRRequestedValue = 2910;
	//chainRRequestedValue = OutPositionChain; //score pre-load

	//chainRRequestedValue = StraitUpChain;
	liftRRequestedValue = 2600;
	wait1Msec(1);
	mobileRRequestedValue = mobileIn;
	wait1Msec(500);

	//--------------------------//

	Atondrive(-580, 127);

	liftRRequestedValue = 3000;
	wait1Msec(200);


	setIntakePower(-127);                   //
	wait1Msec(250);
	setIntakePower(0);                   //

	liftRRequestedValue = 2600;

	turnRight((Nine/2)-100);

	Atondrive(-250, 127);

	turnRight(Nine);

	Atondrive(300, drivepower);         // Drive 300 encoder clicks

	setDrivePower(20,20);							  // Set drive still speed

	mobileRRequestedValue = mobileOut;  // Outake mobile goal
	WaitieThing();										  // Wait for Mobile Goal

	Atondrive(-75, drivepower);         // Drive 175 encoder clicks

	mobileRRequestedValue = mobileIn;
	WaitieThing();											 // Wait for Mobile Goal

	Atondrive(-190, drivepower);         // Drive back 190 encoder clicks
}

//#endregion
//#region Other Programs
void Defensive ()
{
	setDrivePower(127 , 127);
	wait1Msec(5000);
	setDrivePower(0 , 0);
}

void DoNothing ()
{
	liftRRequestedValue = 2600;           // PRESETS
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
//HI trent
