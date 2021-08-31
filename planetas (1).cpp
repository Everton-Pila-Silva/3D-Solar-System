/********************* Projeto de Computação gráfica *************************/
/********************* Criado Por Everton Pila Silva *************************/

#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <stdio.h>
#include <windows.h>



/*
********************************** Instruções de uso **************************************


				ao clicar a tecla (y) faz os planetas girarem em volta do sol
				
				clicar em (d) o planeta gira em torno de si mesmo. (irá girar apenas após clicar em y)
				
				use o mouse para dar zoom in ou zoon out, com os botões esquerdo ou direito.



****************************************************************************************

*/



static int year[8], day = 0, movimento= 0;

GLint win_width, win_height;
GLuint DataPos, imageSize;
GLsizei Width,Height;
GLuint texture_id[1];
GLfloat xf, yf,win, aspecto, angle, fAspect, h, w;
 
void LoadBMP(char *filename) {
    #define SAIR {fclose(fp_arquivo); return ;}
    #define CTOI(C) (*(int*)&C)
 
    GLubyte *image;
    GLubyte Header[0x54];
 
    FILE * fp_arquivo = fopen(filename,"rb");
 
    if (fread(Header,1,0x36,fp_arquivo)!=0x36)
    SAIR;
 
    Width = CTOI(Header[0x12]);
    Height = CTOI(Header[0x16]);
    ( CTOI(Header[0x0A]) == 0 ) ? ( DataPos=0x36 ) : ( DataPos = CTOI(Header[0x0A]) );
    imageSize=Width*Height*3;
 
    image = (GLubyte *) malloc ( imageSize );
    int retorno;
    retorno = fread(image,1,imageSize,fp_arquivo);
 
    int t, i;
    for ( i = 0; i < imageSize; i += 3 ) {
        t = image[i];
        image[i] = image[i+2];
        image[i+2] = t;
    }
 
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);
    glTexEnvf ( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE );
 
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, Width, Height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
    fclose (fp_arquivo);
    free (image);
    return ;
}

void init(void) 
{
   	GLfloat luzAmbiente[4]= { 1.0, 1.0, 0.0, 1.0 };
	GLfloat luzDifusa[4]= { 1.0, 1.0, 0.0, 1.0 };	   // "cor"
	GLfloat luzEspecular[4]= { 50.0 };// "brilho"
	GLfloat posicaoLuz[4]= { 0.0, 1.0, 0.0, 1.0};

	// Capacidade de brilho do material
	GLfloat especularidade[4]={1.0,1.0,1.0,1.0};
	GLint especMaterial = 10;
	glMateriali(GL_FRONT_AND_BACK,GL_SHININESS,especMaterial);

	// Ativa o uso da luz ambiente
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, luzAmbiente);
	glLightfv(GL_LIGHT0, GL_SPECULAR, luzEspecular );
	glLightfv(GL_LIGHT0, GL_POSITION, posicaoLuz );

	// Habilita o modelo de colorizaÃ§Ã£o de Gouraud
	glShadeModel(GL_SMOOTH);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_DEPTH_TEST);
	
	angle=45;
}
void display(void)
{
	GLUquadric *qobj = gluNewQuadric();
	gluQuadricTexture(qobj,GL_TRUE);

   glClear (GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
   glEnable (GL_TEXTURE_2D);
   
    /*********************** sol *****************************/
   			glPushMatrix();
    glBindTexture ( GL_TEXTURE_2D, texture_id[0] ); 	
	LoadBMP("sun.bmp");
   	gluSphere(qobj, 1.5, 520, 160);
    		glPopMatrix();
  
   
   /*********************** mercurio *****************************/
    		glPushMatrix();
    glRotatef ((GLfloat) year[0], 0.0, 1.0, 0.0);//roda a redor do sol
   glTranslatef (2.0, 0.0, 0.0);
   glRotatef ((GLfloat) day, 0.0, 1.0, 0.0);
    glBindTexture ( GL_TEXTURE_2D, texture_id[0] ); 	
	LoadBMP("mercurio.bmp");
   	gluSphere(qobj, 0.2, 50, 100);
     		glPopMatrix();
 
 /*********************** venus *****************************/
 			glPushMatrix();
    glRotatef ((GLfloat) year[1], 0.0, 1.0, 0.0);//segura o planeta
	glTranslatef (4.0, 0.0, 0.0); 
  	 glRotatef ((GLfloat) day, 0.0, 1.0, 0.0); //gira o planeta
    glBindTexture ( GL_TEXTURE_2D, texture_id[0] ); 	
	LoadBMP("venus.bmp");
   	gluSphere(qobj,0.3, 50, 100);
     		glPopMatrix();
  
/*********************** terra *****************************/ 
			glPushMatrix();
    glRotatef ((GLfloat) year[2], 0.0, 1.0, 0.0);//segura o planeta
	glTranslatef (8.0, 0.0, 0.0); 
   glRotatef ((GLfloat) day, 0.0, 1.0, 0.0); //gira o planeta
    glBindTexture ( GL_TEXTURE_2D, texture_id[0] ); 	
	LoadBMP("terra.bmp");
   	gluSphere(qobj,0.5, 50, 100);
    		 glPopMatrix();
  

/*********************** marte *****************************/ 
			glPushMatrix();
    glRotatef ((GLfloat) year[3], 0.0, 1.0, 0.0);//segura o planeta
	glTranslatef (12.0, 0.0, 0.0);
   glRotatef ((GLfloat) day, 0.0, 1.0, 0.0); //gira o planeta
    glBindTexture ( GL_TEXTURE_2D, texture_id[0] ); 	
	LoadBMP("marte.bmp");
   	gluSphere(qobj,0.3, 50, 100);
    		 glPopMatrix();
  

/*********************** jupter *****************************/ 
				glPushMatrix();
       glRotatef ((GLfloat) year[4], 0.0, 1.0, 0.0);//segura o planeta
	glTranslatef (16.0, 0.0, 0.0);
   glRotatef ((GLfloat) day, 0.0, 1.0, 0.0); //gira o planeta
    glBindTexture ( GL_TEXTURE_2D, texture_id[0] ); 	
	LoadBMP("jupter.bmp");
   	gluSphere(qobj,0.6, 50, 100);
     			glPopMatrix();
   

/*********************** saturno *****************************/
				glPushMatrix();
       glRotatef ((GLfloat) year[5], 0.0, 1.0, 0.0);//segura o planeta
	glTranslatef (20.0, 0.0, 0.0); 
   glRotatef ((GLfloat) day, 0.0, 1.0, 0.0); //gira o planeta
    glBindTexture ( GL_TEXTURE_2D, texture_id[0] ); 	
	LoadBMP("saturno.bmp");
   	gluSphere(qobj,0.4, 50, 100);
     			glPopMatrix();
   
  
/*********************** urano *****************************/ 
					glPushMatrix();
       glRotatef ((GLfloat) year[6], 0.0, 1.0, 0.0);//segura o planeta
	glTranslatef (24.0, 0.0, 0.0);   
   glRotatef ((GLfloat) day, 0.0, 1.0, 0.0); //gira o planeta
    glBindTexture ( GL_TEXTURE_2D, texture_id[0] ); 	
	LoadBMP("urano.bmp");
   	gluSphere(qobj,0.2, 50, 100);
     				glPopMatrix();
   

/*********************** netuno *****************************/
				glPushMatrix();
       glRotatef ((GLfloat) year[7], 0.0, 1.0, 0.0);//segura o planeta
	glTranslatef (26.0, 0.0, 0.0);
   glRotatef ((GLfloat) day, 0.0, 1.0, 0.0); //gira o planeta
    glBindTexture ( GL_TEXTURE_2D, texture_id[0] ); 	
	LoadBMP("netuno.bmp");
   	gluSphere(qobj,0.3, 50, 100);
  			 glPopMatrix();
  			 
/*********************** plutão sqn *****************************/
   glutSwapBuffers();
   
}
void Timer(int value){

if(movimento==2){
	year[0]=year[0]+2;
	year[1]=year[1]+3;
	year[2]=year[2]+4;
	year[3]=year[3]+1;
	year[4]=year[4]+3;
	year[5]=year[5]+4;
	year[6]=year[6]+1;
	year[7]=year[7]+3;
	day= day + 5;
	glutPostRedisplay();
}
	glutTimerFunc(30,Timer,1);
}


void EspecificaParametrosVisualizacao(void)
{

   glMatrixMode (GL_PROJECTION);
   glLoadIdentity ();
   gluPerspective(angle, fAspect, 1.0, 20.0);
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
   gluLookAt (0.0, 0.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
}

// Função callback chamada quando o tamanho da janela é alterado 
void AlteraTamanhoJanela(GLsizei w, GLsizei h)
{
	// Para previnir uma divisão por zero
	if ( h == 0 ) h = 1;

	// Especifica o tamanho da viewport
	glViewport(0, 0, w, h);
 
	// Calcula a correção de aspecto
	fAspect = (GLfloat)w/(GLfloat)h;

	EspecificaParametrosVisualizacao();
}

void keyboard (unsigned char key, int x, int y)
{
   switch (key) {
      case 'd':
         day = day % 360;
         glutPostRedisplay();
         break;
      
     case 'y':
         year[0] = year[0] % 360;
          year[1] = year[1] % 360;
           year[2] = year[2] % 360;
            year[3] = year[3] % 360;
             year[4] = year[4] % 360;
              year[5] = year[5] % 360;
               year[6] = year[6] % 360;
                year[7] = year[7] % 360;
                 year[8] = year[8] % 360;
         movimento=2;
         glutPostRedisplay();
         break;
      default:
         break;
   }
}
void GerenciaMouse(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON)
		if (state == GLUT_DOWN) {  // Zoom-in
			if (angle >= 10) angle -= 10;
		}
	if (button == GLUT_RIGHT_BUTTON)
		if (state == GLUT_DOWN) {  // Zoom-out
			if (angle <= 130) angle += 10;
		}
	EspecificaParametrosVisualizacao();
	glutPostRedisplay();
}

int main(int argc, char** argv)
{
   glutInit(&argc, argv);
   glutInitDisplayMode (GLUT_DOUBLE |GLUT_DEPTH| GLUT_RGB);
   glutInitWindowSize (900, 500); 
   glutInitWindowPosition (100, 100);
   glutCreateWindow (argv[0]);
   init ();
   glutDisplayFunc(display); 
  glutReshapeFunc(AlteraTamanhoJanela);
   glutKeyboardFunc(keyboard);
	glutMouseFunc(GerenciaMouse);
   glutTimerFunc(30, Timer, 1);
   glutMainLoop();
   return 0;
}
