#ifndef SCENEASSIGNMENT_H
#define SCENEASSIGNMENT_H

#include "Scene.h"
#include "Camera.h"
#include "Camera3.h"
#include "Mesh.h"
#include "MatrixStack.h"
#include "Material.h"
#include "Utility.h"
#include "Light.h"

class SceneAssignment : public Scene
{
	enum GEOMETRY_TYPE
	{
		GEO_LEFT = 0,
		GEO_RIGHT,
		GEO_TOP,
		GEO_BOTTOM,
		GEO_FRONT,
		GEO_BACK,
		GEO_AXES,
		GEO_LIGHTBALL,
		GEO_TEXT,
		NUM_GEOMETRY,
	};
	enum UNIFORM_TYPE
	{
		U_MVP = 0,
		U_MODELVIEW,
		U_MODELVIEW_INVERSE_TRANSPOSE,
		U_MATERIAL_AMBIENT,
		U_MATERIAL_DIFFUSE,
		U_MATERIAL_SPECULAR,
		U_MATERIAL_SHININESS,
		U_LIGHT0_POSITION,
		U_LIGHT0_COLOR,
		U_LIGHT0_POWER,
		U_LIGHT0_KC,
		U_LIGHT0_KL,
		U_LIGHT0_KQ,
		U_LIGHTENABLED,
		U_LIGHT0_TYPE,
		U_LIGHT0_SPOTDIRECTION,
		U_LIGHT0_COSCUTOFF,
		U_LIGHT0_COSINNER,
		U_LIGHT0_EXPONENT,
		U_NUMLIGHTS, //in case you missed out practical 7
		U_COLOR_TEXTURE_ENABLED,
		U_COLOR_TEXTURE,
		U_TEXT_ENABLED,
		U_TEXT_COLOR,
		U_TOTAL,
	};
public:
	SceneAssignment();
	~SceneAssignment();

	virtual void Init();
	virtual void Update(double dt);
	virtual void Render();
	virtual void Exit();
private:
	Mesh*meshList[NUM_GEOMETRY];
	unsigned m_vertexArrayID;
	unsigned m_programID;
	unsigned m_parameters[U_TOTAL];

	Light lights[1];

	void RenderMesh(Mesh *mesh, bool enableLight);
	void RenderText(Mesh *mesh, std::string text, Color color);
	void RenderTextOnScreen(Mesh *mesh, std::string text, Color color, float size, float x, float y);
	void RenderSkybox();

	float fps;

	Camera3 firstpersoncamera;

	MS modelStack, viewStack, projectionStack;
};

#endif