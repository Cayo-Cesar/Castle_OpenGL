/*
 * Computacao Grafica
 * Codigo Exemplo: Primeira Janela GLUT/OpenGL
 * Autor: Prof. Laurindo de Sousa Britto Neto
 */
 
// Bibliotecas utilizadas pelo OpenGL
#ifdef __APPLE__ // MacOS
    #define GL_SILENCE_DEPRECATION
    #include <GLUT/glut.h>
    #include <OpenGL/gl.h>
    #include <OpenGL/glu.h>
#else // Windows e Linux
    #include <GL/glut.h>
    #include <GL/gl.h>
    #include <GL/glu.h>
#endif

#include <cstdlib>

#include "circulo.h"
#define ESC 27

//Variaveis Globais usadas para definicao de cores
float R,G,B;


// Declaracoes antecipadas (forward) de funcoes para as funcoes callback do OpenGL
void init(void);
void reshape(int w, int h);
void keyboard(unsigned char key, int x, int y);
void keyboard_special(int key, int x, int y);
void display(void);

/*
 * Funcao principal
 */
int main(int argc, char** argv){
    glutInit(&argc, argv); // Passagens de parametros C para o glut
    glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB); // Selecao do Modo do Display e do Sistema de cor utilizado
    glutInitWindowSize (512, 512);  // Tamanho da janela do OpenGL
    glutInitWindowPosition (100, 100); //Posicao inicial da janela do OpenGL
    glutCreateWindow ("Computcao Grafica: Primeira Janela GLUT/OpenGL"); // Da nome para uma janela OpenGL
    init(); // Chama a funcao init();
    glutReshapeFunc(reshape); //funcao callback para redesenhar a tela
    glutDisplayFunc(display); //funcao callback de desenho
    glutKeyboardFunc(keyboard); //funcao callback do teclado
    glutSpecialFunc(keyboard_special);	//funcao callback do teclado especial
    glutMainLoop(); // executa o loop do OpenGL
    return EXIT_SUCCESS; // retorna 0 para o tipo inteiro da funcao main()
}

/*
 * Inicializa alguns parametros do GLUT
 */
void init(void){
    glClearColor(1.0, 1.0, 1.0, 1.0); //Limpa a tela com a cor branca;
    R = 0.0;
    G = 0.0;
    B = 0.0;
}


/*
 * Ajusta a projecao para o redesenho da janela
 */
void reshape(int w, int h)
{
	// Reinicializa o sistema de coordenadas
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

    // Definindo o Viewport para o tamanho da janela
	glViewport(0, 0, w, h);

    glOrtho (0, 1500, 0, 1500, -1 ,1);  // Define o volume de projecao ortografica;
                                      // Nesse caso, o ponto (0,0,0) se encontra no
                                      // canto inferior esquerdo da tela e o viewport
                                      // tem 0 a 512 pixel no eixo x, 0 a 512 pixel no
                                      // eixo y. Como sera trabalhado imagens 2D definimos
                                      // o eixo z com tamanho -1 a 1;

//   glOrtho (-256, 256, -256, 256, -1 ,1); // Nesse caso, continuamos com 512 pixels, porem o
                                            // centro dos eixos passa a se localizar no centro
                                            // da tela.

//   glOrtho (-(w/2), (w/2),-(h/2),(h/2), -1 ,1);   // Nesse caso, ficamos com a quantidade de pixels variavel,
                                                    // dependente da largura e altura da janela, e o
                                                    // centro dos eixos continua a se localizar no centro
                                                    // da tela.
    
   // muda para o modo GL_MODELVIEW (nao pretendemos alterar a projecao
   // quando estivermos desenhando na tela)
	glMatrixMode(GL_MODELVIEW);
}

/*
 * Funcao usada na funcao callback para controlar as teclas comuns (1 Byte) do teclado
 */
void keyboard(unsigned char key, int x, int y){
    switch (key) { // key - variavel que possui valor ASCII da tecla precionada
        case ESC: exit(EXIT_SUCCESS); break; //encerra o programa com sucesso
    }
}

/*
 *Funcao usada na fucao callback para controlar as teclas especiais (2 Byte) do teclado
 */
void keyboard_special(int key, int x, int y){
    switch(key){
      case GLUT_KEY_F1: R=0.0; G=0.0; B=1.0; break; // F1: muda a cor para azul
      case GLUT_KEY_F2: R=0.0; G=1.0; B=0.0; break; // F2: muda a cor para verde
      case GLUT_KEY_F3: R=1.0; G=0.0; B=0.0; break; // F3: muda a cor para vermelho
      default: break;
    }
    glutPostRedisplay();
}

/*
 * Funcao usada na funcao callback para desenhar na tela
 */

void display(void){
	//Limpa o Buffer de Cores e reinicia a matriz
    glClear(GL_COLOR_BUFFER_BIT); 
	glLoadIdentity();

    // Transformacoes usadas no triangulo com vertice esquerdo na origem dos eixos cartesianos
    glColor3f(R, G, B);

    //Pilastras
    
    glColor3f(1, 0.5, 0);
    
    glBegin(GL_QUADS);
    glVertex2f(100, 700); // Canto superior esquerdo quadrado 1
    glVertex2f(300, 700); // Canto superior direito quadrado 1
    glVertex2f(300, 0); // Canto inferior direito quadrado 1
    glVertex2f(100, 0); // Canto inferior esquerdo quadrado 1
	glEnd();
	
	// Copia e translação da torre da esquerda para a torre da direita
	glPushMatrix(); // Salva a matriz de transformação atual
	glTranslatef(800, 0, 0); // Translada para a posição desejada
	glBegin(GL_QUADS);
    glVertex2f(100, 700); // Canto superior esquerdo quadrado 1
    glVertex2f(300, 700); // Canto superior direito quadrado 1
    glVertex2f(300, 0); // Canto inferior direito quadrado 1
    glVertex2f(100, 0); // Canto inferior esquerdo quadrado 1
	glEnd();
	glPopMatrix(); // Restaura a matriz de transformação

	
	glBegin(GL_QUADS);
    glVertex2f(500, 800); // Canto superior esquerdo quadrado 1
    glVertex2f(700, 800); // Canto superior direito quadrado 1
    glVertex2f(700, 500); // Canto inferior direito quadrado 1
    glVertex2f(500, 500); // Canto inferior esquerdo quadrado 1
	glEnd();
	
	//Parede
	
    glColor3f(1, 1, 0);
	
	glBegin(GL_QUADS);
    glVertex2f(300, 500); // Canto superior esquerdo quadrado 1
    glVertex2f(900, 500); // Canto superior direito quadrado 1
    glVertex2f(900, 0); // Canto inferior direito quadrado 1
    glVertex2f(300, 0); // Canto inferior esquerdo quadrado 1
	glEnd();
	
	//Tetos
	
	glColor3f(1, 0, 0);
	
	glBegin(GL_TRIANGLES);
    glVertex2f(400, 700);
    glVertex2f(0, 700);
    glVertex2f(200, 900);
	glEnd();
	
	glBegin(GL_TRIANGLES);
    glVertex2f(1200, 700);
    glVertex2f(800, 700);
    glVertex2f(1000, 900);
	glEnd();
	
	glBegin(GL_TRIANGLES);
    glVertex2f(800, 800);
    glVertex2f(400, 800);
    glVertex2f(600, 1000);
	glEnd();
	
	//Mastros
	
	glColor3f(0, 0, 0);
	
	glBegin(GL_LINES);
    glVertex2f(200, 900); // Ponto inicial
    glVertex2f(200, 1100); // Ponto final
	glEnd();
	
	glBegin(GL_LINES);
    glVertex2f(1000, 900); // Ponto inicial
    glVertex2f(1000, 1100); // Ponto final
	glEnd();
	
	glBegin(GL_LINES);
    glVertex2f(600, 1000); // Ponto inicial
    glVertex2f(600, 1200); // Ponto final
	glEnd();

	//Porta
	
	glColor3f(0, 0, 0);
	
	glBegin(GL_QUADS);
    glVertex2f(500, 300); // Canto superior esquerdo quadrado 1
    glVertex2f(700, 300); // Canto superior direito quadrado 1
    glVertex2f(700, 0); // Canto inferior direito quadrado 1
    glVertex2f(500, 0); // Canto inferior esquerdo quadrado 1
	glEnd();
	
	//Bandeiras
	
	glColor3f(0, 1, 0);
	
	glBegin(GL_QUADS);
    glVertex2f(0, 1100); // Canto superior esquerdo quadrado 1
    glVertex2f(200, 1100); // Canto superior direito quadrado 1
    glVertex2f(200, 1000); // Canto inferior direito quadrado 1
    glVertex2f(0, 1000); // Canto inferior esquerdo quadrado 1
	glEnd();
	
	glBegin(GL_QUADS);
    glVertex2f(400, 1200); // Canto superior esquerdo quadrado 1
    glVertex2f(600, 1200); // Canto superior direito quadrado 1
    glVertex2f(600, 1100); // Canto inferior direito quadrado 1
    glVertex2f(400, 1100); // Canto inferior esquerdo quadrado 1
	glEnd();
	
	glBegin(GL_QUADS);
    glVertex2f(400, 1200); // Canto superior esquerdo quadrado 1
    glVertex2f(600, 1200); // Canto superior direito quadrado 1
    glVertex2f(600, 1100); // Canto inferior direito quadrado 1
    glVertex2f(400, 1100); // Canto inferior esquerdo quadrado 1
	glEnd();
	
	glBegin(GL_QUADS);
    glVertex2f(800, 1100); // Canto superior esquerdo quadrado 1
    glVertex2f(1000, 1100); // Canto superior direito quadrado 1
    glVertex2f(1000, 1000); // Canto inferior direito quadrado 1
    glVertex2f(800, 1000); // Canto inferior esquerdo quadrado 1
	glEnd();


    // Funcao criada para desenhar circulos
    glColor3f(0, 1, 1); // cor cinza para o círculo
    glPushMatrix(); // Salva a matriz de transformação atual
    glTranslatef(1000, 500, 0); // Translada para a posição desejada
    desenhaCirculo(70, 100, true); // raio 100, 50 linhas, preenchido
    glPopMatrix(); // Restaura a matriz de transformação
    
    glPushMatrix(); // Salva a matriz de transformação atual
    glTranslatef(200, 500, 0); // Translada para a posição desejada
    desenhaCirculo(70, 100, true); // raio 100, 50 linhas, preenchido
    glPopMatrix(); // Restaura a matriz de transformação
    
    glPushMatrix(); // Salva a matriz de transformação atual
    glTranslatef(600, 650, 0); // Translada para a posição desejada
    desenhaCirculo(70, 100, true); // raio 100, 50 linhas, preenchido
    glPopMatrix(); // Restaura a matriz de transformação
    
    glColor3f(1, 1, 0);
    glPushMatrix(); // Salva a matriz de transformação atual
    glTranslatef(600, 100, 0); // Translada para a posição desejada
    desenhaCirculo(30, 100, true); // raio 100, 50 linhas, preenchido
    glPopMatrix(); // Restaura a matriz de transformação
    
    glColor3f(0, 0, 0);
    glPushMatrix(); // Salva a matriz de transformação atual
    glTranslatef(600, 100, 0); // Translada para a posição desejada
    desenhaCirculo(20, 100, true); // raio 100, 50 linhas, preenchido
    glPopMatrix(); // Restaura a matriz de transformação
    
    glColor3f(1, 1, 0);
    glPushMatrix(); // Salva a matriz de transformação atual
    glTranslatef(600, 125, 0); // Translada para a posição desejada
    desenhaCirculo(15, 110, true); // raio 100, 50 linhas, preenchido
    glPopMatrix(); // Restaura a matriz de transformação
    
    //Quadradinhos Colunas
    
    glColor3f(1, 1, 0);
    
    glBegin(GL_QUADS);
    glVertex2f(210, 100); // Canto superior esquerdo quadrado 1
    glVertex2f(290, 100); // Canto superior direito quadrado 1
    glVertex2f(290,60); // Canto inferior direito quadrado 1
    glVertex2f(210, 60); // Canto inferior esquerdo quadrado 1
	glEnd();
    
    glBegin(GL_QUADS);
    glVertex2f(110, 200); // Canto superior esquerdo quadrado 1
    glVertex2f(190, 200); // Canto superior direito quadrado 1
    glVertex2f(190, 160); // Canto inferior direito quadrado 1
    glVertex2f(110, 160); // Canto inferior esquerdo quadrado 1
	glEnd();
	
	glBegin(GL_QUADS);
    glVertex2f(210, 300); // Canto superior esquerdo quadrado 1
    glVertex2f(290, 300); // Canto superior direito quadrado 1
    glVertex2f(290, 260); // Canto inferior direito quadrado 1
    glVertex2f(210, 260); // Canto inferior esquerdo quadrado 1
	glEnd();
	
	glBegin(GL_QUADS);
    glVertex2f(110, 400); // Canto superior esquerdo quadrado 1
    glVertex2f(190, 400); // Canto superior direito quadrado 1
    glVertex2f(190, 360); // Canto inferior direito quadrado 1
    glVertex2f(110, 360); // Canto inferior esquerdo quadrado 1
	glEnd();
	
	glBegin(GL_QUADS);
    glVertex2f(910, 100); // Canto superior esquerdo quadrado 1
    glVertex2f(990, 100); // Canto superior direito quadrado 1
    glVertex2f(990, 60); // Canto inferior direito quadrado 1
    glVertex2f(910, 60); // Canto inferior esquerdo quadrado 1
	glEnd();
	
	glBegin(GL_QUADS);
    glVertex2f(1010, 200); // Canto superior esquerdo quadrado 1
    glVertex2f(1090, 200); // Canto superior direito quadrado 1
    glVertex2f(1090, 160); // Canto inferior direito quadrado 1
    glVertex2f(1010, 160); // Canto inferior esquerdo quadrado 1
	glEnd();
	
	glBegin(GL_QUADS);
    glVertex2f(910, 300); // Canto superior esquerdo quadrado 1
    glVertex2f(990, 300); // Canto superior direito quadrado 1
    glVertex2f(990, 260); // Canto inferior direito quadrado 1
    glVertex2f(910, 260); // Canto inferior esquerdo quadrado 1
	glEnd();
	
	glBegin(GL_QUADS);
    glVertex2f(1010, 400); // Canto superior esquerdo quadrado 1
    glVertex2f(1090, 400); // Canto superior direito quadrado 1
    glVertex2f(1090, 360); // Canto inferior direito quadrado 1
    glVertex2f(1010, 360); // Canto inferior esquerdo quadrado 1
	glEnd();
	
	//Quadradinhos Parede
	
	glColor3f(1,0.5, 0);
	
	glBegin(GL_QUADS);
    glVertex2f(350, 100); // Canto superior esquerdo quadrado 1
    glVertex2f(450, 100); // Canto superior direito quadrado 1
    glVertex2f(450, 150); // Canto inferior direito quadrado 1
    glVertex2f(350, 150); // Canto inferior esquerdo quadrado 1
	glEnd();
	
	glBegin(GL_QUADS);
	glVertex2f(750, 100); // Canto superior esquerdo quadrado 2 (do outro lado da porta)
	glVertex2f(850, 100); // Canto superior direito quadrado 2 (do outro lado da porta)
	glVertex2f(850, 150); // Canto inferior direito quadrado 2 (do outro lado da porta)
	glVertex2f(750, 150); // Canto inferior esquerdo quadrado 2 (do outro lado da porta)
	glEnd();
	
	glBegin(GL_QUADS);
	glVertex2f(400, 400); // Canto superior esquerdo quadrado diagonal
	glVertex2f(525, 400); // Canto superior direito quadrado diagonal
	glVertex2f(525, 350); // Canto inferior esquerdo quadrado diagonal
	glVertex2f(400, 350); // Canto inferior direito quadrado diagonal
	glEnd();
	
	glBegin(GL_QUADS);
	glVertex2f(675, 400); // Canto superior esquerdo quadrado diagonal
	glVertex2f(800, 400); // Canto superior direito quadrado diagonal
	glVertex2f(800, 350); // Canto inferior esquerdo quadrado diagonal
	glVertex2f(675, 350); // Canto inferior direito quadrado diagonal
	glEnd();
	
    glFlush(); // manda o OpenGl renderizar as primitivas

}

