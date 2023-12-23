#include <Smedja.h>

class Sandbox : public Smedja::Application {
public:

	Sandbox() {

	}

	~Sandbox() {

	}

};

Smedja::Application* Smedja::createApplication() {
	return new Sandbox();
}
