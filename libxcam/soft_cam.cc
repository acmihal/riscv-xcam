#include <cassert>
#include <iostream>
#include "xcam.h"

using std::cout;
using std::endl;

using xcam::opcodes::soft::soft_cam_t;
using xcam::xcam_index_t;
using xcam::xcam_subkey_t;
using xcam::xcam_key_t;
using xcam::xcam_value_t;
using xcam::xcam_entry_t;

soft_cam_t* soft_cam_t::singleton = nullptr;

xcam_subkey_t soft_cam_t::camlk0(const xcam_index_t ix, const int offset) const {
    const xcam_subkey_t result = cam_state.at(ix + offset).key.k0;
    cout << "cam[" << (ix + offset) << "].k0 => " << result << endl;
    return result;
}

xcam_subkey_t soft_cam_t::camlk1(const xcam_index_t ix, const int offset) const {
    const xcam_subkey_t result = cam_state.at(ix + offset).key.k1;
    cout << "cam[" << (ix + offset) << "].k1 => " << result << endl;
    return result;
}

xcam_value_t soft_cam_t::camlv(const xcam_index_t ix, const int offset) const {
    const xcam_value_t result = cam_state.at(ix + offset).value;
    cout << "cam[" << (ix + offset) << "].v => " << result << endl;
    return result;
}

void soft_cam_t::camsk0(const xcam_index_t ix, const int offset, const xcam_subkey_t k0) {
    const state_ix_t ixo = ix + offset;
    remove_row(ixo);
    cam_state.at(ixo).key.k0 = k0;
    add_row(ixo);
    cout << "cam[" << ixo << "].k0 <= " << k0 << endl;
}

void soft_cam_t::camsk1(const xcam_index_t ix, const int offset, const xcam_subkey_t k1) {
    const state_ix_t ixo = ix + offset;
    remove_row(ixo);
    cam_state.at(ixo).key.k1 = k1;
    add_row(ixo);
    cout << "cam[" << ixo << "].k1 <= " << k1 << endl;
}

void soft_cam_t::camsv(const xcam_index_t ix, const int offset, const xcam_value_t v) {
    const state_ix_t ixo = ix + offset;
    remove_row(ixo);
    cam_state.at(ixo).value = v;
    add_row(ixo);
    cout << "cam[" << ixo << "].v <= " << v << endl;
}

void soft_cam_t::remove_row(const state_ix_t ix) {
    const value_type row = cam_state.at(ix);
    if (row.value != 0) {
        // CAM row does not contain a zero value, so the multimap should have an entry pointing to this row.
        cout << "cam[" << ix << "] invalidating (" << row.key.k0 << ", " << row.key.k1 << ") -> " << row.value << endl;

        std::pair<map_t::iterator, map_t::iterator> range = cam_map.equal_range(row.key);
        while (range.first != range.second) {
            if ((range.first)->second == ix) {
                // Found the correct multimap entry.
                cam_map.erase(range.first);
                return;
            }
            ++range.first;
        }

        // Failed to find the expected entry.
        assert(false);
    }
}

void soft_cam_t::add_row(const state_ix_t ix) {
    const value_type row = cam_state.at(ix);
    if (row.value != 0) {
      // CAM row does not contain a zero value. Create an entry in the multimap pointing to this row.
      cam_map.insert(map_t::value_type(row.key, ix));
      cout << "cam[" << ix << "] validating (" << row.key.k0 << ", " << row.key.k1 << ") -> " << row.value << endl;
    }
}

xcam_value_t soft_cam_t::cam(const xcam_subkey_t k0, const xcam_subkey_t k1, const int insignificantBits) const {
    const xcam_subkey_t mask = -1 << insignificantBits;
    const xcam_subkey_t k1_lowerbound = k1 & mask;
    const xcam_subkey_t k1_upperbound = k1 | ~mask;

    const key_type key_lowerbound(k0, k1_lowerbound);
    const key_type key_upperbound(k0, k1_upperbound);

    // Find a range of entries in the map that could potentially match (k0, k1) considering insignificantBits.
    map_t::const_iterator lb = cam_map.lower_bound(key_lowerbound);
    const map_t::const_iterator ub = cam_map.upper_bound(key_upperbound);

    bool found_match = false;
    state_ix_t match_ix = 0;

    // Iterate over the potentially matching rows and take the actual matching row with the lowest ix.
    while (lb != ub) {
        const xcam_subkey_t row_k0 = lb->first.k0;
        const xcam_subkey_t row_k1 = lb->first.k1;
        const xcam_subkey_t row_k1_lowerbound = row_k1 & mask;
        if (row_k0 == k0 && row_k1_lowerbound == k1_lowerbound) {
            // Found a matching row.
            if (!found_match) {
                found_match = true;
                match_ix = lb->second;
                cout << "cam(" << k0 << ", " << k1 << " & 0x" << std::hex << mask << ").v => " << endl;
            } else {
                match_ix = std::min(match_ix, lb->second);
            }
            cout << "    matches ix=" << lb->second << " (" << row_k0 << ", " << row_k1 << ") -> " << cam_state.at(lb->second).value << endl;
        }
        ++lb;
    }

    if (found_match) {
        // Overwrite the insignificantBits of the result with the least-significant-bits of k1.
        const xcam_value_t result = cam_state.at(match_ix).value;
        const xcam_subkey_t k1_suffix = k1 & ~mask;
        const xcam_value_t result_with_suffix = (result & mask) | k1_suffix;

        cout << "    minimum ix=" << match_ix << " (" << result << " & 0x" << std::hex << mask << ") | 0x " << std::hex << k1_suffix << " = " << result_with_suffix << endl;
        return result_with_suffix;
    }
    else {
        // Key is not in the cam. Return zero.
        cout << "cam(" << k0 << ", " << k1 << " & 0x" << std::hex << mask << ").v => null" << endl;
        return 0;
    }
}
