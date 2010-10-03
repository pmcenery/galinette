# Include & build
include_directories   (. ../libgalinette)
add_executable        (galinette-flash galinette-flash.c)
add_dependencies      (galinette-flash libgalinette)
target_link_libraries (galinette-flash libgalinette)

# Install
install (TARGETS galinette-flash DESTINATION ${bindir})
