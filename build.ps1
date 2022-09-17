Import-Module "C:\Program Files\Microsoft Visual Studio\2022\Enterprise\Common7\Tools\Microsoft.VisualStudio.DevShell.dll"
Enter-VsDevShell e5147e7b -StartInPath .
mkdir build
cd build
cmake -G "NMake Makefiles" ..
nmake
cd ..
copy build\test.uf2 D:test.uf2