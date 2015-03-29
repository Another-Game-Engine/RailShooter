#pragma once

#include <Components/ComponentRegistrationManager.hpp>

#include <RailShooterGame/Components/HealthComponent.cpp>

void RegisterComponents()
{
	REGISTER_COMPONENT_TYPE(AGE::HealthComponent);
}