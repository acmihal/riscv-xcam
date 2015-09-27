#!/bin/bash

mkdir -p build
pushd build
cmake ..
make
make test
make install
popd

mkdir -p crossbuild
pushd crossbuild
cmake -DCMAKE_TOOLCHAIN_FILE=../riscv-toolchain.cmake ..
make
make test
make install
popd
