

static float  chainR_Kp = 0.30;
static float  chainRRequestedValue;
static float  chainR_Kd = 0.6;




float chainRD;
float chainRP;
float lastchainRError;
float chainRDF;









//chain Values Right
//Clamp = 450
//Straight = 2000
//Locked = 3850
//V = 1150

//chain Values Left
//Clamp = 4000
//Straight = 2600
//Locked = 1250
//V = 3600
task chainRController()
{
	float  chainRSensorCurrentValue;
	float  chainRError;
	float  chainRDrive;

	while( true )
	{
		// Read the sensor value and scale
		chainRSensorCurrentValue = SensorValue[ pivP ];

		// calculate error
		chainRError =  chainRRequestedValue - chainRSensorCurrentValue;

		// calculate drive
		chainRP = (chainR_Kp * chainRError);

		chainRD = chainRError- lastchainRError;
		chainRDF = (chainR_Kd * chainRD);

		chainRDrive = chainRP + chainRDF;

		// limit drive
		if( chainRDrive > 127 )
			chainRDrive = 127;
		if( chainRDrive < (-127) )
			chainRDrive = (-127);

		// send to motor

		motor[ pivL ] = -chainRDrive;
		motor[ pivR ] = -chainRDrive;


		lastchainRError = chainRError;

		// Don't hog cpu
		wait1Msec( 25 );
	}
}

static float  liftR_Kp = 0.2.750;
static float  liftRRequestedValue;
static float  liftR_Kd = 0.6;




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
