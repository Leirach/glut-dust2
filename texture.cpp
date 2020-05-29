#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <cstdlib>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#define SCREEN_WIDTH 1024
#define SCREEN_HEIGHT 768

void keyCallback( GLFWwindow *window, int key, int scancode, int action, int mods );
void DrawCube( GLfloat centerPosX, GLfloat centerPosY, GLfloat centerPosZ, GLfloat width, GLfloat height, GLfloat length);

GLfloat rotationX = 0.0f;
GLfloat rotationY = 0.0f;
GLfloat translationX = 0.0f;
GLfloat translationY = 0.0f;
GLfloat scaleFactor = 1.0f;

int main( void )
{
    GLFWwindow *window;
    
    // Inicializar la librería
    if ( !glfwInit( ) )
    {
        return -1;
    }
    
    // Crear la ventana
    window = glfwCreateWindow( SCREEN_WIDTH, SCREEN_HEIGHT, "Hello World", NULL, NULL );
    
    // Declarar que se recibirán comando del teclado
    glfwSetKeyCallback( window, keyCallback );
    glfwSetInputMode( window, GLFW_STICKY_KEYS, 1 );
    
    
    
    int screenWidth, screenHeight;
    glfwGetFramebufferSize( window, &screenWidth, &screenHeight );

    
    if ( !window )
    {
        glfwTerminate( );
        return -1;
    }
    
    
    // Se crea el contexto de la ventana
    glfwMakeContextCurrent( window );
    
    glViewport( 0.0f, 0.0f, screenWidth, screenHeight ); // Específica en que parte de la ventana se dibujaran los elementos
    glMatrixMode(GL_PROJECTION_MATRIX); // Se crea la matriz de proyección
    glLoadIdentity( ); // Se crea de la matriz identidad
    glOrtho( 0, SCREEN_WIDTH, 0, SCREEN_HEIGHT, 0, 1000 ); // Establecer el sistema de coordenadas
    glMatrixMode(GL_MODELVIEW_MATRIX); // Matriz de transformación
    

    // Se establece el sistema de coordenadas dentro de la ventana
    GLfloat halfScreenWidth = SCREEN_WIDTH / 2;
    GLfloat halfScreenHeight = SCREEN_HEIGHT / 2;
    
    
    // Loop en donde se estará dibujando la ventana
    while ( !glfwWindowShouldClose( window ) )
    {
        glClearColor(1, 1, 1, 1.0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Render (Se crea el cubo y se generan los cambios en los vectores de transformación)
        glPushMatrix();
        glTranslatef( halfScreenWidth, halfScreenHeight, -500 ); // Coloca el cubo al centro de la pantalla
        glTranslated(translationX, translationY,0); // Mueve el cubo con las variables de las teclas (Vector de Traslación
        glRotatef( rotationX, 1, 0, 0 ); // Rotar el cubo en X
        glRotatef( rotationY, 0, 1, 0 ); // Rotar el cubo en Y
        glScalef(scaleFactor, scaleFactor, scaleFactor);
        glTranslatef( -halfScreenWidth, -halfScreenHeight, 500 );

        //cubo
        GLfloat boxSize = 175;
        GLfloat edgeHeight = 30;
        GLfloat edgeLength = 800;
        DrawCube( halfScreenWidth, halfScreenHeight, -500, 800, 400, 800 ); //site
        
        glPopMatrix();
        glfwSwapBuffers( window );
        glfwPollEvents( );
    }

    glfwTerminate( );
    
    return 0;
}


// LLamar mandar las teclas
void keyCallback( GLFWwindow *window, int key, int scancode, int action, int mods )
{
    const GLfloat rotationSpeed = 10;
    // Switch en donde se determinan los movimientos del cubo en base a las teclas
    if ( action == GLFW_PRESS || action == GLFW_REPEAT )
    {
        switch ( key )
        {
            case GLFW_KEY_UP:
                rotationX -= rotationSpeed;
                break;
            case GLFW_KEY_DOWN:
                rotationX += rotationSpeed;
                break;
            case GLFW_KEY_RIGHT:
                rotationY += rotationSpeed;
                break;
            case GLFW_KEY_LEFT:
                rotationY -= rotationSpeed;
                break;
            case GLFW_KEY_A:
                translationX -= 10;
                break;
            case GLFW_KEY_D:
                translationX += 10;
                break;
            case GLFW_KEY_W:
                translationY += 10;
                break;
            case GLFW_KEY_S:
                translationY -=10;
                break;
            case GLFW_KEY_X:
                scaleFactor += 0.1;
                break;
            case GLFW_KEY_Z:
                scaleFactor -= 0.1;
                break;
        }
    }
}


void DrawCube( GLfloat centerPosX, GLfloat centerPosY, GLfloat centerPosZ, GLfloat width, GLfloat height, GLfloat length)
{
    GLfloat xOffset = width * 0.5f;
    GLfloat yOffset = height * 0.5f;
    GLfloat zOffset = length * 0.5f;

    float vertices[] = {
    -0.5f, -0.5f, 0.0f,
    -0.5f, 0.5f, 0.0f,
    0.5f, -0.5f, 0.0f,
    0.5f, 0.5f, 0.0f

};

    float texcoords[] = {
        0.0f, 1.0f,
        0.0f, 0.0f,
        1.0, 0.0,
        1.0, 1.0,
    };

    unsigned int texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    // set the texture wrapping/filtering options (on the currently bound texture object)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    int texWidth, texHeight, nrChannels;
    unsigned char *data = stbi_load("container.jpg", &texWidth, &texHeight, &nrChannels, 0);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, texWidth, texHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, data);

    glEnable(GL_DEPTH_TEST); //Agregar la proyección de profundidad
    glDepthMask(GL_TRUE);//Agregar la proyección de profundidad
    glEnableClientState( GL_VERTEX_ARRAY );
    glVertexPointer( 3, GL_FLOAT, 0, vertices );
    glDrawArrays( GL_QUADS, 0, 24 );
    glEnableClientState( GL_VERTEX_ARRAY );
    glVertexPointer( 3, GL_FLOAT, 0, vertices );
    glDisableClientState( GL_VERTEX_ARRAY );
    glDisableClientState( GL_VERTEX_ARRAY );
    
}
