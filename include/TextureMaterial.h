#ifndef _TEXTUREMATERIAL_
#define _TEXTUREMATERIAL_


#include "MaterialGL.h"

class TextureMaterial : public MaterialGL
{
public :
	GLProgramPipeline* m_ProgramPipeline;
	TextureMaterial(string name = "");
	~TextureMaterial();
	virtual void render(Node* o);
	virtual void animate(Node* o, const float elapsedTime);
	virtual void displayInterface() {};

	string getName() { return m_Name; };

protected:
	std::string m_Name;
	Scene* scene;
};

#endif