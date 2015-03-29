#include <Components/Component.hh>

namespace AGE
{
	struct HealthComponent : public ComponentBase
	{
		int _health;
		int _fullHealthValue;

		HealthComponent();
		virtual ~HealthComponent();

		virtual void _copyFrom(const ComponentBase *model);

		void init(int health = 0, int fullHealthValue = 0);

		virtual void reset();

#ifdef EDITOR_ENABLED
		virtual void editorUpdate(AScene *scene);
#endif

		//////
		////
		// Serialization

		template <typename Archive>
		void serialize(Archive &ar, uint32_t version)
		{
			ar(cereal::make_nvp("Health", _health));
			ar(cereal::make_nvp("Full health value", _fullHealthValue));
		}

		// !Serialization
		////
		//////
	};
}

CEREAL_CLASS_VERSION(AGE::HealthComponent, 0);