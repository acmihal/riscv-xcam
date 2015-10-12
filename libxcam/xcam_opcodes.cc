#include "xcam.h"

using xcam::xcam_index_t;
using xcam::xcam_subkey_t;
using xcam::xcam_key_t;
using xcam::xcam_value_t;
using xcam::xcam_entry_t;

////////////////////////////////////////////////////////////////////////////////
// Software-emulated opcode wrappers that take cpu_id and immediates as parameters.
////////////////////////////////////////////////////////////////////////////////

extern xcam_subkey_t xcam::opcodes::camlk0_sw(const int cpu_id, const xcam_index_t ix, const int offset);
extern xcam_subkey_t xcam::opcodes::camlk1_sw(const int cpu_id, const xcam_index_t ix, const int offset);
extern xcam_value_t xcam::opcodes::camlv_sw(const int cpu_id, const xcam_index_t ix, const int offset);
extern void xcam::opcodes::camsk0_sw(const int cpu_id, const xcam_index_t ix, const int offset, const xcam_subkey_t k0);
extern void xcam::opcodes::camsk1_sw(const int cpu_id, const xcam_index_t ix, const int offset, const xcam_subkey_t k1);
extern void xcam::opcodes::camsv_sw(const int cpu_id, const xcam_index_t ix, const int offset, const xcam_value_t v);
extern xcam_value_t xcam::opcodes::cam_sw(const int cpu_id, const xcam_subkey_t k0, const xcam_subkey_t k1, const int insignificantBits);

