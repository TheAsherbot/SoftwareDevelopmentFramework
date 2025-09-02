#include "Manager.h"

namespace Framework
{
	Manager::Manager(void(*onUpdate)(float))
	{
		this->onUpdate = onUpdate;
		//graphicsThread = new std::thread(UpdateGraphics, "Graphics Thread");
	}
	Manager::~Manager()
	{

	}

	void Manager::Init(Rendering::Renderer* renderer)
	{
		this->renderer = renderer;

		while (true)
		{
			onUpdate(0);
			UpdateGraphics();
		}
	}

	void Manager::UpdateGraphics()
	{
		while (true)
		{
			renderer->Update(0);
		}
	}
}