#####################################
# CMakeLists.txt for apps/spaintgui #
#####################################

###########################
# Specify the target name #
###########################

SET(targetname spaintgui)

###########################
# Offer low-power support #
###########################

INCLUDE(${PROJECT_SOURCE_DIR}/cmake/OfferLowPowerSupport.cmake)

################################
# Specify the libraries to use #
################################

INCLUDE(${PROJECT_SOURCE_DIR}/cmake/UseArrayFire.cmake)
INCLUDE(${PROJECT_SOURCE_DIR}/cmake/UseBoost.cmake)
INCLUDE(${PROJECT_SOURCE_DIR}/cmake/UseCUDA.cmake)
INCLUDE(${PROJECT_SOURCE_DIR}/cmake/UseEigen.cmake)
INCLUDE(${PROJECT_SOURCE_DIR}/cmake/UseGLEW.cmake)
INCLUDE(${PROJECT_SOURCE_DIR}/cmake/UseInfiniTAM.cmake)
INCLUDE(${PROJECT_SOURCE_DIR}/cmake/UseLeap.cmake)
INCLUDE(${PROJECT_SOURCE_DIR}/cmake/UseOpenCV.cmake)
INCLUDE(${PROJECT_SOURCE_DIR}/cmake/UseOpenGL.cmake)
INCLUDE(${PROJECT_SOURCE_DIR}/cmake/UseOpenMP.cmake)
INCLUDE(${PROJECT_SOURCE_DIR}/cmake/UseOpenNI.cmake)
INCLUDE(${PROJECT_SOURCE_DIR}/cmake/UseOVR.cmake)
INCLUDE(${PROJECT_SOURCE_DIR}/cmake/UseSDL.cmake)
INCLUDE(${PROJECT_SOURCE_DIR}/cmake/UseVicon.cmake)

#############################
# Specify the project files #
#############################

##
SET(commands_sources
commands/MarkVoxelsCommand.cpp
)

SET(commands_headers
commands/MarkVoxelsCommand.h
)

##
SET(core_sources
core/Interactor.cpp
core/Model.cpp
core/Pipeline.cpp
core/Raycaster.cpp
)

SET(core_headers
core/Interactor.h
core/Model.h
core/Pipeline.h
core/Raycaster.h
)

##
SET(renderers_sources
renderers/Renderer.cpp
renderers/WindowedRenderer.cpp
)

SET(renderers_headers
renderers/Renderer.h
renderers/WindowedRenderer.h
)

IF(WITH_OVR)
  SET(renderers_sources ${renderers_sources} renderers/RiftRenderer.cpp)
  SET(renderers_headers ${renderers_headers} renderers/RiftRenderer.h)
ENDIF()

##
SET(toplevel_sources
main.cpp
Application.cpp
CPUInstantiations.cpp
)

SET(toplevel_headers
Application.h
)

IF(WITH_CUDA)
  SET(toplevel_sources ${toplevel_sources} CUDAInstantiations.cu)
ENDIF()

#################################################################
# Collect the project files into sources, headers and templates #
#################################################################

SET(sources
${commands_sources}
${core_sources}
${renderers_sources}
${toplevel_sources}
)

SET(headers
${commands_headers}
${core_headers}
${renderers_headers}
${toplevel_headers}
)

#############################
# Specify the source groups #
#############################

SOURCE_GROUP("" FILES ${toplevel_sources} ${toplevel_headers})
SOURCE_GROUP(commands FILES ${commands_sources} ${commands_headers})
SOURCE_GROUP(core FILES ${core_sources} ${core_headers})
SOURCE_GROUP(renderers FILES ${renderers_sources} ${renderers_headers})

##########################################
# Specify additional include directories #
##########################################

INCLUDE_DIRECTORIES(${PROJECT_SOURCE_DIR}/modules/rafl/include)
INCLUDE_DIRECTORIES(${PROJECT_SOURCE_DIR}/modules/rigging/include)
INCLUDE_DIRECTORIES(${PROJECT_SOURCE_DIR}/modules/spaint/include)
INCLUDE_DIRECTORIES(${PROJECT_SOURCE_DIR}/modules/tvginput/include)
INCLUDE_DIRECTORIES(${PROJECT_SOURCE_DIR}/modules/tvgutil/include)

##########################################
# Specify the target and where to put it #
##########################################

INCLUDE(${PROJECT_SOURCE_DIR}/cmake/SetCUDAAppTarget.cmake)

#################################
# Specify the libraries to link #
#################################

# Note: spaint needs to precede rafl on Linux.
TARGET_LINK_LIBRARIES(${targetname} spaint rafl rigging tvginput tvgutil)

INCLUDE(${PROJECT_SOURCE_DIR}/cmake/LinkSDL.cmake)
INCLUDE(${PROJECT_SOURCE_DIR}/cmake/LinkArrayFire.cmake)
INCLUDE(${PROJECT_SOURCE_DIR}/cmake/LinkBoost.cmake)
INCLUDE(${PROJECT_SOURCE_DIR}/cmake/LinkGLEW.cmake)
INCLUDE(${PROJECT_SOURCE_DIR}/cmake/LinkInfiniTAM.cmake)
INCLUDE(${PROJECT_SOURCE_DIR}/cmake/LinkLeap.cmake)
INCLUDE(${PROJECT_SOURCE_DIR}/cmake/LinkOpenCV.cmake)
INCLUDE(${PROJECT_SOURCE_DIR}/cmake/LinkOpenGL.cmake)
INCLUDE(${PROJECT_SOURCE_DIR}/cmake/LinkOpenNI.cmake)
INCLUDE(${PROJECT_SOURCE_DIR}/cmake/LinkOVR.cmake)
INCLUDE(${PROJECT_SOURCE_DIR}/cmake/LinkVicon.cmake)

#########################################
# Copy resource files to the build tree #
#########################################

ADD_CUSTOM_COMMAND(TARGET ${targetname} POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_directory "${PROJECT_SOURCE_DIR}/apps/spaintgui/resources" "$<TARGET_FILE_DIR:${targetname}>/resources")

IF(MSVC_IDE)
  ADD_CUSTOM_COMMAND(TARGET ${targetname} POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_directory "${PROJECT_SOURCE_DIR}/apps/spaintgui/resources" "${PROJECT_BINARY_DIR}/apps/spaintgui/resources")
ENDIF()

#############################
# Specify things to install #
#############################

INCLUDE(${PROJECT_SOURCE_DIR}/cmake/InstallApp.cmake)
