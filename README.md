Game of Life
========================

Federico Soave, MCSN student

### Shared libraries

- `Matrix.o` main GameOfLife logic code
- `MatrixG.o` graphical version, needs OpenCV3 to compile


### Executables

Running any of the below without arguments provides the user with a help message:
	
	Usage: ./main.out [<params>]
	Where <params> are:
	  --thread | -t <number>  number of threads
	  --height | -h <number>  height of the matrix
	  --width  | -w <number>  width of the matrix
	  --step   | -s <number>  number of steps
	  --check  | -c           print hashcodes
	  --bottles               draw some Bottles
	  --engines               draw some Schick's Engines
	  --gliders               draw some Gliders
	  --guns                  draw some Gosper's Guns
	  --blobs                 draw some Blobs
	  --heads                 draw some Hammerheads
	  --help   | -?           print this help
	If no patterns are drawn, the World will be initialized at random.


- `main.out`     POSIX threads parallel implementation
- `main.ff.out`  FastFlow parallel implementation
- `main.seq.out` sequential implementation
- `main.x.out`   graphical (pthreads) version, needs OpenCV3.
	This program allows to test the correctness of the algorithm by visualizing
	some example well-known patterns.


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

When switching from one makefile to the other, remember to `make clean` beforehand, or use the `-B` flag.


Verification
---------------------------

The graphical version allows to easily verify the correctness by providing some example well-known patterns.
For example, try running

	./main.x.out --height 500 --width 500 --step 1000 --engines --guns

to see some Schick's Engines lose battle to a batallion of Gosper's Guns.

To check that all programs produce consistent results, the `--check` (`-c`) flag can be used. If enabled, the program outputs a pair of 128-bit hex-encoded hashes computed from the matrix at its first and last iteration, respectively. For any given pair _width,height_, the initial state should always be the same and, for any given pair _initial state,steps_, the final state should always be the same.


Running
----------------------------

All executable are typically run in this way:

	./main.out -w <width> -h <height> -s <steps> -t <threads>

No output is printed, unless the `-c` flag is present.
The matrix is randomly initialized before starting the actual computation.