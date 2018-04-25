//#region motor set up
//-------------Motor Void Set-Up--------------//
void setDrivePower(int left, int right)
{// Defining all of the motors for the -DRIVE-
	motor[LDrive] = left;		//Define this motor as the left drive
	motor[RDrive] = right;	//Define this motor as the right drive
}
void setDrivePowerAton(int left, int right)
{// Defining all of the motors for the -DRIVE-
	motor[LDrive] = left;		//Define this motor as the left drive
	motor[RDrive] = right;	//Define this motor as the right drive
	motor[MobileL] = left;	//Define this motor as the left drive
	motor[MobileR] = right;	//Define this motor as the right drive
}
void setDrivePowerRight(int power)
{// Defining all of the motors for the -Right DRIVE-
	motor[RDrive] = power;	//Define this motor as the right drive
	motor[MobileR] = power;	//Define this motor as the right drive
}

void setDrivePowerLeft(int power)
{// Defining all of the motors for the -Left DRIVE-
	motor[LDrive] = power;		//Define this motor as the left drive
	motor[MobileL] = power;	//Define this motor as the left drive
}

void setLiftPower(int power)
{// Defining all of the motors for the -LIFT-
	motor[UliftR] = power;
	motor[UliftL] = power;
	motor[DliftR] = power;
	motor[DliftL] = power;
}

void setFourBarPower(int cpower)
{// Defining all of the motors for the -FourBar BAR-
	motor[FourBar] = cpower;
}

void setIntakePower(int Ipower)
{// Defining all of the motors for the -INTAKE-
	motor[INtake] = Ipower;
}

void setMobilePower(int Mpower)
{// Defining all of the motors for the -MOBILE GOAL INTAKE-
	motor[MobileL] = Mpower;
	motor[MobileR] = Mpower;
}
//_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_//
void FourBarPosition(int position, int timeest, int power)
{//void to controll the four bar in aton
  if(position == 1)
  {
  setFourBarPower(power);
  wait1Msec(timeest);
  setFourBarPower(15);
  }
  if(position == 0)
  {
  setFourBarPower(-power);
  wait1Msec(timeest);
  setFourBarPower(-20);
  }
}
void RollerMode(int position, int timeest)
{// Void to controll the roller during aton
  if(position == 1 && timeest > 0)
  {
  setIntakePower(127);
  wait1Msec(timeest);
  setIntakePower(10);
  }
  if(position == 0 && timeest > 0)
  {
  setIntakePower(-127);
  wait1Msec(timeest);
  setIntakePower(10);
  }
  if(timeest == 0)
  {
    if(position == 1)
    {
      setIntakePower(127);
    }
    if(position == 0)
    {
      setIntakePower(-127);
    }
  }
}
//#endregion
//#region Lift PID
//----------------------LIFT PID----------------------//

static float  liftR_Kp = 0.2; 	//Power Tuning Value
static float  liftRRequestedValue;
static float  liftR_Kd = 1;			// Requested Guess Value

float liftRD;
float liftRP;
float lastliftRError;
int waitLiftRerror = 150;
float liftRDF;

task liftRController()
{ // PID to set the lift/lock the lift during aton to increase accuracy
	float  liftRSensorCurrentValue;
	float  liftRError;
	float  liftRDrive;

	while( true )
	{
		// Read the sensor value and scale
		liftRSensorCurrentValue = SensorValue[ liftP ];

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
		setLiftPower(liftRDrive);
		lastliftRError = liftRError;
		// Don't hog cpu
		wait1Msec( 25 );
	}
}
//#endregion
//#region Mobile PID
//----------------------Mobile Bar PID----------------------//
static float  mobileR_Kp = 0.30; //Power Tuning Value
static float  mobileRRequestedValue;
static float  mobileR_Kd = 0.5; // Requested Guess Value

float mobileRD;						//Establishing variables
float mobileRP;
float lastmobileRError;
float mobileRDF;
int waitMobliERerror = 100;
float  mobileRSensorCurrentValue;

task mobileRController()
{// PID to set the mobile goal/lock the mobile goal during aton to increase accuracy
	float  mobileRSensorCurrentValue;
	float  mobileRError;
	float  mobileRDrive;

	while( true )
	{
		// Read the sensor value and scale
		mobileRSensorCurrentValue = SensorValue[ mobileP ];
		// calculate error
		mobileRError =  mobileRRequestedValue - mobileRSensorCurrentValue;

		// calculate drive
		mobileRP = (mobileR_Kp * mobileRError);

		mobileRD = mobileRError- lastmobileRError;
		mobileRDF = (mobileR_Kd * mobileRD);

		mobileRDrive = mobileRP + mobileRDF;

		// limit drive
		if( mobileRDrive > 127 )
			mobileRDrive = 127;
		if( mobileRDrive < (-127) )
			mobileRDrive = (-127);

		// send to motor
		setMobilePower(mobileRDrive);
		lastmobileRError = mobileRError;

		// Don't hog cpu
		wait1Msec( 25 );
	}
}
//#endregion
//#region WaityThing for mobilegoal and lift
void goalRequest(int position, bool waity = false)
{// void to call the mobile goal request in aton, to make it simpler
	startTask(mobileRController);
	mobileRRequestedValue = position;
		if(waity)
		{	while(SensorValue[mobileP] >= mobileRRequestedValue + waitMobliERerror
				|| SensorValue[mobileP] <= mobileRRequestedValue - waitMobliERerror)
				{} wait1Msec(50);
		}
}
void liftRequest(int position, bool waity = false)
{// void to call the lift request in aton, to make it simpler
	liftRRequestedValue = position;
		if(waity)
		{	while(SensorValue[ liftP ] >= liftRRequestedValue + waitLiftRerror
			|| SensorValue[ liftP ] <= liftRRequestedValue - waitLiftRerror)
			{} wait1Msec(50);
		}
}
//#endregion
