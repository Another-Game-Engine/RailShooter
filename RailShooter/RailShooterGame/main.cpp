#include <stdlib.h>
#include <Core/Engine.hh>

// DEPENDENCIES
#include <Context/SDL/SdlContext.hh>
#include <Core/ConfigurationManager.hpp>
#include <Physic/BulletDynamicManager.hpp>
#include <Core/Timer.hh>
#include <AssetManagement/AssetManager.hh>
#include <Core/ConfigurationManager.hpp>

#ifdef USE_IMGUI
#include <Utils/Age_Imgui.hpp>
#endif


#include <Threads/ThreadManager.hpp>
#include <Threads/MainThread.hpp>
#include <Core/DefaultConfiguration.hpp>
#include <Threads/RenderThread.hpp>
#include <Threads/Tasks/BasicTasks.hpp>

using namespace AGE;

int			main(int ac, char **av)
{
	InitAGE();
	auto engine = CreateEngine();

	engine->launch(std::function<bool()>([&]()
	{
		GetThreadManager()->setAsWorker(true, true, false);
		engine->setInstance<Timer>();
		engine->setInstance<AssetsManager>();

		auto configurationManager = engine->getInstance<ConfigurationManager>();
		configurationManager->setConfiguration<std::string>(std::string("ShadersPath"), std::string(engine->getApplicationPath() + "/../../../../GameEngine/Shaders/"));
#ifdef USE_IMGUI
		GetRenderThread()->getQueue()->emplaceFutureTask<Tasks::Basic::BoolFunction, bool>([=](){
			Imgui::getInstance()->init(engine);
			return true;
		}).get();
#endif
		return true;
	}));
	return (EXIT_SUCCESS);
}
