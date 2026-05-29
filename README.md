# webpix

Description
-----------
Simple webcam / screen capture.
Written in C++ for Linux.
Requires OpenCV.

Installation of OpenCV
----------------------
1. Download snapshot of repository (around 90Mb) and unpack it:
   $ mkdir ocv
   $ cd ocv
   $ wget -O opencv.zip https://github.com/opencv/opencv/archive/4.x.zip
   $ unzip opencv.zip
   $ mv opencv-4.x opencv

2. Create build directory:
   $ mkdir -p build && cd build

3. Generate build scripts for the preferred build system:
   $ cmake ../opencv

4. Run actual compilation process:
   $ make -j4

5. Check libraries and executables:
   $ ll lib
   $ ll bin

6. Install OpenCV:
   $ sudo make install

7. Check installed files:
   $ ll /usr/local/bin
   $ ll /usr/local/include
   $ ll /usr/local/share/

