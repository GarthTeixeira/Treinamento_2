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
GLfloat xstep = 1.0f;
GLfloat ystep = 1.0f;

// Largura e altura da janela
GLfloat windowWidth;
GLfloat windowHeight;

GLfloat distanciaCentroide = 3.0;

std::vector<glm::vec3> cube;
GLfloat centroide[3] = {0.0f,0.0f,0.0f} ;

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

// Função callback chamada para fazer o desenho
void Desenha(void)
{
     glMatrixMode(GL_MODELVIEW);
     glLoadIdentity();
                   
     // Limpa a janela de visualização com a cor de fundo especificada
     glClear(GL_COLOR_BUFFER_BIT);

     // Especifica que a cor corrente é vermelha
     //         R     G     B
     glColor3f(1.0f, 0.0f, 0.0f);
  
     // Desenha um quadrado preenchido com a cor corrente
     glBegin(GL_QUADS);
               glVertex2i(X1,Y1+rsize); 
               glVertex2i(X1,Y1);
               // Especifica que a cor corrente é azul
               glColor3f(0.0f, 0.0f, 1.0f);
               glVertex2i(X1+rsize,Y1);
               glVertex2i(X1+rsize,Y1+rsize);               
     glEnd();

     // Executa os comandos OpenGL
     glutSwapBuffers();
}

// Função callback chamada pela GLUT a cada intervalo de tempo
// (a window não está sendo redimensionada ou movida)
void Timer(int value)
{
    // Muda a direção quando chega na borda esquerda ou direita
      if(X1 > windowWidth-rsize || X1 < 0)
            xstep = -xstep;

    // Muda a direção quando chega na borda superior ou inferior
    if(Y1 > windowHeight-rsize || Y1 < 0)
          ystep = -ystep;
          
    // Verifica as bordas.  Se a window for menor e o 
    // quadrado sair do volume de visualização 
   if(X1 > windowWidth-rsize)
         X1 = windowWidth-rsize-1;

   if(Y1 > windowHeight-rsize)
         Y1 = windowHeight-rsize-1;

    // Move o quadrado
    X1 += xstep;
    Y1 += ystep;

    // Redesenha o quadrado com as novas coordenadas 
    glutPostRedisplay();
    glutTimerFunc(33,Timer, 1);
}

// Inicializa parâmetros de rendering
void Inicializa (void)
{   
    // Define a cor de fundo da janela de visualização como preta
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
}

// Função callback chamada quando o tamanho da janela é alterado 
void AlteraTamanhoJanela(GLsizei w, GLsizei h)
{
     // Evita a divisao por zero
     if(h == 0) h = 1;
                           
     // Especifica as dimensões da Viewport
     glViewport(0, 0, w, h);

     // Inicializa o sistema de coordenadas
     glMatrixMode(GL_PROJECTION);
     glLoadIdentity();

     // Estabelece a janela de seleção (left, right, bottom, top)     
     if (w <= h)  {
		windowHeight = 250.0f*h/w;
		windowWidth = 250.0f;
     }
     else  { 
		windowWidth = 250.0f*w/h;
		windowHeight = 250.0f;
     }
     
     gluOrtho2D(0.0f, windowWidth, 0.0f, windowHeight);
}

// Programa Principal 
int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(400,350);
    glutInitWindowPosition(10,10);
    glutCreateWindow("Anima");
    glutDisplayFunc(Desenha);
    glutReshapeFunc(AlteraTamanhoJanela);
    glutTimerFunc(33, Timer, 1);
    Inicializa();
    glutMainLoop();
}