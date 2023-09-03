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
#include <map>
#include <math.h>

// Tamanho e posição inicial do quadrado
GLfloat X1 = 100.0f;
GLfloat Y1 = 150.0f;
GLsizei rsize = 50;                                                    

// Tamanho do incremento nas direções x e y 
// (número de pixels para se mover a cada
// intervalo de tempo)
GLfloat xRotation = 0;
GLfloat yRotation = 0;
GLfloat zRotation = 1;

unsigned int steps = 0;

// Largura e altura da janela
GLfloat windowWidth;
GLfloat windowHeight;

GLfloat distanciaCentroide = 3.0;

std::vector<glm::vec3> cube;
GLfloat centroide[3] = {0.0f,0.0f,0.0f} ;

 float angle = 1.0f;

glm::vec3 rotatePoint(const glm::vec3& point, float angle, const glm::vec3& axis) {
    glm::mat4 rotationMatrix = glm::rotate(glm::mat4(1.0f), glm::radians(angle), axis);
    glm::vec4 rotatedPoint = glm::vec4(point, 1.0f) * rotationMatrix;
    return glm::vec3(rotatedPoint);
}

void pontos_cubo()
{
	// Face frontal
    cube.push_back(glm::vec3(centroide[0] - distanciaCentroide, centroide[1] - distanciaCentroide, centroide[2] + distanciaCentroide)); // Vértice 0
    cube.push_back(glm::vec3(centroide[0] + distanciaCentroide, centroide[1] - distanciaCentroide, centroide[2] + distanciaCentroide)); // Vértice 1
    cube.push_back(glm::vec3(centroide[0] + distanciaCentroide, centroide[1] + distanciaCentroide, centroide[2] + distanciaCentroide)); // Vértice 2
    cube.push_back(glm::vec3(centroide[0] - distanciaCentroide, centroide[1] + distanciaCentroide, centroide[2] + distanciaCentroide)); // Vértice 3

    // Face traseira
    cube.push_back(glm::vec3(centroide[0] - distanciaCentroide, centroide[1] - distanciaCentroide, centroide[2] - distanciaCentroide)); // Vértice 4
    cube.push_back(glm::vec3(centroide[0] + distanciaCentroide, centroide[1] - distanciaCentroide, centroide[2] - distanciaCentroide)); // Vértice 5
    cube.push_back(glm::vec3(centroide[0] + distanciaCentroide, centroide[1] + distanciaCentroide, centroide[2] - distanciaCentroide)); // Vértice 6
    cube.push_back(glm::vec3(centroide[0] - distanciaCentroide, centroide[1] + distanciaCentroide, centroide[2] - distanciaCentroide)); // Vértice 7
}



void draw_cubo(std::vector<glm::vec3> cube_in)
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

// Função callback chamada para fazer o desenho
void Desenha(void)
{

     glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
                   
     // Limpa a janela de visualização com a cor de fundo especificada

     // Especifica que a cor corrente é vermelha
     draw_cubo(cube);

     // Executa os comandos OpenGL
     glutPostRedisplay();
     glutSwapBuffers();
}

// Função callback chamada pela GLUT a cada intervalo de tempo
// (a window não está sendo redimensionada ou movida)
void Timer(int value)
{

    if (steps <= 500)
    {
        xRotation = 1.0f;
        yRotation = 0.0f;
        zRotation = 0.0f;
    }
    else if (steps>500 && steps<=1000)
    {
        xRotation = 0.0f;
        yRotation = 1.0f;
        zRotation = 0.0f;
    } else if (steps> 1000 && steps<= 1500)
    {
        xRotation = 0.0f;
        yRotation = 0.0f;
        zRotation = 1.0f;
    }else{
        steps = 0;
    }

    steps++;

    std::cout << "Steps: " << steps << std::endl;
   
    for (size_t i = 0; i < cube.size(); i++)
    {
        cube[i] = rotatePoint(cube[i], angle, glm::vec3(xRotation, yRotation, zRotation));
    }
    
    // Redesenha o quadrado com as novas coordenadas 
    glutPostRedisplay();
    glutTimerFunc(33,Timer, 1);
}

// Inicializa parâmetros de rendering
void Inicializa (void)
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
    gluLookAt(50.0, 50.0, 50.0, 0, 0, 0, 0, 0, 1);
}

// Programa Principal 
int main(int argc, char **argv)
{

    pontos_cubo();
    glutInit(&argc, argv);

    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(500,500);
    glutCreateWindow("Anima");
    glutDisplayFunc(Desenha);
    glutReshapeFunc(AlteraTamanhoJanela);
    glutTimerFunc(33, Timer, 1);
    Inicializa();
    glutMainLoop();
}