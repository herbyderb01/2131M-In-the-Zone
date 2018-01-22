//----------------------Right Drive PID----------------------//

static float  DriveR_Kp = 0.45; 	//Power Tuning Value
static float  DriveRRequestedValue;
static float  DriveR_Kd = 0.03;			// Requested Guess Value

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

static float  DriveL_Kp = 0.45; 	//Power Tuning Value
static float  DriveLRequestedValue;
static float  DriveL_Kd = 0.03;			// Requested Guess Value

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
  		DriveLSensorCurrentValue = SensorValue[ leftEncoder ];

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

  		setDrivePowerLeft(-DriveLDrive);

  		lastDriveLError = DriveLError;

  		// Don't hog cpu
  		wait1Msec( 25 );
  	}
}

task DrivePID()
{
  startTask(RPIDDriveController);
  startTask(LPIDDriveController);

  SensorValue[rightEncoder] = 0;
  SensorValue[leftEncoder] = 0;
  SensorValue[Gyro] = 0;

  while(true)
  {
  }
  // Don't hog cpu
  wait1Msec( 25 );
}
