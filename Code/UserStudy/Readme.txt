Readme (Reverse Regret Query - User Study)
==================================================
This package contains all source codes of our user study. There are two folders. 
a. Back. It contains the back-end code
b. Front. It contains the front-end code

Step 1: Run the back-end code on the server. 
------------------------------------------------
 ```
 node server.js
 ```  


Step 2: Run the front-end code on the server. 
------------------------------------------------
# Build Instructions

(1). Set up [Emscripten](https://emscripten.org) SDK.

   ```sh
   # in libraries/
   ./setup_emsdk.sh

   In file emsdk/upstream/emscripten/emcc.py update the content
   ======================================
   UNSUPPORTED_LLD_FLAGS = {
    # macOS-specific linker flag that libtool (ltmain.sh) will if macOS is detected.
    '-bind_at_load': False,
    '-retain-symbols-file': True,
    # wasm-ld doesn't support soname or other dynamic linking flags (yet).   Ignore them
    # in order to aid build systems that want to pass these flags.
    '-soname': True,
    '-allow-shlib-undefined': False,
    '-rpath': True,
    '-rpath-link': True,
    '-version-script': True,
   }
   ======================================

   source emsdk/emsdk_env.sh
   ```

(2). Compile GLPK for Emscripten

   ```sh
   # in libraries/
   ./make_lib.sh em++
   ```

(3). Transcompile C++ code into JavaScript code.
   (The core algorithm is written in C/C++ by Min Xie).

   emcmake cmake ..
   emmake make

   ```sh
   # in the project root folder
   make web
   ```

(4). Install Yarn.
   [Installation Guide of Yarn](https://yarnpkg.com/lang/en/docs/install/)
   brew install yarn

(5). Install dependencies

   ```sh
   # in react-app/
   yarn install
   ```

(6). Run the code

   ```sh
   # in react-app/
   yarn start
   ```

(7). Others. 
   Note that you can build it for deployment. 
   ```sh
   # in react-app/
   yarn run build
   ```
   The built webpages are placed in the `react-app/build/` folder.
