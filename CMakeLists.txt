# ECEE 2560 Projects CMake configuration.
#
# Author:   Brian Schubert  <schubert.b@northeastern.edu>
# Date:     2020-09-15
#

cmake_minimum_required(VERSION 3.10)
project(eece_2560_projects
        DESCRIPTION "EECE 2560 / Fundamentals of Engineering Projects."
        LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# List of subdirectories corresponding to ECEE2560 projects.
set(EECE2560_PROJECT_LIST
#        8-schcre-non-existent-project-test-sentinel
        8-schcre-1
        8-schcre-2
        8-schcre-3
        8-schcre-4
        8-schcre-5)

add_subdirectory(common)

# Iterate over course project subdirectories and add those that exist to the
# Cmake configuration.
#
# When a course-project is being submitted for grading, this CMake-project may only
# contain a subset of the course-project subdirectories. To make sure that this
# build configuration still works when course-project directories are missing,
# we only add CMake configurations for course-projects that exists.
foreach (PROJ_DIRECTORY ${EECE2560_PROJECT_LIST})
    if (EXISTS "${CMAKE_SOURCE_DIR}/${PROJ_DIRECTORY}")
        add_subdirectory("${CMAKE_SOURCE_DIR}/${PROJ_DIRECTORY}")
    else ()
        message(WARNING "Cannot find project ${PROJ_DIRECTORY} - ignoring this project")
    endif ()
endforeach ()

