//----------------------LIFT PID----------------------//

static float  liftR_Kp = 0.2; 	//Power Tuning Value
static float  liftRRequestedValue;
static float  liftR_Kd = 1;			// Requested Guess Value

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

		motor[ liftL ] = -liftRDrive;
		motor[ liftR ] = -liftRDrive;

		lastliftRError = liftRError;

		// Don't hog cpu
		wait1Msec( 25 );
	}
}

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

		motor[ MobileL ] = mobileRDrive;
		motor[ MobileR ] = mobileRDrive;

		lastmobileRError = mobileRError;
		// Don't hog cpu
		wait1Msec( 25 );
	}
}
void WaitieThing()
{
	while(mobileRSensorCurrentValue >= mobileRRequestedValue + waitMobliERerror
		|| mobileRSensorCurrentValue <= mobileRRequestedValue - waitMobliERerror)
		{}
}
