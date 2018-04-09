MAE 578: Haptic Systems for Virtual Reality and Teleoperation
Problem Set 4: Surface Properties (Team Activity)
Due Date: 3/12/2018 (for hard copy submission)
Prof. P. Marayong, CSULB, Spring 2018

Per group, submit a printout of your edited C++ code (between the lines "`START EDITING HERE`" and "`STOP EDITING HERE`") and submit the same code snippet as a .doc or .txt file in the respective Dropbox on Beachboard. Clearly separate and label the code snippets from each problem on the printout and in the electronic file. To grade your work, I will copy and paste your code snippets into my own .cpp file and test the haptic feedback by hand. I will also look at the code to evaluate the efficiency, generality, and elegance of your solution. Make sure your code includes proper comments. Note that the visual representation of the planes you create in this lab is not rendered. However, you should be able to feel the plane(s) through the haptic device.

For each surface property, explain the algorithm you used and answer the questions on paper (typed) submitted along with the code printout. Clearly separate and label each problem. For all problems, **create a horizontal virtual wall (using F=kx) at a height of y = 0** with the surface properties described in each problem. Use a k value that clearly and stably displays a wall. You can start with the same generic.cpp file as in the previous lab.

1. (5 pts.) Create damping to the surface to make the wall feels less “active”. Describe the maximum value of damping coefficient (with unit) that you can use and remain stable. How does it feel compared to the plane without the damping?

2. (5 pts.) Create damping parallel to the surface using Coulomb friction model. Sketch your force vs. velocity profile. Describe the maximum value of damping coefficient (with unit) that you can use and remain stable.

3. (10 pts.) Generate a textured surface using the damping field method described in lecture. The surface should feel realistic. Explain clearly the method you used, giving sketches and dimensions where appropriate.

4. (15 pts.) Create a perfectly flat virtual wall that feels like it has a dip/valley/trough/bump in the middle. The “dip” should be sufficiently wide and extruded to infinity similar to the figure below. Use Minsky’s local gradient technique of generating forces parallel to the surface to generate the sensation of passing over a “dip”. You can choose the function for the shape of the dip. (With the 3-dof Omni you could create a real dip, but the technique used here could also be implemented on a 1-dof or 2-dof device.) Write an explanation (including sketches and equations) explaining what you did and the geometry of the dip that you created.

5. (15 pts.) Create a surface that feels harder than the maximum stiffness that can be stably displayed by the Omni. Do this by generating a decaying sinusoid upon downward vertical impact with the horizontal virtual wall. Select values for the amplitude-scaling factor and decay rate that generate a compelling sensation of contact. Note that the time used should be the actual time of each haptic update loop. Write an explanation (including sketches and equations) explaining what you did.

Note that to solve these problems, you may need access to variables that were not in the example code you started with (such as velocity). For example, the current code obtains the position vector with the command:
```
hduVector3Dd position;
hdGetDoublev(HD_CURRENT_POSITION, position);
```
Similarly, you can obtain velocity with the commands:
```
hduVector3Dd velocity;
hdGetDoublev(HD_CURRENT_VELOCITY, velocity);
```
The OpenHaptics Programmer's Guide is posted on Beachboard for your reference. Here are some additional functions that may be useful for problem 5.

e^x = exp(x)

ln(x) = log(x)

static double t = 0 (Declaring a static variable will allow the variable to be created and initialized only once. Its value can be carried through during multiple function calls.)

Haptic loop update rate = 1ms
