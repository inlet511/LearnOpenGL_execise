IF EXIST %~dp0build\NUL (rd /s /q %~dp0build) 
mkdir build & pushd build
echo CurrentDir:%CD%

::mkdir Win64 & pushd Win64
::echo CurrentDir:%CD%
cmake ..
::popd

::mkdir Win32 & pushd Win32
::cmake -G "Visual Studio 16 2019" -A Win32 ../../
::popd

::cmake --build .
::cmake --build Win32
popd