#include <GL/glew.h>		// OpenGL Extension Wrangler

// Include our OpenGL & GLUT libraries
// GLUT automatically includes glu.h and gl.h
#ifdef __APPLE__
#include <GLUT/glut.h>	// GLUT, GLU, GL Libraries for Mac
#include <SOIL.h>  	// Simple OpenGL Image Library
#else
#include <GL/glut.h>	// GLUT, GLU, GL Libraries for Windows or *nix
#include <SOIL/SOIL.h>  	// Simple OpenGL Image Library
#endif

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <algorithm>

// including made classes
#include "utilities/camera.h"
#include "utilities/Point.h"
#include "utilities/Vector.h"
#include "utilities/Object.h"
#include "utilities/Skybox.h"
#include "utilities/Shader_Utils.h"
#include "utilities/Planet.h"
#include "utilities/SolarSystem.h"
#include "utilities/Ship.h"

using namespace std;

// Global variables.

size_t window_width = 1024;
size_t window_height = 1024;

GLuint envDL;

GLint leftMouseButton;                      // status of the mouse buttons
int mouseX = 0, mouseY = 0;                 // last known X and Y of the mouse
int frame=0;
int currentTime, timebase=0;
float fps;

Skybox* skybox;
Planet testPlanet;
SolarSystem solarSystem;
Ship ship;

bool fpvMode = false;
bool pause = false;
float lPosition[4] = { 0, 0, 0, 1 };

string solarsystemfile = "solarsystem.txt";

// Camera
Camera mainCamera;
Camera fpvCamera;

bool keys[256];
int a = 0;

Vector up(0, 1, 0);

Point cameraXYZ;
Point pos;

char* sunVertex = "shaders/sphereShader.v.glsl";
char* sunFrag = "shaders/sphereShader.f.glsl";
char* shipVertex1 = "shaders/shipShader.v.glsl";
char* shipFrag1 = "shaders/shipShader.f.glsl";
char* expNorm = "textures/effects/exploda.jpg";
char* expAlp = "textures/effects/td-explosion1alpha.jpg";

GLuint sunShaderHandle;
GLuint shipShaderHandle1;
GLuint framebufferHandle;
GLuint renderbufferHandle;
GLuint framebufferWidth = 1024, framebufferHeight = 1024; // set these to the desired size
GLuint fboTexHandle;
GLuint exptexhandle = 0;

// calculates and then displays the fps to the screen
void calculateFPS() {
    
    // increment frames we will use for fames / sec
    frame++;
    // gets the elapsed time since init
    currentTime = glutGet(GLUT_ELAPSED_TIME);
    
    // we subtract current time and timebase to see if 1000 millis seconds have passed
    if (currentTime - timebase > 1000) {
        // the fps is the amount of frames divided by the time passed converted back to seconds
        fps = frame / ((currentTime - timebase) / 1000.0f);
        timebase = currentTime;
        
        // reset frames
        frame = 0;
    }
}

void drawFps() {
    // in order to display the text we need to first save our current matrix and go through setting the display for a 2D view
    glMatrixMode(GL_PROJECTION);
    glPushMatrix(); {
        glLoadIdentity();
        glMatrixMode(GL_MODELVIEW);
        glPushMatrix(); {
            // disabled depth test and lighting so we can draw the lines
            glLoadIdentity();
            glDisable(GL_DEPTH_TEST);
            glDisable(GL_LIGHTING);
            glColor3f(1, 1, 1);
            
            // set the position for the screen to be on the bottom right corner
            glRasterPos2f(.7, -.9);
            
            // convert the fps into a string to display
            string s;
            ostringstream ss;
            ss << fps;
            s = ss.str();
            s = "FPS: " + s;
            
            // convert the string to bitmap and display each character
            for (int i = 0; i < s.length(); i++)
            {
                glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, s.at(i));
            }
            glMatrixMode(GL_PROJECTION);
        } glPopMatrix();
        glMatrixMode(GL_MODELVIEW);
    } glPopMatrix();
    glEnable(GL_LIGHTING);
    glEnable(GL_DEPTH_TEST);
}

// Environment setup functions.
void generate_env_dl() {
    glMatrixMode(GL_MODELVIEW);
    envDL = glGenLists(1);
    glNewList(envDL, GL_COMPILE);
    
    // draw the skybox
    glDisable(GL_LIGHTING);
    glPushMatrix(); {
        skybox->draw();
    } glPopMatrix();
    glEnable(GL_LIGHTING);
    
    glEndList();
}

// Drawing callback functions.
void resize(int w, int h) {
    window_width = w;
    window_height = h;
    
    glViewport(0, 0, w, h);
    
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, (float) w / h, 0.1, 100000);
}

// draw the stuff in scene here, planets, etc.
void drawScene(bool fpv) {
    glCallList(envDL);
    solarSystem.draw();
    if(!fpv) ship.draw();
}

void scissorScene(size_t w, size_t h) {
    glScissor(0, 0, w, h);
    glViewport(0, 0, w, h);
}

void fpvLook() {
    if(fpvMode) {
        scissorScene(window_width / 3, window_height / 3);
        glEnable(GL_SCISSOR_TEST);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glDisable(GL_SCISSOR_TEST);
        
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        gluPerspective(45.0, (float) window_width / window_height, 0.1, 100000);
        
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        fpvCamera.fpvLook(ship.getPosition(), ship.getDirection(), ship.getHeading());
        
        drawScene(true);
        glViewport(0, 0, window_width, window_height);
    }
}

void render() {
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glBindFramebuffer( GL_FRAMEBUFFER, framebufferHandle );
    glPushAttrib( GL_VIEWPORT_BIT ); {
        //glViewport(0, 0, framebufferWidth, framebufferHeight);
        //scissorScene(framebufferWidth, framebufferHeight);
        /* render our scene as desired */
        /* set camera, lights, materials, draw objects, etc. */
        // make sure that OpenGL has finished rendering everything...
        
        glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        // drawing on back buffer -> clear color and depth to draw
        glDrawBuffer(GL_BACK);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glEnable(GL_SCISSOR_TEST);
        
        // we scissor and set the viewport for main scene to be whole window
        scissorScene(framebufferWidth, framebufferHeight);
        //scissorScene(window_width, window_height);
        
        // set up the projection and modelview matrices
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        gluPerspective(45.0, (float) framebufferWidth / framebufferHeight, 0.1, 100000);
        
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        
        if(mainCamera.mode == 1) cameraXYZ = mainCamera.position;
        else cameraXYZ = mainCamera.arcPosition;
        if(mainCamera.mode == 1) pos = mainCamera.position + mainCamera.camDir;
        else pos = ship.getPosition();
        
        // set the camera to look, if free cam we look in its direction
        // else we are in arcball looking at the current hero
        mainCamera.look(ship.getPosition());
        glLightfv( GL_LIGHT0, GL_POSITION, lPosition );
        
        // draws main scene first time
        drawScene(false);
        
        glFlush(); glFinish();
        // and clean up. detatch the framebuffer so we render to the screen again.
        // the first pass is now inside of that texture! (fboTexHandle!)
    }	; glPopAttrib();
    
    // texture fbo object
    glBindFramebuffer( GL_FRAMEBUFFER, 0 );
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode( GL_PROJECTION );
    glPushMatrix(); {
        glLoadIdentity();
        gluOrtho2D( -1, 1, -1, 1 );
        
        //and the modelview...
        glMatrixMode( GL_MODELVIEW );
        glLoadIdentity();
        glDisable( GL_LIGHTING );
        glDisable( GL_DEPTH_TEST );
        glEnable( GL_TEXTURE_2D );
        glBindTexture( GL_TEXTURE_2D, fboTexHandle );
        glBegin(GL_QUADS); {
            glTexCoord2f(0,0); glVertex2f(-1,-1);
            glTexCoord2f(1,0); glVertex2f( 1,-1);
            glTexCoord2f(1,1); glVertex2f( 1, 1);
            glTexCoord2f(0,1); glVertex2f(-1, 1);
        }; glEnd();
        glDisable( GL_TEXTURE_2D );
        glEnable( GL_DEPTH_TEST );
        glEnable( GL_LIGHTING );
    }; glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    
    // if fpv camera on we then repeat above process for a second view
    glPushMatrix();
    fpvLook();
    glPopMatrix();
    
    // draws the fps to bottom left of screen
    drawFps();
    
    if(!pause) {
        solarSystem.update(ship);
    }
    ship.update(cameraXYZ, pos);
    
    glutSwapBuffers();
}

// Input callback functions.
void mouseCallback(int button, int state, int thisX, int thisY) {
    // update the left mouse button states, if applicable for ctrl click
    if(button == GLUT_LEFT_BUTTON && glutGetModifiers() == GLUT_ACTIVE_CTRL) {
        leftMouseButton = 100;
        mouseX = thisX;
        mouseY = thisY;
    }
    else if(button == GLUT_LEFT_BUTTON) {
        leftMouseButton = state;
        mouseX = thisX;
        mouseY = thisY;
    }
}

void mouseMotion(int x, int y) {
    // if ctrl click we zoom rather than move around the hero
    if(leftMouseButton == 100) {
        mainCamera.zoom((x - mouseX));
    }
    // change position of the camera
    if(leftMouseButton == GLUT_DOWN) {
        float theta = ((x - mouseX) * .005);
        float phi = ((mouseY - y) * .005);
        
        mainCamera.revolve(theta, phi);
        glutPostRedisplay();	    // redraw our scene from our new camera POV
    }
    mouseX = x;
    mouseY = y;
}

void normal_keys_down(unsigned char key, int x, int y) {
    keys[key] = true;
}

void normal_keys_up(unsigned char key, int x, int y) {
    keys[key] = false;
}

void check_keys() {
    if(keys['q'] || keys['Q'] || keys[27]) exit(0);
    
    if(keys['i'] || keys['I']) {
        mainCamera.moveForward();
        glutPostRedisplay();
    }
    else if(keys['k'] || keys['K']) {
        mainCamera.moveBackward();
        glutPostRedisplay();
    }
    
    if(keys['p'] || keys['P']) pause = !pause;
    
    if(!ship.exploded) {
        if(keys['e'] || keys['E']) ship.hyperJump();
        if(keys['w'] || keys['W']) ship.moveForward();
        if(keys['s'] || keys['S']) ship.moveBackward();
        if(keys['a'] || keys['A']) ship.turnright();
        if(keys['d'] || keys['D']) ship.turnleft();
    }
    
    if(!(keys['e'] || keys['E'] ||
         keys['w'] || keys['W'] ||
         keys['s'] || keys['S']
         )) ship.rest();
    
    if(!(keys['a'] || keys['A'] ||
         keys['d'] || keys['D'])) ship.notTurn();
    
    if(ship.exploded && keys['r'] || keys['R']) {
        ship.exploded = false;
        ship.setPosition(Point(6000, 0, 0));
    }
    
    ship.checkPosition(skybox->getSize());
}

void menu_callback(int option) {
    if (option == 0) {
        exit(0);
    }
}

void subMenu_cameraType_callback(int option) {
    if (option == 0) mainCamera.switchMode(1);
    else if(option == 1) mainCamera.switchMode(2);
    else if(option == 2) fpvMode = !fpvMode;
    
}

// Timer functions.
void render_timer(int value) {
    check_keys();
    calculateFPS();
    glutPostRedisplay();
    
    glutTimerFunc(1000.0 / 60.0, render_timer, 0);
}

void anim_timer(int value) {
    // Do animation stuff here
    ship.animate();
    glutTimerFunc(1000.0 / 30.0, anim_timer, 0);
}

void split(const string &s, const char* delim, vector<string> & v){
    // to avoid modifying original string
    // first duplicate the original string and return a char pointer then free the memory
    char * dup = strdup(s.c_str());
    char * token = strtok(dup, delim);
    while(token != NULL){
        v.push_back(string(token));
        // the call is treated as a subsequent calls to strtok:
        // the function continues from where it left in previous invocation
        token = strtok(NULL, delim);
    }
    free(dup);
}

void create_menu() {
    int cameraOptions = glutCreateMenu(subMenu_cameraType_callback);
    glutAddMenuEntry("Free Cam Mode", 0);
    glutAddMenuEntry("Arcball Cam Mode", 1);
    glutAddMenuEntry("Ship POV view", 2);
    glutCreateMenu(menu_callback);
    glutAddSubMenu("Change Camera", cameraOptions);
    glutAddMenuEntry("Quit", 0);
    glutAttachMenu(GLUT_RIGHT_BUTTON);
}

void setupParticleShaders(char* vertexShader, char* fragmentShader, GLuint &shaderProgramHandle) {
    shaderProgramHandle = createShaderProgram(vertexShader, fragmentShader);
}

bool registerTransparentOpenGLTexture(unsigned char *imageData, unsigned char *imageMask, int texWidth, int texHeight, GLuint &texHandle) {
    // combine the 'mask' array with the image data array into an RGBA array.
    unsigned char *fullData = new unsigned char[texWidth*texHeight*4];
    for(int j = 0; j < texHeight; j++) {
        for(int i = 0; i < texWidth; i++) {
            fullData[(j*texWidth+i)*4+0] = imageData[(j*texWidth+i)*3+0];	// R
            fullData[(j*texWidth+i)*4+1] = imageData[(j*texWidth+i)*3+1];	// G
            fullData[(j*texWidth+i)*4+2] = imageData[(j*texWidth+i)*3+2];	// B
            fullData[(j*texWidth+i)*4+3] = imageMask[(j*texWidth+i)*3+0];	// A
        }
    }
    
    // first off, get a real texture handle.
    glGenTextures(1, &texHandle);
    
    // make sure that future texture functions affect this handle
    glBindTexture(GL_TEXTURE_2D, texHandle);
    
    // set this texture's color to be multiplied by the surface colors --
    //  GL_MODULATE instead of GL_REPLACE allows us to take advantage of OpenGL lighting
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    
    // set the minification and magnification functions to be linear; not perfect
    //  but much better than nearest-texel (GL_NEAREST).
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    
    // Set the texture to repeat in S and T -- though it doesn't matter here
    //  because our texture coordinates are always in [0,0] to [1,1].
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    
    // actually transfer the texture to the GPU and use MipMaps!!
    /*    gluBuild2DMipMaps(
     GL_TEXTURE_2D,              //still working with 2D textures, obv.
     GL_RGBA,                    //we're going to provide OpenGL with R, G, B, and A components...
     texWidth,                   //...of this width...
     texHeight,                  //...and this height.
     GL_RGBA,                    //and store it, internally, as RGBA (OpenGL will convert to floats between 0.0 and 1.0f)
     GL_UNSIGNED_BYTE,           //this is the format our data is in, and finally,
     fullData);                  //there's the data!
     */
    gluBuild2DMipmaps( GL_TEXTURE_2D, GL_RGBA, texWidth, texHeight, GL_RGBA, GL_UNSIGNED_BYTE, fullData );
    
    // clean up our memory on the CPU side since it's already been transfered to the GPU
    delete fullData;
    
    // whoops! i guess this function can't fail. in an ideal world, there would
    // be checks with glGetError() that we could use to determine if this failed.
    return true;
}

void loadParticle(char* image, char* alpha, GLuint &handle) {
    int rgbWidth, rgbHeight, alphaWidth, alphaHeight, channels;
    unsigned char *particleTexData, *particleMaskData;
    particleTexData = SOIL_load_image( image,
                                      &rgbWidth, &rgbHeight, &channels,
                                      SOIL_LOAD_AUTO );
    printf( "[INFO]: read in image treeDiff.jpg of size %d x %d with %d colors\n", rgbWidth, rgbHeight, channels );
    particleMaskData = SOIL_load_image( alpha,
                                       &alphaWidth, &alphaHeight, &channels,
                                       SOIL_LOAD_AUTO );
    printf( "[INFO]: read in image treeOpa.jpg of size %d x %d with %d colors\n", alphaWidth, alphaHeight, channels );
    registerTransparentOpenGLTexture( particleTexData, particleMaskData, rgbWidth, rgbHeight, handle );
    printf( "[INFO]: transparent texture read in and registered\n" );
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
}

void init_scene() {
    glEnable(GL_DEPTH_TEST);
    
    float diffuseLightCol[4] = { 1.0, 1.0, 1.0, 1 };	// white light
    float specularLightCol[4] = { 1.0, 1.0, 1.0, 1 };	// white light
    float ambientCol[4] = { 0.1, 0.1, 0.1, 1.0 };		// set this to be very low
    
    // and now set each value
    glLightfv( GL_LIGHT0, GL_DIFFUSE, diffuseLightCol );
    glLightfv( GL_LIGHT0, GL_SPECULAR, specularLightCol );
    glLightfv( GL_LIGHT0, GL_AMBIENT, ambientCol );
    glEnable( GL_LIGHTING );
    glEnable( GL_LIGHT0 );
    
    glShadeModel(GL_SMOOTH);
    
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
    generate_env_dl();
    
    glGenFramebuffers( 1, &framebufferHandle );
    glBindFramebuffer( GL_FRAMEBUFFER, framebufferHandle );
    
    glGenRenderbuffers( 1, &renderbufferHandle );
    glBindRenderbuffer( GL_RENDERBUFFER, renderbufferHandle );
    glRenderbufferStorage( GL_RENDERBUFFER,
                          GL_DEPTH_COMPONENT,
                          framebufferWidth,
                          framebufferHeight );
    glFramebufferRenderbuffer( GL_FRAMEBUFFER,
                              GL_DEPTH_ATTACHMENT,
                              GL_RENDERBUFFER,
                              renderbufferHandle );
    
    glGenTextures(1, &fboTexHandle);
    glBindTexture(GL_TEXTURE_2D, fboTexHandle);
    // SET UP ALL of the texture parameters
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE );
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE );
    // initialize it with nothing! no image! just tell it to hold that much space.
    glTexImage2D( GL_TEXTURE_2D,
                 0,
                 GL_RGBA, //this needs to match the color buffer requested from GLUT
                 framebufferWidth,
                 framebufferHeight,
                 0,
                 GL_RGBA,
                 GL_UNSIGNED_BYTE,
                 NULL );
    // and finally, attach that texture to the FBO
    glFramebufferTexture2D( GL_FRAMEBUFFER,
                           GL_COLOR_ATTACHMENT0,
                           GL_TEXTURE_2D,
                           fboTexHandle,
                           0 );
    // check for any errors
    GLenum status = glCheckFramebufferStatus( GL_FRAMEBUFFER );
    if( status == GL_FRAMEBUFFER_COMPLETE )
        printf( "Framebuffer initialized completely!\n" );
    else
        printf( "Framebuffer FAILED TO INITIALIZE COMPLETELY.\n" );
}

void register_callbacks() {
    glutSetKeyRepeat(GLUT_KEY_REPEAT_ON);
    glutDisplayFunc(render);
    glutReshapeFunc(resize);
    glutKeyboardFunc(normal_keys_down);
    glutKeyboardUpFunc(normal_keys_up);
    glutMouseFunc(mouseCallback);
    glutMotionFunc(mouseMotion);
}

int main(int argc, char** argv) {
    // initialize glut and make sure we have everything set up
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(window_width, window_height);
    glutCreateWindow("SolarSystem");
    
    GLenum glewResult = glewInit();
    /* check for an error */
    if( glewResult != GLEW_OK ) {
        printf( "[ERROR]: Error initalizing GLEW\n");
        return 0;
    }
    
    GLint maxVertexAttribs = 0;
    glGetIntegerv( GL_MAX_VERTEX_ATTRIBS, &maxVertexAttribs );
    
    GLint maxLights = 0;
    glGetIntegerv( GL_MAX_LIGHTS, &maxLights );
    
    GLint maxTextures = 0;
    glGetIntegerv( GL_MAX_TEXTURE_IMAGE_UNITS, &maxTextures );
    
    fprintf( stdout, "[INFO]: /--------------------------------------------------------\\\n");
    fprintf( stdout, "[INFO]: | OpenGL Information                                     |\n");
    fprintf( stdout, "[INFO]: |--------------------------------------------------------|\n");
    fprintf( stdout, "[INFO]: |   OpenGL Version:  %35s |\n", glGetString(GL_VERSION) );
    fprintf( stdout, "[INFO]: |   OpenGL Renderer: %35s |\n", glGetString(GL_RENDERER) );
    fprintf( stdout, "[INFO]: |   OpenGL Vendor:   %35s |\n", glGetString(GL_VENDOR) );
    fprintf( stdout, "[INFO]: |   Shading Version: %35s |\n", glGetString(GL_SHADING_LANGUAGE_VERSION) );
    fprintf( stdout, "[INFO]: >--------------------------------------------------------<\n");
    fprintf( stdout, "[INFO]: |   Max # Vertex Attributes:  %26d |\n", maxVertexAttribs );
    fprintf( stdout, "[INFO]: |   Max # Lights:    %35d |\n", maxLights );
    fprintf( stdout, "[INFO]: |   Max # Textures:  %35d |\n", maxTextures );
    fprintf( stdout, "[INFO]: \\--------------------------------------------------------/\n\n");
    
    /* make sure OpenGL 2.0 is supported */
    if( !glewIsSupported( "GL_VERSION_2_0" ) ) {
        printf( "[ERROR]: System does not support OpenGL 2.0 and GLSL\n" );
        return 0;
    }
    
    printf( "[INFO]: System supports OpenGL2.0 and GLSL!\n\n" );
    
    //do some basic OpenGL setup
    // set camera to arcball initially
    float cameraTheta = M_PI / 3.0f;
    float cameraPhi = 2.8f;
    float cameraRadius = 300;
    mainCamera = Camera(2, 0, 0, 0, cameraRadius, cameraTheta, cameraPhi);
    skybox = new Skybox(20000);
    
    loadParticle(expNorm, expAlp, exptexhandle);
    
    /*exptexhandle = SOIL_load_OGL_texture(
                                         "textures/effects/exploda.png",
                                         SOIL_LOAD_AUTO,
                                         SOIL_CREATE_NEW_ID,
                                         SOIL_FLAG_MIPMAPS
                                         | SOIL_FLAG_INVERT_Y
                                         | SOIL_FLAG_COMPRESS_TO_DXT
                                         );*/
    cout << exptexhandle << endl;
    solarSystem = SolarSystem(solarsystemfile);
    ship = Ship(Point(6000, 0, 0), 1);
    ship.setExpTex(exptexhandle);
    init_scene();
    create_menu();
    printf( "[INFO]: OpenGL Scene set up\n" );
    
    // set up our shaders (the files are hardcoded in)
    setupParticleShaders(sunVertex, sunFrag, sunShaderHandle);
    setupParticleShaders(shipVertex1, shipFrag1, shipShaderHandle1);
    solarSystem.setSunShader(sunShaderHandle);
    ship.setShipShader1(shipShaderHandle1);
    printf( "[INFO]: Shader compilation complete.\n" );
    
    // register callbacks
    register_callbacks();
    anim_timer(0);
    render_timer(0);
    
    glutMainLoop();
    
    return 0;
}
