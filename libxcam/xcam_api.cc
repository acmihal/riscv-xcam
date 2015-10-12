#include "xcam.h"

using xcam::xcam_index_t;
using xcam::xcam_subkey_t;
using xcam::xcam_key_t;
using xcam::xcam_value_t;
using xcam::xcam_entry_t;

void libxcam_is_present(void) { }

extern xcam_subkey_t xcam::camlk0(const xcam_index_t ix);
extern xcam_subkey_t xcam::camlk1(const xcam_index_t ix);
extern xcam_key_t xcam::camlk(const xcam_index_t ix);
extern xcam_value_t xcam::camlv(const xcam_index_t ix);
extern xcam_entry_t xcam::caml(const xcam_index_t ix);
extern void xcam::camsk0(const xcam_index_t ix, const xcam_subkey_t k0);
extern void xcam::camsk1(const xcam_index_t ix, const xcam_subkey_t k1);
extern void xcam::camsk(const xcam_index_t ix, const xcam_key_t key);
extern void xcam::camsv(const xcam_index_t ix, const xcam_value_t value);
extern void xcam::cams(const xcam_index_t ix, const xcam_entry_t entry);

