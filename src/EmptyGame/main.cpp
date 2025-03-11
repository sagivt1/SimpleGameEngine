#include <EngineCore/EngineContext.h>

int main()
{
	Engine::Init();

	auto& wnd = *Engine::Get().Window;

	while(!wnd.CloseRequsted())
	{
		wnd.Update();
	}

	Engine::Shutdown();
}