# bluetooth-file-transfer
An assingnment Mini-Project under subject Mobile Computing & Wireless Communication,We have implemented this mini project, using a library called BlueZ.
Curently this library is compitible with Linux.
## Functionalities of the mini project
* To scan and search for devices in bluetooth range.
* To count the number of devices available in the range.
* To transfer a file from client to server using bluetooth.

## Installing BlueZ
First download the tarball file from [BlueZ](https://www.kernel.org/pub/linux/bluetooth/bluez-5.47.tar.xz) - The library used. Use [this](http://www.linuxfromscratch.org/blfs/view/svn/general/bluez.html) page as guide while installing. Make sure you install all the dependencies, Otherwise the installation will be failed.
## Compilation and executing
### Scanning for nearby bluetooth devices
Compile and execute the simpleSacn.c file using following command:
```
gcc simpleScan.c -o simpleScan -lbluetooth
./simepleScan
```
The flag '-lbluetooth' tells the compiler to use the bluetooth libraries.

This will output List of nearby devices, their bluetooth address and total number of devices in that area.
### File transfering from client to server (server should be executed first)
Compile and execute the server.c file using following command:
```
gcc server.c -o server -lbluetooth
./server
```
Compile and execute the client.c file using following command:
```
gcc client.c -o client -lbluetooth
./clinet
```
The test.txt file in the folder that contains clinet.c, will be sent to server.
