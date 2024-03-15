#include "TextureMaterial.h"

TextureMaterial::TextureMaterial(string name) :
	m_Name(name), m_ProgramPipeline(NULL)
{
	m_ProgramPipeline = new GLProgramPipeline(name);
	scene = Scene::getInstance();
}
TextureMaterial::~TextureMaterial()
{
	if (m_ProgramPipeline != NULL)
		delete m_ProgramPipeline;
}

void TextureMaterial::render(Node* o)
{
}

void TextureMaterial::animate(Node* o, const float elapsedTime)
{
}
