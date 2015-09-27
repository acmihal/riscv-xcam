#include "xcam.h"

using xcam::xcam_index_t;
using xcam::xcam_subkey_t;
using xcam::xcam_key_t;
using xcam::xcam_value_t;
using xcam::xcam_entry_t;
using xcam::opcodes::soft::soft_cam_t;

////////////////////////////////////////////////////////////////////////////////
// Software-emulated opcode wrappers that take cpu_id and immediates as parameters.
////////////////////////////////////////////////////////////////////////////////

xcam_subkey_t xcam::opcodes::camlk0_sw(const int cpu_id, const xcam_index_t ix, const int offset) {
    return soft_cam_t::instance(cpu_id)->camlk0(ix, offset);
}

xcam_subkey_t xcam::opcodes::camlk1_sw(const int cpu_id, const xcam_index_t ix, const int offset) {
    return soft_cam_t::instance(cpu_id)->camlk1(ix, offset);
}

xcam_value_t xcam::opcodes::camlv_sw(const int cpu_id, const xcam_index_t ix, const int offset) {
    return soft_cam_t::instance(cpu_id)->camlv(ix, offset);
}

void xcam::opcodes::camsk0_sw(const int cpu_id, const xcam_index_t ix, const int offset, const xcam_subkey_t k0) {
    soft_cam_t::instance(cpu_id)->camsk0(ix, offset, k0);
}

void xcam::opcodes::camsk1_sw(const int cpu_id, const xcam_index_t ix, const int offset, const xcam_subkey_t k1) {
    soft_cam_t::instance(cpu_id)->camsk1(ix, offset, k1);
}

void xcam::opcodes::camsv_sw(const int cpu_id, const xcam_index_t ix, const int offset, const xcam_value_t v) {
    soft_cam_t::instance(cpu_id)->camsv(ix, offset, v);
}

xcam_value_t xcam::opcodes::cam_sw(const int cpu_id, const xcam_subkey_t k0, const xcam_subkey_t k1, const int insignificantBits) {
    return soft_cam_t::instance(cpu_id)->cam(k0, k1, insignificantBits);
}
