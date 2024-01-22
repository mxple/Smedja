#include "Log.h"

#include "spdlog/sinks/stdout_color_sinks.h"

namespace Smedja {

std::shared_ptr<spdlog::logger> Log::s_CoreLogger;
std::shared_ptr<spdlog::logger> Log::s_ClientLogger;

void Log::init() {
    spdlog::set_pattern("%^[%T] [%l] %n: %v%$");
    s_CoreLogger = spdlog::stdout_color_mt("ENGINE");
    s_CoreLogger->set_level(spdlog::level::trace);

    s_ClientLogger = spdlog::stdout_color_mt("APP");
    s_ClientLogger->set_level(spdlog::level::trace);
}

} // namespace Smedja

// GLenum glCheckError_(const char *file, int line) {
//     GLenum errorCode;
//     while ((errorCode = glGetError()) != GL_NO_ERROR)
//     {
//         std::string error;
//         switch (errorCode)
//         {
//             case GL_INVALID_ENUM:                  error = "INVALID_ENUM"; break;
//             case GL_INVALID_VALUE:                 error = "INVALID_VALUE"; break;
//             case GL_INVALID_OPERATION:             error = "INVALID_OPERATION"; break;
//             case GL_STACK_OVERFLOW:                error = "STACK_OVERFLOW"; break;
//             case GL_STACK_UNDERFLOW:               error = "STACK_UNDERFLOW"; break;
//             case GL_OUT_OF_MEMORY:                 error = "OUT_OF_MEMORY"; break;
//             case GL_INVALID_FRAMEBUFFER_OPERATION: error = "INVALID_FRAMEBUFFER_OPERATION"; break;
//         }
//         SD_CORE_ERROR("OpenGL Error: {0} | {1} ({2})", error, file, line);
//     }
//     return errorCode;
// }
