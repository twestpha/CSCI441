Innocent Until Proven Guildy / Chris Rice (crice@mines.edu), Tim Ross (tross@mines.edu), Trevor Westphal (twestpha@mines.edu)

Guild Wars

This program builds a 3D world with trees and flags and 3 heros. One hero is controllable by the user, the other heros are each set on a track. There are two light in the world, one is stationary and the other circles above the world.

Mouse controls: click and drag to move the camera
Keyboard controls: 'w' and 's' moves Tim the Enchanter forward and back and 'a' and 'd' turn
Right click: Bring up a menu
Menu Options:
	-Display Control Cage: Toggle whether the Control Cage is displayed
	-Display Bezier Curve: Toggle whether the bezier curve is displayed
	-Use free Camera: Gives the user control of a free camera instead of using the arcball camera
	-Use Acrball Camera: Changes the camera to a arcball camera. This option has a submenu which lets the user choose which hero the camera follows.
	-Show/Hide first person camera: toggles whether the first person viewport is shown. This is shown in the bottom left hand corner of the screen.
	-First person Camera Target: This option has a submenu which lets the user choose who's face to look through for the first person camera


To build the program, run make using the Makefile. To execute the program, use the 'guildwars.exe' file.

bugs:
	We had some issues loading in larger bezier curves which we never resolved.

file format:
	We just used JSON as our file format. This was very easy to read

Contributions:
Chris:
-Cameras
-Bezier Curve arc length parameterization
-Lights
-Materials
-Text rendering and input handling

Tim:
-virtual HeroBase class
-Hero: tim_the_enchanter (Hero_tim class)
-animated light
-sub menus with camera switching between heros

Trevor:
-Cameras
-File IO
-Bezier Patch
-Bezier Curve


how long did it take you?
	A week or so

how much did lab help? 1-10
	9/10

how fun was it? 1-10
	9/10
