#include "Manager.h"

namespace Framework
{
	Manager::Manager(void(*onUpdate)(float))
	{
		this->onUpdate = onUpdate;

	}
	Manager::~Manager()
	{

	}

	void Manager::Init(Rendering::Renderer2D* renderer)
	{
		this->renderer = renderer;

		while (true)
		{
			renderer->Update(0);
			onUpdate(0);
		}
	}
}