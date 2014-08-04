The Ghost Fly
=============

This project is part of a Computer Graphics and Image Processing (PICG in Portuguese) class at Universidade Federal de Sergipe. It basically is a Scene creator that loads OBJ files and place them in rooms randomly and you can navigate through the scene. The project is made with C++ with OpenGL. More information in the Project Description Section.

Environment
-------------
* MacOS X 10.9.4 (Mavericks)
* OpenGL 2.1
* [GLFW3](http://www.glfw.org/) Open Source, multi-platform library for creating windows with OpenGL contexts and receiving input and events.
* [SOIL](http://www.lonesock.net/soil.html) Simple OpenGL Image Library. The version used 
in the project is a version with some minor changes in the Makefile by Stephen Barber [available here](https://github.com/smibarber/libSOIL)
* [GLM](http://glm.g-truc.net/0.9.5/index.html) OpenGL Mathematics.
* XCode 5.1.1 using g++ version 4.2.1

Project Description
-------------
The project consists of a static scene visualizer. We had to construct a scene composed by a plane, rooms and objects located in these rooms. Both rooms and objects must be above the plane, which will simulates the scene floor.

The user should see the scene like he was a “ghost fly”, that can fly through the scene and go trough walls and objects. This means that the collision detection shouldn’t be handled, and the camera can:
* Look up, down, left and right
* Move forward and backward at the direction it is

The number of objects in the room is limited based on the size (hard-coded) of each object and the room size (also hard-coded). The bigger the room, more objects can be placed. The smaller the objects are, more objects can be placed. The objects placement is grid-based but the order is random.

Input
-------------
The program input is how many rooms you will create, followed by the description for each room. Each room will have a number of objects for 2 models: a dog and a cat. The program input follows the model:
```
3
s1 o1 3 2 o2 6 3
s2 o1 3 0 o2 6 1
s3 o1 8 1 o2 2 2
```

Each room description has 2 type of objects: object1 (o1) and object2 (o2). The numbers that follow each object is its average and deviation number. In the first case, the room will have between (3-2 = 1) and (3+2 = 5) object1s. this input example is in the input.txt file

The number of rooms is code limited in the common.hpp file. Any try to give a larger number will be ignored and the maximum will be used.

After the input, the window will display the number of rooms according to the given data.

Controls
-------------
* Keyboard: WSAD to move around, Left Shift for speed boost and L for light switching
* Mouse: Just move it to look around

Sources
-------------
* [Cat model](http://tf3dm.com/3d-model/cat-95027.html)
* [Dog model](http://tf3dm.com/3d-model/dog-87991.html)

License
-------------
This is just a school project, so feel free to use it for academic purposes. Author: Matheus A C de Andrade
