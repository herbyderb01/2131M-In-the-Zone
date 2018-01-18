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
		DriveSensorCurrentValue = SensorValue[ mobileP ];
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

		motor[ MobileL ] = DriveDrive;
		motor[ Drive ] = DriveDrive;

		lastDriveError = DriveError;
		// Don't hog cpu
		wait1Msec( 25 );
	}
}
