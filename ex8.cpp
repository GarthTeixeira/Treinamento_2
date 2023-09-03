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


void keyboard(unsigned char key, int x , int y);

std::vector<glm::vec3> cube;

GLfloat centroide[3] = {0.0f,0.0f,0.0f} ;

float angle = 1.0f;

// Exemplo de uso
glm::vec3 startPoint(30.0f, 30.0f, 30.0f);
glm::vec3 targetPoint(4.0f, 5.0f, 6.0f);
float distanceToMove = 0.1f; // A distância pela qual você deseja mover


GLfloat distanciaCentroide = 1.0;


std::map<char,std::vector<GLfloat>> first;


// Função para rotacionar um ponto em torno de um ponto de rotação
glm::vec3 rotatePointAround(glm::vec3 point, glm::vec3 center, float angle, glm::vec3 axis) {
    // Translação para o ponto de rotação
    glm::mat4 translation1 = glm::translate(glm::mat4(1.0f), center);

    // Rotação
    glm::mat4 rotation = glm::rotate(glm::mat4(1.0f), glm::radians(angle), axis);

    // Translação de volta
    glm::mat4 translation2 = glm::translate(glm::mat4(1.0f), -center);

    // Combine as transformações em uma única matriz
    glm::mat4 transformationMatrix = translation2 * rotation * translation1;

    // Aplicar a transformação ao ponto
    glm::vec4 transformedPoint = transformationMatrix * glm::vec4(point, 1.0f);

    return glm::vec3(transformedPoint);
}

glm::vec3 movePointTowards(glm::vec3 startPoint, glm::vec3 targetPoint, float distanceToMove) {
    glm::vec3 direction = glm::normalize(targetPoint - startPoint);
    glm::vec3 newPosition = startPoint + direction * distanceToMove;
    return newPosition;
}


glm::vec3 rotatePoint(const glm::vec3& point, float angle, const glm::vec3& axis) {
    glm::mat4 rotationMatrix = glm::rotate(glm::mat4(1.0f), glm::radians(angle), axis);
    glm::vec4 rotatedPoint = glm::vec4(point, 1.0f) * rotationMatrix;
    return glm::vec3(rotatedPoint);
}


void pontos_cubo()
{
	// Face frontal
    cube.push_back(glm::vec3(targetPoint.x - distanciaCentroide, targetPoint.y - distanciaCentroide, targetPoint.z + distanciaCentroide)); // Vértice 0
    cube.push_back(glm::vec3(targetPoint.x + distanciaCentroide, targetPoint.y - distanciaCentroide, targetPoint.z + distanciaCentroide)); // Vértice 1
    cube.push_back(glm::vec3(targetPoint.x + distanciaCentroide, targetPoint.y + distanciaCentroide, targetPoint.z + distanciaCentroide)); // Vértice 2
    cube.push_back(glm::vec3(targetPoint.x - distanciaCentroide, targetPoint.y + distanciaCentroide, targetPoint.z + distanciaCentroide)); // Vértice 3

    // Face traseira
    cube.push_back(glm::vec3(targetPoint.x - distanciaCentroide, targetPoint.y - distanciaCentroide, targetPoint.z - distanciaCentroide)); // Vértice 4
    cube.push_back(glm::vec3(targetPoint.x + distanciaCentroide, targetPoint.y - distanciaCentroide, targetPoint.z - distanciaCentroide)); // Vértice 5
    cube.push_back(glm::vec3(targetPoint.x + distanciaCentroide, targetPoint.y + distanciaCentroide, targetPoint.z - distanciaCentroide)); // Vértice 6
    cube.push_back(glm::vec3(targetPoint.x - distanciaCentroide, targetPoint.y + distanciaCentroide, targetPoint.z - distanciaCentroide)); // Vértice 7
}

void referencia()
{
    
    glBegin(GL_LINES);
    glColor3f(1, 0, 0);
    glVertex3f(0, 0, 0);
    glVertex3f(100, 0, 0);
    glColor3f(0, 1, 0);
    glVertex3f(0, 0, 0);
    glVertex3f(0, 100, 0);
    glColor3f(0, 0, 1);
    glVertex3f(0, 0, 0);
    glVertex3f(0, 0, 100);
    glEnd();

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


void Display(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Especifica sistema de coordenadas de projeção
    glMatrixMode(GL_PROJECTION);
    // Inicializa sistema de coordenadas de projeção
    glLoadIdentity();

    // Especifica a projeção perspectiva
    gluPerspective(10, (GLfloat)glutGet(GLUT_WINDOW_WIDTH) / (GLfloat)glutGet(GLUT_WINDOW_HEIGHT), 0.5, 500);

    // Especifica sistema de coordenadas do modelo
    glMatrixMode(GL_MODELVIEW);
    // Inicializa sistema de coordenadas do modelo
    glLoadIdentity();
    // Especifica posição do observador e do alvo
    gluLookAt(startPoint.x ,startPoint.y , startPoint.z , targetPoint.x, targetPoint.y, targetPoint.z, 0.0, 0.0, 1.0);


    referencia();
    draw_cubo(cube);
    glutPostRedisplay();
    glutSwapBuffers();
    glutKeyboardFunc(keyboard);
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

// Programa Principal
int main(int argc, char **argv)
{

    pontos_cubo();
   

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(500, 500);
    glutCreateWindow("Visualizacao 3D");
    glutDisplayFunc(Display);
    //glutReshapeFunc(AlteraTamanhoJanela);
    //glutMouseFunc(GerenciaMouse);
    Inicializa();
    glutMainLoop();
}

void keyboard(unsigned char key, int x, int y){

    std::cout << key << std::endl;

    switch (key)
    {
    case 'w':
        startPoint = movePointTowards(startPoint, targetPoint, 0.5f);
        std::cout << "w" << std::endl;
    break;
    case 'a':
        startPoint = rotatePointAround(startPoint, targetPoint, -1.0f, glm::vec3(0.0f, 0.0f, 1.0f));
        std::cout << "a" << std::endl;
        break;
    case 's':
        startPoint = movePointTowards(startPoint, targetPoint, - 0.5f);
        std::cout << "s" << std::endl;
        break;
    case 'd':
        startPoint = rotatePointAround(startPoint, targetPoint, 1.0f, glm::vec3(0.0f, 0.0f, 1.0f));
        std::cout << "d" << std::endl;
        break;
    
    default:
       
        std::cout << "not found" << std::endl;
        break;
    }

    glutPostRedisplay();
}