#pragma once
#include <thread>

#include "Rendering/Renderer.h"

namespace Framework
{

	class Manager
	{
	public:
		Rendering::Renderer* renderer;

		
		Manager(void(*onUpdate)(float));
		~Manager();

		void Init(Rendering::Renderer* renderer);

	private:
		void(*onUpdate)(float);
	
		// std::thread* graphicsThread;


		void UpdateGraphics();
	};
}