	//*** START EDITING HERE ***//////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////////
	
	//PART 1
	//Get velocities
	hduVector3Dd velocity;
	hdGetDoublev(HD_CURRENT_VELOCITY, velocity);
	//Define Plane
	double height_y = 0; //Define plane height
	hduVector3Dd pointP(0, height_y, 0); //Defined point on plane
	hduVector3Dd normalN(0, 1, 0); //Defined normal vector of plane as well as the force direction
	normalN.normalize(); //normalized normal vector
	hduVector3Dd r = position - pointP; // r is defined in the lecture slides
	//distance from user to plane
	double d = dotProduct(r,normalN); //dot product of r with normal vector to get distance
	//Define variables
	double k=0.5; //output force stiffness
	double b = 0.003; // N-s/mm - Solid viscous damping coefficient, .004 unstable vibrating when moving along x-z plane
	//check for distance and output force magnitude
	if ( d < height_y ) { // Checks for distance from plane
		if ( velocity[1] < 0 ) { // Checking for velocity in y-dir, happens in negative velocity
			forceMagnitude = - k * d - b * velocity[1]; // total force output (with damping)
		} else {
			forceMagnitude = - k* d; //Spring force if velocity y > 0 (no damping)
		}
	} else {
		forceMagnitude = 0; // if distance is greater than height no force
	}
	forceDirection.set(normalN[0],normalN[1],normalN[2]); //force direction
	f = forceMagnitude * forceDirection; //calculate force vector
	// command the desired force "f". You must determine the value of "f" before using this line.
	hdSetDoublev(HD_CURRENT_FORCE, f);
	//END OF PART 1
	
	
	
	//PART 2
	//Get velocities
	hduVector3Dd velocity;
	hdGetDoublev(HD_CURRENT_VELOCITY, velocity);
	//Define Plane
	double height_y = 0; //Define plane height
	hduVector3Dd pointP(0, height_y, 0); //defined point on plane
	hduVector3Dd normalN(0, 1, 0); //defined normal vector of plane as well as the force direction
	normalN.normalize(); //normalized normal vector
	// r is defined in the lecture slides
	hduVector3Dd r = position - pointP;
	//distance from user to plane
	double d = dotProduct(r,normalN);
	//output force stiffness
	double k=0.5;
	//friction coeff
	double friction_coeff = 0.01;
	forceDirection.set(normalN[0],normalN[1],normalN[2]);
	//check for distance and output force magnitude
	if (d < height_y) {
		//Spring force output in y-dir
		f[1] = - k * d * forceDirection[1];
		//Friction force in x dir (normal force * coefficient of friction)
		if (velocity[0] < 0) {
			f[0] = friction_coeff * f[1];
		}  else {
			f[0] = - friction_coeff * f[1];
		}  
		//Friction force in z dir (normal force * coefficient of friction)
		if (velocity[2] < 0) {
			f[2] = friction_coeff * f[1];
		} else {
			f[2] = - friction_coeff * f[1];
		}

	} else {
		f.set(0,0,0); // if distance is greater than height no force
	}
	// command the desired force "f". You must determine the value of "f" before using this line.
	hdSetDoublev(HD_CURRENT_FORCE, f);
	//END OF PART 2
	


	
	//PART 3
	//Get velocities
	hduVector3Dd velocity;
	hdGetDoublev(HD_CURRENT_VELOCITY, velocity);
	//Define Plane
	double height_y = 0; //Define plane height
	hduVector3Dd pointP(0, height_y, 0); //Defined point on plane
	hduVector3Dd normalN(0, 1, 0); //Defined normal vector of plane as well as the force direction
	normalN.normalize(); //normalized normal vector
	// r is defined in the lecture slides
	hduVector3Dd r = position - pointP;
	//distance from user to plane
	double d = dotProduct(r,normalN);
	//damping field width and gap
	int width=10;//mm
	//output force stiffness
	double k=0.25;
	// Viscous damping coefficient
	double b = 0.003;//; // N-s/mm
	int x_int_position=floor(position[0]);     //taking floor
	int z_int_position=floor(position[2]);		//taking floor
	//check for damping area and output force magnitude accordingly
	if (d < 0) //inside the plate
	{ 
		f[1] = - k * d; //Output a spring force
		// Check grid in x direction
		if ( (x_int_position%(2*width) >=0 && x_int_position%(2*width)<width) || (x_int_position%(2*width) >= -2*width && x_int_position%(2*width)<-width)) {
			f[0]=- b * velocity[0]; //output force in x direction
		}
		// Check grid in z direction
		if ( (z_int_position%(2*width) >=0 && z_int_position%(2*width)<width) || (z_int_position%(2*width) >= -2*width && z_int_position%(2*width)<-width)) {
			f[2]=- b * velocity[2]; //output force in z direction
		} 
	} else {
		f.set(0,0,0);
	}	
	// command the desired force "f". You must determine the value of "f" before using this line.
	hdSetDoublev(HD_CURRENT_FORCE, f);
	//END OF PART 3
	

	
	//PART 4
	//Get velocities
	hduVector3Dd velocity;
	hdGetDoublev(HD_CURRENT_VELOCITY, velocity);
	//Define Plane
	double height_y = 0; //Define plane height
	hduVector3Dd pointP(0, height_y, 0); //Defined point on plane
	hduVector3Dd normalN(0, 1, 0); //Defined normal vector of plane as well as the force direction
	normalN.normalize(); //normalized normal vector
	// r is defined in the lecture slides
	hduVector3Dd r = position - pointP;
	//distance from user to plane
	double d = dotProduct(r,normalN);
	//output force stiffness
	double k=0.25;
	//create a 3D valley that lies along x direction, so z direction is the extrusion of the x-y plane 
	//define parameters in the function of the valley
	double width=50; //width of the valley
	double height=50;
	double A=1;   //force factor
	//check for damping area and output force magnitude accordingly
	if (d < 0) {                                                                                //inside the plate 
		f[1] = - k * d;
		if(position[0]<width/2 && position[0]>-width/2) {
			double h=-height*cos(2*3.14*position[0]/width);
			double deri_h=height*sin(2*3.14*position[0]/width)*2*3.14/width;
			f[0] = - A*deri_h;
		}                           
	} 
	// command the desired force "f". You must determine the value of "f" before using this line.
	hdSetDoublev(HD_CURRENT_FORCE, f);
	//END OF PART 4
	
	
	
	//PART 5
	hduVector3Dd velocity;
	hdGetDoublev(HD_CURRENT_VELOCITY, velocity);
	static double t=0;//system time
	double update_rate=0.001; //system update rate
 	t=t+update_rate; // adding 0.001s each loop since the system update rate is 1ms	
	double height_y = 0;	// define the height of the plane in y direction
	hduVector3Dd pointP(0, height_y, 0); //defined point on plane
	hduVector3Dd normalN(0, 1, 0); //defined normal vector of plane as well as the force direction
	normalN.normalize(); //normalized normal vector
	// r is defined in the lecture slides
	hduVector3Dd r = position - pointP;
	//distance from user to plane
	double d = dotProduct(r,normalN);
	//output force stiffness
	double k=0.25;
	//create a 3D valley that lies along x direction, so z direction is the extrusion of the x-y plane 
	//define parameters in the function of the valley
	double freq=0.25;
	double duration=0.055;  // the duration of the sinusoid force
	double amplitude=5; // amplitude of the sinusoid force
	//sinusoid parameter
	static double sinusoid_force = 0;
	static double in_plane_time=0;
	static bool initial_velocity_set = 0;  //intialize the initial velocity into the plane
	static double initial_velocity = 0.0;   //initialize the bool that shows whether the initial velocity has been set or not

	//Set initial velocity
	if ( initial_velocity_set == 0 && d < 0) {   //If your velocity has not been set and distance is less than 0, set initial velocity
		initial_velocity = velocity[1];
		initial_velocity_set = 1;  //velocity set, true (velocity has been set)
	}	else if ( d >= 0 ) { //If your distance is greater than or equal to 0, reset initial velocity
		initial_velocity_set = 0; //velocity reset, needs to be set next time in plane
	}

	//Calculate sinusoid
	if (d < 0) { //inside the plate
		double exponential = exp(log(0.01)*in_plane_time/duration); // calculates exponential part of equation
		double sin_calc = sin(2*3.14*in_plane_time*freq); //calculates sin part of equation
		in_plane_time += update_rate;  //set a in_plane timer to record the time user stay the plane since last time entered the plane
		if ( in_plane_time <= duration ) {   //while the in-plane time is less than the duration
			//initial_velocity=0.1;
			sinusoid_force=amplitude*abs(initial_velocity)*exponential*sin_calc;  //decaying sinusoid force according to the equation in the lecture slides//
		} else if ( in_plane_time > duration ) {
			sinusoid_force = 0;      
		}
		f[1] = sinusoid_force - k * d;  
	} else {      //outside of the plane
			sinusoid_force=0;  //sinusoid force=0
			f[1] =0;  //zero all force = 0
			in_plane_time=0;             //everytime user goes out of the plane, reset the in_plane timer
	}
	// command the desired force "f". You must determine the value of "f" before using this line.
	hdSetDoublev(HD_CURRENT_FORCE, f);
	//END OF PART 5
	
	//////////////////////////////////////////////////////////////////////////////////
	//*** STOP EDITING HERE ***//////////////////////////////////////////////////////