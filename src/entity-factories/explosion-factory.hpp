#pragma once

#include <entt/entt.hpp>

#include "factory.hpp"
#include "component-factories/sprite-factory.hpp"
#include "components/sprite.hpp"

class ExplosionFactory : public Factory {
public:
	ExplosionFactory(entt::DefaultRegistry& registry);
	virtual ~ExplosionFactory();

	void create(glm::vec2 pos, ShaderType type);

private:
	SpriteFactory m_spriteFactory;
	cmpt::Sprite m_towerExplosionSprite;
	cmpt::Sprite m_enemyExplosionSprite;
};

