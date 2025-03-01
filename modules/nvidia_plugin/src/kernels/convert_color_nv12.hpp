// Copyright (C) 2022 Intel Corporation
// SPDX-License-Identifier: Apache-2.0
//

#pragma once

#include <cuda_runtime.h>

#include "convert_color.hpp"
#include "cuda_type_traits.hpp"
#include "elementtypeswitch.hpp"

namespace ov {
namespace nvidia_gpu {
namespace kernel {

template <ColorConversion Conversion>
class NV12ColorConvert {
public:
    NV12ColorConvert(Type_t element_type,
                     size_t max_threads_per_block,
                     size_t batch_size,
                     size_t image_h,
                     size_t image_w,
                     size_t stride_y,
                     size_t stride_uv);

    void operator()(cudaStream_t stream, const void* in, void* out) const;
    void operator()(cudaStream_t stream, const void* in0, const void* in1, void* out) const;

    template <typename T, typename... Args>
    constexpr void case_(cudaStream_t stream, Args&&... args) const noexcept;

    template <typename T, typename... Args>
    void default_(T t, cudaStream_t, Args&&...) const noexcept;

private:
    template <typename T>
    void callKernel(const cudaStream_t stream, const void* in, void* out) const;
    template <typename T>
    void callKernel(const cudaStream_t stream, const void* in0, const void* in1, void* out) const;

    using Switcher = ElementTypesSwitch<Type_t::u8,
#ifdef CUDA_HAS_BF16_TYPE
                                        Type_t::bf16,
#endif
                                        Type_t::f16,
                                        Type_t::f32>;

    Type_t element_type_;
    dim3 num_blocks_;
    dim3 threads_per_block_;
    size_t batch_size_;
    size_t image_h_;
    size_t image_w_;
    size_t stride_y_;
    size_t stride_uv_;
};

}  // namespace kernel
}  // namespace nvidia_gpu
}  // namespace ov
