// Copyright (C) 2016 Elviss Strazdins
// This file is part of the Ouzel engine.

#pragma once

#include "graphics/Renderer.h"

namespace ouzel
{
    class Engine;

    namespace graphics
    {
        class RendererEmpty: public Renderer
        {
            friend Engine;
        public:
            virtual BlendStatePtr createBlendState() override;
            virtual TexturePtr createTexture() override;
            virtual RenderTargetPtr createRenderTarget() override;
            virtual ShaderPtr createShader() override;
            virtual MeshBufferPtr createMeshBuffer() override;
            virtual IndexBufferPtr createIndexBuffer() override;
            virtual VertexBufferPtr createVertexBuffer() override;

        protected:
            RendererEmpty();

            virtual bool init(Window* newWindow,
                              uint32_t newSampleCount,
                              TextureFilter newTextureFilter,
                              PixelFormat newBackBufferFormat,
                              bool newVerticalSync,
                              uint32_t newDepthBits) override;
        };
    } // namespace graphics
} // namespace ouzel
