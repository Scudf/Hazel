#pragma once

#include "Hazel/Renderer/GraphicsContext.h"

struct GLFWwindow;

namespace Hazel
{
    class OpenGLContext :
        public GraphicsContext
    {
    private:
        GLFWwindow* m_window = nullptr;

    public:
        OpenGLContext(GLFWwindow* windowHandle);

        void init() override;
        void swapBuffers() override;
    };
}
