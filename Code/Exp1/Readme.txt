Readme (Reverse Regret Query)
=========================
This package contains all source codes for 
a. Algorithm 2DSW 
	1. It only works for the special case of RRQ.
	2. The code is in folder 2DSW.
b. Algorithm APC 
	1. It works for the general case of RRQ. 
	2. The code is in folder HDSP.
c. Algorithm APC-AC 
	1. It works for the general case of RRQ and used for the accuracy experiment.
	2. The code is in folder HDSP.
d. Algorithm EPT 
	1. It works for the general case of RRQ. 
	2. The code is in folder HDSP.
e. Algorithm LPCTA
	1. It is an existing algorithm used for comparison. 
	2. The code is in folder LPCTA. 


Make sure there is a file called "config.txt" under the working directory. They will be used for storing the input parameters.

Usage Step
==========
a. Compilation
	mkdir built
	cd built
	cmake ..
	make

	You will need to install the GLPK package (for solving LPs) at first.
	See GLPK webpage <http://www.gnu.org/software/glpk/glpk.html>.
	Then update the path in CMakeLists.txt
		set(INC_DIR /usr/local/Cellar/glpk/5.0/include)
		set(LINK_DIR /usr/local/Cellar/glpk/5.0/lib)
	Update path "/usr/local/Cellar/glpk/5.0" to the path you install the GLPK package
	
b. Execution
	./run

	You can set the algorithm name in file config.txt to run different algorithms. 
	(1). 2DSW for 2DSW
    (2). APC for APC
    (3). APC-AC for APC-AC
    (4). EPT for EPT
    (5). LPCTA for LPCTA
	
c. Results
	The execution time will be shown in the console. 