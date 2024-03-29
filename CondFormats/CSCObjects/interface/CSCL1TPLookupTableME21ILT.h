#ifndef CondFormats_CSCObjects_CSCL1TPLookupTableME21ILT_h
#define CondFormats_CSCObjects_CSCL1TPLookupTableME21ILT_h

#include "CondFormats/Serialization/interface/Serializable.h"
#include <vector>

class CSCL1TPLookupTableME21ILT {
public:
  CSCL1TPLookupTableME21ILT();

  ~CSCL1TPLookupTableME21ILT() {}

  typedef std::vector<unsigned> t_lut;
  typedef std::vector<int> t_lut_signed;

  // setters
  void set_GEM_pad_CSC_es_ME21_even(t_lut lut);
  void set_GEM_pad_CSC_es_ME21_odd(t_lut lut);

  void set_GEM_roll_L1_CSC_min_wg_ME21_even(t_lut lut);
  void set_GEM_roll_L1_CSC_max_wg_ME21_even(t_lut lut);
  void set_GEM_roll_L1_CSC_min_wg_ME21_odd(t_lut lut);
  void set_GEM_roll_L1_CSC_max_wg_ME21_odd(t_lut lut);

  void set_GEM_roll_L2_CSC_min_wg_ME21_even(t_lut lut);
  void set_GEM_roll_L2_CSC_max_wg_ME21_even(t_lut lut);
  void set_GEM_roll_L2_CSC_min_wg_ME21_odd(t_lut lut);
  void set_GEM_roll_L2_CSC_max_wg_ME21_odd(t_lut lut);

  void set_GEM_align_corr_es_ME21_positive_endcap(t_lut_signed lut);
  void set_GEM_align_corr_es_ME21_negative_endcap(t_lut_signed lut);

  void set_es_diff_slope_L1_ME21_even(t_lut lut);
  void set_es_diff_slope_L1_ME21_odd(t_lut lut);
  void set_es_diff_slope_L2_ME21_even(t_lut lut);
  void set_es_diff_slope_L2_ME21_odd(t_lut lut);

  void set_CSC_slope_cosi_2to1_L1_ME21_even(t_lut lut);
  void set_CSC_slope_cosi_2to1_L1_ME21_odd(t_lut lut);
  void set_CSC_slope_cosi_3to1_L1_ME21_even(t_lut lut);
  void set_CSC_slope_cosi_3to1_L1_ME21_odd(t_lut lut);

  void set_CSC_slope_cosi_corr_L1_ME21_even(t_lut lut);
  void set_CSC_slope_cosi_corr_L1_ME21_odd(t_lut lut);

  void set_CSC_slope_corr_L1_ME21_even(t_lut lut);
  void set_CSC_slope_corr_L1_ME21_odd(t_lut lut);
  void set_CSC_slope_corr_L2_ME21_even(t_lut lut);
  void set_CSC_slope_corr_L2_ME21_odd(t_lut lut);

  // getters
  unsigned GEM_pad_CSC_es_ME21_even(unsigned pad) const;
  unsigned GEM_pad_CSC_es_ME21_odd(unsigned pad) const;

  unsigned GEM_roll_L1_CSC_min_wg_ME21_even(unsigned roll) const;
  unsigned GEM_roll_L1_CSC_max_wg_ME21_even(unsigned roll) const;
  unsigned GEM_roll_L1_CSC_min_wg_ME21_odd(unsigned roll) const;
  unsigned GEM_roll_L1_CSC_max_wg_ME21_odd(unsigned roll) const;

  unsigned GEM_roll_L2_CSC_min_wg_ME21_even(unsigned roll) const;
  unsigned GEM_roll_L2_CSC_max_wg_ME21_even(unsigned roll) const;
  unsigned GEM_roll_L2_CSC_min_wg_ME21_odd(unsigned roll) const;
  unsigned GEM_roll_L2_CSC_max_wg_ME21_odd(unsigned roll) const;

  int GEM_align_corr_es_ME21_positive_endcap(unsigned chamber, unsigned roll) const;
  int GEM_align_corr_es_ME21_negative_endcap(unsigned chamber, unsigned roll) const;

  unsigned CSC_slope_cosi_2to1_L1_ME21_even(unsigned slope) const;
  unsigned CSC_slope_cosi_2to1_L1_ME21_odd(unsigned slope) const;
  unsigned CSC_slope_cosi_3to1_L1_ME21_even(unsigned slope) const;
  unsigned CSC_slope_cosi_3to1_L1_ME21_odd(unsigned slope) const;

  unsigned CSC_slope_cosi_corr_L1_ME21_even(unsigned slope) const;
  unsigned CSC_slope_cosi_corr_L1_ME21_odd(unsigned slope) const;

  unsigned CSC_slope_corr_L1_ME21_even(unsigned slope) const;
  unsigned CSC_slope_corr_L1_ME21_odd(unsigned slope) const;
  unsigned CSC_slope_corr_L2_ME21_even(unsigned slope) const;
  unsigned CSC_slope_corr_L2_ME21_odd(unsigned slope) const;

  // GEM-CSC trigger: 1/8-strip difference to slope
  unsigned es_diff_slope_L1_ME21_even(unsigned es_diff) const;
  unsigned es_diff_slope_L1_ME21_odd(unsigned es_diff) const;
  unsigned es_diff_slope_L2_ME21_even(unsigned es_diff) const;
  unsigned es_diff_slope_L2_ME21_odd(unsigned es_diff) const;

private:
  t_lut GEM_pad_CSC_es_ME21_even_;
  t_lut GEM_pad_CSC_es_ME21_odd_;

  t_lut GEM_roll_L1_CSC_min_wg_ME21_even_;
  t_lut GEM_roll_L1_CSC_max_wg_ME21_even_;
  t_lut GEM_roll_L1_CSC_min_wg_ME21_odd_;
  t_lut GEM_roll_L1_CSC_max_wg_ME21_odd_;

  t_lut GEM_roll_L2_CSC_min_wg_ME21_even_;
  t_lut GEM_roll_L2_CSC_max_wg_ME21_even_;
  t_lut GEM_roll_L2_CSC_min_wg_ME21_odd_;
  t_lut GEM_roll_L2_CSC_max_wg_ME21_odd_;

  t_lut_signed GEM_align_corr_es_ME21_positive_endcap_;
  t_lut_signed GEM_align_corr_es_ME21_negative_endcap_;

  t_lut CSC_slope_cosi_2to1_L1_ME21_even_;
  t_lut CSC_slope_cosi_2to1_L1_ME21_odd_;
  t_lut CSC_slope_cosi_3to1_L1_ME21_even_;
  t_lut CSC_slope_cosi_3to1_L1_ME21_odd_;

  t_lut CSC_slope_cosi_corr_L1_ME21_even_;
  t_lut CSC_slope_cosi_corr_L1_ME21_odd_;

  t_lut CSC_slope_corr_L1_ME21_even_;
  t_lut CSC_slope_corr_L1_ME21_odd_;
  t_lut CSC_slope_corr_L2_ME21_even_;
  t_lut CSC_slope_corr_L2_ME21_odd_;

  t_lut es_diff_slope_L1_ME21_even_;
  t_lut es_diff_slope_L1_ME21_odd_;
  t_lut es_diff_slope_L2_ME21_even_;
  t_lut es_diff_slope_L2_ME21_odd_;

  COND_SERIALIZABLE;
};

#endif
