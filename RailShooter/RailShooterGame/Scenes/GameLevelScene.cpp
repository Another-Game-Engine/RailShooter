#include "GameLevelScene.hpp"

#include <Core/Inputs/Input.hh>
#include <Core/ConfigurationManager.hpp>
#include <AssetManagement/AssetManager.hh>

#include <Components/CameraComponent.hpp>
#include <Components/FreeFlyComponent.hh>

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
		if (getInstance<AGE::AssetsManager>()->isLoading())
		{
			return true;
		}
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
		return true;
	}
}