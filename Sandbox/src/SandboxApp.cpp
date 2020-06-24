#include <Reyes.h>

class Sandbox : public Reyes::Application {
public:
	Sandbox() {

	}

	~Sandbox() {

	}
};

Reyes::Application *Reyes::CreateApplication() {
	return new Sandbox();
}