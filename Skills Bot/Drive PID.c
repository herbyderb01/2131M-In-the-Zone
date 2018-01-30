//#region global variables
float wheelDiameter = 4;
int driveStraightError = 100;

//Drive ramp values
int rampInterval = 1;
int normalRampSpeed = 7;
int highRampSpeed = 30;
int deadband = 10;

// Ramping Vars
int RDriveRampRequest;
int RDriveRampSgn;
int RDriveRampCurrent;

int LDriveRampRequest;
int LDriveRampSgn;
int LDriveRampCurrent;

//#endregion
//#region Ramping
task rightDriveRamping()
{
  while(true)
  {
    RDriveRampSgn = sgn(RDriveRampRequest);

    if(abs(RDriveRampRequest) > deadband)
    {
     if(abs(RDriveRampCurrent) < abs(RDriveRampRequest) && abs(RDriveRampCurrent) < 30)
     RDriveRampCurrent += highRampSpeed*RDriveRampSgn;
     else if(abs(RDriveRampCurrent) < abs(RDriveRampRequest))
     RDriveRampCurrent += normalRampSpeed*RDriveRampSgn;
     else if(abs(RDriveRampCurrent) >= abs(RDriveRampRequest))
     RDriveRampCurrent = RDriveRampRequest*RDriveRampSgn;
    }

    else if(abs(RDriveRampRequest) <= deadband)
    RDriveRampCurrent = 0;

   setDrivePowerRight(RDriveRampCurrent);
   wait1Msec(rampInterval);
  }
}

task leftDriveRamping()
{
  while(true)
  {
    LDriveRampSgn = sgn(LDriveRampRequest);

    if(abs(LDriveRampRequest) > deadband)
    {
     if(abs(LDriveRampCurrent) < abs(LDriveRampRequest) && abs(LDriveRampCurrent) < 30)
     LDriveRampCurrent += highRampSpeed*LDriveRampSgn;
     else if(abs(LDriveRampCurrent) < abs(LDriveRampRequest))
     LDriveRampCurrent += normalRampSpeed*LDriveRampSgn;
     else if(abs(LDriveRampCurrent) >= abs(LDriveRampRequest))
     LDriveRampCurrent = LDriveRampRequest*LDriveRampSgn;
    }

    else if(abs(LDriveRampRequest) <= deadband)
    LDriveRampCurrent = 0;

   setDrivePowerLeft(LDriveRampCurrent);
   wait1Msec(rampInterval);
  }
}

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
  startTask(rightDriveRamping);

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

  		//setDrivePowerRight(DriveRDrive);
      RDriveRampRequest = DriveRDrive;

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
  startTask(leftDriveRamping);

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

      //setDrivePowerLeft(DriveLDrive);
  		LDriveRampRequest = DriveLDrive;

  		lastDriveLError = DriveLError;

  		// Don't hog cpu
  		wait1Msec( 25 );
  	}
}
//#endregion
//#region Turn PID
//----------------------Turn PID----------------------//

static float  DriveT_Kp = 0.5; 	//Power Tuning Value
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
//#region Converter and Called task
int InchesToCounts(float value) //converts drive encoder counts into inches
{
  return (value * 360)/(PI * wheelDiameter);
}

void droveStraight(float distance, bool waity = false)
{
  stopTask(TPIDDriveController);

  startTask(RPIDDriveController);
  startTask(LPIDDriveController);


  SensorValue[rightEncoder] = 0;
  SensorValue[leftEncoder] = 0;

  //distance=InchesToCounts(distance);

  DriveRRequestedValue = distance;
  DriveLRequestedValue = distance;
  if (waity)
  {
  //  distance = abs(distance); //help
    while( SensorValue[ leftEncoder ] >= DriveLRequestedValue + driveStraightError
		|| SensorValue[ leftEncoder ] <= DriveLRequestedValue - driveStraightError){}
    wait1Msec(200);
  }
  wait1Msec(25);
}

void Turn (int turnAmount,int waity=false)
{
  stopTask(RPIDDriveController);
  stopTask(LPIDDriveController);

  startTask(TPIDDriveController);

  SensorValue[Gyro] = 0;
  DriveTRequestedValue = turnAmount;
  if (waity)
  {
    {
    //  distance = abs(distance); //help
      while( SensorValue[ Gyro ] >= DriveTRequestedValue + driveStraightError
  		|| SensorValue[ Gyro ] <= DriveTRequestedValue - driveStraightError){}
      wait1Msec(200);
    }
  }
  wait1Msec(25);
}
//#endregion
