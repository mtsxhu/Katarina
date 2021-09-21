#include "Katarina.h"

class Sandbox:public Katarina::Application
{
public:
	Sandbox() = default;
	virtual ~Sandbox(){}
};

Katarina::Application* Katarina::CreateApplication()
{
	return new Sandbox();
}

