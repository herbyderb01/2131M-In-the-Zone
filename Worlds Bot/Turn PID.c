int driveStraightError = 100;
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
//#region Called functions

void TurnPID (int turnAmount, bool waity=false)
{
  startTask(TPIDDriveController);

  SensorValue[Gyro] = 0;
  DriveTRequestedValue = turnAmount;
  if (waity)
  {
    //  distance = abs(distance); //help
      while( SensorValue[ Gyro ] >= DriveTRequestedValue + driveStraightError
  		|| SensorValue[ Gyro ] <= DriveTRequestedValue - driveStraightError){}
      wait1Msec(200);
      stopTask(TPIDDriveController);
  }
  wait1Msec(25);
  stopTask(TPIDDriveController);
}
//#endregion
