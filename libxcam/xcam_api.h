#ifndef __XCAM_API_H__
#define __XCAM_API_H__

////////////////////////////////////////////////////////////////////////////////
// Public methods
////////////////////////////////////////////////////////////////////////////////

namespace xcam {

// Load the entry at cam[ix].
xcam_entry_t caml(const xcam_index_t ix);

// Load the key at cam[ix].
xcam_key_t camlk(const xcam_index_t ix);

// Load the subkey k0 at cam[ix].
xcam_subkey_t camlk0(const xcam_index_t ix);

// Load the subkey k1 at cam[ix].
xcam_subkey_t camlk1(const xcam_index_t ix);

// Load the value at cam[ix].
xcam_value_t camlv(const xcam_index_t ix);

// Store the given entry into cam[ix].
void cams(const xcam_index_t ix, const xcam_entry_t& entry);

// Store the given key into cam[ix].
void camsk(const xcam_index_t ix, const xcam_key_t& key);

// Store the subkey k0 into cam[ix].
void camsk0(const xcam_index_t ix, const xcam_subkey_t k0);

// Store the subkey k1 into cam[ix].
void camsk1(const xcam_index_t ix, const xcam_subkey_t k1);

// Store the given value into cam[ix].
void camsv(const xcam_index_t ix, const xcam_value_t value);

// Fetch the value associated with the given key, ignoring InsignificantBits least-significant-bits of subkey k1.
// The return value is bitwise-OR'd with the InsignificantBits lsb's of subkey k1.
template <int InsignificantBits> xcam_value_t cam(const xcam_key_t& key) {
    return opcodes::cam<InsignificantBits>(key.k0, key.k1);
};

} /* namespace xcam */

#endif /* __XCAM_API_H__ */
