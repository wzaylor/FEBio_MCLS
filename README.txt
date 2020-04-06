FEBio Setup
----------------------------------------------------------------------------
1) Install Intel Parallel Studio.
This installs the Intel compiler and Intel MKL (Math Kernel Library).
You may be able to get a Student license for Intel Parallel Studio.
    a) Sign up for an Intel profile to get Intel Parallel Studio, then download the package. (https://software.intel.com/en-us/parallel-studio-xe/choose-download/student-windows)
    b) Extract the file, then open a terminal and navigate to the directory.
    c) Enter this command to execute the installation wizard: sudo ./install_GUI.sh
    d) Test the install by opening a terminal and entering the command: 
        source /opt/intel/bin/compilervars.sh intel64
    Then enter this command if there were no error messages:
        icpc -help

2) Install Levmar
    a) Download Levmar from this link: http://users.ics.forth.gr/~lourakis/levmar/index.html
    b) Extract the package to a directory, such as /home/username/Programs
    c) If you are using a linux computer, change the file "FEBioSource2.9/build/lnx64d.mk" to have the levmar variables reflect the levmar directory.
    For example:
        # Levmar library
        LEV_LIB = -L/home/will/Programs/levmar-2.6 -llevmar
        LEV_INC = /home/will/Programs/levmar-2.6
    d) Build levmar with cmake.

3) Move Include and lib directories to the build directory
The "lib" directory has files too large for the repository, and they can be found in the original version of the source code, so they must be added manually.
    a) Copy 'febio_source_2.9.zip' to a different directory
    b) MAKE SURE YOU ARE NOT IN THIS DIRECTORY (or else you will overwrite the local files), extract 'febio_source_2.9.zip'
    c) Copy the /FEBioSource2.9/build/lib directory to the same location in this project's directory.

4) Try to build the package.
This describes how to build the package using a terminal, though you should setup a build task in vscode to make things easier.
    a) Navigate to FEBioSource2.9/build
    b) Enter the command (this only needs to be done once): bash Mkdir.bash lnx64
    c) Enter the command (this needs to be done every time you want to run a build in a new terminal): source /opt/intel/bin/compilervars.sh intel64
    d) Enter the command: make lnx64

If you get the following error:
    catastrophic error: cannot open source file "sys/cdefs.h"
    a) Open a terminal and enter this command: sudo apt-get install libc6-dev-i386