# libKitsunemimiConfig

![Gitlab pipeline status](https://img.shields.io/gitlab/pipeline/tobiasanker/libKitsunemimiConfig?label=build%20and%20test&style=flat-square)
![GitHub tag (latest SemVer)](https://img.shields.io/github/v/tag/tobiasanker/libKitsunemimiConfig?label=version&style=flat-square)
![GitHub](https://img.shields.io/github/license/tobiasanker/libKitsunemimiConfig?style=flat-square)
![C++Version](https://img.shields.io/badge/c%2B%2B-14-blue?style=flat-square)
![Platform](https://img.shields.io/badge/platform-Linux--x64-lightgrey?style=flat-square)

## Description

This library provides a simple interface for reading config files.


## Build

### Requirements

name | repository | version | task
--- | --- | --- | ---
g++ | g++ | 6.x | Compiler for the C++ code.
qmake | qt5-qmake | 5.x | This package provides the tool qmake, to build the project
boost-filesystem library | libboost-filesystem-dev | 1.6x | interactions with files and directories on the system
FLEX | flex | >= 2.6 | Build the lexer-code for all used parser.
GNU Bison | bison | 3.x | Build the parser-code together with the lexer-code.

Installation on Ubuntu/Debian:

```bash
sudo apt-get install g++ qt5-qmake libboost-filesystem-dev flex bison
```

IMPORTANT: All my projects are only tested on Linux. 

### Kitsunemimi-repositories

Repository-Name | Version-Tag | Download-Path
--- | --- | ---
libKitsunemimiCommon | v0.12.1 |  https://github.com/tobiasanker/libKitsunemimiCommon.git
libKitsunemimiPersistence | v0.8.1 | https://github.com/tobiasanker/libKitsunemimiPersistence.git
libKitsunemimiIni | v0.4.2 | https://github.com/tobiasanker/libKitsunemimiIni.git

HINT: These Kitsunemimi-Libraries will be downloaded and build automatically with the build-script below.

### build library

In all of my repositories you will find a `build.sh`. You only have to run this script. It doesn't required sudo, because you have to install required tool via apt, for example, by yourself. But if other projects from me are required, it download them from github and build them in the correct version too. This script is also use by the ci-pipeline, so its tested with every commit.


Run the following commands:

```
git clone https://github.com/tobiasanker/libKitsunemimiConfig.git
cd libKitsunemimiConfig
./build.sh
cd ../result
```

It create automatic a `build` and `result` directory in the directory, where you have cloned the project. At first it build all into the `build`-directory and after all build-steps are finished, it copy the include directory from the cloned repository and the build library into the `result`-directory. So you have all in one single place.

Tested on Debian and Ubuntu. If you use Centos, Arch, etc and the build-script fails on your machine, then please write me a mail and I will try to fix the script.

## Usage by example

Content of example config-file:

```
[DEFAULT]
string_val = asdf.asdf
int_val = 2
float_val = 123.0
string_list = a,b,c
bool_value = true
```

Example usage in code:

```cpp
#include <libKitsunemimiConfig/config_handler.h>

// init configuration
// called anywhere at the beginning of the programm
Kitsunemimi::Config::initConfig(m_testFilePath, errorMessage), true);

bool success = false;

// register values
success = REGISTER_STRING_CONFIG("DEFAULT", "string_val", "");
//     variable success is true
success = REGISTER_INT_CONFIG("DEFAULT", "int_val", 42);
//     variable success is true
success = REGISTER_INT_CONFIG("DEFAULT", "another_int_val", 42);
//     variable success is true

// all register options:
//
// REGISTER_STRING_CONFIG
// REGISTER_INT_CONFIG
// REGISTER_FLOAT_CONFIG
// REGISTER_BOOL_CONFIG
// REGISTER_STRING_ARRAY_CONFIG


std::string firstValue = GET_STRING_CONFIG("DEFAULT", "string_val", success);
//     variable success is true
long number1 = GET_INT_CONFIG("DEFAULT", "int_val", success);
//     variable success is true
long number2 = GET_INT_CONFIG("DEFAULT", "another_int_val", success);
//     variable success is true

// all get options:
//
// GET_STRING_CONFIG
// GET_INT_CONFIG
// GET_FLOAT_CONFIG
// GET_BOOL_CONFIG
// GET_STRING_ARRAY_CONFIG

// get on not registered value
std::string fail = GET_STRING_CONFIG("DEFAULT", "fail", success);
//     variable success is false
```

## Contributing

Please give me as many inputs as possible: Bugs, bad code style, bad documentation and so on.

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details
