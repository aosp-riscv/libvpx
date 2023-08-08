#include <assert.h>
#include "./vpx_dsp_rtcd.h"
#include <riscv_vector.h>

/***
 * This function appends contents of b[] to the end of a[].
 * a[] is of size m+n and b[] is of size n. 
*/
void concat(uint8_t a[], uint8_t b[], int m, int n)
{
  memcpy(a + m, b, sizeof(b));
}

/***
 * This function computes the value of  (va + vb) / 2
*/
vuint8m1_t average_add(const vuint8m1_t va, const vuint8m1_t vb, const size_t vl){
  vuint16m2_t vavg = __riscv_vwaddu_vv_u16m2(va, vb, vl);
  vavg = __riscv_vadd_vx_u16m2(vavg, 1, vl);
  return __riscv_vnsrl_wx_u8m1 (vavg, 1, vl);
}

void vpx_comp_avg_pred_rvv(uint8_t *comp_pred, const uint8_t *pred, int width,
                         int height, const uint8_t *ref, int ref_stride) {
  if (width > 8){
    int x, y = height;
    const size_t vl = 16;
    vuint8m1_t vr, vavg;
    do {
      for (x = 0; x < width; x += 16) {
        const vuint8m1_t vp = __riscv_vle8_v_u8m1(pred + x, vl);
        vr = __riscv_vle8_v_u8m1(ref + x, vl);
        vr = average_add(vp, vr, vl);
        __riscv_vse8_v_u8m1(comp_pred + x, vr, vl);
      }
      comp_pred += width;
      pred += width;
      ref += ref_stride;
    } while (--y);
  } else if (width == 8) {
    int i = width * height;
    const size_t vl = 16;
    vuint8m1_t vr;
    vuint8m1_t vr_0, vr_1, vv;
    uint8_t a[16] = {0};
    uint8_t b[8] = {0};
    do {
      const vuint8m1_t vp = __riscv_vle8_v_u8m1(pred, vl);
      vr_0 = __riscv_vle8_v_u8m1(ref, vl / 2);
      __riscv_vse8_v_u8m1(a, vr_0, vl / 2);
      vr_1 = __riscv_vle8_v_u8m1(ref + ref_stride, vl / 2);
      __riscv_vse8_v_u8m1(b, vr_1, vl / 2);
      concat(a, b, 8, 8);
      vr = __riscv_vle8_v_u8m1(a, vl);
      vr = average_add(vp, vr, vl);
      ref += 2 * ref_stride;
      __riscv_vse8_v_u8m1(comp_pred, vr, vl);

      pred += 16;
      comp_pred += 16;
      i -= 16;
      } while (i);
  } else {
    int i = width * height;
    assert(width == 4);
    const size_t vl = 16;
    vuint8m1_t vr;
    if (width == ref_stride) {
      do {
        const vuint8m1_t vp  = __riscv_vle8_v_u8m1(pred, vl);
        vr = __riscv_vle8_v_u8m1(ref, vl);
        ref += 4 * ref_stride;
        vr = average_add(vp, vr, vl);
        __riscv_vse8_v_u8m1(comp_pred, vr, vl);

        pred += 16;
        comp_pred += 16;
        i -= 16; 
      } while (i);
    } else {
      do {
        uint32_t a;
        vuint32m1_t a_u32;

        const vuint8m1_t vp  = __riscv_vle8_v_u8m1(pred, vl);
        a_u32 = __riscv_vlse32_v_u32m1(ref, ref_stride, vl / 4);
        vuint8m1_t vr = __riscv_vreinterpret_v_u32m1_u8m1(a_u32);
        ref += 4 * ref_stride;
        vr = average_add(vp, vr, vl);        
        __riscv_vse8_v_u8m1(comp_pred, vr, vl);

        pred += 16;
        comp_pred += 16;
        i -= 16;  
      } while (i);
    }
  }
}
