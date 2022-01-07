Configuration for MacOS:
1. Copy SFML lib into ~/Projects/lib forlder or change SFML_PATH in CMakeLists.txt
2. Copy all files from sfml-lib/extlibs to /Library/Frameworks

Configuration for Windows:
1. Copy SFML lib into D:\Projects\lib folder or change SFML_PATH in CMakeLists.txt
2. Copy all files from sfml-lib/bin folder to folder where .exe file

VS Code hint:
To fix inteliSence issue you should manualy add reference to include file in c_cpp_properties.json:

"includePath": [
    "${workspaceFolder}/**",
    "D:/Projects/c++/libs/SFML-2.5.1/include"
]