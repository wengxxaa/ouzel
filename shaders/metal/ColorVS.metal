// Copyright (C) 2016 Elviss Strazdins
// This file is part of the Ouzel engine.

#include <simd/simd.h>

using namespace metal;

typedef struct __attribute__((__aligned__(256)))
{
    matrix_float4x4 modelViewProj;
} uniforms_t;

typedef struct
{
    float3 position [[attribute(0)]];
    half4 color [[attribute(1)]];
} VertexPCT;

typedef struct
{
    float4 position [[position]];
    half4  color;
} ColorInOut;

// Vertex shader function
vertex ColorInOut main_vs(VertexPCT vert [[stage_in]],
                          constant uniforms_t& uniforms [[buffer(1)]])
{
    ColorInOut out;
    
    float4 in_position = float4(vert.position, 1.0);
    out.position = uniforms.modelViewProj * in_position;

    out.color = vert.color;
    return out;
}
