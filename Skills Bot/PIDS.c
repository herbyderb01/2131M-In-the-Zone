#include "Voids & Vars.c"
//----------------------Drive PID----------------------//

static float  Drive_Kp = 0.30; //Power Tuning Value
static float  DriveRequestedValue;
static float  Drive_Kd = 0.5; // Requested Guess Value

float DriveD;						//Establishing variables
float DriveP;
float lastDriveError;
float DriveDF;
int waitMobliERerror = 100;
float  DriveSensorCurrentValue;

//mobile Values Right
//Clamp = 450
//Straight = 2000
//Locked = 3850
//V = 1150

//mobile Values Left
//Clamp = 4000
//Straight = 2600
//Locked = 1250
//V = 3600
task DriveController()
{
	//float  DriveSensorCurrentValue;
	float  DriveError;
	float  DriveDrive;

	while( true )
	{
		// Read the sensor value and scale
		DriveSensorCurrentValue = SensorValue[ rightEncoder ];
		// calculate error
		DriveError =  DriveRequestedValue - DriveSensorCurrentValue;

		// calculate drive
		DriveP = (Drive_Kp * DriveError);

		DriveD = DriveError- lastDriveError;
		DriveDF = (Drive_Kd * DriveD);

		DriveDrive = DriveP + DriveDF;

		// limit drive
		if( DriveDrive > 127 )
			DriveDrive = 127;
		if( DriveDrive < (-127) )
			DriveDrive = (-127);

		// send to motor

		setDrivePower(drivepowerPID);

		lastDriveError = DriveError;
		// Don't hog cpu
		wait1Msec( 25 );
	}
}
//----------------------LIFT PID----------------------//


static float  liftR_Kp = 0.2750; 	//Power Tuning Value
static float  liftRRequestedValue;
static float  liftR_Kd = 0.6;			// Requested Guess Value

float liftRD;
float liftRP;
float lastliftRError;
float liftRDF;

//lift Values Right
//Clamp = 450
//Straight = 2000
//Locked = 3850
//V = 1150

//lift Values Left
//Clamp = 4000
//Straight = 2600
//Locked = 1250
//V = 3600
task liftRController()
{
	float  liftRSensorCurrentValue;
	float  liftRError;
	float  liftRDrive;

	while( true )
	{
		// Read the sensor value and scale
		liftRSensorCurrentValue = SensorValue[ liftPot ];

		// calculate error
		liftRError =  liftRRequestedValue - liftRSensorCurrentValue;

		// calculate drive
		liftRP = (liftR_Kp * liftRError);

		liftRD = liftRError- lastliftRError;
		liftRDF = (liftR_Kd * liftRD);

		liftRDrive = liftRP + liftRDF;

		// limit drive
		if( liftRDrive > 127 )
			liftRDrive = 127;
		if( liftRDrive < (-127) )
			liftRDrive = (-127);

		// send to motor

		setLiftPower(127);

		lastliftRError = liftRError;

		// Don't hog cpu
		wait1Msec( 25 );
	}
}
//----------------------Mobile Bar PID----------------------//

static float  calw_Kp = 0.30; //Power Tuning Value
static float  calwRequestedValue;
static float  calw_Kd = 0.5; // Requested Guess Value

float calwD;						//Establishing variables
float calwP;
float lastcalwError;
float calwDF;
int waitMobliERerror = 100;
float  calwSensorCurrentValue;

//mobile Values Right
//Clamp = 450
//Straight = 2000
//Locked = 3850
//V = 1150

//mobile Values Left
//Clamp = 4000
//Straight = 2600
//Locked = 1250
//V = 3600
task calwController()
{
	//float  calwSensorCurrentValue;
	float  calwError;
	float  calwDrive;

	while( true )
	{
		// Read the sensor value and scale
		calwSensorCurrentValue = SensorValue[ clawp ];
		// calculate error
		calwError =  calwRequestedValue - calwSensorCurrentValue;

		// calculate drive
		calwP = (calw_Kp * calwError);

		calwD = calwError- lastcalwError;
		calwDF = (calw_Kd * calwD);

		calwDrive = calwP + calwDF;

		// limit drive
		if( calwDrive > 127 )
			calwDrive = 127;
		if( calwDrive < (-127) )
			calwDrive = (-127);

		// send to motor

		motor[ Calw ] = calwDrive;

		lastcalwError = calwError;
		// Don't hog cpu
		wait1Msec( 25 );
	}
}
