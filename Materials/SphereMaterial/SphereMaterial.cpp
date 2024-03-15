
#include "SphereMaterial.h"
#include "Node.h"
#include <glm/gtc/type_ptr.hpp>
#include <glad/glad.h>
#include <iostream>
#include <vector>
#include <chrono>
#include "utils.hpp"
#include <list>
#include <math.h>
#include <GLFW/include/glfw3.h>



SphereMaterial::SphereMaterial(string name) :


	MaterialGL(name)
{
	
	vp = new GLProgram(MaterialPath+"SphereMaterial/Main-VS.glsl", GL_VERTEX_SHADER);
	fp = new GLProgram(MaterialPath+"SphereMaterial/Main-FS.glsl", GL_FRAGMENT_SHADER);
	
	m_ProgramPipeline->useProgramStage(vp, GL_VERTEX_SHADER_BIT);
	m_ProgramPipeline->useProgramStage(fp, GL_FRAGMENT_SHADER_BIT);


	l_View = glGetUniformLocation(vp->getId(), "View");
	l_Proj = glGetUniformLocation(vp->getId(), "Proj");
	l_Model = glGetUniformLocation(vp->getId(), "Model");

	
}

SphereMaterial::~SphereMaterial()
{
	
}

void SphereMaterial::render(Node *o)
{

	
	m_ProgramPipeline->bind();

	o->drawGeometry(GL_TRIANGLES);
	m_ProgramPipeline->release();

	
}
void SphereMaterial::animate(Node* o, const float elapsedTime)
{
	/**********************************************
	*
	* TP 2 - A completer
	Calculer et Transmettre les matrices Model View et Proj au shaders
	- Utilisez glm::value_ptr(mat) pour trouver le pointeur de la matrice mat a transmettre au GPU via la fonction glProgramUniform*()
	- Une matrice 4X4 se transmet grace a glProgramUniformMatrix4fv

	****************************************************/
	scene = Scene::getInstance();

	glm::mat4 matModel = o->frame()->getModelMatrix();
	glm::f32* modelValue = glm::value_ptr(matModel);
	glProgramUniformMatrix4fv(vp->getId(), l_Model, 1, false, modelValue);
	
	glm::mat4 matView = scene->camera()->getViewMatrix();
	glm::f32* viewValue = glm::value_ptr(matView);
	glProgramUniformMatrix4fv(vp->getId(), l_View, 1, false, viewValue);

	glm::mat4 matProj = scene->camera()->getProjectionMatrix();
	glm::f32* projValue = glm::value_ptr(matProj);
	glProgramUniformMatrix4fv(vp->getId(), l_Proj, 1, false, projValue);

	float time = glfwGetTime();
	float sinValue = 0;
	sinValue = abs(sinf(time) * 0.1f);
	o->frame()->rotate(glm::vec3(0,1,0), time * 0.001);



	//o->animate(elapsedTime);

	/*********************************************/


}
