This site aims to help beginners understand and solve forward and inverse kinematics
robot arms through interactive visualizations.

# 1. Building your first arm, some advice

There are many robot arms that you can readily buy online.

I think the most popular one is the 4-DOF MeArm. It's popular because
it is open source and also very cheap. It uses four very small microservos motors
that are widely available. You can 3d print the body yourself or have it lazer cut 
from an 3mm acrylic sheet, and screw the parts together with standard screws and nuts
from your local hardware store.  

A lot of people have made step-by-step instructions on how to build MeArms from start
to finish. 

If you've never tinkered with an Arduino before, i suggest you a buy a beginner kit
and go play with it for an afternoon before building your first arm. 

There are many beginner kits out there, I personally like the instruction manuals
(free) made by Arduino Experimenter’s Guide By Oomlout. 

The instruction manuals made by Sparkfun, Adafruit, and DFRobot are well designed as well.

The robot arm I have at home is 7bot which I bought from Kickstarter a few years back.
This is a six dof robot arm excluding the gripper. 

Of course you can always design your own if you know how to use cad tools like
OnShape or Fusion360.

# 2. A 5 minute trigonometry Refresher 

- Sine, Cosine, Tan
- The cosine Rule
- Pythagorean theorem
- Triangle Inequality Rule

# 3. 2D Geometry

### Recommended readings
To understand inverse and forward kinematics you must understand 2d geometry first. 

Professor Peter Corke has series of bite-size videos about this. He's really a great teacher. 
The whole section is maybe around 30 minutes long. 

Alan Zucconi has two articles about this if you want a crash course.
- A Gentle Primer on 2D Rotations
- The Transformation Matrix for 2D Games

You can also checkout this visualizer by U Texas
https://web.ma.utexas.edu/users/ysulyma/matrix/

##  Visualize Rotation

In summary, if you rotate a point (x, y) about its origin
with an angle of phi, the resulting point would be:

```
x' = x cos(phi) - ysin(phi) 
y' = x sin (phi) + ycos(phi)
```

In matrix form, the equation would be written as

```
| x' | = | cos(phi) -sin(phi) |  * | x |
| y' |   | sin(phi) cos(phi)  |    | y |
```

Note that the new x axis Rx is now the vector [cos(phi), sin(phi)] which used to be [1, 0]
and the new y axis Yx is now the vector [-sin(phi), cos(phi)] whi used to be [0, 1]
Notice that the length of both vectors equals 1 (ie they are unit vectors)


## Visualize rotation and translation 

If you rotate about a point and then translate in the x and y direction
by tx and ty amount, the equation would be

```
x' = x cos(phi) - ysin(phi) + tx
y' = x sin (phi) + ycos(phi) + ty
```

And the equivalent matrix formula would be 
```
| x' | = | cos(phi) -sin(phi) tx |  * | x |
| y' |   | sin(phi) cos(phi)  ty |    | y |
| 1  |   |  0         0        1 |    | 1 |
```

This matrix that captures the rotation and then translation is
also called a rigid body transformation matrix or homogenous transform matrix.

This matrix M can also be thought of as that coordinate system
where  The x axis and y axes is represented by the matrix first column vector
and second column vector. And the origin is at tx, and ty. 

if the point (x, y) is with respect to this coordinate system defined by 
m, then this same point would be (x', y') with respect to the
coordinate system where the x axis is [1, 0] and y axis is [0, 1]
and the origin is at [0, 0]. 


## Animate two transformation on top of each other

You can stack transformations as well. 

From the origin (0, 0):
1. you can rotate and translate by [rz] [tx] [ty] and you get: point A
2. from point A, you can rotate and translate by [rz] [tx] [yz] and you get point B

Here are the correspoding equations. 


Click to animate

## AnimationElementary operations visualization

We can also break down the transformations in something simpler, 
1. Rotate by how much
2. Translate by how much and in what direction
(add another elementary operation)
Submit to animate.

## Exercise: Forward and inverse kinematics and a 2 link robot in 2d 
Rotate about X by q then translate by dx1 then rotate about new x by q
then translate by dx2 

------------
# 4. Forward and inverse Kinematics of a simple 4 DOF arm
------------

Given everything you know you can actually solve for the forward
and inverse kinematics of a simple 4 DOF robot arm now. 

Forward kinematics is just simply: given that you know the angles of each 
joint, what will the robot look like. 

Inverse kinematics is just simply, if we know where we want the end-effector
of the robot arm to be, what are the angles that would make it happen? 

Alistairwick has a really good article about this which I recommend you to
read. 

- https://github.com/mithi/arm-robot-simulator/blob/master/arm/ik_solver.py
- https://github.com/nanicalabs/EvoArm
- https://github.com/glumb/kinematics
- https://robohub.org/robotics-maths-python-a-fledgling-computer-scientists-guide-to-inverse-kinematics/
- http://www.alistairwick.com/posts/ik-for-dummies/

----------
# 5. 3D geometry
----------

Sometimes two dimensional geometry just won't cut it when your arm is somewhat more
complicated. So let's build upon what we already know. 

Again, I recommend Professor Peter Corke's lectures. 
https://robotacademy.net.au/masterclass/3d-geometry/ 

This article by Mauricio Poppe is also good.
https://www.mauriciopoppe.com/notes/computer-graphics/transformation-matrices/rotation/introduction/

But essentially, you can describe rigid body transform
(rotation and translation in 3d) in several ways like
(but not limited to) :

1. vector + yaw alpha, pitch beta, and roll gamma angles
2. vector + quaternion 
3. homogenous transforms matrix
4. vector a, b (direction and rotation)

They have some advantages and disadvantages. And you can convert the representation 
from one to another.  (Will discuss this more later)

And just like in the 2d version, you can stack these transforms 
on top of one another. 

Rotating about x by angle phi would be like multiplying the point 
with this matrix. 

And these are the matrix also Ry, and Rz respectively.

given that you know the roll pitch and yaw angles
the matrix representation would be 
(a 3x3 matrx)
```
Rxyz = Rx * Ry * Rz

```

If we add a translation (tz, ty, tz) it would be

```
Mxyz = 
```

As in the 2d version
(Rx, Rz, Ry) are the x, y, z axes and
(tx, ty, tz) is the origin of this frame

Please use the visualization and animation tool below

1. Rotate by (alpha, beta, gamma) and translate by (tx, ty, tz)
(this is pA)

2. Then rotate  by (alpha, beta, gamma) and translate by (tx, yz, tz)
(this is pB)

(Animate this!)

Like in the 2d version we can use elementary operations
do the forward kinematics for example to 
do forward kinematics of a robot like the scara



----------
# 6. Other visualizations of 3d operations
----------

https://github.com/mithi/hexapod/blob/master/src/hexapod/geometry.js
- dot product
- cross product 
- normal of three points
- scale vector 
- etc 

----------
# 7. DH parameters and Modified DH Parameters
----------

Explain dh parameters and how use it to describe 
the configuration of purely revolute robot arms 


----------
# 8. Inverse kinematics of a robot with a spherical wrist and no joint offsets Analytical
----------
- https://meuse.co.jp/?p=2732
- https://meuse.co.jp/?p=885
- https://www.eecs.yorku.ca/course_archive/2017-18/W/4421/lectures/Inverse%20kinematics%20-%20annotated.pdf


----------
# 9. 3D visualization of the Inverse Kinematic of an industrial robot with 6 degrees of freedom(Kuka)
----------
- https://www.youtube.com/watch?v=3s2x4QsD3uM&t=3s

----------
# 10. Inverse kinematics of other 6dof robots
----------

- https://github.com/glumb/kinematics 











