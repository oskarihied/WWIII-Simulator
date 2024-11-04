# Define the list of search paths for headers and libraries
set(FIND_BOX2D_PATHS
    /usr
)

# Library
find_library(BOX2D_LIBRARY
    NAMES
        box2d
    PATHS
        ${FIND_SFML_PATHS}  
)

# Include directory
find_path(BOX2D_INCLUDE_DIR
    NAMES
        box2d/box2d.h
    PATHS
        ${FIND_SFML_PATHS}        
)

if(NOT TARGET Box2D::Box2D)
    add_library(Box2D::Box2D UNKNOWN IMPORTED)
    set_target_properties(Box2D::Box2D PROPERTIES
        IMPORTED_LOCATION ${BOX2D_LIBRARY}
        INTERFACE_INCLUDE_DIRECTORIES ${BOX2D_INCLUDE_DIR}
    )
endif()