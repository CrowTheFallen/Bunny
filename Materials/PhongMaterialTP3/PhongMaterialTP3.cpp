#include "PhongMaterialTP3.h"

#include "TextureMaterial.h"
#include "Node.h"
#include <glm/gtc/type_ptr.hpp>


PhongMaterialTP3::PhongMaterialTP3(string name) :
	TextureMaterial(name)
{

	vp = new GLProgram(MaterialPath + "PhongMaterialTP3/PhongMaterial-VS.glsl", GL_VERTEX_SHADER);
	fp = new GLProgram(MaterialPath + "PhongMaterialTP3/PhongMaterial-FS.glsl", GL_FRAGMENT_SHADER);

	m_ProgramPipeline->useProgramStage(vp, GL_VERTEX_SHADER_BIT);
	m_ProgramPipeline->useProgramStage(fp, GL_FRAGMENT_SHADER_BIT);


	l_View = glGetUniformLocation(vp->getId(), "View");
	l_Proj = glGetUniformLocation(vp->getId(), "Proj");
	l_Model = glGetUniformLocation(vp->getId(), "Model");
	l_PosLum = glGetUniformLocation(vp->getId(), "PosLum");
	l_PosCam = glGetUniformLocation(vp->getId(), "PosCam");


	l_Phong = glGetUniformLocation(fp->getId(), "Phong");
	l_Albedo = glGetUniformLocation(fp->getId(), "diffuseAlbedo");
	l_Sampler = glGetUniformLocation(fp->getId(), "tex");



	param.albedo = glm::vec3(0.2, 0.7, 0.8);
	param.coeff = glm::vec4(0.2, 0.8, 1.0, 100.0);

	l_Time = glGetUniformLocation(vp->getId(), "Time");


	updatePhong();
}


PhongMaterialTP3::~PhongMaterialTP3()
{

}

void PhongMaterialTP3::render(Node* o)
{


	m_ProgramPipeline->bind();

	o->drawGeometry(GL_TRIANGLES);
	m_ProgramPipeline->release();
}
void PhongMaterialTP3::animate(Node* o, const float elapsedTime)
{

	//Recuperer la matrice view
	glm::mat4 view = Scene::getInstance()->camera()->getViewMatrix();
	//Recuperer la matrice proj
	glm::mat4 proj = Scene::getInstance()->camera()->getProjectionMatrix();
	//Recuperer la matrice model
	glm::mat4 model = o->frame()->getModelMatrix();




	glProgramUniformMatrix4fv(vp->getId(), l_View, 1, GL_FALSE, glm::value_ptr(view));
	glProgramUniformMatrix4fv(vp->getId(), l_Proj, 1, GL_FALSE, glm::value_ptr(proj));
	glProgramUniformMatrix4fv(vp->getId(), l_Model, 1, GL_FALSE, glm::value_ptr(model));

	//Cr�ez dans le fragment shader une variable de type sampler2D et transmettez-lui la valeur du handle de cette texture



	// convertir le point (0,0,0) du rep�re "light" vers le repere de l'objet
	glProgramUniform3fv(vp->getId(), l_PosLum, 1, glm::value_ptr(Scene::getInstance()->getNode("Light")->frame()->convertPtTo(glm::vec3(0.0, 0.0, 0.0), o->frame())));
	// convertir le point (0,0,0) du rep�re camera vers le repere de l'objet
	glProgramUniform3fv(vp->getId(), l_PosCam, 1, glm::value_ptr(Scene::getInstance()->camera()->frame()->convertPtTo(glm::vec3(0.0, 0.0, 0.0), o->frame())));



	auto now_time = std::chrono::high_resolution_clock::now();
	auto timevar = now_time.time_since_epoch();
	float millis = 0.001f * std::chrono::duration_cast<std::chrono::milliseconds>(timevar).count();
	glProgramUniform1fv(vp->getId(), l_Time, 1, &millis);



}


void PhongMaterialTP3::updatePhong()
{
	glProgramUniform4fv(fp->getId(), l_Phong, 1, glm::value_ptr(glm::vec4(param.coeff)));
	glProgramUniform3fv(fp->getId(), l_Albedo, 1, glm::value_ptr(param.albedo));
}


void PhongMaterialTP3::setTexture(Texture2D* tex)
{
	m_Texture = tex;
	GLuint64 handle = m_Texture->getHandle();

	glProgramUniform1i(fp->getId(), l_Sampler, handle);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, m_Texture->getId());
}


void PhongMaterialTP3::displayInterface()
{

}





