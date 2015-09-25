#ifndef __XCAM_OPCODES_H__
#define __XCAM_OPCODES_H__

////////////////////////////////////////////////////////////////////////////////
// The xcam::opcodes namespace provides C++ wrappers for the Xcam instruction set.
// The *_hw variants use the actual RISC-V Xcam assembler instructions.
// The *_sw variants provide software implementations of the instructions.
// The regular variants default to hardware unless SOFT_XCAM is #defined.
////////////////////////////////////////////////////////////////////////////////

namespace xcam {
namespace opcodes {

////////////////////////////////////////////////////////////////////////////////
// camlk0
////////////////////////////////////////////////////////////////////////////////

template <int Offset> xcam_subkey_t camlk0_hw(const xcam_index_t ix) {
    xcam_subkey_t result;
    asm volatile ("camlk0 %0, %1(%2)"
                  : "=r"(result)
                  : "i"(Offset), "r"(ix)
                 );
    return result;
};

template <int Offset> xcam_subkey_t camlk0_sw(const xcam_index_t ix) {
    return soft::soft_cam_t::instance()->camlk0(ix, Offset);
};

////////////////////////////////////////////////////////////////////////////////
// camlk1
////////////////////////////////////////////////////////////////////////////////

template <int Offset> xcam_subkey_t camlk1_hw(const xcam_index_t ix) {
    xcam_subkey_t result;
    asm volatile ("camlk1 %0, %1(%2)"
                  : "=r"(result)
                  : "i"(Offset), "r"(ix)
                 );
    return result;
};

template <int Offset> xcam_subkey_t camlk1_sw(const xcam_index_t ix) {
    return soft::soft_cam_t::instance()->camlk1(ix, Offset);
};

////////////////////////////////////////////////////////////////////////////////
// camlv
////////////////////////////////////////////////////////////////////////////////

template <int Offset> xcam_value_t camlv_hw(const xcam_index_t ix) {
    xcam_value_t result;
    asm volatile ("camlv %0, %1(%2)"
                  : "=r"(result)
                  : "i"(Offset), "r"(ix)
                 );
    return result;
};

template <int Offset> xcam_value_t camlv_sw(const xcam_index_t ix) {
    return soft::soft_cam_t::instance()->camlv(ix, Offset);
};

////////////////////////////////////////////////////////////////////////////////
// camsk0
////////////////////////////////////////////////////////////////////////////////

template <int Offset> void camsk0_hw(const xcam_index_t ix, const xcam_subkey_t k0) {
    asm volatile ("camsk0 %0, %1(%2)"
                  : /* no outputs */
                  : "r"(k0), "i"(Offset), "r"(ix)
                 );
};

template <int Offset> void camsk0_sw(const xcam_index_t ix, const xcam_subkey_t k0) {
    soft::soft_cam_t::instance()->camsk0(ix, Offset, k0);
};

////////////////////////////////////////////////////////////////////////////////
// camsk1
////////////////////////////////////////////////////////////////////////////////

template <int Offset> void camsk1_hw(const xcam_index_t ix, const xcam_subkey_t k1) {
    asm volatile ("camsk1 %0, %1(%2)"
                  : /* no outputs */
                  : "r"(k1), "i"(Offset), "r"(ix)
                 );
};

template <int Offset> void camsk1_sw(const xcam_index_t ix, const xcam_subkey_t k1) {
    soft::soft_cam_t::instance()->camsk1(ix, Offset, k1);
};

////////////////////////////////////////////////////////////////////////////////
// camsv
////////////////////////////////////////////////////////////////////////////////

template <int Offset> void camsv_hw(const xcam_index_t ix, const xcam_value_t v) {
    asm volatile ("camsv %0, %1(%2)"
                  : /* no outputs */
                  : "r"(v), "i"(Offset), "r"(ix)
                 );
};

template <int Offset> void camsv_sw(const xcam_index_t ix, const xcam_value_t v) {
    soft::soft_cam_t::instance()->camsv(ix, Offset, v);
};

////////////////////////////////////////////////////////////////////////////////
// camsv
////////////////////////////////////////////////////////////////////////////////

template <int InsignificantBits> xcam_value_t cam_hw(const xcam_subkey_t k0, const xcam_subkey_t k1) {
    xcam_value_t result;
    asm volatile ("cam %0, %1, %2(%3)"
                  : "=r"(result)
                  : "r"(k0), "i"(InsignificantBits), "r"(k1)
                 );
    return result;
};

template <int InsignificantBits> xcam_value_t cam_sw(const xcam_subkey_t k0, const xcam_subkey_t k1) {
    return soft::soft_cam_t::instance()->cam(k0, k1, InsignificantBits);
};

////////////////////////////////////////////////////////////////////////////////
// Type aliases
////////////////////////////////////////////////////////////////////////////////

#ifdef SOFT_XCAM
    template <int Offset> xcam_subkey_t camlk0(const xcam_index_t ix) { return camlk0_sw<Offset>(ix); };
    template <int Offset> xcam_subkey_t camlk1(const xcam_index_t ix) { return camlk1_sw<Offset>(ix); };
    template <int Offset> xcam_value_t camlv(const xcam_index_t ix) { return camlv_sw<Offset>(ix); };
    template <int Offset> void camsk0(const xcam_index_t ix, const xcam_subkey_t k0) { camsk0_sw<Offset>(ix, k0); };
    template <int Offset> void camsk1(const xcam_index_t ix, const xcam_subkey_t k1) { camsk1_sw<Offset>(ix, k1); };
    template <int Offset> void camsv(const xcam_index_t ix, const xcam_value_t v) { camsv_sw<Offset>(ix, v); };
    template <int InsignificantBits> xcam_value_t cam(const xcam_subkey_t k0, const xcam_subkey_t k1) { return cam_sw<InsignificantBits>(k0, k1); };
#else
    template <int Offset> xcam_subkey_t camlk0(const xcam_index_t ix) { return camlk0_hw<Offset>(ix); };
    template <int Offset> xcam_subkey_t camlk1(const xcam_index_t ix) { return camlk1_hw<Offset>(ix); };
    template <int Offset> xcam_value_t camlv(const xcam_index_t ix) { return camlv_hw<Offset>(ix); };
    template <int Offset> void camsk0(const xcam_index_t ix, const xcam_subkey_t k0) { camsk0_hw<Offset>(ix, k0); };
    template <int Offset> void camsk1(const xcam_index_t ix, const xcam_subkey_t k1) { camsk1_hw<Offset>(ix, k1); };
    template <int Offset> void camsv(const xcam_index_t ix, const xcam_value_t v) { camsv_hw<Offset>(ix, v); };
    template <int InsignificantBits> xcam_value_t cam(const xcam_subkey_t k0, const xcam_subkey_t k1) { return cam_hw<InsignificantBits>(k0, k1); };
#endif

} /* namespace opcodes */
} /* namespace xcam */

#endif /* __XCAM_OPCODES_H__ */
