add_library(xcamsw soft_cam.cc xcam_api.cc)
#target_compile_features(libxcamsw PUBLIC cxx_nullptr)
target_compile_definitions(xcamsw PUBLIC -DSOFT_XCAM)

if(CMAKE_CROSSCOMPILING)
    add_library(xcam soft_cam.cc xcam_api.cc)
    #target_compile_features(libxcam PUBLIC cxx_nullptr)
endif(CMAKE_CROSSCOMPILING)
