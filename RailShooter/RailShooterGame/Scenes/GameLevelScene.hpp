#pragma once

#include <Core/AScene.hh>
#include <Core/Engine.hh>
#include <memory>

namespace AGE
{
	class GameLevelScene : public AScene
	{
	public:
		static const std::string Name;

		GameLevelScene(AGE::Engine *engine);

		virtual ~GameLevelScene(void);
		virtual bool _userStart();
		virtual bool _userUpdateBegin(float time);
		virtual bool _userUpdateEnd(float time);
	};
}