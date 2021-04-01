**************************************

ZIA / C++
Conan / Cmake

Maxence Pellerin
Jonathan Hugonnard-Bruyère
Erin Grouille
Thomas Prugnon

**************************************

mkdir build && cd build && conan install .. --build=missing && cmake
.. -G “Unix Makefiles” && cmake --build . --config "RelWithDebInfo"

./zia IP port

**************************************

The zia project contains and comply to the zia-api elected
by the EPITECH LYON 2021 teams for the zia project.

**************************************

The zia executable takes its module configuration from the file config.yaml.
If the file is missing or invalid, the zia initializes with no modules.

**************************************

Modules must be compiled as libs having the name of the module in the config.yaml.
All modules must have a load_module function as specified in the Module.h file of the zia-api.
Modules must comply to the zia-api.

**************************************
