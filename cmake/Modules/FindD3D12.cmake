#.rst:
# FindD3D12
# ----------
#
# Try to find D3D12
#
# IMPORTED Targets
# ^^^^^^^^^^^^^^^^
#
# This module defines :prop_tgt:`IMPORTED` target ``D3D12::D3D12``, if
# D3D12 has been found.
#
# Result Variables
# ^^^^^^^^^^^^^^^^
#
# This module defines the following variables::
#
#   D3D12_FOUND          - True if D3D12 was found
#   D3D12_INCLUDE_DIRS   - include directories for D3D12
#   D3D12_LIBRARIES      - link against this library to use D3D12
#   DXGI_INCLUDE_DIRS    - include directories for DXGI
#   DXGI_LIBRARIES       - link against this library to use DXGI
#
# The module will also define two cache variables::
#
#   D3D12_INCLUDE_DIR    - the D3D12 include directory
#   D3D12_LIBRARY        - the path to the D3D12 library
#   DXGI_INCLUDE_DIR     - the DXGI include directory
#   DXGI_LIBRARY         - the path to the DXGI library
#

# Find the Windows 10 SDK path.
get_filename_component(WIN10_SDK_PATH "[HKEY_LOCAL_MACHINE\\SOFTWARE\\WOW6432Node\\Microsoft\\Microsoft SDKs\\Windows\\v10.0;InstallationFolder]" ABSOLUTE CACHE)
get_filename_component(WIN10_SDK_VERSION "[HKEY_LOCAL_MACHINE\\SOFTWARE\\WOW6432Node\\Microsoft\\Microsoft SDKs\\Windows\\v10.0;ProductVersion]" NAME)


# WIN10_SDK_VERSION will be something like 10.0.14393 or 10.0.14393.0; we need the
# one that matches the directory name.
if (IS_DIRECTORY "${WIN10_SDK_PATH}/Include/${WIN10_SDK_VERSION}.0")
  set(WIN10_SDK_VERSION "${WIN10_SDK_VERSION}.0")
endif (IS_DIRECTORY "${WIN10_SDK_PATH}/Include/${WIN10_SDK_VERSION}.0")

# Find the d3d12 include path, it will typically look something like this.
# C:\Program Files (x86)\Windows Kits\10\Include\10.0.10586.0\um\d3d12.h
find_path(D3D12_INCLUDE_DIR    # Set variable D3D12_INCLUDE_DIR
          d3d12.h                # Find a path with d3d12.h
          HINTS "${WIN10_SDK_PATH}/Include/${WIN10_SDK_VERSION}/um"
          DOC "path to DirectX 12 SDK header files"
          HINTS
          )

if(CMAKE_SIZEOF_VOID_P EQUAL 8)
    find_library(D3D12_LIBRARY NAMES d3d12.lib
                 HINTS ${WIN10_SDK_PATH}/Lib/${WIN10_SDK_VERSION}/um/x64 )
elseif(CMAKE_SIZEOF_VOID_P EQUAL 4)
    find_library(D3D12_LIBRARY NAMES d3d12.lib
                 HINTS ${WIN10_SDK_PATH}/Lib/${WIN10_SDK_VERSION}/um/x86 )
endif()

set(D3D12_LIBRARIES ${D3D12_LIBRARY})
set(D3D12_INCLUDE_DIRS ${D3D12_INCLUDE_DIR})


# Find the dxgi include path, it will typically look something like this.
# C:\Program Files (x86)\Windows Kits\10\Include\10.0.10586.0\shared\dxgi1_4.h
find_path(DXGI_INCLUDE_DIR    # Set variable DXGI_INCLUDE_DIR
          dxgi1_6.h           # Find a path with dxgi1_6.h
          HINTS "${WIN10_SDK_PATH}/Include/${WIN10_SDK_VERSION}/shared"
          DOC "path to Microsoft DirectX Graphics Infrastructure header files"
          HINTS
          )

if(CMAKE_SIZEOF_VOID_P EQUAL 8)
    find_library(DXGI_LIBRARY NAMES dxgi.lib
                 HINTS ${WIN10_SDK_PATH}/Lib/${WIN10_SDK_VERSION}/um/x64 )
elseif(CMAKE_SIZEOF_VOID_P EQUAL 4)
    find_library(DXGI_LIBRARY NAMES dxgi.lib
                 HINTS ${WIN10_SDK_PATH}/Lib/${WIN10_SDK_VERSION}/um/x86 )
endif()		  

set(DXGI_LIBRARIES ${DXGI_LIBRARY})
set(DXGI_INCLUDE_DIRS ${DXGI_INCLUDE_DIR})


include(FindPackageHandleStandardArgs)
# handle the QUIETLY and REQUIRED arguments and set D3D12_FOUND to TRUE
# if all listed variables are TRUE
find_package_handle_standard_args(D3D12  DEFAULT_MSG
                                  D3D12_INCLUDE_DIRS D3D12_LIBRARIES
								  DXGI_INCLUDE_DIRS DXGI_LIBRARIES)

mark_as_advanced(D3D12_INCLUDE_DIRS D3D12_LIBRARIES DXGI_INCLUDE_DIRS DXGI_LIBRARIES)


if(D3D12_FOUND AND NOT TARGET D3D12::D3D12)
  add_library(D3D12::D3D12 UNKNOWN IMPORTED)
  set_target_properties(D3D12::D3D12 PROPERTIES
    IMPORTED_LOCATION "${D3D12_LIBRARIES}"
    INTERFACE_INCLUDE_DIRECTORIES "${D3D12_INCLUDE_DIRS}")
endif()

if(D3D12_FOUND AND NOT TARGET D3D12::DXGI)
  add_library(D3D12::DXGI UNKNOWN IMPORTED)
  set_target_properties(D3D12::DXGI PROPERTIES
    IMPORTED_LOCATION "${DXGI_LIBRARIES}"
    INTERFACE_INCLUDE_DIRECTORIES "${DXGI_INCLUDE_DIRS}")
endif()