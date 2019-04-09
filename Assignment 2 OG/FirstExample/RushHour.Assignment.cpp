//***************************************************************************
// Final-Assignment.cpp by Rush Hour (C) 2019 All Rights Reserved.
//
// Final Assignment submission.
//
// Description:
// Click run to see the results.

//*****************************************************************************

using namespace std;
//using namespace glm;
#include <iostream>
#include "stdlib.h"
#include "time.h"
#include "vgl.h"
#include "LoadShaders.h"
#include "glm\glm.hpp"
#include "glm\gtc\matrix_transform.hpp"

enum VAO_IDs { Triangles, NumVAOs };
enum Buffer_IDs { ArrayBuffer, NumBuffers };
enum Attrib_IDs { vPosition = 0 };

//GLuint Buffers[NumBuffers];
GLuint cubeVao;
GLuint cubeVbo;
GLuint cubeColoursVbo;
GLuint cubeIbo;

GLuint pyramidVao;
GLuint pyramidVbo;
GLuint pyramidColoursVbo;
GLuint pyramidIbo;

GLuint wedgeVao;
GLuint wedgeVbo;
GLuint wedgeColoursVbo;
GLuint wedgeIbo;

GLint model;
glm::mat4 Projection;
glm::mat4 View;
glm::mat4 ModelViewProjection;




GLuint program;

float camX = 0;
float camY = 0;
float camZ = 0;

void keyboardCamera(unsigned char Key, int x, int y) {
	
	switch (Key) {
		case 'W':
			camZ--;
			break;
		case 'A':
			camX--;
			break;
		case 'S':
			camZ++;
			break;
		case 'D':
			camX++;
			break;
		case 'R':
			camY++;
			break;
		case 'F':
			camY--;
			break;
	}
}

void init(void)
{
	
	//Specifying the name of vertex and fragment shaders.
	ShaderInfo shaders[] = {
		{ GL_VERTEX_SHADER, "triangles.vert" },
		{ GL_FRAGMENT_SHADER, "triangles.frag" },
		{ GL_NONE, NULL }
	};

	//Loading and compiling shaders
	program = LoadShaders(shaders);
	glUseProgram(program);	//My Pipeline is set up

	//////////////
	// WEDGE //
	/////////////

	glGenVertexArrays(1, &wedgeVao);
	glBindVertexArray(wedgeVao);

	float wedgeVertices[] = {
		-0.45, -0.45, 0.45,		//0
		0.45, -0.45, 0.45,		//1
		-0.45, -0.45, -0.45,	//2
		0.45, -0.45, -0.45,		//3
		0, 0.45, 0,				//4
		0 , -0.45 , -1,//5
		0 , -0.45 , 1 //6

	};
	wedgeVbo = 0;
	glGenBuffers(1, &wedgeVbo);
	glBindBuffer(GL_ARRAY_BUFFER, wedgeVbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(wedgeVertices), wedgeVertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(0);

	float wedgeColours[] = {
	1.0f, 0.0f, 0.0f,
	0.0f, 1.0f, 0.0f,
	0.0f, 0.0f, 1.0f,
	0.0f, 1.0f, 1.0f,
	1.0f, 1.0f, 0.0f,
	1.0f, 1.0f, 1.0f,
	1.0f, 0.0f, 1.0f,
	0.0f, 0.0f, 0.0f,

	};
	wedgeColoursVbo = 0;
	glGenBuffers(1, &wedgeColoursVbo);
	glBindBuffer(GL_ARRAY_BUFFER, wedgeColoursVbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(wedgeColours), wedgeColours, GL_STATIC_DRAW);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(1);

	GLushort wedgeIndices[] = {
		//base
		3,1,0,
		1,6,0,
		0,2,3,
		2,5,3,
		//front face
		//0,1,4,
		//right face
		1,3,4,
		//left face
		4,2,0,
		//back face
		//4,3,2,
		1,4,6,
		0,4,6,
		3,4,5,
		2,4,5,

	};
	glGenBuffers(1, &wedgeIbo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, wedgeIbo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(wedgeIndices), wedgeIndices, GL_STATIC_DRAW);



	//////////////
	// PYRAMID //
	/////////////


	glGenVertexArrays(1, &pyramidVao);
	glBindVertexArray(pyramidVao);

	float pyramidVertices[] = {
		-0.45, -0.45, 0.45,		//0
		0.45, -0.45, 0.45,		//1
		-0.45, -0.45, -0.45,	//2
		0.45, -0.45, -0.45,		//3
		0, 0.45, 0,				//4
	};
	pyramidVbo = 0;
	glGenBuffers(1, &pyramidVbo);
	glBindBuffer(GL_ARRAY_BUFFER, pyramidVbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(pyramidVertices), pyramidVertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(0);

	float pyramidColours[] = {
	1.0f, 0.0f, 0.0f,
	0.0f, 1.0f, 0.0f,
	0.0f, 0.0f, 1.0f,
	0.0f, 1.0f, 1.0f,
	1.0f, 1.0f, 0.0f,
	1.0f, 1.0f, 1.0f,
	1.0f, 0.0f, 1.0f,
	0.0f, 0.0f, 0.0f,

	};
	pyramidColoursVbo = 0;
	glGenBuffers(1, &pyramidColoursVbo);
	glBindBuffer(GL_ARRAY_BUFFER, pyramidColoursVbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(pyramidColours), pyramidColours, GL_STATIC_DRAW);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(1);

	GLushort pyramidIndices[] = {
		//base
		3,1,0,
		0,2,3,
		//front face
		0,1,4,
		//right face
		1,3,4,
		//left face
		4,2,0,
		//back face
		4,3,2,

	};
	glGenBuffers(1, &pyramidIbo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, pyramidIbo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(pyramidIndices), pyramidIndices, GL_STATIC_DRAW);

	///////////
	// CUBE //
	//////////

	glGenVertexArrays(1, &cubeVao);
	glBindVertexArray(cubeVao);

	
	
	float cubeVertices[] = {
	-0.45f, -0.45f, 0.45f,  //0
	0.45f, -0.45f, 0.45f,   //1 
	0.45f, 0.45f, 0.45f,	//2
	-0.45f, 0.45f, 0.45f,	//3
	-0.45f, -0.45f, -0.45f,	//4
	0.45f, -0.45f, -0.45f,	//5
	0.45f, 0.45f, -0.45f,	//6
	-0.45f, 0.45f, -0.45f,	//7

	};
	cubeVbo = 0;
	glGenBuffers(1, &cubeVbo);
	glBindBuffer(GL_ARRAY_BUFFER, cubeVbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(cubeVertices),cubeVertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(0);
	
	float cubeColours[] = {
	1.0f, 0.0f, 0.0f,
	0.0f, 1.0f, 0.0f,
	0.0f, 0.0f, 1.0f,
	0.0f, 1.0f, 1.0f,
	1.0f, 1.0f, 0.0f,
	1.0f, 1.0f, 1.0f,
	1.0f, 0.0f, 1.0f,
	0.0f, 0.0f, 0.0f,

	};
	cubeColoursVbo = 0;
	glGenBuffers(1, &cubeColoursVbo);
	glBindBuffer(GL_ARRAY_BUFFER, cubeColoursVbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(cubeColours), cubeColours, GL_STATIC_DRAW);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(1);

	GLushort cubeIndices[] = {
		//face
		0,1,2,
		2,3,0,
		//top
		3,2,6,
		6,7,3,
		//right
		1,5,6,
		6,2,1,
		//left
		7,4,0,
		0,3,7,
		//back
		6,5,4,
		4,7,6,
		//base
		5,1,0,
		0,4,5,
	};
	glGenBuffers(1, &cubeIbo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, cubeIbo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(cubeIndices), cubeIndices, GL_STATIC_DRAW);

	//=====

	model = glGetUniformLocation(program, "Model");

	Projection = glm::perspective(glm::radians(45.0f), 4.0f / 3.0f, 0.1f, 100.0f);
	View = glm::lookAt(glm::vec3(camX, camY, camZ), glm::vec3(0, 0, 0), glm::vec3(0, 2, 0));
}

void transformModel(float scale, glm::vec3 rotationAxis, float rotationAngle, glm::vec3 translation) {
	glm::mat4 Model;
	Model = glm::mat4(1.0f);
	Model = glm::translate(Model, translation);
	//Model = glm::rotate(Model, glm::radians(rotationAngle), rotationAxis);
	Model = glm::scale(Model, glm::vec3(scale));
	ModelViewProjection =  Projection *View *Model;
	glUniformMatrix4fv(model, 1, GL_FALSE, &ModelViewProjection[0][0]);
}
//---------------------------------------------------------------------
//
// display
//


void
display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(1.0f, 0.0f, 1.0f, 0.0f);
	View = glm::lookAt(glm::vec3(camX, 1, 4), glm::vec3(0, 0, 0), glm::vec3(0, 2, 0));
	//Selecting the buffer
	//glBindBuffer(GL_ARRAY_BUFFER, Buffers[0]);
	float angle = glutGet(GLUT_ELAPSED_TIME) / 1000.0 * 45;
	

	glBindVertexArray(cubeVao);
	transformModel(1.0f, glm::vec3(0, 0, 0), angle, glm::vec3(0, -0.45, 0)); // size,rotation axis, rotation angle, transform
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_SHORT, 0);
	glBindVertexArray(cubeVao);
	transformModel(1.0f, glm::vec3(0, 0, 0), angle, glm::vec3(0, -1.35, 0)); // size,rotation axis, rotation angle, transform
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_SHORT, 0);


	glBindVertexArray(pyramidVao);
	transformModel(1.0f, glm::vec3(0, 0, 0), angle, glm::vec3(0, 0.45, 0)); // size,rotation axis, rotation angle, transform
	glDrawElements(GL_TRIANGLES, 18, GL_UNSIGNED_SHORT, 0);

	glBindVertexArray(wedgeVao);
	transformModel(1.0f, glm::vec3(0, 0, 0), angle, glm::vec3(0, 1.45, 0)); // size,rotation axis, rotation angle, transform
	glDrawElements(GL_TRIANGLES, 30, GL_UNSIGNED_SHORT, 0);

	//transformModel(1.0f, glm::vec3(1, 0, 0), angle, glm::vec3(0, -0.45, 0)); // size,rotation axis, rotation angle, transform
	//glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_SHORT, 0);

	
	//glm::mat4 Model;
	//Model = glm::mat4(1.0f);
		for (int i = 0; i < 10; i++)
		{


	//		GLint model = glGetUniformLocation(program, "Model");
	//		glUniformMatrix4fv(model, 1, GL_FALSE, &Model[0][0]);
	//		//Ordering the GPU to start the pipeline
	//		glDrawArrays(GL_LINE_LOOP, 0, 4);
			/*float angle = glutGet(GLUT_ELAPSED_TIME) / 1000.0 * 45;
			Model = glm::rotate(Model, glm::radians(angle), glm::vec3(0.0f, 0.0f, 1.0f));
			Model = glm::scale(Model, glm::vec3(.7072135f));*/
	}

	glutSwapBuffers();
}

void timer(int) {
	glutTimerFunc(33,timer,0);
}


void idle()
{
	glutPostRedisplay();
}
 
//---------------------------------------------------------------------
//
// main
//

int
main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);
	glutInitWindowSize(600, 600);
	glutCreateWindow("Rush Hour");


	glewInit();	//Initializes the glew and prepares the drawing pipeline.

	glutKeyboardFunc(keyboardCamera);

	init();
	glEnable(GL_CULL_FACE); // cull face
	glCullFace(GL_BACK); // cull back face
	glFrontFace(GL_CCW); // GL_CCW for counter clock-wise
	glEnable(GL_DEPTH_TEST);
	display();
	glutTimerFunc(33, timer, 0);
	glutDisplayFunc(display);



	glutIdleFunc(idle);

	glutMainLoop();
	
	

}
