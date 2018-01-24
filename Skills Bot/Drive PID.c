//#region global variables
float wheelDiameter = 4;
int driveStraightError = 100;
//#endregion
//#region Right Drive PID
//----------------------Right Drive PID----------------------//

static float  DriveR_Kp = 0.6; 	//Power Tuning Value
static float  DriveRRequestedValue;
static float  DriveR_Kd = 4;			// Requested Guess Value

float DriveRD;
float DriveRP;
float lastDriveRError;
float DriveRDF;


task RPIDDriveController()
{
  float  DriveRSensorCurrentValue;
	float  DriveRError;
	float  DriveRDrive;

  	while( true )
  	{
  		// Read the sensor value and scale
  		DriveRSensorCurrentValue = SensorValue[ rightEncoder ];

  		// calculate error
  		DriveRError =  DriveRRequestedValue - DriveRSensorCurrentValue;

  		// calculate drive
  		DriveRP = (DriveR_Kp * DriveRError);

  		DriveRD = DriveRError- lastDriveRError;
  		DriveRDF = (DriveR_Kd * DriveRD);

  		DriveRDrive = DriveRP + DriveRDF;

  		// limit drive
  		if( DriveRDrive > 127 )
  			DriveRDrive = 127;
  		if( DriveRDrive < (-127) )
  			DriveRDrive = (-127);

  		// send to motor

  		setDrivePowerRight(DriveRDrive);

  		lastDriveRError = DriveRError;

  		// Don't hog cpu
  		wait1Msec( 25 );
  	}
}
//#endregion
//#region Left Drive PID
//----------------------Left Drive PID----------------------//

static float  DriveL_Kp = 0.6; 	//Power Tuning Value
static float  DriveLRequestedValue;
static float  DriveL_Kd = 4;			// Requested Guess Value

float DriveLD;
float DriveLP;
float lastDriveLError;
float DriveLDF;

task LPIDDriveController()
{
  float  DriveLSensorCurrentValue;
	float  DriveLError;
	float  DriveLDrive;

  	while( true )
  	{
  		// Read the sensor value and scale
  		DriveLSensorCurrentValue = -SensorValue[ leftEncoder ];

  		// calculate error
  		DriveLError =  DriveLRequestedValue - DriveLSensorCurrentValue;

  		// calculate drive
  		DriveLP = (DriveL_Kp * DriveLError);

  		DriveLD = DriveLError- lastDriveLError;
  		DriveLDF = (DriveL_Kd * DriveLD);

  		DriveLDrive = DriveLP + DriveLDF;

  		// limit drive
  		if( DriveLDrive > 127 )
  			DriveLDrive = 127;
  		if( DriveLDrive < (-127) )
  			DriveLDrive = (-127);

  		// send to motor

  		setDrivePowerLeft(DriveLDrive);

  		lastDriveLError = DriveLError;

  		// Don't hog cpu
  		wait1Msec( 25 );
  	}
}
//#endregion
//#region Converter
int InchesToCounts(float value) //converts drive encoder counts into inches
{
  return (value * 360)/(PI * wheelDiameter);
}
#endregion
#region
void droveStraight(float distance, bool waity = false)
{
  SensorValue[rightEncoder] = 0;
  SensorValue[leftEncoder] = 0;

  //distance=InchesToCounts(distance);

  DriveRRequestedValue = distance;
  DriveLRequestedValue = distance;
  if (waity)
  {
  //  distance = abs(distance); //help
    while( -SensorValue[ leftEncoder ] >= DriveLRequestedValue + driveStraightError
		|| -SensorValue[ leftEncoder ] <= DriveLRequestedValue - driveStraightError){}
    wait1Msec(200);
  }
}
//#endregion
