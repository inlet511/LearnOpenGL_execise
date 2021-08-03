IF EXIST %~dp0build\NUL (rd /s /q %~dp0build) 
mkdir build & pushd build
echo CurrentDir:%CD%

<<<<<<< HEAD
mkdir Win64 & pushd Win64
echo CurrentDir:%CD%
cmake -G "Visual Studio 16 2019" -A x64 ../../
popd
=======
::mkdir Win64 & pushd Win64
::echo CurrentDir:%CD%
cmake ..
::popd
>>>>>>> 92a39112e79189229a3f3b8e64c9053d348eae73

::mkdir Win32 & pushd Win32
::cmake -G "Visual Studio 16 2019" -A Win32 ../../
::popd

::cmake --build .
::cmake --build Win32
popd