#include <GLFW/glfw3.h>
#include <stdio.h>
#include <GL/glu.h>
#include <math.h>

#define WIDTH 1600
#define HEIGHT 900
#define MAP_SIZE 400
#define SCALE 1.0f


float timeCounter = 0.0f;


float angleX,angleY = 0.0f;

float calculateHeight(float x, float z){

	return sin(x * 0.5f + timeCounter) * cos(z * 0.5f) * 1.5f;
}
void drawTerrain() {
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glColor3f(0.0f, 1.0f, 0.5f);
    glBegin(GL_QUADS);
    for (int x = -MAP_SIZE / 2; x < MAP_SIZE / 2; x++) {
        for (int z = -MAP_SIZE / 2; z < MAP_SIZE / 2; z++) {

            // --- Vértice 1 ---
            float y1 = calculateHeight(x * SCALE, z * SCALE);
            glVertex3f(x * SCALE, y1, z * SCALE);

            // --- Vértice 2 ---
            float y2 = calculateHeight((x + 1) * SCALE, z * SCALE);
            glVertex3f((x + 1) * SCALE, y2, z * SCALE);

            // --- Vértice 3 ---
            float y3 = calculateHeight((x + 1) * SCALE, (z + 1) * SCALE);
            glVertex3f((x + 1) * SCALE, y3, (z + 1) * SCALE);

            // --- Vértice 4 ---
            float y4 = calculateHeight(x * SCALE, (z + 1) * SCALE);
            glVertex3f(x * SCALE, y4, (z + 1) * SCALE);
        }
    }
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


	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0f, 800.0f/600.0f, 0.1f, 100.0f);

	glMatrixMode(GL_MODELVIEW);

	while(!glfwWindowShouldClose(window)){
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glLoadIdentity();

		gluLookAt(
			   0.0f, 10.0f, 15.0f,
			   0.0f, 0.0f, 0.0f,
			   0.0f, 1.0f, 0.0f
			  );


		drawTerrain();

		timeCounter += 0.01f;

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	printf("Hello, World!");
	glfwDestroyWindow(window);
	glfwTerminate();

	return 0;
}
