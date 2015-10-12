#ifndef __XCAM_API_H__
#define __XCAM_API_H__

////////////////////////////////////////////////////////////////////////////////
// Public methods
////////////////////////////////////////////////////////////////////////////////

namespace xcam {

// Load the subkey k0 at cam[ix].
inline xcam_subkey_t camlk0(const xcam_index_t ix) {
    return opcodes::camlk0<0>(ix);
}

// Load the subkey k1 at cam[ix].
inline xcam_subkey_t camlk1(const xcam_index_t ix) {
    return opcodes::camlk1<0>(ix);
}

// Load the key at cam[ix].
inline xcam_key_t camlk(const xcam_index_t ix) {
    return xcam_key_t(camlk0(ix), camlk1(ix));
}

// Load the value at cam[ix].
inline xcam_value_t camlv(const xcam_index_t ix) {
    return opcodes::camlv<0>(ix);
}

// Load the entry at cam[ix].
inline xcam_entry_t caml(const xcam_index_t ix) {
    return xcam_entry_t(camlk(ix), camlv(ix));
}

// Store the subkey k0 into cam[ix].
inline void camsk0(const xcam_index_t ix, const xcam_subkey_t k0) {
    opcodes::camsk0<0>(ix, k0);
}

// Store the subkey k1 into cam[ix].
inline void camsk1(const xcam_index_t ix, const xcam_subkey_t k1) {
    opcodes::camsk1<0>(ix, k1);
}

// Store the given key into cam[ix].
inline void camsk(const xcam_index_t ix, const xcam_key_t key) {
    camsk0(ix, key.k0);
    camsk1(ix, key.k1);
}

// Store the given value into cam[ix].
inline void camsv(const xcam_index_t ix, const xcam_value_t v) {
    opcodes::camsv<0>(ix, v);
}

// Store the given entry into cam[ix].
inline void cams(const xcam_index_t ix, const xcam_entry_t entry) {
    camsk(ix, entry.key);
    camsv(ix, entry.value);
}

// Fetch the value associated with the given key, ignoring InsignificantBits least-significant-bits of subkey k1.
// The return value is bitwise-OR'd with the InsignificantBits lsb's of subkey k1.
template <int InsignificantBits> xcam_value_t cam(const xcam_key_t key) {
    return opcodes::cam<InsignificantBits>(key.k0, key.k1);
};

} /* namespace xcam */

#endif /* __XCAM_API_H__ */
