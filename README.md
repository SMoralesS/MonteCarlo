# MonteCarlo
In this code we use Monte Carlo methods (specifically Metropolis) to solve the Ising model in 1D, 2D and 3D, and also to find, using path integrals the ground state of two different quantum systems (quantum armonic oscllator and quantum bouncer).

In the MonteCarlo.ipynb notebook are reported all the results found solving the systems using c++

To compile the system just use g++ -std=c++11 MonteCarlo.cpp WaveFunction_interfaz.cpp IsingModel_interfaz.cpp -o MonteCarlo.out in the
command line.

In the file IsingModel_interfaz.cpp are defined the methods of the classes spinConfiguration, spinConfiguration2D and spinConfiguration3D,

And in the file WaveFunction_interfaz.cpp are define the methods of the class particle used in MonteCarlo.cpp
