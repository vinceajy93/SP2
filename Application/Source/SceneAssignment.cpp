#include "SceneAssignment.h"
#include "GL\glew.h"
#include <sstream>

#include "shader.hpp"
#include "Mtx44.h"
#include "LoadTGA.h"
#include "Application.h"
#include "MeshBuilder.h"

SceneAssignment::SceneAssignment()
{
}

SceneAssignment::~SceneAssignment()
{
}

void SceneAssignment::Init()
{
	// Init VBO here

	// Set background color to dark blue
	glClearColor(0.0f, 0.0f, 0.4f, 0.0f);

	//Enable depth buffer and depth testing
	glEnable(GL_DEPTH_TEST);

	//Enable back face culling
	glEnable(GL_CULL_FACE);

	//Enable blending
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	//Default to fill mode
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	// Generate a default VAO for now
	glGenVertexArrays(1, &m_vertexArrayID);
	glBindVertexArray(m_vertexArrayID);

	//Load vertex and fragment shaders
	m_programID = LoadShaders( "Shader//Texture.vertexshader", "Shader//MultiLight.fragmentshader" );
	m_parameters[U_MVP] = glGetUniformLocation(m_programID, "MVP");
	m_parameters[U_MODELVIEW] = glGetUniformLocation(m_programID, "MV");
	m_parameters[U_MODELVIEW_INVERSE_TRANSPOSE] = glGetUniformLocation(m_programID, "MV_inverse_transpose");
	m_parameters[U_MATERIAL_AMBIENT] = glGetUniformLocation(m_programID, "material.kAmbient");
	m_parameters[U_MATERIAL_DIFFUSE] = glGetUniformLocation(m_programID, "material.kDiffuse");
	m_parameters[U_MATERIAL_SPECULAR] = glGetUniformLocation(m_programID, "material.kSpecular");
	m_parameters[U_MATERIAL_SHININESS] = glGetUniformLocation(m_programID, "material.kShininess");
	m_parameters[U_LIGHT0_POSITION] = glGetUniformLocation(m_programID, "lights[0].position_cameraspace");
	m_parameters[U_LIGHT0_COLOR] = glGetUniformLocation(m_programID, "lights[0].color");
	m_parameters[U_LIGHT0_POWER] = glGetUniformLocation(m_programID, "lights[0].power");
	m_parameters[U_LIGHT0_KC] = glGetUniformLocation(m_programID, "lights[0].kC");
	m_parameters[U_LIGHT0_KL] = glGetUniformLocation(m_programID, "lights[0].kL");
	m_parameters[U_LIGHT0_KQ] = glGetUniformLocation(m_programID, "lights[0].kQ");
	m_parameters[U_LIGHTENABLED] = glGetUniformLocation(m_programID, "lightEnabled");
	m_parameters[U_NUMLIGHTS] = glGetUniformLocation(m_programID, "numLights");
	m_parameters[U_LIGHT0_TYPE] = glGetUniformLocation(m_programID, "lights[0].type");
	m_parameters[U_LIGHT0_SPOTDIRECTION] = glGetUniformLocation(m_programID, "lights[0].spotDirection");
	m_parameters[U_LIGHT0_COSCUTOFF] = glGetUniformLocation(m_programID, "lights[0].cosCutoff");
	m_parameters[U_LIGHT0_COSINNER] = glGetUniformLocation(m_programID, "lights[0].cosInner");
	m_parameters[U_LIGHT0_EXPONENT] = glGetUniformLocation(m_programID, "lights[0].exponent");

	// Get a handle for our "colorTexture" uniform
	m_parameters[U_COLOR_TEXTURE_ENABLED] = glGetUniformLocation(m_programID, "colorTextureEnabled");
	m_parameters[U_COLOR_TEXTURE] = glGetUniformLocation(m_programID, "colorTexture");

	m_parameters[U_TEXT_ENABLED] = glGetUniformLocation(m_programID, "textEnabled");
	m_parameters[U_TEXT_COLOR] = glGetUniformLocation(m_programID, "textColor");

	glUseProgram(m_programID);

	lights[0].type = Light::LIGHT_POINT;
	lights[0].position.Set(0, 450, 1000);
	lights[0].color.Set(1, 1, 1);
	lights[0].power = 70;
	lights[0].kC = 1.f;
	lights[0].kL = 0.01f;
	lights[0].kQ = 0.001f;
	lights[0].cosCutoff = cos(Math::DegreeToRadian(45));
	lights[0].cosInner = cos(Math::DegreeToRadian(30));
	lights[0].exponent = 3.f;
	lights[0].spotDirection.Set(0.f, 1.f, 0.f);

	// Make sure you pass uniform parameters after glUseProgram()
	glUniform1i(m_parameters[U_LIGHT0_TYPE], lights[0].type);
	glUniform3fv(m_parameters[U_LIGHT0_COLOR], 1, &lights[0].color.r);
	glUniform1f(m_parameters[U_LIGHT0_POWER], lights[0].power);
	glUniform1f(m_parameters[U_LIGHT0_KC], lights[0].kC);
	glUniform1f(m_parameters[U_LIGHT0_KL], lights[0].kL);
	glUniform1f(m_parameters[U_LIGHT0_KQ], lights[0].kQ);
	glUniform1f(m_parameters[U_LIGHT0_COSCUTOFF], lights[0].cosCutoff);
	glUniform1f(m_parameters[U_LIGHT0_COSINNER], lights[0].cosInner);
	glUniform1f(m_parameters[U_LIGHT0_EXPONENT], lights[0].exponent);

	glUniform1i(m_parameters[U_NUMLIGHTS], 1);

	//Initialize camera settings
	firstpersoncamera.Init(Vector3(0, 100, 0), Vector3(0, 100, 50), Vector3(0, 1, 0));

	meshList[GEO_AXES] = MeshBuilder::GenerateAxes("axes", 1, 1, 1);

	meshList[GEO_LIGHTBALL] = MeshBuilder::GenerateSphere("lightball", 1 ,Color(1,1,1));
	/*
	meshList[GEO_FRONT] = MeshBuilder::GenerateQuad("front", Color(1, 1, 1), 1.f, 1.f);
	meshList[GEO_FRONT]->textureID = LoadTGA("Image//Skybox_Front.tga");

	meshList[GEO_BACK] = MeshBuilder::GenerateQuad("back", Color(1, 1, 1), 1.f, 1.f);
	meshList[GEO_BACK]->textureID = LoadTGA("Image//Skybox_Back.tga");


	meshList[GEO_RIGHT] = MeshBuilder::GenerateQuad("right", Color(1, 1, 1), 1.f, 1.f);
	meshList[GEO_RIGHT]->textureID = LoadTGA("Image//Skybox_Right.tga");


	meshList[GEO_LEFT] = MeshBuilder::GenerateQuad("left", Color(1, 1, 1), 1.f, 1.f);
	meshList[GEO_LEFT]->textureID = LoadTGA("Image//Skybox_Left.tga");


	meshList[GEO_TOP] = MeshBuilder::GenerateQuad("top", Color(1, 1, 1), 1.f, 1.f);
	meshList[GEO_TOP]->textureID = LoadTGA("Image//Skybox_Top.tga");


	meshList[GEO_BOTTOM] = MeshBuilder::GenerateQuad("bottom", Color(1, 1, 1), 1.f, 1.f);
	meshList[GEO_BOTTOM]->textureID = LoadTGA("Image//Skybox_Bottom.tga");
	*/

	meshList[GEO_TEXT] = MeshBuilder::GenerateText("text", 16, 16);
	meshList[GEO_TEXT] ->textureID = LoadTGA("Image//Fixedsys.tga");
	
	//Example
	/* 
	meshList[GEO_TABLE] = MeshBuilder::GenerateOBJ("/Table", "OBJ//Table.obj");
	meshList[GEO_TABLE]->material.kAmbient.Set(0.2f, 0.2f, 0.2f);
	meshList[GEO_TABLE]->material.kDiffuse.Set(0.5f, 0.5f, 0.5f);
	meshList[GEO_TABLE]->material.kSpecular.Set(0.7f, 0.7f, 0.7f);
	meshList[GEO_TABLE]->material.kShininess = 5.f;
	meshList[GEO_TABLE]->textureID = LoadTGA("Image//TableTexture.tga");
	*/

	Mtx44 projection;
	projection.SetToPerspective(45.f,4.f/3.f,0.1f,10000.f);
	projectionStack.LoadMatrix(projection);

	fps = 0;
}

static float ROT_LIMIT = 45.f;
static float SCALE_LIMIT = 5.f;

#define LSPEED 20.0f

void SceneAssignment::Update(double dt)
{
	if(Application::IsKeyPressed('1')) //enable back face culling
		glEnable(GL_CULL_FACE);
	if(Application::IsKeyPressed('2')) //disable back face culling
		glDisable(GL_CULL_FACE);
	if(Application::IsKeyPressed('3'))
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); //default fill mode
	if(Application::IsKeyPressed('4'))
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); //wireframe mode

	static const float Move = 250.f;
	static const float Turn = 50.f;
	
	//Example
	/*if(CameraSwitch)
	{
		if(Application::IsKeyPressed('W'))
		{
			MoveBody += (float)(Move * dt);
			Displacement.Set(0,0,MoveBody);
			Rotation.SetToRotation(TurnBody,0,1,0);
			Displacement =  Rotation * Displacement;
			CharacterPos += Displacement;

			firstpersoncamera.position.x += Displacement.x;
			firstpersoncamera.position.y += Displacement.y;
			firstpersoncamera.position.z += Displacement.z;

			firstpersoncamera.target.x += Displacement.x;
			firstpersoncamera.target.y += Displacement.y;
			firstpersoncamera.target.z += Displacement.z;

			if(CharacterPos.z < GengarMax.z && CharacterPos.z > GengarMin.z && CharacterPos.x < GengarMax.x && CharacterPos.x > GengarMin.x)
			{
				CharacterPos -= Displacement;
				firstpersoncamera.position.x -= Displacement.x;
				firstpersoncamera.position.y -= Displacement.y;
				firstpersoncamera.position.z -= Displacement.z;

				firstpersoncamera.target.x -= Displacement.x;
				firstpersoncamera.target.y -= Displacement.y;
				firstpersoncamera.target.z -= Displacement.z;

			}

			if(CharacterPos.z < MidofRoom)
			{
				if(CharacterPos.x > Maximum.x || CharacterPos.x < Minimum.x || CharacterPos.y > Maximum.y || CharacterPos.y < Minimum.y || CharacterPos.z < Minimum.z)
				{
					CharacterPos -= Displacement;
					firstpersoncamera.position.x -= Displacement.x;
					firstpersoncamera.position.y -= Displacement.y;
					firstpersoncamera.position.z -= Displacement.z;

					firstpersoncamera.target.x -= Displacement.x;
					firstpersoncamera.target.y -= Displacement.y;
					firstpersoncamera.target.z -= Displacement.z;
				}
			}

			else if(CharacterPos.z > MidofRoom)
			{
				if(CharacterPos.z > TableBound.z)
				{
					if(CharacterPos.z > BedBound.z)
					{
						if(CharacterPos.x > TableBound.x || CharacterPos.x < BedBound.x || CharacterPos.y > Maximum.y || CharacterPos.y < Minimum.y || CharacterPos.z > Maximum.z)
						{
							CharacterPos -= Displacement;
							firstpersoncamera.position.x -= Displacement.x;
							firstpersoncamera.position.y -= Displacement.y;
							firstpersoncamera.position.z -= Displacement.z;

							firstpersoncamera.target.x -= Displacement.x;
							firstpersoncamera.target.y -= Displacement.y;
							firstpersoncamera.target.z -= Displacement.z;
						}
					}

					else
					{
						if(CharacterPos.x > TableBound.x || CharacterPos.x < SideRoomXBound || CharacterPos.y > Maximum.y || CharacterPos.y < Minimum.y || CharacterPos.z > Maximum.z)
						{
							CharacterPos -= Displacement;
							firstpersoncamera.position.x -= Displacement.x;
							firstpersoncamera.position.y -= Displacement.y;
							firstpersoncamera.position.z -= Displacement.z;

							firstpersoncamera.target.x -= Displacement.x;
							firstpersoncamera.target.y -= Displacement.y;
							firstpersoncamera.target.z -= Displacement.z;
						}
					}
				}
				else
				{
					if(CharacterPos.x > Maximum.x || CharacterPos.x < -1390 || CharacterPos.y > Maximum.y || CharacterPos.y < Minimum.y || CharacterPos.z > Maximum.z)
					{
						CharacterPos -= Displacement;
						firstpersoncamera.position.x -= Displacement.x;
						firstpersoncamera.position.y -= Displacement.y;
						firstpersoncamera.position.z -= Displacement.z;

						firstpersoncamera.target.x -= Displacement.x;
						firstpersoncamera.target.y -= Displacement.y;
						firstpersoncamera.target.z -= Displacement.z;
					}
				}
			}
			MoveBody = 0;
		}

		if(Application::IsKeyPressed(VK_LEFT))
		{
			TurnBody += (float)(Turn * dt);
			Displacement.Set(MoveBody,0,0);
			Rotation.SetToRotation(TurnBody,0,1,0);
			Displacement =  Rotation * Displacement;
			CharacterPos += Displacement;

			firstpersoncamera.position.x += Displacement.x;
			firstpersoncamera.position.y += Displacement.y;
			firstpersoncamera.position.z += Displacement.z;

			if(CharacterPos.z < GengarMax.z && CharacterPos.z > GengarMin.z && CharacterPos.x < GengarMax.x && CharacterPos.x > GengarMin.x)
			{
				CharacterPos -= Displacement;
				firstpersoncamera.position.x -= Displacement.x;
				firstpersoncamera.position.y -= Displacement.y;
				firstpersoncamera.position.z -= Displacement.z;

			}

			if(CharacterPos.z < MidofRoom)
			{
				if(CharacterPos.x > Maximum.x || CharacterPos.x < Minimum.x || CharacterPos.y > Maximum.y || CharacterPos.y < Minimum.y || CharacterPos.z < Minimum.z)
				{
					CharacterPos -= Displacement;
					firstpersoncamera.position.x -= Displacement.x;
					firstpersoncamera.position.y -= Displacement.y;
					firstpersoncamera.position.z -= Displacement.z;
				}
			}

			else if(CharacterPos.z > MidofRoom)
			{
				if(CharacterPos.z > TableBound.z)
				{
					if(CharacterPos.z > BedBound.z)
					{
						if(CharacterPos.x > TableBound.x || CharacterPos.x < BedBound.x || CharacterPos.y > Maximum.y || CharacterPos.y < Minimum.y || CharacterPos.z > Maximum.z)
						{
							CharacterPos -= Displacement;
							firstpersoncamera.position.x -= Displacement.x;
							firstpersoncamera.position.y -= Displacement.y;
							firstpersoncamera.position.z -= Displacement.z;
						}
					}

					else
					{
						if(CharacterPos.x > TableBound.x || CharacterPos.x < SideRoomXBound || CharacterPos.y > Maximum.y || CharacterPos.y < Minimum.y || CharacterPos.z > Maximum.z)
						{
							CharacterPos -= Displacement;
							firstpersoncamera.position.x -= Displacement.x;
							firstpersoncamera.position.y -= Displacement.y;
							firstpersoncamera.position.z -= Displacement.z;
						}
					}
				}
				else
				{
					if(CharacterPos.x > Maximum.x || CharacterPos.x < -1390 || CharacterPos.y > Maximum.y || CharacterPos.y < Minimum.y || CharacterPos.z > Maximum.z)
					{
						CharacterPos -= Displacement;
						firstpersoncamera.position.x -= Displacement.x;
						firstpersoncamera.position.y -= Displacement.y;
						firstpersoncamera.position.z -= Displacement.z;
					}
				}
			}
		}
		*/

		firstpersoncamera.Update(dt);

	fps = 1/dt;
}

void SceneAssignment::RenderMesh(Mesh *mesh, bool enableLight)
{
	Mtx44 MVP, modelView, modelView_inverse_transpose;

	MVP = projectionStack.Top() * viewStack.Top() * modelStack.Top();
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);
	if(enableLight)
	{
		glUniform1i(m_parameters[U_LIGHTENABLED], 2);
		modelView = viewStack.Top() * modelStack.Top();
		glUniformMatrix4fv(m_parameters[U_MODELVIEW], 1, GL_FALSE, &modelView.a[0]);
		modelView_inverse_transpose = modelView.GetInverse().GetTranspose();
		glUniformMatrix4fv(m_parameters[U_MODELVIEW_INVERSE_TRANSPOSE], 1, GL_FALSE, &modelView_inverse_transpose.a[0]);

		//load material
		glUniform3fv(m_parameters[U_MATERIAL_AMBIENT], 1, &mesh->material.kAmbient.r);
		glUniform3fv(m_parameters[U_MATERIAL_DIFFUSE], 1, &mesh->material.kDiffuse.r);
		glUniform3fv(m_parameters[U_MATERIAL_SPECULAR], 1, &mesh->material.kSpecular.r);
		glUniform1f(m_parameters[U_MATERIAL_SHININESS], mesh->material.kShininess);
	}
	else
	{	
		glUniform1i(m_parameters[U_LIGHTENABLED], 0);
	}

	if(mesh->textureID > 0)
	{
		glUniform1i(m_parameters[U_COLOR_TEXTURE_ENABLED], 1);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, mesh->textureID);
		glUniform1i(m_parameters[U_COLOR_TEXTURE], 0);
	}
	else
	{
		glUniform1i(m_parameters[U_COLOR_TEXTURE_ENABLED], 0);
	}
	mesh->Render(); //this line should only be called once 
	if(mesh->textureID > 0)
	{
		glBindTexture(GL_TEXTURE_2D, 0);
	}

}

void SceneAssignment::Render()
{
	// Render VBO here
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	viewStack.LoadIdentity();
	viewStack.LookAt(
	firstpersoncamera.position.x,firstpersoncamera.position.y,firstpersoncamera.position.z,
	firstpersoncamera.target.x,firstpersoncamera.target.y,firstpersoncamera.target.z,
	firstpersoncamera.up.x,firstpersoncamera.up.y,firstpersoncamera.up.z);

	modelStack.LoadIdentity();

	//Light 1
	if(lights[0].type == Light::LIGHT_DIRECTIONAL)
	{
		Vector3 lightDir(lights[0].position.x, lights[0].position.y, lights[0].position.z);
		Vector3 lightDirection_cameraspace = viewStack.Top() * lightDir;
		glUniform3fv(m_parameters[U_LIGHT0_POSITION], 1, &lightDirection_cameraspace.x);
	}
	else if(lights[0].type == Light::LIGHT_SPOT)
	{
		Position lightPosition_cameraspace = viewStack.Top() * lights[0].position;
		glUniform3fv(m_parameters[U_LIGHT0_POSITION], 1, &lightPosition_cameraspace.x);
		Vector3 spotDirection_cameraspace = viewStack.Top() * lights[0].spotDirection;
		glUniform3fv(m_parameters[U_LIGHT0_SPOTDIRECTION], 1, &spotDirection_cameraspace.x);
	}
	else
	{
		Position lightPosition_cameraspace = viewStack.Top() * lights[0].position;
		glUniform3fv(m_parameters[U_LIGHT0_POSITION], 1, &lightPosition_cameraspace.x);
	}

	RenderMesh(meshList[GEO_AXES], false);

	//RenderSkybox();

	std::ostringstream stringfps;

	stringfps << fps;

	RenderTextOnScreen(meshList[GEO_TEXT], "FPS:", Color(0, 1, 0), 3, 0, 1);

	RenderTextOnScreen(meshList[GEO_TEXT], stringfps.str(), Color(0, 1, 0), 3, 4, 1);
}

void SceneAssignment::RenderSkybox()
{
	
}

void SceneAssignment::RenderText(Mesh *mesh, std::string text, Color color)
{
	if(!mesh || mesh->textureID <= 0) //Proper error check
		return;

	glDisable(GL_DEPTH_TEST);
	glUniform1i(m_parameters[U_TEXT_ENABLED], 1);
	glUniform3fv(m_parameters[U_TEXT_COLOR], 1, &color.r);
	glUniform1i(m_parameters[U_LIGHTENABLED], 0);
	glUniform1i(m_parameters[U_COLOR_TEXTURE_ENABLED], 1);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, mesh->textureID);
	glUniform1i(m_parameters[U_COLOR_TEXTURE], 0);
	for(unsigned i = 0; i < text.length(); ++i)
	{
		Mtx44 characterSpacing;
		characterSpacing.SetToTranslation(i * 1.0f, 0, 0); //1.0f is the spacing of each character, you may change this value
		Mtx44 MVP = projectionStack.Top() * viewStack.Top() * modelStack.Top() * characterSpacing;
		glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);

		mesh->Render((unsigned)text[i] * 6, 6);
	}
	glBindTexture(GL_TEXTURE_2D, 0);
	glUniform1i(m_parameters[U_TEXT_ENABLED], 0);
	glEnable(GL_DEPTH_TEST);
}

void SceneAssignment::RenderTextOnScreen(Mesh *mesh, std::string text, Color color, float size, float x, float y)
{
	if(!mesh || mesh->textureID <= 0) //Proper error check
		return;

	glDisable(GL_DEPTH_TEST);
	Mtx44 ortho;
	ortho.SetToOrtho(0, 80, 0, 60, -10, 10); //size of screen UI
	projectionStack.PushMatrix();
	projectionStack.LoadMatrix(ortho);
	viewStack.PushMatrix();
	viewStack.LoadIdentity(); //No need camera for ortho mode
	modelStack.PushMatrix();
	modelStack.LoadIdentity(); //Reset modelStack
	modelStack.Scale(size, size, size);
	modelStack.Translate(x, y, 0);
	glUniform1i(m_parameters[U_TEXT_ENABLED], 1);
	glUniform3fv(m_parameters[U_TEXT_COLOR], 1, &color.r);
	glUniform1i(m_parameters[U_LIGHTENABLED], 0);
	glUniform1i(m_parameters[U_COLOR_TEXTURE_ENABLED], 1);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, mesh->textureID);
	glUniform1i(m_parameters[U_COLOR_TEXTURE], 0);
	for(unsigned i = 0; i < text.length(); ++i)
	{
		Mtx44 characterSpacing;
		characterSpacing.SetToTranslation(0.5f + i * 1.0f, 0.5f, 0); //1.0f is the spacing of each character, you may change this value
		Mtx44 MVP = projectionStack.Top() * viewStack.Top() * modelStack.Top() * characterSpacing;
		glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);

		mesh->Render((unsigned)text[i] * 6, 6);
	}
	glBindTexture(GL_TEXTURE_2D, 0);
	glUniform1i(m_parameters[U_TEXT_ENABLED], 0);
	glEnable(GL_DEPTH_TEST);
	projectionStack.PopMatrix();
	viewStack.PopMatrix();
	modelStack.PopMatrix();
}

void SceneAssignment::Exit()
{
	// Cleanup VBO here
	glDeleteVertexArrays(1, &m_vertexArrayID);
	glDeleteProgram(m_programID);
}