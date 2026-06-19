#ifndef __cer0_synthesizer_speech_h
#define __cer0_synthesizer_speech_h

#include <cer0_synthesizer.h>

enum cer0_synthesizer_speech_sound {
  cer0_synthesizer_speech_sound_a = 0x00,
  cer0_synthesizer_speech_sound_i = 0x01,
  cer0_synthesizer_speech_sound_u = 0x02,
  cer0_synthesizer_speech_sound_e = 0x03,
  cer0_synthesizer_speech_sound_o = 0x04,
  
  cer0_synthesizer_speech_sound_ka = 0x05,
  cer0_synthesizer_speech_sound_ki = 0x06,
  cer0_synthesizer_speech_sound_ku = 0x07,
  cer0_synthesizer_speech_sound_ke = 0x08,
  cer0_synthesizer_speech_sound_ko = 0x09,
  
  cer0_synthesizer_speech_sound_ga = 0x0a,
  cer0_synthesizer_speech_sound_gi = 0x0b,
  cer0_synthesizer_speech_sound_gu = 0x0c,
  cer0_synthesizer_speech_sound_ge = 0x0d,
  cer0_synthesizer_speech_sound_go = 0x0e,
  
  cer0_synthesizer_speech_sound_ja = 0x0f,
  cer0_synthesizer_speech_sound_ji = 0x10,
  cer0_synthesizer_speech_sound_ju = 0x11,
  cer0_synthesizer_speech_sound_je = 0x12,
  cer0_synthesizer_speech_sound_jo = 0x13,
  
  cer0_synthesizer_speech_sound_ha = 0x14,
  cer0_synthesizer_speech_sound_hi = 0x15,
  cer0_synthesizer_speech_sound_hu = 0x16,
  cer0_synthesizer_speech_sound_he = 0x17,
  cer0_synthesizer_speech_sound_ho = 0x18,
  
  cer0_synthesizer_speech_sound_ta = 0x19,
  cer0_synthesizer_speech_sound_ti = 0x1a,
  cer0_synthesizer_speech_sound_tu = 0x1b,
  cer0_synthesizer_speech_sound_te = 0x1c,
  cer0_synthesizer_speech_sound_to = 0x1d,
  
  cer0_synthesizer_speech_sound_cha = 0x1e,
  cer0_synthesizer_speech_sound_chi = 0x1f,
  cer0_synthesizer_speech_sound_chu = 0x20,
  cer0_synthesizer_speech_sound_che = 0x21,
  cer0_synthesizer_speech_sound_cho = 0x22,
  
  cer0_synthesizer_speech_sound_da = 0x23,
  cer0_synthesizer_speech_sound_di = 0x24,
  cer0_synthesizer_speech_sound_jsu = 0x25,
  cer0_synthesizer_speech_sound_de = 0x26,
  cer0_synthesizer_speech_sound_do = 0x27,
  
  cer0_synthesizer_speech_sound_ba = 0x28,
  cer0_synthesizer_speech_sound_bi = 0x29,
  cer0_synthesizer_speech_sound_bu = 0x2a,
  cer0_synthesizer_speech_sound_be = 0x2b,
  cer0_synthesizer_speech_sound_bo = 0x2c,
  
  cer0_synthesizer_speech_sound_na = 0x2d,
  cer0_synthesizer_speech_sound_ni = 0x2e,
  cer0_synthesizer_speech_sound_nu = 0x2f,
  cer0_synthesizer_speech_sound_ne = 0x30,
  cer0_synthesizer_speech_sound_no = 0x31,
  cer0_synthesizer_speech_sound_nn = 0x32,
  
  cer0_synthesizer_speech_sound_ma = 0x33,
  cer0_synthesizer_speech_sound_mi = 0x34,
  cer0_synthesizer_speech_sound_mu = 0x35,
  cer0_synthesizer_speech_sound_me = 0x36,
  cer0_synthesizer_speech_sound_mo = 0x37,
  
  cer0_synthesizer_speech_sound_pa = 0x38,
  cer0_synthesizer_speech_sound_pi = 0x39,
  cer0_synthesizer_speech_sound_pu = 0x3a,
  cer0_synthesizer_speech_sound_pe = 0x3b,
  cer0_synthesizer_speech_sound_po = 0x3c,
  
  cer0_synthesizer_speech_sound_ra = 0x3d,
  cer0_synthesizer_speech_sound_ri = 0x3e,
  cer0_synthesizer_speech_sound_ru = 0x3f,
  cer0_synthesizer_speech_sound_re = 0x40,
  cer0_synthesizer_speech_sound_ro = 0x41,
  
  cer0_synthesizer_speech_sound_la = 0x42,
  cer0_synthesizer_speech_sound_li = 0x43,
  cer0_synthesizer_speech_sound_lu = 0x44,
  cer0_synthesizer_speech_sound_le = 0x45,
  cer0_synthesizer_speech_sound_lo = 0x46,
  
  cer0_synthesizer_speech_sound_fa = 0x47,
  cer0_synthesizer_speech_sound_fi = 0x48,
  cer0_synthesizer_speech_sound_fu = 0x49,
  cer0_synthesizer_speech_sound_fe = 0x4a,
  cer0_synthesizer_speech_sound_fo = 0x4b,
  
  cer0_synthesizer_speech_sound_sa = 0x4c,
  cer0_synthesizer_speech_sound_si = 0x4d,
  cer0_synthesizer_speech_sound_su = 0x4e,
  cer0_synthesizer_speech_sound_se = 0x4f,
  cer0_synthesizer_speech_sound_so = 0x50,
  
  cer0_synthesizer_speech_sound_sha = 0x51,
  cer0_synthesizer_speech_sound_shi = 0x52,
  cer0_synthesizer_speech_sound_shu = 0x53,
  cer0_synthesizer_speech_sound_she = 0x54,
  cer0_synthesizer_speech_sound_sho = 0x55,
  
  cer0_synthesizer_speech_sound_za = 0x56,
  cer0_synthesizer_speech_sound_zi = 0x57,
  cer0_synthesizer_speech_sound_zu = 0x58,
  cer0_synthesizer_speech_sound_ze = 0x59,
  cer0_synthesizer_speech_sound_zo = 0x5a,
 
  cer0_synthesizer_speech_sound_ya = 0x5b,
  cer0_synthesizer_speech_sound_yi = 0x5c,
  cer0_synthesizer_speech_sound_yu = 0x5d,
  cer0_synthesizer_speech_sound_ye = 0x5e,
  cer0_synthesizer_speech_sound_yo = 0x5f,
  
  cer0_synthesizer_speech_sound_wa = 0x60,
  cer0_synthesizer_speech_sound_wi = 0x61,
  cer0_synthesizer_speech_sound_wu = 0x62,
  cer0_synthesizer_speech_sound_we = 0x63,
  cer0_synthesizer_speech_sound_wo = 0x64,
  
  cer0_synthesizer_speech_sound_va = 0x65,
  cer0_synthesizer_speech_sound_vi = 0x66,
  cer0_synthesizer_speech_sound_vu = 0x67,
  cer0_synthesizer_speech_sound_ve = 0x68,
  cer0_synthesizer_speech_sound_vo = 0x69
};

struct cer0_synthesizer_speech_segment {
  enum cer0_synthesizer_speech_sound sound;

  unsigned long int length;
};

struct cer0_synthesizer_speech {
  struct cer0_synthesizer synthesizer;
  
  struct cer0_synthesizer_speech_segment* segments;
  unsigned int length_segments;
};

void cer0_synthesier_speech_initialize(
  struct cer0_synthesizer_speech*,
  float
);

void cer0_synthesizer_speech_speak_segments(
  struct cer0_synthesizer_speech*,
  struct cer0_synthesizer_speech_segment*,
  unsigned int
);

void cer0_synthesizer_speech_segment_next(
  struct cer0_synthesizer_speech*
);

float cer0_synthesizer_speech_poll(
  struct cer0_synthesizer_speech*
);

void cer0_synthesizer_speech_destroy(
  struct cer0_synthesizer_speech*
);

#endif
