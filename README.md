# EECE 2560 Projects

Group members:
 - David Cree <[cree.d@northeastern.edu](mailto:cree.d@northeastern.edu)>
 - Brian Schubert <[schubert.b@northeastern.edu](mailto:schubert.b@northeastern.edu)>
 
Group ID: `8-schcre`

Projects from our EECE 2560 _Fundamentals of Engineering Algorithms_ course 
taken Fall 2020 at Northeastern University.

## Building

All project targets are specified using CMake. 

### Using Makefiles
To build all projects using GNU or Unix Makefiles, run

```shell
$ mkdir cmake-build
$ cd cmake-build
$ cmake .. -G"Unix Makefiles"
$ make all
```
The `-G"Unix Makefiles` flag is not required if this is the default generator 
for your system.

### Using CLion
CLion will recognize CMake targets automatically. No additional configuration required.


### Using MS Visual Studio

Either follow the steps in [Microsoft's documentation](https://docs.microsoft.com/en-us/cpp/build/cmake-projects-in-visual-studio?view=vs-2019)
for building CMake projects, or generate Visual Studio project files manually by running
```shell
$ cmake . -G"Visual Studio 16 2019"
```
See the [CMake documentation](https://cmake.org/cmake/help/latest/manual/cmake-generators.7.html#visual-studio-generators) for a list of supported Visual Studio generators.

### Using Xcode
Xcode project files can be generated by running
```shell
$ cmake . -G"Xcode"
```
