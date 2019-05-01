#include "explosion-factory.hpp"

#include "core/tags.hpp"
#include "core/constants.hpp"
#include "components/transform.hpp"
#include "components/sprite-animation.hpp"

ExplosionFactory::ExplosionFactory(entt::DefaultRegistry& registry)
: Factory(registry)
{
	m_explosionSprite = m_spriteFactory.createAtlas("res/images/spritesheets/explosion-100x100.png", glm::vec2(30.0f), glm::vec2(100, 100));
}


void ExplosionFactory::create(glm::vec2 pos) {
	auto myEntity = m_registry.create();
	m_registry.assign<cmpt::Sprite>(myEntity, m_explosionSprite);
	m_registry.assign<renderTag::Atlas>(myEntity);
	m_registry.assign<renderTag::OneTimeAtlas>(myEntity);
	m_registry.assign<cmpt::SpriteAnimation>(myEntity, 0, 99, 6);
	m_registry.assign<cmpt::Transform>(myEntity, pos);
}
