#include "GameLevelScene.hpp"

#include <Core/Inputs/Input.hh>
#include <Core/ConfigurationManager.hpp>
#include <AssetManagement/AssetManager.hh>

#include <Components/CameraComponent.hpp>
#include <Components/FreeFlyComponent.hh>

#include <Components/MeshRenderer.hh>
#include <Components/RigidBody.hpp>
#include <Components/Light.hh>

#include <Threads/ThreadManager.hpp>
#include <Threads/RenderThread.hpp>
#include <Threads/PrepareRenderThread.hpp>
#include <Threads/Commands/MainToPrepareCommands.hpp>
#include <Threads/Commands/ToRenderCommands.hpp>
#include <Threads/Tasks/BasicTasks.hpp>
#include <Threads/Tasks/ToRenderTasks.hpp>

namespace AGE
{
	const std::string GameLevelScene::Name = "GameLevelScene";

	GameLevelScene::GameLevelScene(AGE::Engine *engine)
		: AScene(engine)
	{
	}

	GameLevelScene::~GameLevelScene(void)
	{
	}

	bool GameLevelScene::_userStart()
	{
		clearAllEntities();
		auto camera = createEntity();
		auto cam = camera.addComponent<CameraComponent>();
		camera.addComponent<FreeFlyComponent>();
		cam->addPipeline(RenderType::DEFERRED);
		camera.getLink().setPosition(glm::vec3(0, 2.5f, 4.5f));

		auto sceneFilePathConfiguration = getInstance<ConfigurationManager>()->getConfiguration<std::string>("ScenesPath");
		AGE_ASSERT(sceneFilePathConfiguration != nullptr);

		auto sceneFileName = sceneFilePathConfiguration->getValue() + "level0_export.json";
		auto assetPackageFileName = sceneFilePathConfiguration->getValue() + "level0_assets.json";

		getInstance<AssetsManager>()->pushNewCallback(assetPackageFileName, std::function<void()>([=](){
			loadFromJson(sceneFileName);
		}));
		getInstance<AssetsManager>()->loadPackage(assetPackageFileName, assetPackageFileName);

		return true;
	}

	bool GameLevelScene::_userUpdateBegin(float time)
	{
		AGE::GetPrepareThread()->getQueue()->emplaceCommand<AGE::Commands::MainToPrepare::PrepareDrawLists>();
		AGE::GetPrepareThread()->getQueue()->emplaceCommand<AGE::Commands::ToRender::RenderDrawLists>();
		return true;
	}

	bool GameLevelScene::_userUpdateEnd(float time)
	{
		if (getInstance<AGE::AssetsManager>()->isLoading())
		{
			return true;
		}
		if (getInstance<Input>()->getPhysicalKeyJustReleased(AGE_ESCAPE))
			return (false);
		if (getInstance<Input>()->getPhysicalKeyJustReleased(AGE_r))
		{
			_userStart();
		}
		return true;
	}
}