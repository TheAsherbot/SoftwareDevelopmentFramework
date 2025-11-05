#pragma once
#include "Rendering/Renderer2D.h"

namespace Framework
{

	class Manager
	{
	public:
		Rendering::Renderer2D* renderer;

		
		Manager(void(*onUpdate)(float));
		~Manager();

		void Init(Rendering::Renderer2D* renderer);

	private:
		void(*onUpdate)(float);
	


	};
}