# curves-test

This is a small test library for supporting 3D curves hierarchy. All curves are parametrically defined.\
There is one sample using this library created for testing purposes.

### Supporting types

* **circle** - defined by radius and centre point. Planar in XoY. Radius must be positive.
* **ellipse** - defined by radii along X and Y axis and centre point. Planar in XoY. Radii must be positive.
* **helix** - defined by radius, step and centre point. Helix is spatial. Step defines distance along Z axis for helix to perform full round.

### Sample usage

Sample creates random curves and prints coordinates and first derivative for parameter t = PI/4.\
It also selects circles sorts them by their radii prints them and calculates their total sum.

#### Sample parameters

* **-s** - initial number of curves.
* **-min_d** **-max_d** - ranges for random generator. This is used for generating coordinates.
* **-max_p** - maximum range for positive random generator. Tsis is used for generating radii and other positive parameters.
* **-t** - defines number of threads for parrallel computations.
