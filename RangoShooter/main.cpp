#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <cmath>
#include <time.h>

#ifdef __APPLE__
#include <GLUT/glut.h>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#else
#include <GL/glut.h>
#include <GL/glu.h>
#include <GL/gl.h>
#endif

#include "loader.h"
#include "trgt_crct.h"
#include "text3d.h"
#include "menu.h"

#include <IL/il.h>
#include <IL/ilu.h>
#include <IL/ilut.h>

//to map image filenames to textureIds
#include <string.h>
#include <map>

#define aisgl_min(x,y) (x<y?x:y)
#define aisgl_max(x,y) (y>x?y:x)
#define TRUE                1
#define FALSE               0
#define UP                  1
#define DOWN                0
#define MAX_LIV				3
#define LEVEL_TIME			3000
#define PI 3.141592654
#define SENSITIVITY 0.04149 //set by me to be almost equal to the mouse movement (yeah right should be computed after distance of the quad)
#define NMONKEYS 10
#define BULLET_NUMBER 6

GLuint scene_list_target;

struct myScene level1_scene, level2_scene, level3_scene,target_scene; 

// angle of rotation (non static)
float  xpos = 15, ypos = 0, zpos = 0, xrot = 3, yrot = 0, lastx, lasty;
float cRadius = 10.0f; // our radius distance from our character

float windowWidth = 900, windowHeight = 600;
float middleX = windowWidth / 2, middleY = windowHeight / 2;
float relativeX, relativeY;
float flag = 0;
int score;


//VARIABILI AGGIUNTE
motion m[18];
m_time t;
level livelli;
indice_personaggi ch_index;

float zoom=5.2f;
int livello=1;
int pos,durata=-200;
int ch;
int stop_level=0;

GLfloat LightAmbient[]= { 0.5f, 0.5f, 0.5f, 1.0f };
GLfloat LightDiffuse[]= { 1.0f, 1.0f, 1.0f, 1.0f };
GLfloat LightPosition[]= { 0.0f, 0.0f, 15.0f, 1.0f };

struct gun {
    struct myScene pistola;
    int bullet_number;
    struct myScene proiettile;
};

struct gun gun0;
bool first;

// need an array for the skybox - using DevIL

GLuint skyboxArray[5];


// ---------------------------------------------------------------------------
void mouseMovement(int x, int y)
{
    int diffx=x-lastx; //check the difference between the current x and the last x position
    int diffy=y-lasty; //check the difference between the current y and the last y position
    lastx=x; //set lastx to the current x position
    lasty=y; //set lasty to the current y position
    relativeX += (float) diffx;
    relativeY += (float) diffy;
}


// ---------------------------------------------------------------------------
void drawHUD()
{
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    glOrtho(0.0, windowWidth, windowHeight, 0.0, -1.0, 10.0);
    glMatrixMode(GL_MODELVIEW);
    //glPushMatrix();        ----Not sure if I need this
    glLoadIdentity();
    glDisable(GL_CULL_FACE);
    
    glClear(GL_DEPTH_BUFFER_BIT);
    
    // it create a "over HUD" - a white rectangle at the top
    
    glBegin(GL_QUADS);
    glColor3f(1.0f, 0.0f, 0.0);
    glVertex2f(0.0, 0.0);
    glVertex2f(windowWidth, 0.0);
    glVertex2f(windowWidth, 30.0);
    glVertex2f(0.0, 30.0);
    glEnd();
    
    // Making sure we can render 3d again
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
    //glPopMatrix();        ----and this?

}

// ----------------------------------------------------------------------------
void reload ()
{
    /*
    if (score > 5) {
        gun0.bullet_number = BULLET_NUMBER;
        score -= 5;
    }
    */
    
    gun0.bullet_number = BULLET_NUMBER;
    
    return;
}

// ----------------------------------------------------------------------------
void newGame ()
{
    int j;
    
    for(j=0; j<18; j++){
        m[j]=reset_motion(m[j]);
    }
    
	t=reset_time(t);
    
    zoom=5.2f;
    livello=1;
    
    stop_level=0;
    
    // for the score
    
    score = 0;
    
    first = TRUE;
    
    return;
}

// ----------------------------------------------------------------------------
void changeLevel(int move)
{
    
    if (move == 1){
        // UP!
        if(livello<MAX_LIV){
            
            for(int i=(livello*6);i<6+(livello*6);i++){
                m[i]=reset_motion(m[i]);
            }
            
            for(int i=((livello-1)*6);i<6+((livello-1)*6);i++){
                m[i].stato=2;
            }
            
            livello++;
            
        }
    } else {
        // DOWN!
        if(livello!=1){
            for(int i=((livello-2)*6);i<6+((livello-2)*6);i++){
                m[i]=reset_motion(m[i]);
            }
            for(int i=((livello-1)*6);i<6+((livello-1)*6);i++){
                m[i].stato=2;
            }
            
            livello--;
        }
    }
    
    if(livello==3){
        zoom=3.0f;
    } else {
        zoom=5.2f;
    }
    
}


// ----------------------------------------------------------------------------
//Called when the window is resized
void handleResize(int w, int h)
{
	//Tell OpenGL how to convert from coordinates to pixel values
	glViewport(0, 0, w, h);
	
	glMatrixMode(GL_PROJECTION); //Switch to setting the camera perspective
	
	//Set the camera perspective
	glLoadIdentity(); //Reset the camera
	gluPerspective(45.0,                  //The camera angle
				   (double)w / (double)h, //The width-to-height ratio
				   1.0,                   //The near z clipping coordinate
				   200.0);                //The far z clipping coordinate
}


// ----------------------------------------------------------------------------
//Called when a key is pressed
void handleKeypress(unsigned char key, //The key that was pressed
					int x, int y)
{    //The current mouse coordinates
    float xrotrad, yrotrad;
	switch (key) {
		case 'w':
            yrotrad = (yrot / 180 * 3.141592654f);
            xrotrad = (xrot / 180 * 3.141592654f);
            xpos += float(sin(yrotrad)) ;
            zpos -= float(cos(yrotrad)) ;
            ypos -= float(sin(xrotrad)) ;
            break;
        case 's':
            yrotrad = (yrot / 180 * 3.141592654f);
            xrotrad = (xrot / 180 * 3.141592654f);
            xpos -= float(sin(yrotrad));
            zpos += float(cos(yrotrad)) ;
            ypos += float(sin(xrotrad));
            break;
        case 'd':
            yrotrad = (yrot / 180 * 3.141592654f);
            xpos += float(cos(yrotrad)) * 0.2;
            zpos += float(sin(yrotrad)) * 0.2;
            break;
        case 'a':
            yrotrad = (yrot / 180 * 3.141592654f);
            xpos -= float(cos(yrotrad)) * 0.2;
            zpos -= float(sin(yrotrad)) * 0.2;
            break;
        case 'n':
            newGame();
            break;
        case 'r':
            reload();
            break;
        case 'p':
            // restart the level 
			if(stop_level==1){
                for(int i=((livello-1)*6);i<6+((livello-1)*6);i++)
                    m[i]=reset_motion(m[i]);
                for(int i=0;i<10;i++)livelli.posizione[i].check=0;
                pos=scegli_pos(livello,livelli);
                stop_level=0;
			}
            break;
		case 'o':
            // stop the level
			if(stop_level==0){
				for(int i=((livello-1)*6);i<6+((livello-1)*6);i++)m[i].stato=2;
				stop_level=1;
			}
            break;
        case '+':
            //t.v+=0.01;
            zoom+=0.2;
            break;
		case '-':
            //t.v-=0.01;
            zoom-=0.2;
            break;
		case 'x':
            changeLevel(UP);
            break;
		case 'z':
            changeLevel(DOWN);
            break;
		case 27: //Escape key
			exit(0); //Exit the program
	}
}


// ----------------------------------------------------------------------------

void drawBullet()
{
    int i;
    float posX = 0.0f;
    
    for (i = 0; i < gun0.bullet_number; i++) {
        glPushMatrix();
        glScalef(0.05,0.05,0.05); //rimpiccioliamo i proiettili
        glTranslatef(5.f+posX, -6.5f, -23.0f);
        recursive_render(gun0.proiettile.scene,gun0.proiettile.scene->mRootNode, 1.0);
        posX += 1.0f;
        glPopMatrix();
        
    }
    
    return;
}

// ----------------------------------------------------------------------------

void drawGun ()
{
    glPushMatrix();
    // first the "movement" rotations
    float shoulder = -4.1 * fabs(gun0.pistola.scene_max.z-gun0.pistola.scene_min.z);
    float normX = relativeX/middleX;
    float normY = relativeY/middleY;
    float hypX = sqrtf(shoulder*shoulder + normX*normX);
    float hypY = sqrtf(shoulder*shoulder + normY*normY);
    float radY = asinf(normY/hypY);
    float radX = asinf(normX/hypX);
    //glTranslatef(0.f, shoulder, shoulder);
	glScalef(0.05,0.05,0.05); //la rimpiccioliamo perche' e' enorme
    glTranslatef(0.f, 5.f, shoulder);
    float rotX, rotY;
    rotX = -(radX*180)/PI;
    rotY = -(radY*180)/PI;
    glRotatef(rotY*0.6, 1.0f, 0.0f, 0.f);
    glRotatef(rotX*2.3, 0.0f, 1.0f, 0.f);
    glTranslatef(0.f, -5.f, -shoulder);
    //glTranslatef(0.f, -shoulder, -shoulder);
    // and then "position" tra&rot
    
	glTranslatef(0.f, -7.f, -28.0f);
    glRotatef(89.0,0.0,1.0,0.0);
    glRotatef(8.0,0.0,0.0,1.0);
    recursive_render(gun0.pistola.scene,gun0.pistola.scene->mRootNode, 1.0);
    
    glPopMatrix();
    
}

// ----------------------------------------------------------------------------

void drawScope ()
{
    glPushMatrix();
    glEnable(GL_COLOR_MATERIAL);
    glTranslatef(relativeX*SENSITIVITY,-relativeY*SENSITIVITY,0.0);
    glColor3f(1.f, 0.f, 1.f);
    glBegin(GL_LINE_LOOP);
    
    //Trapezoid
    glVertex3f(-0.5f, -0.5f, -30.0f);
    glVertex3f(0.5f, -0.5f, -30.0f);
    glVertex3f(0.5f, 0.5f, -30.0f);
    glVertex3f(-0.5f, 0.5f, -30.0f);
    
    glEnd();
    
    glDisable(GL_COLOR_MATERIAL);
    
    glPopMatrix();
}

// ----------------------------------------------------------------------------
void drawScore ()
{
    
    std::string str = "Score = ";
    
    char string_score[5]; // enough to hold all numbers up to 64-bits
    sprintf(string_score, "%d", score);
    str += string_score;
    /*
    str += "\n Mouse X:";
    char mouse_X[5]; // enough to hold all numbers up to 64-bits
    sprintf(mouse_X, "%.1f", lastx);
    str += mouse_X;
    
    str += "\n Mouse Y:";
    char mouse_Y[5]; // enough to hold all numbers up to 64-bits
    sprintf(mouse_Y, "%.1f", windowHeight-lasty);
    str += mouse_Y;
    */
    glPushMatrix();
    
    glEnable(GL_COLOR_MATERIAL);
    glColor3f(0.f, 0.3f, 1.f);
    
	//Draw instructions
	glTranslatef(-10.f, -10.f, -30.0f);
    // to this function i pass the hAlign, vAligh, Depth
	t3dDraw3D(str, 0.0, -0.5, 0.3f);
    
    glDisable(GL_COLOR_MATERIAL);
    
    glPopMatrix();
    
    return;
}


// ----------------------------------------------------------------------------
void drawSkybox(void)
{
    
    // Center the Skybox around the given x,y,z position - here i put the center of the scene, and a far Z
    // i want to modify it so the Z is a given global variable that stores the farest Z
    //int conv_success;
    
    float backgroundX, backgroundY, backgroundZ;
    float foregroundX, foregroundY, foregroundZ;
    
    backgroundX = 0.8f;
    backgroundY = 0.5f;
    backgroundZ = 5.f;
    foregroundX = 0.8f;
    foregroundY = 0.5f;
    foregroundZ = 0.5f;
    
    glPushMatrix();
    glEnable(GL_TEXTURE_2D);
    glDisable(GL_DEPTH_TEST);
    glEnable(GL_COLOR_MATERIAL);
    glColor3f(250.f, 250.f, 250.f);
    
    
    // NB: i don't need the back one
    
	// Draw Front side
    glBindTexture(GL_TEXTURE_2D, skyboxArray[0]);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0, 0.0); glVertex3f(backgroundX, backgroundY, -backgroundZ); // Top Right
    glTexCoord2f(0.0, 1.0); glVertex3f(-backgroundX, backgroundY, -backgroundZ); // Top Left
    glTexCoord2f(1.0, 1.0); glVertex3f(-backgroundX, -backgroundY, -backgroundZ); // Bottom Left
    glTexCoord2f(1.0, 0.0); glVertex3f(backgroundX, -backgroundY, -backgroundZ); // Bottom Right
	glEnd();
    
	// Draw Left side
    glBindTexture(GL_TEXTURE_2D, skyboxArray[1]);
	glBegin(GL_QUADS);
    glTexCoord2f(0.0, 0.0); glVertex3f(-backgroundX, backgroundY, -backgroundZ); // Top Right
    glTexCoord2f(0.0, 1.0); glVertex3f(-foregroundX, foregroundY, foregroundZ); // Top Left
    glTexCoord2f(1.0, 1.0); glVertex3f(-foregroundX, -foregroundY, foregroundZ); // Bottom Left
    glTexCoord2f(1.0, 0.0); glVertex3f(-backgroundX, -backgroundY, -backgroundZ); // Bottom Right
	glEnd();
    
	// Draw Right side
    glBindTexture(GL_TEXTURE_2D, skyboxArray[2]);
	glBegin(GL_QUADS);
    glTexCoord2f(0.0, 0.0); glVertex3f(foregroundX, foregroundY, foregroundZ); // Top Right
    glTexCoord2f(0.0, 1.0); glVertex3f(backgroundX, backgroundY, -backgroundZ); // Top Left
    glTexCoord2f(1.0, 1.0); glVertex3f(backgroundX, -backgroundY, -backgroundZ); // Bottom Left
    glTexCoord2f(1.0, 0.0); glVertex3f(foregroundX, -foregroundY, foregroundZ); // Bottom Right
	glEnd();
    
	// Draw Up side
    glBindTexture(GL_TEXTURE_2D, skyboxArray[3]);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0, 0.0); glVertex3f(foregroundX, foregroundY, foregroundZ); // Top Right
    glTexCoord2f(0.0, 1.0); glVertex3f(-foregroundX, foregroundY, foregroundZ); // Top Left
    glTexCoord2f(1.0, 1.0); glVertex3f(-backgroundX, backgroundY, -backgroundZ); // Bottom Left
    glTexCoord2f(1.0, 0.0); glVertex3f(backgroundX, backgroundY, -backgroundZ); // Bottom Right
	glEnd();
    
	// Draw Down side
    glBindTexture(GL_TEXTURE_2D, skyboxArray[4]);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0, 0.0); glVertex3f(backgroundX, -backgroundY, -backgroundZ); // Top Right
    glTexCoord2f(0.0, 1.0); glVertex3f(-backgroundX, -backgroundY, -backgroundZ); // Top Left
    glTexCoord2f(1.0, 1.0); glVertex3f(-foregroundX, -foregroundY,foregroundZ); // Bottom Left
    glTexCoord2f(1.0, 0.0); glVertex3f(foregroundX, -foregroundY,foregroundZ); // Bottom Right
	glEnd();
    
    glDisable(GL_COLOR_MATERIAL);
    glDisable(GL_TEXTURE_2D);
    glEnable(GL_DEPTH_TEST);
    //glClear(GL_DEPTH_BUFFER_BIT);
    
    glPopMatrix();
    
    return;
}



// ----------------------------------------------------------------------------
GLuint toGLTexture (const char* path)
{
    // this will be a badass function
    ILuint singleimg;
    ILboolean success;
    GLuint textureID;
    
    ilGenImages(1, &singleimg); /* Generation of one image name */
    ilBindImage(singleimg); /* Binding of image name */
    success = ilLoadImage(path); /* Loading of image "image.jpg" */
    if (success) /* If no error occured: */
    {
        success = ilConvertImage(IL_RGBA, IL_UNSIGNED_BYTE); /* Convert every colour component into
                                                             unsigned byte. If your image contains alpha channel you can replace IL_RGB with IL_RGBA */
        if (!success)
        {
            /* Error occured */
            return -1;
        }
        glGenTextures(1, &textureID); /* Texture name generation */
        glBindTexture(GL_TEXTURE_2D, textureID); /* Binding of texture name */
        // Set texture clamping method
		
		//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE); //commentate, nella versione di windows di openGL non c'e' clamp_to_edge
		//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST); //Puts a magnification filter on the texture
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST); //Puts a minification filter on the texture
        
        glTexImage2D(GL_TEXTURE_2D, 0, ilGetInteger(IL_IMAGE_BPP), ilGetInteger(IL_IMAGE_WIDTH),
                     ilGetInteger(IL_IMAGE_HEIGHT), 0, ilGetInteger(IL_IMAGE_FORMAT), GL_UNSIGNED_BYTE,
                     ilGetData()); /* Texture specification */
    }
    else
    {
        /* Error occured */
        return -1;
    }
    ilDeleteImages(1, &singleimg); /* Because we have already copied image data into texture data
                                    we can release memory used by image. */
    
    return textureID;
}

// ---------------------------------------------------------------------------
GLuint menuImg = 0;

void display(void)
{

	float tmp;
		
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glDisable(GL_FOG);

    drawSkybox();
    drawHUD();
    drawScope();
	drawGun();
	drawBullet();
    drawScore();

	
	//Fog----------------------

	glFogi(GL_FOG_MODE, GL_LINEAR);        // Fog Mode
	GLfloat fogColor[4]= {0.6f, 0.5f, 0.3f, 1.0f};
	glFogfv(GL_FOG_COLOR, fogColor);            // Set Fog Color
	glFogf(GL_FOG_DENSITY, 0.25f);              // How Dense Will The Fog Be
	glHint(GL_FOG_HINT, GL_DONT_CARE);          // Fog Hint Value
	glFogf(GL_FOG_START, 1.0f);             // Fog Start Depth
	glFogf(GL_FOG_END, 5.0f);               // Fog End Depth
	glEnable(GL_FOG);                   // Enables GL_FOG

	//-------------------------
    
    glPushMatrix();
    gluLookAt(0.f,0.f,3.f,0.f,0.f,-5.f,0.f,1.f,0.f);

	// scale the whole asset to fit into our view frustum
	// scale the whole asset to fit into our view frustum
	if(livello==1){
	tmp = level1_scene.scene_max.x-level1_scene.scene_min.x;
	tmp = aisgl_max(level1_scene.scene_max.y - level1_scene.scene_min.y,tmp);
	tmp = aisgl_max(level1_scene.scene_max.z - level1_scene.scene_min.z,tmp);
	}
	if(livello==2){
	tmp = level2_scene.scene_max.x-level2_scene.scene_min.x;
	tmp = aisgl_max(level2_scene.scene_max.y - level2_scene.scene_min.y,tmp);
	tmp = aisgl_max(level2_scene.scene_max.z - level2_scene.scene_min.z,tmp);
	}
	if(livello==3){
	tmp = level3_scene.scene_max.x-level3_scene.scene_min.x;
	tmp = aisgl_max(level3_scene.scene_max.y - level3_scene.scene_min.y,tmp);
	tmp = aisgl_max(level3_scene.scene_max.z - level3_scene.scene_min.z,tmp);
	}
	tmp = zoom / tmp;
	glScalef(tmp, tmp, tmp);
    
    glTranslated(-xpos,0.0f,-zpos); //translate the screen to the position of our camera
    
	
	if(first == TRUE){
		scene_list_target=glGenLists(10);
		lista_target(scene_list_target,target_scene.scene);
		pos=scegli_pos(livello,livelli);
		first = FALSE;
	}
	
	if(m[pos].stato==2){
        m[pos]=reset_motion(m[pos]);
        pos=scegli_pos(livello,livelli);
    }
        
	ch=render_target(scene_list_target,pos,livelli,m[pos],ch,t.v);
     renderLevel(level1_scene.scene,level2_scene.scene,level3_scene.scene, livello);
    
	if (menuImg == 0) menuImg = toGLTexture("./dati/models/textures/menu_principale.png");
	DrawMenu(0,0,menuImg,true);

	m[pos]=scegli_mov(m[pos],livelli,pos,t.tempoi, t.v, ch_index,ch);
	
	glutPostRedisplay ();
    
	t=count_time(t);
    
    glPopMatrix();
    
	glutSwapBuffers();
    
}

// ---------------------------------------------------------------------------

void levelChanger(void)
{
    if (score > 100) {
        changeLevel(UP);
        score = 0;
    }
    return;
}

// ----------------------------------------------------------------------------
int target_hit(GLint hits, GLuint *names)
{
 	int i;
    
    int number, minZ, maxZ, name;
    
 	/*
     For each hit in the buffer are allocated 4 bytes:
     1. Number of hits selected (always one,
     beacuse when we draw each object
     we use glLoadName, so we replace the
     prevous name in the stack)
     2. Min Z
     3. Max Z
     4. Name of the hit (glLoadName)
    */
    
 	for (i = 0; i < hits; i++){
        
        number = (GLubyte)names[i * 4];
        minZ = (GLubyte)names[i * 4 + 1];
        maxZ = (GLubyte)names[i * 4 + 2];
        name = (GLubyte)names[i * 4 + 3];
        
        if ( name > 100 && name < 150 ) {
            // right now it "force" this return just so i'm sure it will "attack" a target
            return name;
        }
    }
    
    return -1;
    
}

// ----------------------------------------------------------------------------
void collisionCurse (void)
{
    int hitten, id;
    
    float fittX, fittY;
    
    fittX = lastx;
    fittY = windowHeight-lasty;
    
    GLuint buff[64] = {0};
 	GLint hits, view[4];
    
 	
    //This choose the buffer where store the values for the selection data
 	glSelectBuffer(64, buff);
    
 	
    //This retrieve info about the viewport
    
 	glGetIntegerv(GL_VIEWPORT, view);
    
 	
    //Switching in selecton mode
 	glRenderMode(GL_SELECT);
    
    //Clearing the name's stack
    //This stack contains all the info about the objects
 	glInitNames();
    
 	
    //Now fill the stack with one element (or glLoadName will generate an error)
 	glPushName(0);
    
 	
    //Now modify the vieving volume, restricting selection area around the cursor
 	glMatrixMode(GL_PROJECTION);
 	glPushMatrix();
    glLoadIdentity();
    
    
    //restrict the draw to an area around the cursor
    gluPickMatrix(fittX, fittY, 500.0, 500.0, view);
    gluPerspective(60, 1.0, 0.0001, 1000.0);
    
    
    //Draw the objects onto the screen
    glMatrixMode(GL_MODELVIEW);
    
    //draw only the names in the stack, and fill the array
    
    glutSwapBuffers();
    display();
    
    
    //Do you remeber? We do pushMatrix in PROJECTION mode
    glMatrixMode(GL_PROJECTION);
 	glPopMatrix();
    
 	
    //get number of objects drawed in that area
    //and return to render mode

 	hits = glRenderMode(GL_RENDER);
    
    id  = target_hit(hits, buff);
    
    if (id != -1 ){
        hitten = id - 100;
        if(livelli.posizione[hitten].movimento==1){
            m[hitten].stato=0;
            m[hitten].count=2;
            m[hitten].temp_rel=t.tempoi-1;
        }else if(livelli.posizione[hitten].movimento==2){
            m[hitten].stato=2;
        }    
        score += ch_index.character[ch].punteggio;
        levelChanger();
    }
    
 	glMatrixMode(GL_MODELVIEW);
    
    return;
}


// ----------------------------------------------------------------------------
void handleMouseKeypress(int key, int state, int x, int y)
{
    switch (key) {
		case GLUT_LEFT_BUTTON:
            if (state == 0){
                gun0.bullet_number--;
                if (gun0.bullet_number > 0) {
                    collisionCurse();
                }
            }
            break;
    }
}


// ----------------------------------------------------------------------------
void initSkybox ()
{
    
    if (1 != 1){
        skyboxArray[0] = toGLTexture("./dati/skybox_bello/front.jpg");
        skyboxArray[1] = toGLTexture("./dati/skybox_bello/right.jpg");
        skyboxArray[2] = toGLTexture("./dati/skybox_bello/left.jpg");
        skyboxArray[3] = toGLTexture("./dati/skybox_bello/up.jpg");
        skyboxArray[4] = toGLTexture("./dati/skybox_bello/down.jpg");
    } else {
        skyboxArray[0] = toGLTexture("./dati/skybox/front.jpg");
        skyboxArray[1] = toGLTexture("./dati/skybox/left.jpg");
        skyboxArray[2] = toGLTexture("./dati/skybox/right.jpg");
        skyboxArray[3] = toGLTexture("./dati/skybox/up.jpg");
        skyboxArray[4] = toGLTexture("./dati/skybox/down.jpg");
    }
    
    return;
}


// ----------------------------------------------------------------------------
void initAssets()
{
    // init of the levels and targets
    
    loadasset("./dati/models/bersaglio1.blend",&target_scene);
	//loadasset("./dati/models/livelli.blend",&level_scene);
	loadasset("./dati/models/livello1.obj",&level1_scene);
	loadasset("./dati/models/livello2.obj",&level2_scene);
	loadasset("./dati/models/livello3.obj",&level3_scene);
	//loadasset("./dati/models/tuttiIn1.obj",&level_scene);
	//loadasset("./dati/models/PeanutsDivisoLOWPOLY.obj",&level_scene);
	
	if (!LoadGLTextures(level1_scene.scene))
	{
		exit(-1);
	}

	if (!LoadGLTextures(level2_scene.scene))
	{
		exit(-1);
	}

	if (!LoadGLTextures(level3_scene.scene))
	{
		exit(-1);
	}
    
	if (!LoadGLTextures(target_scene.scene))
	{
		exit(-1);
	}
    
    // initialization of the gun
    
	//loadasset("./dati/models/Gioco.obj", &gun0.pistola);
	loadasset("./dati/models/Pistola_MaterialsLOWPOLY.obj", &gun0.pistola);
    if (!LoadGLTextures(gun0.pistola.scene))
    {
		exit(-1);
    }
    
    loadasset("./dati/models/bullet.blend", &gun0.proiettile);
    if (!LoadGLTextures(gun0.proiettile.scene))
    {
		exit(-1);
    }
    
	gun0.bullet_number = BULLET_NUMBER;
    return;
}

// ----------------------------------------------------------------------------

int InitGL()					 // All Setup For OpenGL goes here
{
	glShadeModel(GL_SMOOTH);		 // Enables Smooth Shading
    glClearColor(0.0, 0.0, 0.0, 1.0);
	glClearDepth(1.0f);				// Depth Buffer Setup
	glEnable(GL_DEPTH_TEST);		// Enables Depth Testing
	glDepthFunc(GL_LEQUAL);			// The Type Of Depth Test To Do
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);	// Really Nice Perspective Calculation
    
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);    // Uses default lighting parameters
	glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);
	glEnable(GL_NORMALIZE);
    
	glLightfv(GL_LIGHT1, GL_AMBIENT, LightAmbient);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, LightDiffuse);
	glLightfv(GL_LIGHT1, GL_POSITION, LightPosition);
	glEnable(GL_LIGHT1);
    
    glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
    
    // and now some init I need to do for other stuff
    
    ilInit(); /* Initialization of DevIL */
    
    // mouse stuff
    lastx = middleX;
    lasty = middleY;
    relativeX = 0.0;
    relativeY = 0.0;
    glutWarpPointer(middleX, middleY); // put the cursor in the middle of the screen
    
    // for the text
    
    t3dInit();
    
    // for the skybox
    
    initSkybox();
    
    // for the blend
    
    initAssets();
    
	return TRUE;					// Initialization Went OK
}

// ----------------------------------------------------------------------------
void initGame()
{
    
    livelli=InitPos();
	
    ch_index=InitPers();
	
    newGame();
    
    return;
}


// ----------------------------------------------------------------------------
void cleanUp()
{
    // cleanup - calling 'aiReleaseImport' is important, as the library
	// keeps internal resources until the scene is freed again. Not
	// doing so can cause severe resource leaking.
    
    aiReleaseImport(gun0.pistola.scene);
    aiReleaseImport(gun0.proiettile.scene);
    aiReleaseImport(level1_scene.scene);
	aiReleaseImport(level2_scene.scene);
	aiReleaseImport(level3_scene.scene);
    aiReleaseImport(target_scene.scene);
        
    t3dCleanup();
    
    return;
}

// ----------------------------------------------------------------------------
int main(int argc, char **argv)
{
	struct aiLogStream stream;
    
    initGame();
    
	glutInitWindowSize(windowWidth, windowHeight);
	glutInitWindowPosition(100,100);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	
	glutInit(&argc, argv);
    
	glutCreateWindow("Progetto OpenGL - Informatica Grafica");
	glutDisplayFunc(display);
	glutKeyboardFunc(handleKeypress);
    glutPassiveMotionFunc(mouseMovement); //check for mouse movement
	glutMotionFunc(mouseMovement);
    glutReshapeFunc(handleResize);
    
    glutMouseFunc(handleMouseKeypress);
    
	// get a handle to the predefined STDOUT log stream and attach
	// it to the logging system. It will be active for all further
	// calls to aiImportFile(Ex) and aiApplyPostProcessing.
    
	stream = aiGetPredefinedLogStream(aiDefaultLogStream_STDOUT,NULL);
	aiAttachLogStream(&stream);
    
	// ... exactly the same, but this stream will now write the
	// log file to assimp_log.txt
	stream = aiGetPredefinedLogStream(aiDefaultLogStream_FILE,"assimp_log.txt");
	aiAttachLogStream(&stream);
	

	if (!InitGL()) {
		fprintf(stderr,"Initialization failed");
		return FALSE;
	}
    
	glutGet(GLUT_ELAPSED_TIME);
	glutMainLoop();
    
    cleanUp();
    
	// We added a log stream to the library, it's our job to disable it
	// again. This will definitely release the last resources allocated
	// by Assimp.
	aiDetachAllLogStreams();
    
	return 0;
}