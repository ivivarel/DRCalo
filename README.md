# DRCalo

This package provides an integrated build for the IDEA dual readout standalone simulation, digitisation and reconstruction. The simulation and digitisation are introduced as submodules, and developed independently in their own repositories.

To use the package (from a machine mounting /cvmfs): 
* checkout the package 

```git clone --recursive git@github.com:ivivarel/DRCalo.git```

* source the key4hep stack 

``` source DRCalo/setup_key4hep.sh``

* build the package
```
mkdir build 
cd build 
cmake ../DRCalo
make && make install
```
* configure the environment to use the package

```source setup.sh```
* The directories x86_64-centos7-gcc8-opt/python and x86_64-centos7-gcc8-opt/bin contain a number of scripts and executables that demonstrate how to use the package. In particular, the python/run_digitization.py and python/test_digitization.py run and validate the digitization.  
   
