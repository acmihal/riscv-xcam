add_executable(testxcamsw test_sk.cc test_cam.cc)
target_link_libraries(testxcamsw xcamsw libgtestmain libgtest)
add_test(testxcamsw testxcamsw)
