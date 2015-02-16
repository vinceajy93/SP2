#include "MeshBuilder.h"
#include <GL\glew.h>
#include <vector>
#include "Vertex.h"
#include "MyMath.h"
#include "LoadOBJ.h"

/******************************************************************************/
/*!
\brief
Generate the vertices of a reference Axes; Use red for x-axis, green for y-axis, blue for z-axis
Then generate the VBO/IBO and store them in Mesh object

\param meshName - name of mesh
\param lengthX - x-axis should start at -lengthX / 2 and end at lengthX / 2
\param lengthY - y-axis should start at -lengthY / 2 and end at lengthY / 2
\param lengthZ - z-axis should start at -lengthZ / 2 and end at lengthZ / 2

\return Pointer to mesh storing VBO/IBO of reference axes
*/
/******************************************************************************/
Mesh* MeshBuilder::GenerateAxes(const std::string &meshName, float lengthX, float lengthY, float lengthZ)
{
	Vertex v;
	std::vector<Vertex> vertex_buffer_data;
	
	v.pos.Set(-1000,0,0);
	v.color.Set(1,0,0);
	vertex_buffer_data.push_back(v);

	v.pos.Set(1000,0,0);
	v.color.Set(1,0,0);
	vertex_buffer_data.push_back(v);

	v.pos.Set(0,-1000,0);
	v.color.Set(0,1,0);
	vertex_buffer_data.push_back(v);

	v.pos.Set(0,1000,0);
	v.color.Set(0,1,0);
	vertex_buffer_data.push_back(v);

	v.pos.Set(0,0,-1000);
	v.color.Set(0,0,1);
	vertex_buffer_data.push_back(v);

	v.pos.Set(0,0,1000);
	v.color.Set(0,0,1);
	vertex_buffer_data.push_back(v);

	std::vector<GLuint> index_buffer_data;
	for(int i =0; i<6; i++)
	{
		index_buffer_data.push_back(i);
	}

	Mesh *mesh = new Mesh(meshName);

	glBindBuffer(GL_ARRAY_BUFFER, mesh->vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertex_buffer_data.size() * sizeof(Vertex), &vertex_buffer_data[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->indexBuffer); //bind index buffer
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_buffer_data.size() * sizeof(GLuint), &index_buffer_data[0], GL_STATIC_DRAW);

	mesh -> indexSize = index_buffer_data.size();
	mesh -> mode = Mesh::DRAW_LINES;

	return mesh;
}

/******************************************************************************/
/*!
\brief
Generate the vertices of a quad; Use random color for each vertex
Then generate the VBO/IBO and store them in Mesh object

\param meshName - name of mesh
\param lengthX - width of quad
\param lengthY - height of quad

\return Pointer to mesh storing VBO/IBO of quad
*/
/******************************************************************************/
Mesh* MeshBuilder::GenerateQuad(const std::string &meshName,Color color,float lengthX, float lengthY)
{
	Vertex v;
	std::vector<Vertex> vertex_buffer_data;

	v.pos.Set(-0.5f,0.5f,0.0f);
	v.color = color;
	v.normal.Set(0,0,1);
	v.texCoord.Set(0, 1);
	vertex_buffer_data.push_back(v);

	v.pos.Set(-0.5f,-0.5f,0.0f);
	v.color = color;
	v.normal.Set(0,0,1);
	v.texCoord.Set(0, 0);
	vertex_buffer_data.push_back(v);

	v.pos.Set(0.5f,0.5f,0.0f);
	v.color = color;
	v.normal.Set(0,0,1);
	v.texCoord.Set(1, 1);
	vertex_buffer_data.push_back(v);

	v.pos.Set(0.5f,-0.5f,0.0f);
	v.color = color;
	v.normal.Set(0,0,1);
	v.texCoord.Set(1, 0);
	vertex_buffer_data.push_back(v);

	std::vector<GLuint> index_buffer_data;

	index_buffer_data.push_back(2);
	index_buffer_data.push_back(0);
	index_buffer_data.push_back(1);
	index_buffer_data.push_back(2);
	index_buffer_data.push_back(1);
	index_buffer_data.push_back(3);

	Mesh *mesh = new Mesh(meshName);

	glBindBuffer(GL_ARRAY_BUFFER, mesh->vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertex_buffer_data.size() * sizeof(Vertex), &vertex_buffer_data[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->indexBuffer); //bind index buffer
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_buffer_data.size() * sizeof(GLuint), &index_buffer_data[0], GL_STATIC_DRAW);

	mesh->indexSize = index_buffer_data.size();
	mesh->mode = Mesh::DRAW_TRIANGLES;

	return mesh;
}

/******************************************************************************/
/*!
\brief
Generate the vertices of a cube; Use random color for each vertex
Then generate the VBO/IBO and store them in Mesh object

\param meshName - name of mesh
\param lengthX - width of cube
\param lengthY - height of cube
\param lengthZ - depth of cube

\return Pointer to mesh storing VBO/IBO of cube
*/
/******************************************************************************/
Mesh* MeshBuilder::GenerateCube(const std::string &meshName, Color color, float lengthX, float lengthY, float lengthZ)
{
	Vertex v;
	std::vector<Vertex> vertex_buffer_data;

	v.pos.Set(-0.5f,-0.5f,-0.5f);
	v.color = color;
	vertex_buffer_data.push_back(v);
	
	v.pos.Set(0.5f,-0.5f,-0.5f);
	v.color = color;
	vertex_buffer_data.push_back(v);

	v.pos.Set(0.5f, 0.5f,-0.5f);
	v.color = color;
	vertex_buffer_data.push_back(v);

	v.pos.Set(-0.5f, 0.5f,-0.5f);
	v.color = color;
	vertex_buffer_data.push_back(v);

	v.pos.Set(-0.5f,-0.5f, 0.5f);
	v.color = color;
	vertex_buffer_data.push_back(v);

	v.pos.Set(0.5f,-0.5f, 0.5f);
	v.color = color;
	vertex_buffer_data.push_back(v);

	v.pos.Set(0.5f, 0.5f, 0.5f);
	v.color = color;
	vertex_buffer_data.push_back(v);

	v.pos.Set(-0.5f, 0.5f, 0.5f);
	v.color = color;
	vertex_buffer_data.push_back(v);

	std::vector<GLuint> index_buffer_data;
		
	index_buffer_data.push_back(7);
	index_buffer_data.push_back(4);
	index_buffer_data.push_back(6);
	index_buffer_data.push_back(5);
	index_buffer_data.push_back(6);
	index_buffer_data.push_back(4);
	index_buffer_data.push_back(6);
	index_buffer_data.push_back(5);
	index_buffer_data.push_back(2);
	index_buffer_data.push_back(1);
	index_buffer_data.push_back(2);
	index_buffer_data.push_back(5);
	index_buffer_data.push_back(3);
	index_buffer_data.push_back(7);
	index_buffer_data.push_back(2);
	index_buffer_data.push_back(6);
	index_buffer_data.push_back(2);
	index_buffer_data.push_back(7);
	index_buffer_data.push_back(2);
	index_buffer_data.push_back(1);
	index_buffer_data.push_back(3);
	index_buffer_data.push_back(0);
	index_buffer_data.push_back(3);
	index_buffer_data.push_back(1);
	index_buffer_data.push_back(3);
	index_buffer_data.push_back(0);
	index_buffer_data.push_back(7);
	index_buffer_data.push_back(4);
	index_buffer_data.push_back(7);
	index_buffer_data.push_back(0);
	index_buffer_data.push_back(1);
	index_buffer_data.push_back(5);
	index_buffer_data.push_back(0);
	index_buffer_data.push_back(4);
	index_buffer_data.push_back(0);
	index_buffer_data.push_back(5);
	
	Mesh *mesh = new Mesh(meshName);

	glBindBuffer(GL_ARRAY_BUFFER, mesh->vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertex_buffer_data.size() * sizeof(Vertex), &vertex_buffer_data[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->indexBuffer); //bind index buffer
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_buffer_data.size() * sizeof(GLuint), &index_buffer_data[0], GL_STATIC_DRAW);

	mesh->indexSize = index_buffer_data.size();
	mesh->mode = Mesh::DRAW_TRIANGLES;

	return mesh;
}

Mesh* MeshBuilder::GenerateCircle(const std::string &meshName, int radius, Color color)
{
	Vertex v;
	std::vector<Vertex> vertex_buffer_data;

	v.pos.Set(0.0f,0.0f,0.0f);
	v.color=color;

	vertex_buffer_data.push_back(v);

	for(float theta = 0; theta <= 360; theta +=10)
	{
		v.pos.Set(radius*cos(Math::DegreeToRadian(theta)),radius*sin(Math::DegreeToRadian(theta)),0);
		v.color=color;
		v.normal.Set(0,0,1);
		vertex_buffer_data.push_back(v);
	}

	std::vector<GLuint> index_buffer_data;

	for(int i=1; i<= vertex_buffer_data.size();i++)
	{
		index_buffer_data.push_back(0);
		index_buffer_data.push_back(i);
	}

	Mesh *mesh = new Mesh(meshName);

	glBindBuffer(GL_ARRAY_BUFFER, mesh->vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertex_buffer_data.size() * sizeof(Vertex), &vertex_buffer_data[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->indexBuffer); //bind index buffer
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_buffer_data.size() * sizeof(GLuint), &index_buffer_data[0], GL_STATIC_DRAW);

	mesh->indexSize = index_buffer_data.size();
	mesh->mode = Mesh::DRAW_TRIANGLE_STRIP;

	return mesh;
}

Mesh* MeshBuilder::GenerateRing(const std::string &meshName, int inner_radius, int outer_radius, Color color)
{
	Vertex v;
	std::vector<Vertex> vertex_buffer_data;

	for(float theta = 0; theta <= 360; theta +=10)
	{
		v.pos.Set(outer_radius*cos(Math::DegreeToRadian(theta)),0,outer_radius*sin(Math::DegreeToRadian(theta)));
		v.color=color;
		v.normal.Set(0,1,0);
		vertex_buffer_data.push_back(v);

		v.pos.Set(inner_radius*cos(Math::DegreeToRadian(theta)),0,inner_radius*sin(Math::DegreeToRadian(theta)));
		v.color=color;
		v.normal.Set(0,1,0);
		vertex_buffer_data.push_back(v);
	}

	std::vector<GLuint> index_buffer_data;

	for(int i=0; i<= vertex_buffer_data.size();i++)
	{
		index_buffer_data.push_back(i);
	}

	Mesh *mesh = new Mesh(meshName);

	glBindBuffer(GL_ARRAY_BUFFER, mesh->vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertex_buffer_data.size() * sizeof(Vertex), &vertex_buffer_data[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->indexBuffer); //bind index buffer
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_buffer_data.size() * sizeof(GLuint), &index_buffer_data[0], GL_STATIC_DRAW);

	mesh->indexSize = index_buffer_data.size();
	mesh->mode = Mesh::DRAW_TRIANGLE_STRIP;

	return mesh;
}

Mesh* MeshBuilder::GenerateSphere(const std::string &meshName, int radius, Color color)
{

	Vertex v;
	std::vector<Vertex> vertex_buffer_data;

	for(float phi = -90; phi < 90; phi +=10)
	{
		for(float theta = 0; theta <= 360; theta +=10)
		{
			v.pos.Set(radius * cos(Math::DegreeToRadian(phi)) * cos(Math::DegreeToRadian(theta)) , radius * sin(Math::DegreeToRadian(phi)) , radius * cos(Math::DegreeToRadian(phi)) * sin(Math::DegreeToRadian(theta)));
			v.color=color;
			v.normal.Set(radius * cos(Math::DegreeToRadian(phi)) * cos(Math::DegreeToRadian(theta)) , radius * sin(Math::DegreeToRadian(phi)) , radius * cos(Math::DegreeToRadian(phi)) * sin(Math::DegreeToRadian(theta)));
			vertex_buffer_data.push_back(v);

			v.pos.Set(radius * cos(Math::DegreeToRadian(phi+10)) * cos(Math::DegreeToRadian(theta)) , radius * sin(Math::DegreeToRadian(phi+10)) , radius * cos(Math::DegreeToRadian(phi+10)) * sin(Math::DegreeToRadian(theta)));
			v.color=color;
			v.normal.Set(radius * cos(Math::DegreeToRadian(phi+10)) * cos(Math::DegreeToRadian(theta)) , radius * sin(Math::DegreeToRadian(phi+10)) , radius * cos(Math::DegreeToRadian(phi+10)) * sin(Math::DegreeToRadian(theta)));
			vertex_buffer_data.push_back(v);
		}
	}
	
	std::vector<GLuint> index_buffer_data;

	for(int i=0; i<= vertex_buffer_data.size();i++)
	{
		index_buffer_data.push_back(i);
	}

	Mesh *mesh = new Mesh(meshName);

	glBindBuffer(GL_ARRAY_BUFFER, mesh->vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertex_buffer_data.size() * sizeof(Vertex), &vertex_buffer_data[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->indexBuffer); //bind index buffer
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_buffer_data.size() * sizeof(GLuint), &index_buffer_data[0], GL_STATIC_DRAW);

	mesh->indexSize = index_buffer_data.size();
	mesh->mode = Mesh::DRAW_TRIANGLE_STRIP;

	return mesh;
}

Mesh* MeshBuilder::GenerateOBJ(const std::string &meshName, const std::string &file_path) {
	//Read vertices, texcoords & normals from OBJ
	std::vector<Position> vertices;
	std::vector<TexCoord> uvs;
	std::vector<Vector3> normals;
	bool success = LoadOBJ(file_path.c_str(), vertices, uvs, normals);
	if(!success)
		return NULL;
	//Index the vertices, texcoords & normals properly
	std::vector<Vertex> vertex_buffer_data;
	std::vector<GLuint> index_buffer_data;
	IndexVBO(vertices, uvs, normals, index_buffer_data, vertex_buffer_data);
	//Create the mesh and call glBindBuffer, glBufferData
	//Use triangle list and remember to set index size

	Mesh *mesh = new Mesh(meshName);

	glBindBuffer(GL_ARRAY_BUFFER, mesh->vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertex_buffer_data.size() * sizeof(Vertex), &vertex_buffer_data[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->indexBuffer); //bind index buffer
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_buffer_data.size() * sizeof(GLuint), &index_buffer_data[0], GL_STATIC_DRAW);

	mesh->indexSize = index_buffer_data.size();
	mesh->mode = Mesh::DRAW_TRIANGLES;

	return mesh;
}

Mesh* MeshBuilder::GenerateCylinder(const std::string &meshName, Color color,int height, float bottomradius, float topradius, bool bottomcircle)
{
	Vertex v;
	std::vector<Vertex> vertex_buffer_data;

	for(double theta=0; theta<= 360; theta +=10)
	{
		v.pos.Set(bottomradius* cos(Math::DegreeToRadian(theta)), -height/2, bottomradius* sin(Math::DegreeToRadian(theta)));
		v.color=color;
		v.normal.Set(cos(Math::DegreeToRadian(theta)), 0, sin(Math::DegreeToRadian(theta)));
		v.normal.Normalize();
		vertex_buffer_data.push_back(v);

		v.pos.Set(topradius* cos(Math::DegreeToRadian(theta)), -height/2 + height, topradius* sin(Math::DegreeToRadian(theta)));
		v.color=color;
		v.normal.Set(cos(Math::DegreeToRadian(theta)), 0, sin(Math::DegreeToRadian(theta)));
		v.normal.Normalize();
		vertex_buffer_data.push_back(v);		
	}

	if(bottomcircle)
	{
		for(float theta = 0; theta <= 360; theta +=10)
		{
			v.pos.Set(0.0f,-height/2,0.0f);
			v.color=color;
			v.normal.Set(0,-1,0);
			vertex_buffer_data.push_back(v);

			v.pos.Set(bottomradius*cos(Math::DegreeToRadian(theta)),-height/2,bottomradius*sin(Math::DegreeToRadian(theta)));
			v.color=color;
			v.normal.Set(0,-1,0);
			vertex_buffer_data.push_back(v);
		}
	}

	std::vector<GLuint> index_buffer_data;

	for(int i=0;i <vertex_buffer_data.size(); i++)
	{
		index_buffer_data.push_back(i);
	}

	Mesh *mesh = new Mesh(meshName);

	glBindBuffer(GL_ARRAY_BUFFER, mesh->vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertex_buffer_data.size() * sizeof(Vertex), &vertex_buffer_data[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->indexBuffer); //bind index buffer
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_buffer_data.size() * sizeof(GLuint), &index_buffer_data[0], GL_STATIC_DRAW);

	mesh->indexSize = index_buffer_data.size();
	mesh->mode = Mesh::DRAW_TRIANGLE_STRIP;

	return mesh;
}

Mesh* MeshBuilder::GenerateCone(const std::string &meshName, Color color, int height, float radius)
{
	Vertex v;
	std::vector<Vertex> vertex_buffer_data;

	for(int theta = 0; theta <= 360; theta += 10)
	{
		v.pos.Set(radius *cos(Math::DegreeToRadian(theta)), -height /2, radius *sin(Math::DegreeToRadian(theta)));
		v.color=color;
		v.normal.Set(height *cos(Math::DegreeToRadian(theta)), 0, height *sin(Math::DegreeToRadian(theta)));
		v.normal.Normalize();
		vertex_buffer_data.push_back(v);

		v.pos.Set(0,height/2,0);
		v.color=color;
		v.normal.Set(height *cos(Math::DegreeToRadian(theta)), 0, height *sin(Math::DegreeToRadian(theta)));
		v.normal.Normalize();
		vertex_buffer_data.push_back(v);
	}

	std::vector<GLuint> index_buffer_data;

	for(int i=0;i<vertex_buffer_data.size(); i++)
	{
		index_buffer_data.push_back(i);
	}

	Mesh *mesh = new Mesh(meshName);

	glBindBuffer(GL_ARRAY_BUFFER, mesh->vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertex_buffer_data.size() * sizeof(Vertex), &vertex_buffer_data[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->indexBuffer); //bind index buffer
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_buffer_data.size() * sizeof(GLuint), &index_buffer_data[0], GL_STATIC_DRAW);

	mesh->indexSize = index_buffer_data.size();
	mesh->mode = Mesh::DRAW_TRIANGLE_STRIP;

	return mesh;
}

Mesh* MeshBuilder::GenerateHemiSphere(const std::string &meshName, float radius, Color color)
{
	Vertex v;
	std::vector<Vertex> vertex_buffer_data;

	for(float phi = 0; phi < 90; phi +=10)
	{
		for(float theta = 0; theta <= 360; theta +=10)
		{
			v.pos.Set(radius * cos(Math::DegreeToRadian(phi)) * cos(Math::DegreeToRadian(theta)) , radius * sin(Math::DegreeToRadian(phi)) , radius * cos(Math::DegreeToRadian(phi)) * sin(Math::DegreeToRadian(theta)));
			v.color=color;
			v.normal.Set(cos(Math::DegreeToRadian(phi)) * cos(Math::DegreeToRadian(theta)) , sin(Math::DegreeToRadian(phi)) , cos(Math::DegreeToRadian(phi)) * sin(Math::DegreeToRadian(theta)));
			v.normal.Normalize();
			vertex_buffer_data.push_back(v);

			v.pos.Set(radius * cos(Math::DegreeToRadian(phi+10)) * cos(Math::DegreeToRadian(theta)) , radius * sin(Math::DegreeToRadian(phi+10)) , radius * cos(Math::DegreeToRadian(phi+10)) * sin(Math::DegreeToRadian(theta)));
			v.color=color;
			v.normal.Set(cos(Math::DegreeToRadian(phi+10)) * cos(Math::DegreeToRadian(theta)) , sin(Math::DegreeToRadian(phi+10)) ,  cos(Math::DegreeToRadian(phi+10)) * sin(Math::DegreeToRadian(theta)));
			v.normal.Normalize();
			vertex_buffer_data.push_back(v);
		}
	}
	
	for(float phi = 0; phi < 90; phi +=10)
	{
		for(float theta = 0; theta <= 360; theta +=10)
		{
			v.pos.Set(radius * cos(Math::DegreeToRadian(phi+10)) * cos(Math::DegreeToRadian(theta)) , radius * sin(Math::DegreeToRadian(phi+10)) , radius * cos(Math::DegreeToRadian(phi+10)) * sin(Math::DegreeToRadian(theta)));
			v.color=color;
			v.normal.Set(-cos(Math::DegreeToRadian(phi+10)) * cos(Math::DegreeToRadian(theta)), -sin(Math::DegreeToRadian(phi+10)) , -cos(Math::DegreeToRadian(phi+10)) * sin(Math::DegreeToRadian(theta)));
			v.normal.Normalize();
			vertex_buffer_data.push_back(v);

			v.pos.Set(radius * cos(Math::DegreeToRadian(phi)) * cos(Math::DegreeToRadian(theta)) , radius * sin(Math::DegreeToRadian(phi)) , radius * cos(Math::DegreeToRadian(phi)) * sin(Math::DegreeToRadian(theta)));
			v.color=color;
			v.normal.Set(-cos(Math::DegreeToRadian(phi)) * cos(Math::DegreeToRadian(theta)), -sin(Math::DegreeToRadian(phi)) , -cos(Math::DegreeToRadian(phi)) * sin(Math::DegreeToRadian(theta)));
			v.normal.Normalize();
			vertex_buffer_data.push_back(v);
		}
	}

	std::vector<GLuint> index_buffer_data;

	for(int i=0; i<= vertex_buffer_data.size();i++)
	{
		index_buffer_data.push_back(i);
	}

	Mesh *mesh = new Mesh(meshName);

	glBindBuffer(GL_ARRAY_BUFFER, mesh->vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertex_buffer_data.size() * sizeof(Vertex), &vertex_buffer_data[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->indexBuffer); //bind index buffer
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_buffer_data.size() * sizeof(GLuint), &index_buffer_data[0], GL_STATIC_DRAW);

	mesh->indexSize = index_buffer_data.size();
	mesh->mode = Mesh::DRAW_TRIANGLE_STRIP;

	return mesh;
}

Mesh* MeshBuilder::GenerateText(const std::string &meshName,unsigned numRow,unsigned numCol)
{
	Vertex v;
	std::vector<Vertex> vertex_buffer_data;
	std::vector<GLuint> index_buffer_data;
	
	float width = 1.f/numCol;
	float height = 1.f/numRow;
	
	for(unsigned i = 0; i < numRow; ++i)
	{
		for(unsigned j = 0; j < numCol; ++j)
		{
			v.pos.Set(-0.5f,-0.5f,0.0f);
			v.texCoord.Set((j*width),1.f - height - i*height);
			vertex_buffer_data.push_back(v);

			v.pos.Set(0.5f,-0.5f,0.0f);
			v.texCoord.Set((j*width) + width,1.f - height - i*height);
			vertex_buffer_data.push_back(v);

			v.pos.Set(0.5f,0.5f,0.0f);
			v.texCoord.Set((j*width) + width,(1.f - height - i*height) + height);
			vertex_buffer_data.push_back(v);

			v.pos.Set(-0.5f,0.5f,0.0f);
			v.texCoord.Set((j*width),(1.f - height - i*height) + height);
			vertex_buffer_data.push_back(v);

			index_buffer_data.push_back((i * numRow + j) * 4 + 3);
			index_buffer_data.push_back((i * numRow + j) * 4 + 0);
			index_buffer_data.push_back((i * numRow + j) * 4 + 2);
			index_buffer_data.push_back((i * numRow + j) * 4 + 1);
			index_buffer_data.push_back((i * numRow + j) * 4 + 2);
			index_buffer_data.push_back((i * numRow + j) * 4 + 0);
		}

	}

	Mesh *mesh = new Mesh(meshName);

	glBindBuffer(GL_ARRAY_BUFFER, mesh->vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertex_buffer_data.size() * sizeof(Vertex), &vertex_buffer_data[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->indexBuffer); //bind index buffer
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_buffer_data.size() * sizeof(GLuint), &index_buffer_data[0], GL_STATIC_DRAW);

	mesh->indexSize = index_buffer_data.size();
	mesh->mode = Mesh::DRAW_TRIANGLES;

	return mesh;
}