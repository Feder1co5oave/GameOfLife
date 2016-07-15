Game of Life
========================

Federico Soave, MCSN student

### Shared libraries
- `Matrix.o` main GameOfLife logic code
- `MatrixG.o` graphical version, needs OpenCV3 to compile
- `Barrier.o` the thread barrier

### Executables
Running any of the below without arguments provides the user with a help message.
- `main.out`     POSIX threads parallel implementation
- `main.ff.out`  FastFlow parallel implementation
- `main.seq.out` sequential implementation
- `main.x.out`   graphical (parallel) version, needs OpenCV3.
	This program has a different parameter format and allows to test the correctness of the algorithm by providing
	some example patterns.


Compiling
-------------------------

Compilation is done via `make`. Three makefiles are provided to address different target machines:

- `makefile` suitable for compilation on a generic GNU/Linux operating system
	- the `OPENCV` variable should be set to contain the correct compilation flags to include the OpenCV3 libraries.
		If these libraries are globally installed on the system, the provided `pkg-config` command should automate this task.
	- the `FF_ROOT` variable should be set to the absolute path containing the fastflow source code
- `makefile.xeon` suitable for compilation on the Xeon host machine with the Intel C++ compiler
	- the `FF_ROOT` variable should be set to the absolute path containing the fastflow source code
- `makefile.mic` suitable for cross-compilation for the MIC architecture

For example, to compile the FastFlow version for the MIC, run:

	cd src
	make -f makefile.mic main.ff.out


Verification
---------------------------

The graphical version allows to easily verify the correctness by providing some sample well-known patterns.
For example, try running

	./main.x.out --height 500 --width 500 --step 1000 --engines --guns

to see some Schick's Engines lose battle to a batallion of Gosper's Guns.


Running
----------------------------

Apart from the graphical version, all executable are to be run in this way:

	./main.out <size> <steps> <threads>

where `<size>` is the side length of the square matrix, `<steps>` is the number of iterations to be computed and `<threads>` is the number of workers to be run.
No output is printed.
The matrix is randomly initialized before starting the actual computation.