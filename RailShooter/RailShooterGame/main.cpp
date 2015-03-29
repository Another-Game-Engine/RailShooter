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

//COMPONENTS
#include <Components/CameraComponent.hpp>
#include <Components/FPController.hpp>
#include <Components/MeshRenderer.hh>
#include <Components/Light.hh>
#include <Components/RigidBody.hpp>
#include <Components/SpotLight.hh>
#include <Components/FreeFlyComponent.hh>

#include <scenes/GameLevelScene.hpp>


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
		engine->setInstance<AGE::BulletDynamicManager, AGE::BulletCollisionManager>()->init();
		engine->getInstance<AGE::BulletCollisionManager>()->setAssetsDirectory(engine->getApplicationPath() + "/../../../../GameEngine/Vendors/Serialized/");

		//auto configurationManager = engine->getInstance<ConfigurationManager>();
		//configurationManager->setConfiguration<std::string>(std::string("ShadersPath"), std::string(engine->getApplicationPath() + "/../../../../GameEngine/Shaders/"));
#ifdef USE_IMGUI
		GetRenderThread()->getQueue()->emplaceFutureTask<Tasks::Basic::BoolFunction, bool>([=](){
			Imgui::getInstance()->init(engine);
			return true;
		}).get();
#endif

		REGISTER_COMPONENT_TYPE(MeshRenderer);
		REGISTER_COMPONENT_TYPE(RigidBody);
		REGISTER_COMPONENT_TYPE(PointLightComponent);
		REGISTER_COMPONENT_TYPE(CameraComponent);
		REGISTER_COMPONENT_TYPE(FreeFlyComponent);

		engine->addScene(std::make_shared<AGE::GameLevelScene>(engine), AGE::GameLevelScene::Name);

		if (!engine->initScene(AGE::GameLevelScene::Name))
		{
			return false;
		}

		engine->enableScene(AGE::GameLevelScene::Name, 0);

		return true;
	}));
	return (EXIT_SUCCESS);
}
