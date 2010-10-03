# Dependencies
find_package          (PkgConfig)
pkg_check_modules     (FTDI  REQUIRED  libftdi>=0.13)

# Include & build
include_directories   (.)
add_library           (libgalinette SHARED device.c error.c firmware.c flash.c libgalinette.h libgalinette-private.h)
set_target_properties (libgalinette PROPERTIES PREFIX "" LINK_INTERFACE_LIBRARIES "" SOVERSION 0) 
target_link_libraries (libgalinette ${FTDI_LIBRARIES})

# Install
install (TARGETS libgalinette LIBRARY DESTINATION ${libdir})
