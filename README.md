# libKitsunemimiConfig

![Github workfloat status](https://img.shields.io/github/actions/workflow/status/kitsudaiki/libKitsunemimiConfig/build_test.yml?branch=develop&style=flat-square&label=build%20and%20test)
![GitHub tag (latest SemVer)](https://img.shields.io/github/v/tag/kitsudaiki/libKitsunemimiConfig?label=version&style=flat-square)
![GitHub](https://img.shields.io/github/license/kitsudaiki/libKitsunemimiConfig?style=flat-square)
![C++Version](https://img.shields.io/badge/c%2B%2B-17-blue?style=flat-square)
![Platform](https://img.shields.io/badge/platform-Linux--x64-lightgrey?style=flat-square)

## Description

This library provides a simple interface for reading config files.


## Build

### Requirements

name | repository | version | task
--- | --- | --- | ---
g++ | g++ | >= 8.0 | Compiler for the C++ code.
make | make | >= 4.0 | process the make-file, which is created by qmake to build the programm with g++
qmake | qt5-qmake | >= 5.0 | This package provides the tool qmake, which is similar to cmake and create the make-file for compilation.
FLEX | flex | >= 2.6 | Build the lexer-code for all used parser.
GNU Bison | bison | 3.x | Build the parser-code together with the lexer-code.

Installation on Ubuntu/Debian:

```bash
sudo apt-get install g++ make qt5-qmake flex bison
```

IMPORTANT: All my projects are only tested on Linux. 

### Kitsunemimi-repositories

Repository-Name | Version-Tag | Download-Path
--- | --- | ---
libKitsunemimiCommon | develop |  https://github.com/kitsudaiki/libKitsunemimiCommon.git
libKitsunemimiIni | develop | https://github.com/kitsudaiki/libKitsunemimiIni.git

HINT: These Kitsunemimi-Libraries will be downloaded and build automatically with the build-script below.

### build library

In all of my repositories you will find a `build.sh`. You only have to run this script. It doesn't required sudo, because you have to install required tool via apt, for example, by yourself. But if other projects from me are required, it download them from github and build them in the correct version too. This script is also use by the ci-pipeline, so its tested with every commit.


Run the following commands:

```
git clone https://github.com/kitsudaiki/libKitsunemimiConfig.git
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
#include <libKitsunemimiCommon/logger.h>

ErrorContainer error;

// init configuration
// called anywhere at the beginning of the programm
Kitsunemimi::Config::initConfig(m_testFilePath, error), true);

// register values
REGISTER_STRING_CONFIG("DEFAULT", "string_val", error, "");
REGISTER_INT_CONFIG("DEFAULT", "int_val", error, 42);
REGISTER_INT_CONFIG("DEFAULT", "another_int_val", error, 42);

// check if config is valid and all registrations were successfull
bool valid = Kitsunemimi::Config::isConfigValid();
// is true in this example
if(valid == false) {
	LOG_ERROR(error);
}

// all register options:
//
// REGISTER_STRING_CONFIG
// REGISTER_INT_CONFIG
// REGISTER_FLOAT_CONFIG
// REGISTER_BOOL_CONFIG
// REGISTER_STRING_ARRAY_CONFIG

bool success = false;

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
