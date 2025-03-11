#include "EngineContext.h"

namespace Engine
{
	void OSInit();
	void OSShutdown();
}

void Engine::Init()
{
	OSInit();

	// TODO: OS Independet init
}

void Engine::Shutdown()
{
	OSShutdown();

	//TODO: OS Independet Shutdown
}

Engine::EngineContext& Engine::Get()
{
	static EngineContext ctx;
	return ctx;
}
