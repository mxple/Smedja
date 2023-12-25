#include "Window.h"
#include "Application.h"
#include "pch.h"

namespace Smedja {

static bool s_GLFWInitialized = false;

Window::Window() {
	init(WindowProps());
}

Window::Window(const WindowProps& props) {
	init(props);
}

Window::~Window() {
	shutdown();
}

// Initializes a GLFW window as per GLFW documentation
// Should support multiple window instances
void Window::init(const WindowProps& props) {
	m_Data.title = props.title;
	m_Data.width = props.width;
	m_Data.height = props.height;

	SD_CORE_INFO("Creating window {0} ({1}, {2})", props.title, props.width, props.height);

	if (!s_GLFWInitialized) {
		int success = glfwInit();
		CORE_ASSERT(success, "Could not initialize GLFW!");

		// Set GLFW error callback which will report GLFW errors using spdlog
		glfwSetErrorCallback([](int error, const char* description) {
			SD_CORE_ERROR("GLFW Error ({0}): {1}", error, description);
		});
		s_GLFWInitialized = true;
	}

	m_Window = glfwCreateWindow((int)props.width, (int)props.height, m_Data.title.c_str(), nullptr, nullptr);

	if (m_Window == nullptr) {
		SD_CORE_ERROR("Failed to create GLFW window!");
		glfwTerminate();
		return;
	}

	glfwMakeContextCurrent(m_Window);
	glfwSetWindowUserPointer(m_Window, &m_Data);
	setVSync(true);
}

// Shutdown does not call GLFW terminate as it may be used by other windows
void Window::shutdown() {
	glfwDestroyWindow(m_Window);
}

void Window::onUpdate() {
	glfwPollEvents();
	glfwSwapBuffers(m_Window);
}

void Window::setVSync(bool enabled) {
	if (enabled) {
		glfwSwapInterval(1);
	} else {
		glfwSwapInterval(0);
	}
	m_Data.vSync = enabled;
}

bool Window::isVSync() const {
	return m_Data.vSync;
}

}


