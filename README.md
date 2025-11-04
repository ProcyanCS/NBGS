# NBGS

N-Body Gravitational Simulator



Author:
James Price


Description: N-Body Gravitational Simulator (NBGS) is an attempt to create a large scale physics engine to simulate stellar gravitational interactions in groups.



Future Features:	
=============================================================================
* Change to modular interactions, e.g. Gravity, Electromagnetic, Strong, Collisions, etc. that can be imported into a simulation
* Simulation controls with stepping frame by frame, forward and reverse
* Data dialog for observing particle trajectory parameters in real-time
* Population generation methods for creating random simulations
* Visualization Tools for tracking individual particles
* Deployment Scripts (since Qt is not behaving with POST_LINK actions
* Sample datasets such as an Orrery, binary companions, ellipitcal galaxy box orbits, Poission distributions, particle in a box demonstrations
* Regression and Unit testing


Regression Tests:
=============================================================================
* CSV import/export functionality: load test.csv, save test\_out.csv, load test\_out.csv, save test\_out2.csv, diff test.csv, test\_out.csv, test\_out2.csv
* forward/reverse frames synchronous data
