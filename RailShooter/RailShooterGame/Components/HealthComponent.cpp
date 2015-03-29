#include "Health.hpp"

namespace AGE
{
	HealthComponent::HealthComponent()
		: _health(0)
		, _fullHealthValue(0)
	{}

	HealthComponent::~HealthComponent()
	{}

	void HealthComponent::_copyFrom(const ComponentBase *model)
	{
		auto o = static_cast<const HealthComponent*>(model);
		_health = o->_health;
		_fullHealthValue = o->_fullHealthValue;
	}

	void HealthComponent::init(int health, int fullHealthValue/* = 0 */)
	{
		_health = health;
		_fullHealthValue = fullHealthValue;
		if (_fullHealthValue == 0)
		{
			_fullHealthValue = _health;
		}
	}

	void HealthComponent::reset()
	{
		_health = 0;
		_fullHealthValue = 0;
	}

#ifdef EDITOR_ENABLED
	void HealthComponent::editorUpdate(AScene *scene)
	{
		ImGui::InputInt("Health", &_health);
		ImGui::InputInt("Full health value", &_fullHealthValue);
	}
#endif // EDITOR_ENABLED
}