IF EXIST %~dp0build\NUL (rd /s /q %~dp0build) 
mkdir build & pushd build
echo CurrentDir:%CD%

mkdir Win64 & pushd Win64
echo CurrentDir:%CD%
cmake -G "Visual Studio 15 2017" -A x64 ../../
popd

::mkdir Win32 & pushd Win32
::cmake -G "Visual Studio 15 2017" -A Win32 ../../
::popd

cmake --build Win64
::cmake --build Win32
popd