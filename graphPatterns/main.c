#include <GLFW/glfw3.h>
#include <time.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#define WIDTH 1600
#define HEIGHT 900
#define POINTSIZE 5.0f
#define STEPSIZE 0.006f

void error_callback(int error, const char* description){

	fprintf(stderr, "ERROR, %s\n", description);
}

void checkBoundaries(float *x, float *y){
	if(*x > 1.0f) *x = 1.0f;
	if(*x < -1.0f) *x = -1.0f;

	if(*y > 1.0f) *y = 1.0f;
	if(*y < -1.0f) *y = -1.0f;
}

int randomizerBaseX(int x){
	return (rand()%x);
}

void paintAgent(float x, float y, float r, float g, float b){
	glColor3f(r, g, b);
	glPointSize(POINTSIZE);
	glBegin(GL_POINTS);
		glVertex2f(x, y);
	glEnd();
}

void randomMove(float *x, float *y){
	int choice = randomizerBaseX(4);
	float step = STEPSIZE;
	switch(choice){
		case 0: *x += step; break;
		case 1: *x -= step; break;
		case 2: *y += step; break;
		case 3: *y -= step; break;
		default : exit(-1);
	}
	checkBoundaries(x,y);
}

float * setColor(int tamanhoVetor){
	float *vetor = calloc(tamanhoVetor, sizeof(float));
	for(int i = 0; i < tamanhoVetor; i++){
		vetor[i] = (float)rand()/(float) RAND_MAX;
		//printf("\nCHOICE = %f", vetor[i]);
	}
	return vetor;
}


int main(int argc, char * argv[]){
	if(argc < 2){
		printf("FALTA DE ARGUMENTOS -> USO: exec <num_agents>");
		return 1;
	}
	int agentsNum = atoi(argv[1]);

	srand(time(NULL));
	if(!glfwInit()){
		glfwSetErrorCallback(error_callback);
		return 1;//ERRO

	}

	GLFWwindow* window = glfwCreateWindow(WIDTH,HEIGHT, "Random Walk",NULL,NULL);
	if(!window){
		glfwTerminate();
		glfwSetErrorCallback(error_callback);
		return 1;//ERRO
	}

	glfwMakeContextCurrent(window);

	glfwSwapInterval(1);

	float pointXs[agentsNum], pointYs[agentsNum];
	float *rs, *gs, *bs;

	rs = setColor(agentsNum);
	gs = setColor(agentsNum);
	bs = setColor(agentsNum);

	rs[agentsNum] = 0.0f;
	gs[agentsNum] = 0.0f;
	bs[agentsNum] = 0.0f;
	//DEBUG
	//for(int i = 0 ; i < agentsNum; i++){
	//	printf("\nR = %fG = %fB = %f", rs[i], gs[i], bs[i]);
	//}



	while(!glfwWindowShouldClose(window)){
		//glClear(GL_COLOR_BUFFER_BIT);

		for(int i = 0; i < agentsNum; i ++){
			float r = rs[i];
			float g = gs[i];
			float b = bs[i];

			randomMove(&pointXs[i], &pointYs[i]);
			paintAgent(pointXs[i], pointYs[i], r, g, b);
		}
		glfwSwapBuffers(window);
		glfwPollEvents();
		//usleep(5000);

	}


	printf("Hello, World!");
	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}
