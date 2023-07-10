#include <riscv_vector.h>
#include <stdio.h>
#include "./vpx_config.h"
#include "./vp8_rtcd.h"

#define UNUSED(x) (void)(x)

void vp8_sixtap_predict4x4_rvv(unsigned char *src_ptr, int src_pixels_per_line,
                                int xoffset, int yoffset,
                                unsigned char *dst_ptr, int dst_pitch)
{
  UNUSED(src_ptr);
  UNUSED(src_pixels_per_line);
  UNUSED(xoffset);
  UNUSED(yoffset);
  UNUSED(dst_ptr);
  UNUSED(dst_pitch);

  printf("--> vp8_sixtap_predict4x4_rvv\n");
}

void vp8_sixtap_predict8x4_rvv(unsigned char *src_ptr, int src_pixels_per_line,
                                int xoffset, int yoffset,
                                unsigned char *dst_ptr, int dst_pitch)
{
  UNUSED(src_ptr);
  UNUSED(src_pixels_per_line);
  UNUSED(xoffset);
  UNUSED(yoffset);
  UNUSED(dst_ptr);
  UNUSED(dst_pitch);

  printf("--> vp8_sixtap_predict8x4_rvv\n");
}

void vp8_sixtap_predict8x8_rvv(unsigned char *src_ptr, int src_pixels_per_line,
                                int xoffset, int yoffset,
                                unsigned char *dst_ptr, int dst_pitch)
{
  UNUSED(src_ptr);
  UNUSED(src_pixels_per_line);
  UNUSED(xoffset);
  UNUSED(yoffset);
  UNUSED(dst_ptr);
  UNUSED(dst_pitch);

  printf("--> vp8_sixtap_predict8x8_rvv\n");
}

void vp8_sixtap_predict16x16_rvv(unsigned char *src_ptr,
                                  int src_pixels_per_line, int xoffset,
                                  int yoffset, unsigned char *dst_ptr,
                                  int dst_pitch)
{
  UNUSED(src_ptr);
  UNUSED(src_pixels_per_line);
  UNUSED(xoffset);
  UNUSED(yoffset);
  UNUSED(dst_ptr);
  UNUSED(dst_pitch);

  printf("--> vp8_sixtap_predict16x16_rvv\n");
}
