#include "pch.h"

#include "Application.h"

namespace Smedja {

Application::Application() {
	m_Window = std::unique_ptr<Window>(new Window());
}

Application::~Application() {
}

void Application::run() {
	while (m_Running) {
		glClearColor(1, 1, 1, 1);
		glClear(GL_COLOR_BUFFER_BIT);
		m_Window->onUpdate();
	}
}

}
