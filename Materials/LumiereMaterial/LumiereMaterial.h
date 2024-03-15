

#ifndef _LumiereMaterial_
#define _LumiereMaterial_


#include "MaterialGL.h"

class LumiereMaterial : public MaterialGL
{
	public :

		//Attributs
		
		//Constructeur-Destructeur

		/**
			Constructeur de la classe à partir du nom du matériau 
			@param name : nom du matériau
		*/
		LumiereMaterial(string name="");

		/**
			Destructeur de la classe
		*/
		~LumiereMaterial();

		//Méthodes

		/**
			Méthode virtuelle qui est appelée pour faire le rendu d'un objet en utilisant ce matériau
			@param o : Node/Objet pour lequel on veut effectuer le rendu
		*/
		virtual void render(Node *o);

		/**
			Méthode virtuelle qui est appelée pour modifier une valeur d'un paramètre nécessaire pour le rendu
			@param o : Node/Objet concerné par le rendu
			@param elapsedTime : temps écoulé depuis la dernière frame
		*/
		virtual void animate(Node* o, const float elapsedTime);


		virtual void displayInterface() {};

		
	protected :
		GLProgram* vp;
		GLProgram* fp;

		GLuint l_View,l_Proj, l_Model, l_Sin;
};

#endif