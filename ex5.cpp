#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glext.h>

#include <glm/glm.hpp> // vec2, vec3, mat4, radians
#include <glm/ext.hpp> // perspective, translate, rotate
#include <glm/gtx/string_cast.hpp>
#include <glm/gtc/constants.hpp>
#include <glm/gtx/io.hpp>


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

void Inicializa(void)
{
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    
    // Habilita o depth-buffering
    glEnable(GL_DEPTH_TEST);
    
}

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
    gluLookAt(20.0, 20.0, 20.0, 0, 0, 0, 0, 0, 1);
}

int main(int argc, char **argv)
{
    
    
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
