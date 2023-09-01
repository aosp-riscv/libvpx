#ifdef __riscv_v_intrinsic
#include <riscv_vector.h>
#endif /* __riscv_v_intrinsic */

#include "./vpx_config.h"
#include "./vp8_rtcd.h"

void vp8_copy_mem16x16_rvv(unsigned char *src, int src_stride,
                           unsigned char *dst, int dst_stride) {
  vuint64m2_t v;
  size_t vl;
  size_t n = 16;
  while (n) {
    /* Assume e64 is supported. */
    vl = __riscv_vsetvl_e64m2(n);

    v = __riscv_vlse64_v_u64m2((uint64_t *) src, src_stride, vl);
    __riscv_vsse64_v_u64m2((uint64_t *) dst, dst_stride, v, vl);

    v = __riscv_vlse64_v_u64m2((uint64_t *) (src + 8), src_stride, vl);
    __riscv_vsse64_v_u64m2((uint64_t *) (dst + 8), dst_stride, v, vl);

    n -= vl;
    src += src_stride * vl;
    dst += dst_stride * vl;
  }
}

void vp8_copy_mem8x8_rvv(unsigned char *src, int src_stride,
                         unsigned char *dst, int dst_stride) {
  size_t n = 8;
  size_t vl;
  vuint64m2_t v;

  while (n) {
    /* Assume e64 is supported. */
    vl = __riscv_vsetvl_e64m2(n);

    v = __riscv_vlse64_v_u64m2((uint64_t *) src, src_stride, vl);
    __riscv_vsse64_v_u64m2((uint64_t *) dst, dst_stride, v, vl);

    n -= vl;
    src += src_stride * vl;
    dst += dst_stride * vl;
  }
}

void vp8_copy_mem8x4_rvv(unsigned char *src, int src_stride,
                         unsigned char *dst, int dst_stride) {
  size_t vl;
  vuint64m2_t v;

  /* VL must be 4 because VLEN must be >= 128. Assume e64 is supported. */
  vl = __riscv_vsetvl_e64m2(4);
  v = __riscv_vlse64_v_u64m2((uint64_t *) src, src_stride, vl);
  __riscv_vsse64_v_u64m2((uint64_t *) dst, dst_stride, v, vl);
}
