Import-Module "C:\Program Files\Microsoft Visual Studio\2022\Community\Common7\Tools\Microsoft.VisualStudio.DevShell.dll"
Enter-VsDevShell -VsInstallPath "C:\Program Files\Microsoft Visual Studio\2022\Community" -StartInPath .
mkdir build
cd build
cmake -G "NMake Makefiles" ..
nmake
cd ..
copy build\test.uf2 D:test.uf2

