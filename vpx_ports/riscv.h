/*
 *  Copyright (c) 2023 The WebM project authors. All Rights Reserved.
 *
 *  Use of this source code is governed by a BSD-style license
 *  that can be found in the LICENSE file in the root of the source
 *  tree. An additional intellectual property rights grant can be found
 *  in the file PATENTS.  All contributing project authors may
 *  be found in the AUTHORS file in the root of the source tree.
 */

#ifndef VPX_VPX_PORTS_RISCV_H_
#define VPX_VPX_PORTS_RISCV_H_

#ifdef __riscv_v_intrinsic
#include <riscv_vector.h>
#endif/* __riscv_v_intrinsic */

#ifdef __cplusplus
extern "C" {
#endif

#define HAS_RVV 0x01

int riscv_cpu_caps(void);

#ifdef __cplusplus
}  // extern "C"
#endif

#endif  // VPX_VPX_PORTS_RISCV_H_

