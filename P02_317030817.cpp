//Práctica 2: índices, mesh, proyecciones, transformaciones geométricas
#include <stdio.h>
#include <string.h>
#include<cmath>
#include<vector>
#include <glew.h>
#include <glfw3.h>
//glm
#include<glm.hpp>
#include<gtc\matrix_transform.hpp>
#include<gtc\type_ptr.hpp>
//clases para dar orden y limpieza al código
#include"Mesh.h"
#include"Shader.h"
#include"Window.h"
//Dimensiones de la ventana
const float toRadians = 3.14159265f/180.0; //grados a radianes
Window mainWindow;
std::vector<Mesh*> meshList;
std::vector<MeshColor*> meshColorList;
std::vector<Shader>shaderList;
//Vertex Shader
static const char* vShader = "shaders/shader.vert";
static const char* fShader = "shaders/shader.frag";
static const char* vShaderColor = "shaders/shadercolor.vert";
static const char* fShaderColor = "shaders/shadercolor.frag";
//shaders nuevos se crearían acá

float angulo = 0.0f;

//color café en RGB : 0.478, 0.255, 0.067

//Pirámide triangular regular
void CreaPiramide()
{
	unsigned int indices[] = { 
		0,1,2,
		1,3,2,
		3,0,2,
		1,0,3
		
	};
	GLfloat vertices[] = {
		-0.5f, -0.5f,0.0f,	//0
		0.5f,-0.5f,0.0f,	//1
		0.0f,0.5f, -0.25f,	//2
		0.0f,-0.5f,-0.5f,	//3

	};
	Mesh *obj1 = new Mesh();
	obj1->CreateMesh(vertices, indices, 12, 12);
	meshList.push_back(obj1);
}

//Vértices de un cubo
void CrearCubo()
{
	unsigned int cubo_indices[] = {
		// front
		0, 1, 2,
		2, 3, 0,
		// right
		1, 5, 6,
		6, 2, 1,
		// back
		7, 6, 5,
		5, 4, 7,
		// left
		4, 0, 3,
		3, 7, 4,
		// bottom
		4, 5, 1,
		1, 0, 4,
		// top
		3, 2, 6,
		6, 7, 3
	};

GLfloat cubo_vertices[] = {
	// front
	-0.5f, -0.5f,  0.5f,
	0.5f, -0.5f,  0.5f,
	0.5f,  0.5f,  0.5f,
	-0.5f,  0.5f,  0.5f,
	// back
	-0.5f, -0.5f, -0.5f,
	0.5f, -0.5f, -0.5f,
	0.5f,  0.5f, -0.5f,
	-0.5f,  0.5f, -0.5f
};
Mesh *cubo = new Mesh();
cubo->CreateMesh(cubo_vertices, cubo_indices,24, 36);
meshList.push_back(cubo);
}

void CrearLetrasyFiguras()
{
	GLfloat vertices_LetraA[] = {
		//   X         Y         Z         R       G       B
		// Triángulo 1
		-0.8f,    -0.4f,    0.0f,    0.7f,   0.4f,   0.9f,
		-0.8f,    -0.95f,   0.0f,    0.7f,   0.4f,   0.9f,
		-0.95f,   -0.95f,   0.0f,    0.7f,   0.4f,   0.9f,

		// Triángulo 2
		-0.8f,    -0.4f,    0.0f,    0.7f,   0.4f,   0.9f,
		-0.8f,    -0.95f,   0.0f,    0.7f,   0.4f,   0.9f,
		-0.7f,    -0.5f,    0.0f,    0.7f,   0.4f,   0.9f,

		// Triángulo 3
		-0.8f,    -0.4f,    0.0f,    0.7f,   0.4f,   0.9f,
		-0.7f,    -0.5f,    0.0f,    0.7f,   0.4f,   0.9f,
		-0.6f,    -0.4f,    0.0f,    0.7f,   0.4f,   0.9f,

		// Triángulo 4
		-0.7f,    -0.5f,    0.0f,    0.7f,   0.4f,   0.9f,
		-0.6f,    -0.4f,    0.0f,    0.7f,   0.4f,   0.9f,
		-0.6f,    -0.95f,   0.0f,    0.7f,   0.4f,   0.9f,

		// Triángulo 5
		-0.6f,    -0.4f,    0.0f,    0.7f,   0.4f,   0.9f,
		-0.6f,    -0.95f,   0.0f,    0.7f,   0.4f,   0.9f,
		-0.45f,   -0.95f,   0.0f,    0.7f,   0.4f,   0.9f,

		// Triángulo 6
		-0.656f,  -0.700f,  0.0f,    0.7f,   0.4f,   0.9f,
		-0.646f,  -0.751f,  0.0f,    0.7f,   0.4f,   0.9f,
		-0.744f,  -0.699f,  0.0f,    0.7f,   0.4f,   0.9f,

		// Triángulo 7
		-0.755f,  -0.750f,  0.0f,    0.7f,   0.4f,   0.9f,
		-0.646f,  -0.751f,  0.0f,    0.7f,   0.4f,   0.9f,
		-0.744f,  -0.699f,  0.0f,    0.7f,   0.4f,   0.9f,
	};

	MeshColor* letraA = new MeshColor();
	letraA->CreateMeshColor(vertices_LetraA, 126);
	meshColorList.push_back(letraA);

	GLfloat vertices_LetraP[] = {
		//   X         Y         Z         R       G       B
		// Triángulo 1
		-0.17f,    0.27f,    0.0f,    0.9f,   0.3f,   0.3f,
		-0.17f,   -0.3f,     0.0f,    0.9f,   0.3f,   0.3f,
		-0.1f,    -0.3f,     0.0f,    0.9f,   0.3f,   0.3f,

		// Triángulo 2
		-0.1f,    -0.3f,     0.0f,    0.9f,   0.3f,   0.3f,
		-0.17f,    0.27f,    0.0f,    0.9f,   0.3f,   0.3f,
		-0.1f,     0.27f,    0.0f,    0.9f,   0.3f,   0.3f,

		// Triángulo 3
		-0.1f,     0.25f,    0.0f,    0.9f,   0.3f,   0.3f,
		-0.1f,     0.17f,    0.0f,    0.9f,   0.3f,   0.3f,
		 0.1f,     0.25f,    0.0f,    0.9f,   0.3f,   0.3f,

		 // Triángulo 4
		 -0.1f,     0.17f,    0.0f,    0.9f,   0.3f,   0.3f,
		  0.1f,     0.25f,    0.0f,    0.9f,   0.3f,   0.3f,
		  0.04f,    0.17f,    0.0f,    0.9f,   0.3f,   0.3f,

		 // Triángulo 5
		  0.04f,    0.17f,    0.0f,    0.9f,   0.3f,   0.3f,
		  0.1f,     0.25f,    0.0f,    0.9f,   0.3f,   0.3f,
		  0.07f,    0.15f,    0.0f,    0.9f,   0.3f,   0.3f,

		 // Triángulo 6
		  0.1f,     0.25f,    0.0f,    0.9f,   0.3f,   0.3f,
		  0.07f,    0.15f,    0.0f,    0.9f,   0.3f,   0.3f,
		  0.15f,    0.2f,     0.0f,    0.9f,   0.3f,   0.3f,

		 // Triángulo 7
		  0.07f,    0.15f,    0.0f,    0.9f,   0.3f,   0.3f,
		  0.15f,    0.2f,     0.0f,    0.9f,   0.3f,   0.3f,
		  0.15f,    0.0f,     0.0f,    0.9f,   0.3f,   0.3f,

		 // Triángulo 8
		  0.07f,    0.15f,    0.0f,    0.9f,   0.3f,   0.3f,
		  0.15f,    0.0f,     0.0f,    0.9f,   0.3f,   0.3f,
		  0.07f,    0.05f,    0.0f,    0.9f,   0.3f,   0.3f,

		 // Triángulo 9
		  0.15f,    0.0f,     0.0f,    0.9f,   0.3f,   0.3f,
		  0.07f,    0.05f,    0.0f,    0.9f,   0.3f,   0.3f,
		  0.1f,    -0.05f,    0.0f,    0.9f,   0.3f,   0.3f,

		 // Triángulo 10
		  0.07f,    0.05f,    0.0f,    0.9f,   0.3f,   0.3f,
		  0.1f,    -0.05f,    0.0f,    0.9f,   0.3f,   0.3f,
		  0.04f,    0.02f,    0.0f,    0.9f,   0.3f,   0.3f,

		 // Triángulo 11
		  0.1f,    -0.05f,    0.0f,    0.9f,   0.3f,   0.3f,
		  0.04f,    0.02f,    0.0f,    0.9f,   0.3f,   0.3f,
		 -0.1f,    -0.05f,    0.0f,    0.9f,   0.3f,   0.3f,

		 // Triángulo 12
		  0.04f,    0.02f,    0.0f,    0.9f,   0.3f,   0.3f,
		 -0.1f,    -0.05f,    0.0f,    0.9f,   0.3f,   0.3f,
		 -0.1f,     0.02f,    0.0f,    0.9f,   0.3f,   0.3f,
	};
	MeshColor* letraP = new MeshColor();
	letraP->CreateMeshColor(vertices_LetraP, 216);
	meshColorList.push_back(letraP);

	GLfloat vertices_LetraB[] = {
		//   X         Y         Z         R       G       B
		// Triángulo 1
		0.45f,    0.35f,    0.0f,    0.0f,   0.7f,   0.0f,
		0.45f,    0.95f,    0.0f,    0.0f,   0.7f,   0.0f,
		0.54f,    0.42f,    0.0f,    0.0f,   0.7f,   0.0f,

		// Triángulo 2
		0.45f,    0.95f,    0.0f,    0.0f,   0.7f,   0.0f,
		0.54f,    0.42f,    0.0f,    0.0f,   0.7f,   0.0f,
		0.54f,    0.86f,    0.0f,    0.0f,   0.7f,   0.0f,

		// Triángulo 3
		0.45f,    0.95f,    0.0f,    0.0f,   0.7f,   0.0f,
		0.54f,    0.86f,    0.0f,    0.0f,   0.7f,   0.0f,
		0.75f,    0.95f,    0.0f,    0.0f,   0.7f,   0.0f,

		// Triángulo 4
		0.54f,    0.86f,    0.0f,    0.0f,   0.7f,   0.0f,
		0.75f,    0.95f,    0.0f,    0.0f,   0.7f,   0.0f,
		0.70f,    0.86f,    0.0f,    0.0f,   0.7f,   0.0f,

		// Triángulo 5
		0.75f,    0.95f,    0.0f,    0.0f,   0.7f,   0.0f,
		0.70f,    0.86f,    0.0f,    0.0f,   0.7f,   0.0f,
		0.85f,    0.90f,    0.0f,    0.0f,   0.7f,   0.0f,

		// Triángulo 6
		0.70f,    0.86f,    0.0f,    0.0f,   0.7f,   0.0f,
		0.85f,    0.90f,    0.0f,    0.0f,   0.7f,   0.0f,
		0.76f,    0.84f,    0.0f,    0.0f,   0.7f,   0.0f,

		// Triángulo 7
		0.85f,    0.90f,    0.0f,    0.0f,   0.7f,   0.0f,
		0.76f,    0.84f,    0.0f,    0.0f,   0.7f,   0.0f,
		0.85f,    0.70f,    0.0f,    0.0f,   0.7f,   0.0f,

		// Triángulo 8
		0.76f,    0.84f,    0.0f,    0.0f,   0.7f,   0.0f,
		0.85f,    0.70f,    0.0f,    0.0f,   0.7f,   0.0f,
		0.76f,    0.75f,    0.0f,    0.0f,   0.7f,   0.0f,

		// Triángulo 9
		0.85f,    0.70f,    0.0f,    0.0f,   0.7f,   0.0f,
		0.76f,    0.75f,    0.0f,    0.0f,   0.7f,   0.0f,
		0.70f,    0.65f,    0.0f,    0.0f,   0.7f,   0.0f,

		// Triángulo 10
		0.76f,    0.75f,    0.0f,    0.0f,   0.7f,   0.0f,
		0.70f,    0.65f,    0.0f,    0.0f,   0.7f,   0.0f,
		0.69f,    0.72f,    0.0f,    0.0f,   0.7f,   0.0f,

		// Triángulo 11
		0.69f,    0.72f,    0.0f,    0.0f,   0.7f,   0.0f,
		0.70f,    0.65f,    0.0f,    0.0f,   0.7f,   0.0f,
		0.54f,    0.72f,    0.0f,    0.0f,   0.7f,   0.0f,

		// Triángulo 12
		0.70f,    0.65f,    0.0f,    0.0f,   0.7f,   0.0f,
		0.54f,    0.72f,    0.0f,    0.0f,   0.7f,   0.0f,
		0.54f,    0.57f,    0.0f,    0.0f,   0.7f,   0.0f,

		// Triángulo 13
		0.54f,    0.57f,    0.0f,    0.0f,   0.7f,   0.0f,
		0.70f,    0.65f,    0.0f,    0.0f,   0.7f,   0.0f,
		0.83f,    0.57f,    0.0f,    0.0f,   0.7f,   0.0f,

		// Triángulo 14
		0.70f,    0.65f,    0.0f,    0.0f,   0.7f,   0.0f,
		0.83f,    0.57f,    0.0f,    0.0f,   0.7f,   0.0f,
		0.90f,    0.65f,    0.0f,    0.0f,   0.7f,   0.0f,

		// Triángulo 15
		0.83f,    0.57f,    0.0f,    0.0f,   0.7f,   0.0f,
		0.90f,    0.65f,    0.0f,    0.0f,   0.7f,   0.0f,
		0.87f,    0.53f,    0.0f,    0.0f,   0.7f,   0.0f,

		// Triángulo 16
		0.90f,    0.65f,    0.0f,    0.0f,   0.7f,   0.0f,
		0.87f,    0.53f,    0.0f,    0.0f,   0.7f,   0.0f,
		0.95f,    0.60f,    0.0f,    0.0f,   0.7f,   0.0f,

		// Triángulo 17
		0.87f,    0.53f,    0.0f,    0.0f,   0.7f,   0.0f,
		0.95f,    0.60f,    0.0f,    0.0f,   0.7f,   0.0f,
		0.87f,    0.46f,    0.0f,    0.0f,   0.7f,   0.0f,

		// Triángulo 18
		0.95f,    0.60f,    0.0f,    0.0f,   0.7f,   0.0f,
		0.87f,    0.46f,    0.0f,    0.0f,   0.7f,   0.0f,
		0.95f,    0.40f,    0.0f,    0.0f,   0.7f,   0.0f,

		// Triángulo 19
		0.87f,    0.46f,    0.0f,    0.0f,   0.7f,   0.0f,
		0.95f,    0.40f,    0.0f,    0.0f,   0.7f,   0.0f,
		0.82f,    0.42f,    0.0f,    0.0f,   0.7f,   0.0f,

		// Triángulo 20
		0.95f,    0.40f,    0.0f,    0.0f,   0.7f,   0.0f,
		0.82f,    0.42f,    0.0f,    0.0f,   0.7f,   0.0f,
		0.90f,    0.35f,    0.0f,    0.0f,   0.7f,   0.0f,

		// Triángulo 21
		0.82f,    0.42f,    0.0f,    0.0f,   0.7f,   0.0f,
		0.90f,    0.35f,    0.0f,    0.0f,   0.7f,   0.0f,
		0.54f,    0.42f,    0.0f,    0.0f,   0.7f,   0.0f,

		// Triángulo 22
		0.90f,    0.35f,    0.0f,    0.0f,   0.7f,   0.0f,
		0.54f,    0.42f,    0.0f,    0.0f,   0.7f,   0.0f,
		0.45f,    0.35f,    0.0f,    0.0f,   0.7f,   0.0f,
	};

	MeshColor* letraB = new MeshColor();
	letraB->CreateMeshColor(vertices_LetraB, 396);
	meshColorList.push_back(letraB);
}


void CreateShaders()
{
	// Indice 0:
	Shader* shader1 = new Shader(); //shader para usar índices: objetos: cubo y  pirámide
	shader1->CreateFromFiles(vShader, fShader);
	shaderList.push_back(*shader1);

	// Indice 1:
	Shader* shader2 = new Shader();//shader para usar color como parte del VAO: letras 
	shader2->CreateFromFiles(vShaderColor, fShaderColor);
	shaderList.push_back(*shader2);

	// Indice 2: Rojo
	Shader* shRojo = new Shader();
	shRojo->CreateFromFiles("shaders/shader.vert", "shaders/rojo.frag");
	shaderList.push_back(*shRojo);

	// Indice 3: Azul
	Shader* shAzul = new Shader();
	shAzul->CreateFromFiles("shaders/shader.vert", "shaders/azul.frag");
	shaderList.push_back(*shAzul);

	// Indice 4: Verde
	Shader* shVerde = new Shader();
	shVerde->CreateFromFiles("shaders/shader.vert", "shaders/verde.frag");
	shaderList.push_back(*shVerde);

	// Indice 5: Verde Oscuro
	Shader* shVerdeO = new Shader();
	shVerdeO->CreateFromFiles("shaders/shader.vert", "shaders/verde_oscuro.frag");
	shaderList.push_back(*shVerdeO);

	// Indice 6: Cafe
	Shader* shCafe = new Shader();
	shCafe->CreateFromFiles("shaders/shader.vert", "shaders/cafe.frag");
	shaderList.push_back(*shCafe);
}


int main()
{
	mainWindow = Window(800, 800);
	mainWindow.Initialise();
	CreaPiramide(); //índice 0 en MeshList
	CrearCubo();//índice 1 en MeshList
	CrearLetrasyFiguras(); //usa MeshColor, índices en MeshColorList
	CreateShaders();
	GLuint uniformProjection = 0;
	GLuint uniformModel = 0;
	//Projection: Matriz de Dimensión 4x4 para indicar si vemos en 2D( orthogonal) o en 3D) perspectiva
	
	
	//------------------- Proyeccion Para ACtividad 01 -----------------------
	//glm::mat4 projection = glm::ortho(-1.0f, 1.0f, -1.0f, 1.0f, 10.0f, 100.0f);

	//------------------- Proyecciones Para ACtividad 02 -----------------------
	glm::mat4 projection = glm::ortho(-3.0f, 3.0f, -3.0f, 3.0f, 0.1f, 100.0f);
	//glm::mat4 projection = glm::perspective(glm::radians(60.0f)	,mainWindow.getBufferWidth() / mainWindow.getBufferHeight(), 0.1f, 100.0f);

	//Model: Matriz de Dimensión 4x4 en la cual se almacena la multiplicación de las transformaciones geométricas.
	//Siempre crear variabes fuera del while
	glm::mat4 model(1.0); //fuera del while se usa para inicializar la matriz con una identidad

	//Loop mientras no se cierra la ventana
	while (!mainWindow.getShouldClose())
	{
		//Recibir eventos del usuario
		glfwPollEvents();
		//Limpiar la ventana
		glClearColor(0.5f, 0.8f, 0.9f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //Se agrega limpiar el buffer de profundidad

		//Para las letras hay que usar el segundo set de shaders con índice 1 en ShaderList 
		shaderList[1].useShader();
		uniformModel = shaderList[1].getModelLocation();
		uniformProjection = shaderList[1].getProjectLocation();

		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		//Inicializar matriz de dimensión 4x4 que servirá como matriz de modelo para almacenar las transformaciones geométricas
		
		//---------------------------- ACTIVIDAD 01 ------------------------------
		// Letra A
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, -10.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA y se envían al shader como variables de tipo uniform
		meshColorList[0]->RenderMeshColor();

		// Letra P
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, -10.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA y se envían al shader como variables de tipo uniform
		meshColorList[1]->RenderMeshColor();

		// Letra B
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, -10.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA y se envían al shader como variables de tipo uniform
		meshColorList[2]->RenderMeshColor();

		//---------------------------- ACTIVIDAD 02 ------------------------------
		// --- CUERPO DE LA CASA (Cubo Rojo) ---
		shaderList[2].useShader(); // Shader Rojo
		uniformModel = shaderList[2].getModelLocation();
		uniformProjection = shaderList[2].getProjectLocation();

		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, -1.5f, -6.0f)); // Posición central inferior
		model = glm::scale(model, glm::vec3(3.0f, 3.0f, 3.0f));      // Cubo de 3x3 unidades
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		meshList[1]->RenderMesh(); // Dibujar Cubo
		
		// --- TECHO (Pirámide Azul) ---
		shaderList[3].useShader(); // Shader Azul
		uniformModel = shaderList[3].getModelLocation();
		uniformProjection = shaderList[3].getProjectLocation();

		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, 1.0f, -6.0f));
		model = glm::scale(model, glm::vec3(4.5f, 2.0f, 4.5f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		meshList[0]->RenderMesh(); // Dibujar Pirámide

		// --- PUERTA (Cubo Verde) ---
		shaderList[4].useShader(); // Shader Verde
		uniformModel = shaderList[4].getModelLocation();
		uniformProjection = shaderList[4].getProjectLocation();

		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, -2.5f, -4.99f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		meshList[1]->RenderMesh(); // Dibujar Cubo

		// --- VENTANA IZQUIERDA (Cubo Verde) ---
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(-0.7f, -0.7f, -4.99f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		meshList[1]->RenderMesh();

		// --- VENTANA DERECHA (Cubo Verde) ---
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.7f, -0.7f, -4.99f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		meshList[1]->RenderMesh();

		// --- TRONCO ÁRBOL DERECHA (Cubo Cafe) ---
		shaderList[6].useShader(); // Shader Cafe
		uniformModel = shaderList[6].getModelLocation();

		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(2.3f, -2.8f, -5.5f));
		model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		meshList[1]->RenderMesh(); // Dibujar Cubo

		// --- TRONCO ÁRBOL INZQUIERDA (Cubo Cafe) ---
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(-2.3f, -2.8f, -5.5f));
		model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		meshList[1]->RenderMesh(); // Dibujar Cubo

		// --- PINO IZQUIERDO (Pirámide Verde Oscuro) ---
		shaderList[5].useShader(); // Shader Verde Oscuro
		uniformModel = shaderList[5].getModelLocation();

		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(-2.3f, -1.6f, -5.2f));
		model = glm::scale(model, glm::vec3(1.0f, 2.0f, 1.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		meshList[0]->RenderMesh(); // Dibujar Pirámide

		// --- PINO  DERECHO (Pirámide Verde Oscuro) ---
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(2.3f, -1.6f, -5.2f));
		model = glm::scale(model, glm::vec3(1.0f, 2.0f, 1.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		meshList[0]->RenderMesh(); // Dibujar Pirámide

		glUseProgram(0);
		mainWindow.swapBuffers();

	}
	return 0;
}