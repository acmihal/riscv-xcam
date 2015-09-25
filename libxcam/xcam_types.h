#ifndef __XCAM_TYPES_H__
#define __XCAM_TYPES_H__

////////////////////////////////////////////////////////////////////////////////
// Public datatypes
////////////////////////////////////////////////////////////////////////////////

namespace xcam {

typedef uint32_t xcam_index_t;

typedef int32_t xcam_subkey_t;

struct xcam_key_t {
    xcam_key_t() : k0(0), k1(0) { }
    xcam_key_t(const xcam_subkey_t _k0, const xcam_subkey_t _k1) : k0(_k0), k1(_k1) { }
    bool operator<(const xcam_key_t& other) const { return std::make_pair(k0, k1) < std::make_pair(other.k0, other.k1); }
    xcam_subkey_t k0;
    xcam_subkey_t k1;
};

typedef int32_t xcam_value_t;
    
struct xcam_entry_t {
    xcam_entry_t() : value(0) { }
    xcam_entry_t(const xcam_key_t& _key, const xcam_value_t& _value) : key(_key), value(_value) { }
    xcam_key_t key;
    xcam_value_t value;
};

} /* namespace xcam */

#endif /* __XCAM_TYPES_H__ */
