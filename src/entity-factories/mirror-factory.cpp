#include "mirror-factory.hpp"

#include <glm/glm.hpp>
#include <glad/glad.h>

#include "core/tags.hpp"
#include "core/constants.hpp"
#include "logger/gl-log-handler.hpp"
#include "components/transform.hpp"
#include "components/hitbox.hpp"

#include "components/constrained-rotation.hpp"

#include "services/locator.hpp"
#include "services/random/i-random.hpp"

MirrorFactory::MirrorFactory(entt::DefaultRegistry& registry) : Factory(registry)
{
	m_mirrorSprite = m_spriteFactory.createSingle("res/images/textures/mirror.png", glm::vec2(2*MIRROR_RADIUS));
}

MirrorFactory::~MirrorFactory() {
	GLCall(glDeleteTextures(1, &m_mirrorSprite.textureID));
	GLCall(glDeleteVertexArrays(1, &m_mirrorSprite.vaID));
}

unsigned int MirrorFactory::create(float posX, float posY) {
	IRandom& randomService = entt::ServiceLocator<IRandom>::ref();
	auto myEntity = m_registry.create();
	m_registry.assign<entityTag::Mirror>(myEntity);
	m_registry.assign<cmpt::Sprite>(myEntity, m_mirrorSprite);
	m_registry.assign<renderTag::Single>(myEntity);
	m_registry.assign<cmpt::Transform>(myEntity, glm::vec2(posX, posY), glm::vec2(1.0f));
	m_registry.assign<cmpt::Hitbox>(myEntity, MIRROR_RADIUS);
	m_registry.assign<cmpt::ConstrainedRotation>(myEntity, 16);
	return myEntity;
}
