#include <iostream>
#include "xcam.h"

using xcam::xcam_index_t;
using xcam::xcam_subkey_t;
using xcam::xcam_key_t;
using xcam::xcam_value_t;
using xcam::xcam_entry_t;

xcam_entry_t xcam::caml(const xcam_index_t ix) {
    return xcam_entry_t(xcam::camlk(ix), xcam::camlv(ix));
}

xcam_key_t xcam::camlk(const xcam_index_t ix) {
    return xcam_key_t(xcam::camlk0(ix), xcam::camlk1(ix));
}

xcam_subkey_t xcam::camlk0(const xcam_index_t ix) {
    return xcam_subkey_t(xcam::opcodes::camlk0<0>(ix));
}

xcam_subkey_t xcam::camlk1(const xcam_index_t ix) {
    return xcam_subkey_t(xcam::opcodes::camlk1<0>(ix));
}

xcam_value_t xcam::camlv(const xcam_index_t ix) {
    return xcam_value_t(xcam::opcodes::camlv<0>(ix));
}

void xcam::cams(const xcam_index_t ix, const xcam_entry_t& entry) {
    xcam::camsk(ix, entry.key);
    xcam::camsv(ix, entry.value);
}

void xcam::camsk(const xcam_index_t ix, const xcam_key_t& key) {
    xcam::camsk0(ix, key.k0);
    xcam::camsk1(ix, key.k1);
}

void xcam::camsk0(const xcam_index_t ix, const xcam_subkey_t k0) {
    xcam::opcodes::camsk0<0>(ix, k0);
}

void xcam::camsk1(const xcam_index_t ix, const xcam_subkey_t k1) {
    xcam::opcodes::camsk1<0>(ix, k1);
}

void xcam::camsv(const xcam_index_t ix, const xcam_value_t v) {
    xcam::opcodes::camsv<0>(ix, v);
}
