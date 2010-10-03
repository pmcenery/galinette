# Dependencies
find_package      (PkgConfig)
pkg_check_modules (DBUS       REQUIRED   dbus-1>=1.2.12)
pkg_check_modules (DBUS-GLIB  REQUIRED   dbus-glib-1>=0.80)
pkg_check_modules (GTK2       REQUIRED   gtk+-2.0>=2.16.1)
pkg_check_modules (HAL        REQUIRED   hal>=0.5.12)

# Main config
add_definitions(-DUIFILE="${CMAKE_INSTALL_PREFIX}/${sharedir}/galinette_gtk.ui")
add_definitions(-DGALINETTE_VERSION="${GALINETTE_VERSION}")

# Include & build
include_directories   (. ${DBUS_INCLUDE_DIRS} ${DBUS-GLIB_INCLUDE_DIRS} ${GTK2_INCLUDE_DIRS} ${HAL_INCLUDE_DIRS})
add_executable        (galinette callbacks.c callbacks.h galinette-gtk.c galinette_gtk.ui galinette-gtk.h hal.c hal.h main.c)
add_dependencies      (galinette libgalinette)
target_link_libraries (galinette libgalinette ${DBUS_LIBRARIES} ${DBUS-GLIB_LIBRARIES} ${GTK2_LIBRARIES} ${HAL_LIBRARIES})

# Other resources
add_custom_target (galinette_gtk.ui)

# Install
install (TARGETS galinette        DESTINATION ${bindir})
install (FILES   galinette_gtk.ui DESTINATION ${sharedir})
