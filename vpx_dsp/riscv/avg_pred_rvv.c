#include <assert.h>
#include "./vpx_dsp_rtcd.h"
#include <riscv_vector.h>
#include <stdlib.h>
#include <string.h>

void vpx_comp_avg_pred_rvv(uint8_t *comp_pred, const uint8_t *pred, int width,
                         int height, const uint8_t *ref, int ref_stride) {
                          
  const size_t avl = 16;
  size_t vl;
  if (width > 8){
    int x, y = height;
    vuint8m8_t vr, vp;
    do {
      for (x = 0; x < width; x += vl){
        vl =  __riscv_vsetvl_e8m8(width - x);
        vp = __riscv_vle8_v_u8m8(pred + x, vl);
        vr = __riscv_vle8_v_u8m8(ref + x, vl);
        vr = __riscv_vaaddu_vv_u8m8(vp, vr, __RISCV_VXRM_RNU, vl);
        __riscv_vse8_v_u8m8(comp_pred + x, vr, vl);
      }
      comp_pred += width;
      pred += width;
      ref += ref_stride;
    } while (--y);
  } else if (width == 8) {
    int i = width * height;
    size_t k;
    uint8_t *index;
    vuint8m1_t vr, vp, vindex;
    do {
      vl = __riscv_vsetvl_e8m1(avl);
      index = (uint8_t *)malloc(vl * sizeof(uint8_t));
      memset(index, 0, vl);
      vp = __riscv_vle8_v_u8m1(pred, vl);
      for(k = 0; k < vl; k++){
        if(k < vl / 2){
          index[k] = (uint8_t)k;
        }else{
          index[k] = (uint8_t)(ref_stride + k - 8);
        }
      }
      vindex = __riscv_vle8_v_u8m1(index, vl);
      vr =  __riscv_vloxei8_v_u8m1(ref, vindex, vl);
      vr = __riscv_vaaddu_vv_u8m1(vp, vr, __RISCV_VXRM_RNU, vl);
      __riscv_vse8_v_u8m1(comp_pred, vr, vl);
      ref += 2 * ref_stride;
      pred += vl;
      comp_pred += vl;
      i -= vl;
      } while (i);
  } else {
    int i = width * height;
    vuint8m1_t vr, vp;
    vuint32m1_t a_u32;
    assert(width == 4);
    vl = __riscv_vsetvl_e8m1(avl);
    do {
      vp  = __riscv_vle8_v_u8m1(pred, vl);
      a_u32 = __riscv_vlse32_v_u32m1((const uint32_t*)ref, ref_stride, vl / 4);
      vr = __riscv_vreinterpret_v_u32m1_u8m1(a_u32);
      ref += 4 * ref_stride;
      vr = __riscv_vaaddu_vv_u8m1(vp, vr, __RISCV_VXRM_RNU, vl);  
      __riscv_vse8_v_u8m1(comp_pred, vr, vl);

      pred += vl;
      comp_pred += vl;
      i -= vl;  
    } while (i);
  }
}