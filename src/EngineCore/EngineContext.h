#pragma once

#include <EngineCore/IWindow.h>

#include <memory>
 
namespace Engine 
{
	/*
	* @brief Core struct that defines all engine subsystem 
	*/
	struct EngineContext
	{
		std::unique_ptr<IWindow> Window;
	};

	/*
	* @brief init the engine systems
	*/
	void Init();

	/*
	* @brief Shoutdown the engine systems
	*/
	void Shutdown();

	/*
	* @brief Retrives the engines context
	* @return Refernce to context
	*/
	EngineContext& Get();
}

