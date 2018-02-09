float wheelDiameter = 4;
int driveStraightError = 100;

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

//#region Turn PID
//----------------------Turn PID----------------------//

static float  DriveT_Kp = 0.4; 	//Power Tuning Value
static float  DriveTRequestedValue;
static float  DriveT_Kd = 2.5;			// Requested Guess Value

float DriveTD;
float DriveTP;
float lastDriveTError;
float DriveTDF;

task TPIDDriveController()
{
  float  DriveTSensorCurrentValue;
	float  DriveTError;
	float  DriveTDrive;

  	while( true )
  	{
  		// Read the sensor value and scale
  		DriveTSensorCurrentValue = SensorValue[ Gyro ];

  		// calculate error
  		DriveTError =  DriveTRequestedValue - DriveTSensorCurrentValue;

  		// calculate drive
  		DriveTP = (DriveT_Kp * DriveTError);

  		DriveTD = DriveTError- lastDriveTError;
  		DriveTDF = (DriveT_Kd * DriveTD);

  		DriveTDrive = DriveTP + DriveTDF;

  		// limit drive
  		if( DriveTDrive > 127 )
  			DriveTDrive = 127;
  		if( DriveTDrive < (-127) )
  			DriveTDrive = (-127);

  		// send to motor

  		setDrivePowerLeft(-DriveTDrive);
      setDrivePowerRight(DriveTDrive);

  		lastDriveTError = DriveTError;

  		// Don't hog cpu
  		wait1Msec( 25 );
  	}
}
//#endregion
//#region Called functions
int InchesToCounts(float value) //converts drive encoder counts into inches
{
  return (value * 360)/(PI * wheelDiameter);
}
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

void TurnPID (int turnAmount, bool waity=false)
{
  //stopTask(RPIDDriveController);
  //stopTask(LPIDDriveController);

  startTask(TPIDDriveController);

  SensorValue[Gyro] = 0;
  DriveTRequestedValue = turnAmount;
  if (waity)
  {
    //  distance = abs(distance); //help
      while( SensorValue[ Gyro ] >= DriveTRequestedValue + driveStraightError
  		|| SensorValue[ Gyro ] <= DriveTRequestedValue - driveStraightError){}
      wait1Msec(200);
  }
  wait1Msec(25);
  stopTask(TPIDDriveController);
}
//#endregion
