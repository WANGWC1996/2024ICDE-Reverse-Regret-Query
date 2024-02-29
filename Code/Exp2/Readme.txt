Readme (Reverse Regret Query)
==================================================
This package contains all source code of algorithm PBA+ that is used as a baseline for comparison in our project. 

Step 1: Libraries gdb, Qhull, lpsolve, rtree, boost, and osqp
---------------------------------------------------- 
This project require several libraries. 
(1). gdb
  To install gdb
  ```
  sudo apt-get update
  sudo apt-get install gdb
  ```
(2). Qhull, a lib that computes the convex hull, Delaunay triangulation, Voronoi diagram, halfspace intersection about a point, furthest-site Delaunay triangulation, and furthest-site Voronoi diagram. Its official website is http://www.qhull.org/  
  To build Qhull, static libraries, shared library, and C++ interface
  ```
  git clone https://github.com/qhull/qhull.git
  cd qhull/build
  cmake --help  # List build generators, get generator for the next step, usually in linux it shall be "Unix Makefiles"
  cmake -G "<generator>" ..    # e.g.,  cmake -G "Unix Makefiles" ..   
  cmake --build .
  sudo cmake --build . --target install
  ```
  

(3). lpsolve, a lib that can solve (mix integer) linear programming problem. Its official website is http://lpsolve.sourceforge.net/5.5/index.htm. Library lpsolve have been embedded in folder /lib/lp_lib

(4). rtree, a data structure lib used for spatial data. Library rtree have been embedded in folder /lib/rtree 
  
(5). boost, a general C++ lib. In this project we mainly use its hash lib. Its official website is https://www.boost.org/
  To install boost
  ```
  sudo apt-get update
  sudo apt-get install libboost-all-dev # after install boost, please check the version of it and change CMakeList.txt of Boost's version
  ```  
  
(6). osqp, a Quadratic Programming lib and its offcial website is https://osqp.org/
  To install osqp
  ```
  git clone --recursive https://github.com/oxfordcontrol/osqp
  cd osqp
  mkdir build
  cd build
  cmake ..
  make
  ```

Step 2: Compile this project
------------
  mkdir build
  cd build
  cmake ..
  make
  ``` 
  
Step 3: Run this project
 ------------
 We have set some settings in config.txt
 You can build an index with setting "buildidx" in config.txt and run as:
 ```
 ./k_level
 ```
 After building an index file, you could load that index file and run with setting "loadidx" in config.txt:
 ```
 ./k_level 
 ```

