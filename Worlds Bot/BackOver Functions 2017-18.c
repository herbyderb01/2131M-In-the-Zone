//#region motor set up
//-------------Motor Void Set-Up--------------//
void setDrivePower(int left, int right)
{// Defining all of the motors for the -DRIVE-
	motor[LDrive] = left;		//Define this motor as the left drive
	motor[RDrive] = right;	//Define this motor as the right drive
	//motor[MobileL] = left;	//Define this motor as the left drive
	//motor[MobileR] = right;	//Define this motor as the right drive
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
	motor[MobileR] = power;	//Define this motor as the right drive
}

void setDrivePowerLeft(int power)
{// Defining all of the motors for the -Left DRIVE-
	motor[LDrive] = power;		//Define this motor as the left drive
	motor[MobileL] = power;	//Define this motor as the left drive
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
float liftRSensorCurrentValue;

task liftRController()
{
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
int waitMobliERerror = 75;
float  mobileRSensorCurrentValue;

task mobileRController()
{
	//float  mobileRSensorCurrentValue;
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
{
	mobileRRequestedValue = position;
		if(waity)
		{	while(mobileRSensorCurrentValue >= mobileRRequestedValue + waitMobliERerror
				|| mobileRSensorCurrentValue <= mobileRRequestedValue - waitMobliERerror)
				{} wait1Msec(50);
		}
}
void liftRequest(int position, bool waity = false)
{
	liftRRequestedValue = position;
		if(waity)
		{	while(liftRSensorCurrentValue >= liftRRequestedValue + waitLiftRerror
			|| liftRSensorCurrentValue <= liftRRequestedValue - waitLiftRerror)
			{} wait1Msec(50);
		}
}
//#endregion
