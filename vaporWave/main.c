#include <GLFW/glfw3.h>
#include <stdio.h>
#include <GL/glu.h>
#define WIDTH 600
#define HEIGHT 600

float angleX,angleY = 0.0f;


void drawCube() {
    // FACE DA FRENTE (Z = 1.0) - Vermelha
    glColor3f(1.0f, 0.0f, 0.0f);
    glBegin(GL_QUADS);
        glVertex3f(-1.0f, -1.0f,  1.0f); // Inferior Esquerdo
        glVertex3f( 1.0f, -1.0f,  1.0f); // Inferior Direito
        glVertex3f( 1.0f,  1.0f,  1.0f); // Superior Direito
        glVertex3f(-1.0f,  1.0f,  1.0f); // Superior Esquerdo
    glEnd();

    // FACE DE TRÁS (Z = -1.0) - Verde
    glColor3f(0.0f, 1.0f, 0.0f);
    glBegin(GL_QUADS);
        glVertex3f(-1.0f, -1.0f, -1.0f);
        glVertex3f(-1.0f,  1.0f, -1.0f);
        glVertex3f( 1.0f,  1.0f, -1.0f);
        glVertex3f( 1.0f, -1.0f, -1.0f);
    glEnd();

    // FACE DA ESQUERDA (X = -1.0) - Azul
    glColor3f(0.0f, 0.0f, 1.0f);
    glBegin(GL_QUADS);
        glVertex3f(-1.0f, -1.0f, -1.0f);
        glVertex3f(-1.0f, -1.0f,  1.0f);
        glVertex3f(-1.0f,  1.0f,  1.0f);
        glVertex3f(-1.0f,  1.0f, -1.0f);
    glEnd();

    // FACE DA DIREITA (X = 1.0) - Amarelo
    glColor3f(1.0f, 1.0f, 0.0f);
    glBegin(GL_QUADS);
        glVertex3f( 1.0f, -1.0f, -1.0f);
        glVertex3f( 1.0f,  1.0f, -1.0f);
        glVertex3f( 1.0f,  1.0f,  1.0f);
        glVertex3f( 1.0f, -1.0f,  1.0f);
    glEnd();

    // FACE DE CIMA (Y = 1.0) - Ciano
    glColor3f(0.0f, 1.0f, 1.0f);
    glBegin(GL_QUADS);
        glVertex3f(-1.0f,  1.0f, -1.0f);
        glVertex3f(-1.0f,  1.0f,  1.0f);
        glVertex3f( 1.0f,  1.0f,  1.0f);
        glVertex3f( 1.0f,  1.0f, -1.0f);
    glEnd();

    // FACE DE BAIXO (Y = -1.0) - Magenta
    glColor3f(1.0f, 0.0f, 1.0f);
    glBegin(GL_QUADS);
        glVertex3f(-1.0f, -1.0f, -1.0f);
        glVertex3f( 1.0f, -1.0f, -1.0f);
        glVertex3f( 1.0f, -1.0f,  1.0f);
        glVertex3f(-1.0f, -1.0f,  1.0f);
    glEnd();
}

int main(void){
	if(!glfwInit()){
		printf("\nERRO: JANELA NAO FOI INICIALIZADA CORRETAMENTE\n");

		return -1;
	}

	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Sen Montains", NULL, NULL);
	if(!window){
		glfwTerminate();
		printf("\nERRO: JANELA NAO FOI INICIALIZADA CORRETAMENTE\n");
		return 1;
	}

	glfwMakeContextCurrent(window);

	glfwSwapInterval(1);
	glEnable(GL_DEPTH_TEST);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0f, 800.0f/600.0f, 0.1f, 100.0f);

	glMatrixMode(GL_MODELVIEW);

	while(!glfwWindowShouldClose(window)){
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glLoadIdentity();

		gluLookAt(
			   0.0f, 0.0f, 5.0f,
			   0.0f, 0.0f, 0.0f,
			   0.0f, 1.0f, 0.0f
			  );

		glRotatef(angleX, 1.0f, 0.0f, 0.0f);
		glRotatef(angleY, 0.0f, 1.0f, 0.0f);

		drawCube();
		angleX += 0.01f;
		angleY += 0.3f;

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	printf("Hello, World!");
	glfwDestroyWindow(window);
	glfwTerminate();

	return 0;
}
