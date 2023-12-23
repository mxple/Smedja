#pragma once

#include "Core.h"

namespace Smedja {

	class Application {
	public:
		Application();
		virtual ~Application();

		void run();
	};

	// To be defined in client
	Application* createApplication();

}
