#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glext.h>

#include <glm/glm.hpp> // vec2, vec3, mat4, radians
#include <glm/ext.hpp> // perspective, translate, rotate
#include <glm/gtx/string_cast.hpp>
#include <glm/gtc/constants.hpp>
#include <glm/gtx/io.hpp>

#include <vector>
#include <iostream>
#include <math.h>

// Instale as seguintes bibliotecas:
//sudo apt-get install cmake build-essential libgl1-mesa-dev freeglut3 libglm-dev

// Para compilar execute no terminal:
// g++ -o Transformacao exemplo_transformacao.cpp -lglut -lGLU -lGL -lm

std::vector<glm::vec4> cube;


void pontos_cubo()
{
	cube.push_back(glm::vec4( 0.0f, 0.0f, 0.0f, 1.0f ));
	cube.push_back(glm::vec4( 1.0f, 0.0f, 0.0f, 1.0f ));
	cube.push_back(glm::vec4( 1.0f, 1.0f, 0.0f, 1.0f ));
	cube.push_back(glm::vec4( 0.0f, 1.0f, 0.0f, 1.0f ));
	cube.push_back(glm::vec4( 0.0f, 0.0f,-1.0f, 1.0f ));
	cube.push_back(glm::vec4( 1.0f, 0.0f,-1.0f, 1.0f ));
	cube.push_back(glm::vec4( 1.0f, 1.0f,-1.0f, 1.0f ));
	cube.push_back(glm::vec4( 0.0f, 1.0f,-1.0f, 1.0f ));
}

std::vector<glm::vec4> transformacao(std::vector<glm::vec4> cube_in)
{
	std::cout << "Initial points: \n";	
	for(int i=0;i<cube.size();i++)
		std::cout << cube_in[i] << "\n";
	
	glm::mat4 T = glm::translate( glm::mat4( 1.0f ), glm::vec3( -1.0f, -1.0f,1.0f ) );
		
	std::cout << "Matrix: \n " << T << "\n";
	
	std::vector<glm::vec4> cube_out;
	
	for(int i=0;i<cube.size();i++)
	{
		glm::vec4 point = T * cube_in[i];
		cube_out.push_back(point);
	}
	
	std::cout << "Final points: \n";
	for(int i=0;i<cube.size();i++)
		std::cout << cube_out[i] << "\n";
	
	return cube_out;

}

void referencia()
{
    
    glBegin(GL_LINES);
    glColor3f(1, 0, 0);
    glVertex3f(0, 0, 0);
    glVertex3f(35, 0, 0);
    glColor3f(0, 1, 0);
    glVertex3f(0, 0, 0);
    glVertex3f(0, 35, 0);
    glColor3f(0, 0, 1);
    glVertex3f(0, 0, 0);
    glVertex3f(0, 0, 35);
    glEnd();

}

void draw_cubo(std::vector<glm::vec4> cube_in)
{
    
    glColor3f(1, 0, 0);
    glBegin(GL_QUADS);
    glNormal3f(0, 0, 1);
    glVertex3f(cube_in[0].x,cube_in[0].y,cube_in[0].z);
    glVertex3f(cube_in[1].x,cube_in[1].y,cube_in[1].z);
    glVertex3f(cube_in[2].x,cube_in[2].y,cube_in[2].z);
    glVertex3f(cube_in[3].x,cube_in[3].y,cube_in[3].z);
    glEnd();
    
    
    glColor3f(1, 1, 0);
    glBegin(GL_QUADS);
    glNormal3f(0, -1, 0);
    glVertex3f(cube_in[0].x,cube_in[0].y,cube_in[0].z);
    glVertex3f(cube_in[1].x,cube_in[1].y,cube_in[1].z);
    glVertex3f(cube_in[5].x,cube_in[5].y,cube_in[5].z);
    glVertex3f(cube_in[4].x,cube_in[4].y,cube_in[4].z);
    glEnd();
    
    
    glColor3f(0, 1, 1);
    glBegin(GL_QUADS);
    glNormal3f(0, 0, -1);
    glVertex3f(cube_in[4].x,cube_in[4].y,cube_in[4].z);
    glVertex3f(cube_in[5].x,cube_in[5].y,cube_in[5].z);
    glVertex3f(cube_in[6].x,cube_in[6].y,cube_in[6].z);
    glVertex3f(cube_in[7].x,cube_in[7].y,cube_in[7].z);
    glEnd();
    
    
    glColor3f(1, 0, 1);
    glBegin(GL_QUADS);
    glNormal3f(-1, 0, 0);
    glVertex3f(cube_in[0].x,cube_in[0].y,cube_in[0].z);
    glVertex3f(cube_in[3].x,cube_in[3].y,cube_in[3].z);
    glVertex3f(cube_in[7].x,cube_in[7].y,cube_in[7].z);
    glVertex3f(cube_in[4].x,cube_in[4].y,cube_in[4].z);
    glEnd();
    
    
     glColor3f(0, 0, 1);
    glBegin(GL_QUADS);
    glNormal3f(0, 1, 0);
    glVertex3f(cube_in[3].x,cube_in[3].y,cube_in[3].z);
    glVertex3f(cube_in[2].x,cube_in[2].y,cube_in[2].z);
    glVertex3f(cube_in[6].x,cube_in[6].y,cube_in[6].z);
    glVertex3f(cube_in[7].x,cube_in[7].y,cube_in[7].z);
    glEnd();
    
    
    
    glColor3f(0, 1, 0);
    glBegin(GL_QUADS);
    glNormal3f(1, 0, 0);
    glVertex3f(cube_in[1].x,cube_in[1].y,cube_in[1].z);
    glVertex3f(cube_in[2].x,cube_in[2].y,cube_in[2].z);
    glVertex3f(cube_in[6].x,cube_in[6].y,cube_in[6].z);
    glVertex3f(cube_in[5].x,cube_in[5].y,cube_in[5].z);
    glEnd();
    
   
}


void Display(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    referencia();
    //draw_cubo(cube);
    
    // std::vector<glm::vec4> pontos = transformacao(cube);
    // draw_cubo(pontos);
    
    glutPostRedisplay();
    glutSwapBuffers();
}

// Inicializa parâmetros de rendering
void Inicializa(void)
{
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    
    // Habilita o depth-buffering
    glEnable(GL_DEPTH_TEST);
    
}

// Função callback chamada quando o tamanho da janela é alterado
void AlteraTamanhoJanela(GLsizei w, GLsizei h)
{
    // Para previnir uma divisão por zero
    if (h == 0)
        h = 1;

    // Especifica o tamanho da viewport
    glViewport(0, 0, w, h);

    // Especifica sistema de coordenadas de projeção
    glMatrixMode(GL_PROJECTION);
    // Inicializa sistema de coordenadas de projeção
    glLoadIdentity();

    // Especifica a projeção perspectiva
    gluPerspective(10, (GLfloat)w / (GLfloat)h, 0.5, 500);

    // Especifica sistema de coordenadas do modelo
    glMatrixMode(GL_MODELVIEW);
    // Inicializa sistema de coordenadas do modelo
    glLoadIdentity();
    // Especifica posição do observador e do alvo
    gluLookAt(15.0, 15.0, 15.0, 0, 0, 0, 0, 0, 1);
}

// Programa Principal
int main(int argc, char **argv)
{

    pontos_cubo();
    
    
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(500, 500);
    glutCreateWindow("Visualizacao 3D");
    glutDisplayFunc(Display);
    glutReshapeFunc(AlteraTamanhoJanela);
    //glutMouseFunc(GerenciaMouse);
    Inicializa();
    glutMainLoop();
}
