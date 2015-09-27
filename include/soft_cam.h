#ifndef __SOFT_CAM_H__
#define __SOFT_CAM_H__

////////////////////////////////////////////////////////////////////////////////
// The xcam::opcodes::soft namespace provides a software model of the Xcam hardware.
////////////////////////////////////////////////////////////////////////////////

#include <array>
#include <map>

namespace xcam {
namespace opcodes {
namespace soft {

class soft_cam_t {
protected:

    // The soft_cam_t object models stateful hardware.
    // There should be one instance of this class per processor core.
    soft_cam_t() { }

    typedef std::map<int, soft_cam_t*> cpu_map_t;
    static cpu_map_t cpu_map;

    typedef xcam_key_t key_type;
    typedef xcam_value_t data_type;
    typedef xcam_entry_t value_type;
    typedef std::array<value_type, 128> state_t;
    typedef state_t::size_type state_ix_t;
    typedef std::multimap<key_type, state_ix_t> map_t;

    // A fixed-size array representing the contents of the hardware cam.
    state_t cam_state;

    // A software map mimicking the lookup functionality of the hardware cam.
    map_t cam_map;

    // Functions to synchronize cam_map with cam_state.
    void remove_row(const state_ix_t ix);
    void add_row(const state_ix_t ix);

public:
    static soft_cam_t* instance(int cpu_id);

    xcam_subkey_t camlk0(const xcam_index_t ix, const int offset) const;
    xcam_subkey_t camlk1(const xcam_index_t ix, const int offset) const;
    xcam_value_t  camlv (const xcam_index_t ix, const int offset) const;
    void          camsk0(const xcam_index_t ix, const int offset, const xcam_subkey_t k0);
    void          camsk1(const xcam_index_t ix, const int offset, const xcam_subkey_t k1);
    void          camsv (const xcam_index_t ix, const int offset, const xcam_value_t v);
    xcam_value_t  cam   (const xcam_subkey_t k0, const xcam_subkey_t k1, const int insignificantBits) const;
};

} /* namespace soft */
} /* namespace opcodes */
} /* namespace xcam */

#endif /* __SOFT_CAM_H__ */
