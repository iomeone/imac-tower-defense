#include "sprite-factory.hpp"

#include "logger/gl-log-handler.hpp"
#include "graphics/vertex-array.hpp"
#include "graphics/shader.hpp"
#include "graphics/texture.hpp"
#include "graphics/texture-array.hpp"

SpriteFactory::SpriteFactory()
: m_shaderTex("res/shaders/texture/texture.vert", "res/shaders/texture/texture.frag"),
  m_shaderTexArray("res/shaders/texture/texture.vert", "res/shaders/texture/texture-array.frag")
{
    /* Index buffer */
	unsigned int indices[] = {
		0, 1, 2, // First triangle
		3, 1, 2  // Second triangle
	};
	unsigned int arraySize = sizeof(indices) / sizeof(unsigned int);
    m_ib.init(indices, arraySize);
    m_ib.unbind();
}

cmpt::Sprite SpriteFactory::create(const std::string& textureFilepath, glm::vec2 displaySize) {
	/* Vertex buffer */
    // TODO add enum to specify the pivot point ? By default center
	float positions[] = {
        // Pos                           // UV
		-displaySize.x,  displaySize.y,  0.0f, 1.0f, // 0 topleft
		 displaySize.x,  displaySize.y,  1.0f, 1.0f, // 1 topright
		-displaySize.x, -displaySize.y,  0.0f, 0.0f, // 2 bottomleft
		 displaySize.x, -displaySize.y,  1.0f, 0.0f  // 3 bottomright
	};
    unsigned int arraySize = sizeof(positions) / sizeof(float);
    VertexBuffer vb(positions, arraySize * sizeof(float), GL_STATIC_DRAW);
	VertexBufferLayout vbLayout;
	vbLayout.push<float>(2); // Pos (x, y)
    vbLayout.push<float>(2); // Texture coordinates

    /* Vertex array */
    VertexArray va;
	va.addBuffer(vb, vbLayout);

    /* Uniforms */
    m_shaderTex.bind();
    m_shaderTex.setUniformMat4f("u_mvp", glm::mat4(1.0f));
    Texture texture(textureFilepath);
    texture.bind();
	m_shaderTex.setUniform1i("u_texture", 0);
    
    /* Cleanup */
    m_shaderTex.unbind();
    va.unbind();
    vb.unbind();
    texture.unbind();

    /* Send copy of object */
    cmpt::Sprite mySprite(texture.getID(), va.getID(), GL_TEXTURE_2D, &m_shaderTex, &m_ib);
    return mySprite;
}

cmpt::Sprite SpriteFactory::createAtlas(const std::string& textureFilepath, glm::vec2 displaySize, glm::vec2 tileSize) {
    float positions[] = {
        // Pos                           // Inverted UV to start at topleft
		-displaySize.x,  displaySize.y,  0.0f, 0.0f, // 0 topleft
		 displaySize.x,  displaySize.y,  1.0f, 0.0f, // 1 topright
		-displaySize.x, -displaySize.y,  0.0f, 1.0f, // 2 bottomleft
		 displaySize.x, -displaySize.y,  1.0f, 1.0f  // 3 bottomright
	};
    unsigned int arraySize = sizeof(positions) / sizeof(float);
    VertexBuffer vb(positions, arraySize * sizeof(float), GL_STATIC_DRAW);
	VertexBufferLayout vbLayout;
	vbLayout.push<float>(2); // Pos (x, y)
    vbLayout.push<float>(2); // Texture coordinates

    /* Vertex array */
    VertexArray va;
	va.addBuffer(vb, vbLayout);
	
    /* Uniforms */
    m_shaderTexArray.bind();
    m_shaderTexArray.setUniformMat4f("u_mvp", glm::mat4(1.0f));
    TextureArray texture(textureFilepath, (GLsizei) tileSize.x, (GLsizei) tileSize.y);
    texture.bind();
	m_shaderTexArray.setUniform1i("u_texture", 0);
	m_shaderTexArray.setUniform1i("u_activeTile", 0);
    
    /* Cleanup */
    m_shaderTexArray.unbind();
    va.unbind();
    vb.unbind();
    texture.unbind();
    
    /* Send copy of object */
    cmpt::Sprite mySprite(texture.getID(), va.getID(), GL_TEXTURE_2D_ARRAY, &m_shaderTexArray, &m_ib);
    return mySprite;
}