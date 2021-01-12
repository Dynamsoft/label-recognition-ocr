# Label Recognition Samples
DLR ([Dynamsoft Label Recognition](https://www.dynamsoft.com/label-recognition/overview)) C/C++ sample code for `Windows` and `Linux`.

## Version
1.0 Beta

## Requirements
- [Visual Studio](https://www.visualstudio.com/downloads/)
- [CMake](https://cmake.org/download/)
- [Dynamsoft Label Recognition 1.0 Beta](https://www.dynamsoft.com/label-recognition/downloads)

## License
Get a [free trial license](https://www.dynamsoft.com/customer/license/trialLicense) and save it to `license.txt`.

## Contact Us
https://www.dynamsoft.com/Company/Contact.aspx

## Windows
1. Copy *.lib files to platforms\win\lib and copy *.dll files to platforms\win\bin folder.

2. Create a build folder:

    ```
    mkdir build
    cd build
    ```

3. Configure and build the project:

    ```
    // x86
    cmake -DCMAKE_GENERATOR_PLATFORM=x86 ..

    // x64
    cmake -DCMAKE_GENERATOR_PLATFORM=x64 ..

    cmake --build . --config release
    ```

4. Run the app:

    ```
    Release\BarcodeReader license.txt
    ```

## Linux
1. Install CMake:

    ```
    sudo apt-get install cmake
    ```

2. Copy *.so files to platforms\linux.
3. Create a build folder:
    
    ```
    mkdir build
    cd build
    ```

4. Configure and build the project:

    ```
    cmake ..
    cmake --build . --config release 
    ```

5. Run the app:

    ```
    Release\BarcodeReader license.txt
    ```