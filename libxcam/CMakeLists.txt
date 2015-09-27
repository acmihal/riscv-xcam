set(libxcam_srcs soft_cam.cc xcam_api.cc xcam_opcodes.cc)

if(CMAKE_CROSSCOMPILING)
    add_library(xcamsw ${libxcam_srcs})
    target_compile_definitions(xcamsw PUBLIC -DSOFT_XCAM)
    #target_compile_features(xcamsw PUBLIC cxx_nullptr)

    add_library(xcam ${libxcam_srcs})
    #target_compile_features(xcam PUBLIC cxx_nullptr)
    # Install both cross-compiled libraries to the crosscompiler lib directory.
    install(TARGETS xcam xcamsw
	    ARCHIVE DESTINATION $ENV{RISCV}/riscv64-unknown-elf/lib/32)
else()
    add_library(xcamsw SHARED ${libxcam_srcs})
    target_compile_definitions(xcamsw PUBLIC -DSOFT_XCAM)
    #target_compile_features(xcamsw PUBLIC cxx_nullptr)

    # Install only the host sw-emulated library to the RISCV/lib directory.
    install(TARGETS xcamsw
            LIBRARY DESTINATION $ENV{RISCV}/lib)
endif()
