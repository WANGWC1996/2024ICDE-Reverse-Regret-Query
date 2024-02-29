# CMake generated Testfile for 
# Source directory: /Users/wangweicheng/Dropbox/My Mac (王伟程的MacBook Pro)/Desktop/reverse_kregret/VLDB_submission/upload/Code/Exp1
# Build directory: /Users/wangweicheng/Dropbox/My Mac (王伟程的MacBook Pro)/Desktop/reverse_kregret/VLDB_submission/upload/Code/Exp1/cmake-build-debug
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(testqset "./testqset" "10000")
set_tests_properties(testqset PROPERTIES  _BACKTRACE_TRIPLES "/Users/wangweicheng/Dropbox/My Mac (王伟程的MacBook Pro)/Desktop/reverse_kregret/VLDB_submission/upload/Code/Exp1/CMakeLists.txt;650;add_test;/Users/wangweicheng/Dropbox/My Mac (王伟程的MacBook Pro)/Desktop/reverse_kregret/VLDB_submission/upload/Code/Exp1/CMakeLists.txt;0;")
add_test(testqset_r "./testqset_r" "10000")
set_tests_properties(testqset_r PROPERTIES  _BACKTRACE_TRIPLES "/Users/wangweicheng/Dropbox/My Mac (王伟程的MacBook Pro)/Desktop/reverse_kregret/VLDB_submission/upload/Code/Exp1/CMakeLists.txt;652;add_test;/Users/wangweicheng/Dropbox/My Mac (王伟程的MacBook Pro)/Desktop/reverse_kregret/VLDB_submission/upload/Code/Exp1/CMakeLists.txt;0;")
add_test(smoketest "sh" "-c" "./rbox D4 | ./qhull Tv")
set_tests_properties(smoketest PROPERTIES  _BACKTRACE_TRIPLES "/Users/wangweicheng/Dropbox/My Mac (王伟程的MacBook Pro)/Desktop/reverse_kregret/VLDB_submission/upload/Code/Exp1/CMakeLists.txt;654;add_test;/Users/wangweicheng/Dropbox/My Mac (王伟程的MacBook Pro)/Desktop/reverse_kregret/VLDB_submission/upload/Code/Exp1/CMakeLists.txt;0;")
add_test(rbox-10-qhull "sh" "-c" "./rbox 10 | ./qhull Tv")
set_tests_properties(rbox-10-qhull PROPERTIES  _BACKTRACE_TRIPLES "/Users/wangweicheng/Dropbox/My Mac (王伟程的MacBook Pro)/Desktop/reverse_kregret/VLDB_submission/upload/Code/Exp1/CMakeLists.txt;656;add_test;/Users/wangweicheng/Dropbox/My Mac (王伟程的MacBook Pro)/Desktop/reverse_kregret/VLDB_submission/upload/Code/Exp1/CMakeLists.txt;0;")
add_test(rbox-10-qconvex "sh" "-c" "./rbox 10 | ./qconvex Tv")
set_tests_properties(rbox-10-qconvex PROPERTIES  _BACKTRACE_TRIPLES "/Users/wangweicheng/Dropbox/My Mac (王伟程的MacBook Pro)/Desktop/reverse_kregret/VLDB_submission/upload/Code/Exp1/CMakeLists.txt;658;add_test;/Users/wangweicheng/Dropbox/My Mac (王伟程的MacBook Pro)/Desktop/reverse_kregret/VLDB_submission/upload/Code/Exp1/CMakeLists.txt;0;")
add_test(rbox-10-qdelaunay "sh" "-c" "./rbox 10 | ./qdelaunay Tv")
set_tests_properties(rbox-10-qdelaunay PROPERTIES  _BACKTRACE_TRIPLES "/Users/wangweicheng/Dropbox/My Mac (王伟程的MacBook Pro)/Desktop/reverse_kregret/VLDB_submission/upload/Code/Exp1/CMakeLists.txt;660;add_test;/Users/wangweicheng/Dropbox/My Mac (王伟程的MacBook Pro)/Desktop/reverse_kregret/VLDB_submission/upload/Code/Exp1/CMakeLists.txt;0;")
add_test(rbox-10-qhalf "sh" "-c" "./rbox 10 | ./qconvex FQ FV n Tv | ./qhalf Tv")
set_tests_properties(rbox-10-qhalf PROPERTIES  _BACKTRACE_TRIPLES "/Users/wangweicheng/Dropbox/My Mac (王伟程的MacBook Pro)/Desktop/reverse_kregret/VLDB_submission/upload/Code/Exp1/CMakeLists.txt;662;add_test;/Users/wangweicheng/Dropbox/My Mac (王伟程的MacBook Pro)/Desktop/reverse_kregret/VLDB_submission/upload/Code/Exp1/CMakeLists.txt;0;")
add_test(rbox-10-qvoronoi "sh" "-c" "./rbox 10 | ./qvoronoi Tv")
set_tests_properties(rbox-10-qvoronoi PROPERTIES  _BACKTRACE_TRIPLES "/Users/wangweicheng/Dropbox/My Mac (王伟程的MacBook Pro)/Desktop/reverse_kregret/VLDB_submission/upload/Code/Exp1/CMakeLists.txt;664;add_test;/Users/wangweicheng/Dropbox/My Mac (王伟程的MacBook Pro)/Desktop/reverse_kregret/VLDB_submission/upload/Code/Exp1/CMakeLists.txt;0;")
add_test(user_eg "sh" "-c" "./user_eg")
set_tests_properties(user_eg PROPERTIES  _BACKTRACE_TRIPLES "/Users/wangweicheng/Dropbox/My Mac (王伟程的MacBook Pro)/Desktop/reverse_kregret/VLDB_submission/upload/Code/Exp1/CMakeLists.txt;666;add_test;/Users/wangweicheng/Dropbox/My Mac (王伟程的MacBook Pro)/Desktop/reverse_kregret/VLDB_submission/upload/Code/Exp1/CMakeLists.txt;0;")
add_test(user_eg2 "sh" "-c" "./user_eg2")
set_tests_properties(user_eg2 PROPERTIES  _BACKTRACE_TRIPLES "/Users/wangweicheng/Dropbox/My Mac (王伟程的MacBook Pro)/Desktop/reverse_kregret/VLDB_submission/upload/Code/Exp1/CMakeLists.txt;668;add_test;/Users/wangweicheng/Dropbox/My Mac (王伟程的MacBook Pro)/Desktop/reverse_kregret/VLDB_submission/upload/Code/Exp1/CMakeLists.txt;0;")
