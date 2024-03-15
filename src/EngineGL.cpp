
#include "EngineGL.h"
#include "Scene.h"

#include "Materials/BaseMaterial/BaseMaterial.h"



#include "Texture2D.h"
//#include <Materials/PhongMaterial/PhongMaterial.h>
#include <Materials/SphereMaterial/SphereMaterial.h>
#include <Materials/LumiereMaterial/LumiereMaterial.h>
#include <Materials/PhongMaterialTP3/PhongMaterialTP3.h>


// Message callbck error for getting OpenGL problems 
// All credits to https://github.com/fendevel/Guide-to-Modern-OpenGL-Functions/blob/master/README.md#gltexture
void message_callback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, GLchar const* message, void const* user_param)
{
	auto const src_str = [source]() {
		switch (source)
		{
		case GL_DEBUG_SOURCE_API: return "API";
		case GL_DEBUG_SOURCE_WINDOW_SYSTEM: return "WINDOW SYSTEM";
		case GL_DEBUG_SOURCE_SHADER_COMPILER: return "SHADER COMPILER";
		case GL_DEBUG_SOURCE_THIRD_PARTY: return "THIRD PARTY";
		case GL_DEBUG_SOURCE_APPLICATION: return "APPLICATION";
		case GL_DEBUG_SOURCE_OTHER: return "OTHER";
		default:return "";
		}
	}();

	auto const type_str = [type]() {
		switch (type)
		{
		case GL_DEBUG_TYPE_ERROR: return "ERROR";
		case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR: return "DEPRECATED_BEHAVIOR";
		case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR: return "UNDEFINED_BEHAVIOR";
		case GL_DEBUG_TYPE_PORTABILITY: return "PORTABILITY";
		case GL_DEBUG_TYPE_PERFORMANCE: return "PERFORMANCE";
		case GL_DEBUG_TYPE_MARKER: return "MARKER";
		case GL_DEBUG_TYPE_OTHER: return "OTHER";
		default:return "";
		}
	}();

	auto const severity_str = [severity]() {
		switch (severity) {
		case GL_DEBUG_SEVERITY_NOTIFICATION: return "NOTIFICATION";
		case GL_DEBUG_SEVERITY_LOW: return "LOW";
		case GL_DEBUG_SEVERITY_MEDIUM: return "MEDIUM";
		case GL_DEBUG_SEVERITY_HIGH: return "HIGH";
		default:return "";
		}
	}();
	LOG_INFO << src_str << ", " << type_str << ", " << severity_str << ", " << id << ": " << message << '\n';
}



EngineGL::EngineGL(int width, int height) 
{
	m_Width = width;
	m_Height = height;

	myFBO = NULL;



	scene = Scene::getInstance();	
	scene->resizeViewport(m_Width, m_Height);

}

EngineGL::~EngineGL()
{


}


void EngineGL::setupEngine()
{
	glEnable(GL_DEPTH_TEST);
	glViewport(0, 0, m_Width, m_Height);
	setClearColor(glm::vec4(0.5,0.5,0.5,1.0));


	this->allNodes = new NodeCollector();

	allNodes->collect(scene->getRoot());

	glEnable(GL_DEBUG_OUTPUT);
	glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
	glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DEBUG_SEVERITY_NOTIFICATION, 0, nullptr, GL_FALSE);
	glDebugMessageCallback(message_callback, nullptr);

	LOG_INFO << "initialisation complete" << std::endl;
}

bool EngineGL::init()
{

	LOG_INFO << "Initializing Scene" << std::endl;
	//Création d'un materiau de Base
	// 
	// TP 2 *******************************************
	// 
	//PhongMaterial* s = new PhongMaterial("IMN401-TP2");
	//PhongMaterial* phongMaterial = new PhongMaterial("IMN401-TP2");
	//SphereMaterial* sphereMaterial = new SphereMaterial("IMN401-TP2");
	PhongMaterialTP3* s = new PhongMaterialTP3("IMN401-TP3");
	
	BaseMaterial* baseMaterial = new BaseMaterial("IMN401-TP2");
	PhongMaterialTP3* phongMaterial = new PhongMaterialTP3("IMN401-TP2");
	LumiereMaterial* lumiereMaterial = new LumiereMaterial("IMN401-TP2");

	//TEXTURE
	Texture2D* t1 = new Texture2D(TexturePath + "Bunny1.png");
	Texture2D* t2 = new Texture2D(TexturePath + "Bunny2.png");
	phongMaterial->setTexture(t1);

	// d'un objet, méthode détaillée
	Node* bunny = scene->getNode("Bunny");
	bunny->setModel(scene->m_Models.get<ModelGL>(ObjPath + "Bunny.obj"));
	bunny->frame()->scale(glm::vec3(5.0));
	bunny->setMaterial(phongMaterial);
	bunny->adopt(scene->getNode("A"));


	//add Lumiere
	Node* lumiere = scene->getNode("Light");
	lumiere->setModel(scene->m_Models.get<ModelGL>(ObjPath + "Sphere.obj"));
	lumiere->setMaterial(lumiereMaterial);
	lumiere->frame()->translate(glm::vec3(0, 5.0, 0));

	// add sphere L
	Node* l = scene->getNode("L");
	l->setModel(scene->m_Models.get<ModelGL>(ObjPath + "Sphere.obj"));
	l->setMaterial(s);
	l->frame()->translate(glm::vec3(1.0, 0.0, 0.0));
 


	// add A source
	//Node* a = scene->getNode("A");
	//a->setMaterial(sphereMaterial);
	//a->adopt(l);
	
	//add floor
	//Node* floor = scene->getNode("Floor");
	//floor->setModel(scene->m_Models.get<ModelGL>(ObjPath + "wall.obj"));
	//floor->setMaterial(phongMaterial);
	//floor->frame()->translate(glm::vec3(0.0, -0.5, 0.0));

	scene->getSceneNode()->adopt(lumiere);
	scene->getSceneNode()->adopt(bunny);
	//scene->getSceneNode()->adopt(floor);

	setupEngine();	
	return(true);
}


void EngineGL::render ()
{
		
	glEnable(GL_DEPTH_TEST);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	for (unsigned int i = 0; i < allNodes->nodes.size(); i++)
		allNodes->nodes[i]->render();
	
	
}

void EngineGL::animate (const float elapsedTime)
{
	// Animate each node
	for (unsigned int i = 0; i < allNodes->nodes.size(); i++)
	{
		
		allNodes->nodes[i]->animate(elapsedTime);
	}
		

	// Update Camera Buffer
	scene->camera()->updateBuffer();
}

void EngineGL::onWindowResize(int w, int h)
{
	m_Width = w;
	m_Height = h;
	glViewport(0, 0, w, h);
	float ratio = (float)w / (float)h;

	scene->resizeViewport(w,h);
	scene->camera()->setPerspectiveProjection(glm::radians(45.0f), ratio, 1.0f, 2000.0f);

}

void EngineGL::setClearColor(glm::vec4 color)
{
	glClearColor(color.x, color.y, color.z,color.w);
}
void EngineGL::displayInterface()
{
	if (myFBO)
	{
		if (ImGui::BeginMainMenuBar())
		{
			if (ImGui::BeginMenu("FBOs"))
			{
				ImGui::MenuItem(myFBO->getName().c_str(), NULL, &(myFBO->show_interface));
				ImGui::EndMenu();
			}
			ImGui::EndMainMenuBar();
		}

		myFBO->displayInterface();
	}

}
