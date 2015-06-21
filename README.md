# dcmtk-basic-example

dcmtk-basic-example demonstrats how to compile, link and include [dcmtk](http://dicom.offis.de/dcmtk.php.en) 3.6.0 toolkit for developing C++11 programs to process DICOM images. The example was developed and tested on Ubuntu 14.04.  

## motivation

When wanting to use dcmtk libraries in my own C++ code, I noticed that basic examples how to link and use dcmtk in Ubuntu 14.04 are scarse. Thus, I decided to make this simple example, to help you guys get started with dcmtk. 


## Compilation and installation (Ubuntu 14.04)

#### Dependencies:
```bash
sudo apt-get install build-essential cmake libdcmtk2-dev
```


#### Get the source code
```bash
git clone https://github.com/marcinwol/mwbarcode
cd mwbarcode
```

#### Compile
```bash
cmake -DCMAKE_INSTALL_PREFIX=/opt/mwimage
make
````
`CMAKE_INSTALL_PREFIX` specifies where the binary should be installed.


#### Install
```bash
make install 
````
 or if root required 
```bash
sudo make install 
````
