:# README #

This project runs on linux machines out of the box. To run in other platforms makefiles should be modified accordingly. 
The follwing dependencies are required:

## GNU Scientific Library (GSL)
This is a numerical library for C and C++ programmers. It is free software under the GNU General Public License.
## CPGPLOT Graphix Library. 
This is a set of functions written in C relying on cpgplot primitives from pgplot, and plplot. As a consequence, the CPGPLOT Graphix library, in turns, depends on: 
### [pgplot](/http://www.astro.caltech.edu/~tjp/pgplot/)
### [plplot](http://plplot.sourceforge.net/)
You can git clone the CPGPLOT library from my repository upon request (dalonso@ceab.csic.es).

### What is this repository for? ###

* This repository sets up a number of Sexual-Transmitted Disease Models with application to the spread of HIV-AIDS in heterogeneous populations in endemic regions from Africa 
* Version: 0.0.0.999
* [Learn Markdown](https://bitbucket.org/tutorials/markdowndemo)

### How do I get set up? ###

First you should install the libraries to meet the dependencies mentioned above. Look for GSL, pgplot and libplplot12 in your usual package handler.
Notice that the linking command from most makefiles contains, at least, the following libraries:

* -lgsl -lgslcblas 
* -lWL -lpng -lplplotd -lpgplot -lcpgplot 
* -lda_cpgplot_XY_GRID_FILE -lda_cpgplot_BASIC

The first two ones are basic GSL libraries. The following 5 are required to use primitive plotting functions from the graphic libraries cpplot and plplot. The final two are mandatory when using higher-level plotting functions from the CPGPLOT Graphix library. All of them are usually required to produce a graphical output. However, the control variable (see 
any makefile) 'CPG" can also be set up to 'NON_CPG_REPRESENTATION' and, then, through conditional compilation, the same program is built
to just run the numerical computations. In all cases, the output may be saved in files. 

When you git clone the repository on your machine, you should do it from your home directory. As a result, the directory 'project_std-aids_models' will be expanded on ~/project_std_aids_models, as usual. Then, do:

~$ ln -s project_std_aids_models PROJECT_STD_AIDS_MODELS 

If graphic libraries have been correctly installed, this symbolic link should be enough to make all makefiles work out of the box.  

* Summary of set up:
	+ #### 1. Install GSL library
	+ #### 2. Install plplot library
	+ #### 3. Install pgplot library
	+ #### 4. 
	+ #### 5. git clone https://p252205@bitbucket.org/p252205/project_std_aids_models.git
	+ #### 6. Tests: 
	In order to test if pgplot, plplot and CPGPLOT are correctly installed in your machine, you can expand the tar file PROJECT_CPGPLOT_EXAMPLES.tar, which is in the project root directory on your home directory. Then you will get the directory ~/PROJECT_CPGPLOT_EXAMPLES. In that directory, there is a simple example of how to use the CPGPLOT library. You build it by typing:
	
		+ ~/PROJECT_CPGPLOT_EXAMPLES/make
		
		and you will get the exectutable file PLOT. You may run the example with some command arguments (see main.c). You should get a graph with four different subplots. You may also type:
		
		+ ~/PROJECT_CPGPLOT_EXAMPLES/PLOT -h
		
		and see other available command line arguments. You may also type: 
		
		+ ~/PROJECT_CPGPLOT_EXAMPLES/PLOT -G29 ?
		
	and see the different avaiable graphic formats in which plots can be saved. Notice that sometimes the value for these input arguments is overriden by the internal program code. When this happens, it is for a good reason. Please check the code to understand why and make moodgodfications at your own risk. Be creative.   
	
	+ #### 7. Examples:
	See, for instance, ./MODEL_CALCULATIONS/TEMPORAL_EVOLUTION_DETERMINISTIC/main.c, and follow the directions to compile and run the code: 
		
		+ ~$ make 
		
		+ ~$ ./XWSILD-YSILD -h  (for help on input arguments)
		
		+ ~$ ./XWSILD-YSILD -S0 5 -n 6 -v0 12 -v1 13 -v2 14 -v3 15 -v4 16 -v5 18 -G0 3 -G1 2 -tn 5000 -t0 0.0 -t1 100.0 -t4 0 -xn 0 -xN 100000

### Contribution guidelines ###

* Writing tests
* Code review
* Other guidelines

### Who do I talk to? ###

* Drop an email to David Alonso (<dalonso@ceab.csic.es>)
