#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <cstdlib>

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

void keyCallback( GLFWwindow *window, int key, int scancode, int action, int mods );
void DrawCube( GLfloat centerPosX, GLfloat centerPosY, GLfloat centerPosZ, GLfloat edgeLength );

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
    glMatrixMode( GL_PROJECTION ); // Se crea la matriz de proyección
    glLoadIdentity( ); // Se crea de la matriz identidad
    glOrtho( 0, SCREEN_WIDTH, 0, SCREEN_HEIGHT, 0, 1000 ); // Establecer el sistema de coordenadas
    glMatrixMode( GL_MODELVIEW ); // Matriz de transformación
    

    // Se establece el sistema de coordenadas dentro de la ventana
    GLfloat halfScreenWidth = SCREEN_WIDTH / 2;
    GLfloat halfScreenHeight = SCREEN_HEIGHT / 2;
    
    
    // Loop en donde se estará dibujando la ventana
    while ( !glfwWindowShouldClose( window ) )
    {
        glClear( GL_COLOR_BUFFER_BIT );
        // Render (Se crea el cubo y se generan los cambios en los vectores de transformación
        glPushMatrix( );

        //Envia el cubo al origen.
        glTranslatef( halfScreenWidth, halfScreenHeight, -500 );

        // Translacion
        glTranslated(translationX, translationY,0);

        // Rotacion
        glRotatef( rotationX, 1, 0, 0 );
        glRotatef( rotationY, 0, 1, 0 );

        // Escalar
        glScalef(scaleFactor, scaleFactor, scaleFactor);

        //Regresar el cubo al centro de la pantalla
        glTranslatef( -halfScreenWidth, -halfScreenHeight, 500 );

        DrawCube( halfScreenWidth, halfScreenHeight, -500, 200 );
        glPopMatrix(); //?
        glfwSwapBuffers( window ); //Buffers?
        glfwPollEvents( ); //teclas
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
            case GLFW_KEY_S:
                translationX += 10;
                break;
            case GLFW_KEY_W:
                translationY += 10;
                break;
            case GLFW_KEY_X:
                translationY -=10;
                break;
            case GLFW_KEY_1:
                scaleFactor += 0.1;
                break;
            case GLFW_KEY_2:
                scaleFactor -= 0.1;
                break;
        }
        
        
    }
}


void DrawCube( GLfloat centerPosX, GLfloat centerPosY, GLfloat centerPosZ, GLfloat edgeLength )
{
    GLfloat halfSideLength = edgeLength * 0.5f;
    
    GLfloat vertices[] =
    {
        // Cara frontal
        centerPosX - halfSideLength, centerPosY + halfSideLength, centerPosZ + halfSideLength, // Arriba Izquierda
        centerPosX + halfSideLength, centerPosY + halfSideLength, centerPosZ + halfSideLength, // Arriba Derecha
        centerPosX + halfSideLength, centerPosY - halfSideLength, centerPosZ + halfSideLength, // Abajo Derecha
        centerPosX - halfSideLength, centerPosY - halfSideLength, centerPosZ + halfSideLength, // Abajo Izquierda
        
        // Cara Tracera
        centerPosX - halfSideLength, centerPosY + halfSideLength, centerPosZ - halfSideLength, // Arriba Izquierda
        centerPosX + halfSideLength, centerPosY + halfSideLength, centerPosZ - halfSideLength, // Arriba Derecha
        centerPosX + halfSideLength, centerPosY - halfSideLength, centerPosZ - halfSideLength, // Abajo Derecha
        centerPosX - halfSideLength, centerPosY - halfSideLength, centerPosZ - halfSideLength, // Abajo Izquierda
        
        // Cara Izquierda
        centerPosX - halfSideLength, centerPosY + halfSideLength, centerPosZ + halfSideLength, // Arriba Izquierda
        centerPosX - halfSideLength, centerPosY + halfSideLength, centerPosZ - halfSideLength, // Arriba Dereccha
        centerPosX - halfSideLength, centerPosY - halfSideLength, centerPosZ - halfSideLength, // Abajo Derecha
        centerPosX - halfSideLength, centerPosY - halfSideLength, centerPosZ + halfSideLength, // Abajo Izquierda
        
        // Cara Derecha
        centerPosX + halfSideLength, centerPosY + halfSideLength, centerPosZ + halfSideLength, // Arriba Izquierda
        centerPosX + halfSideLength, centerPosY + halfSideLength, centerPosZ - halfSideLength, // Arriba Derecha
        centerPosX + halfSideLength, centerPosY - halfSideLength, centerPosZ - halfSideLength, // Abajo Derecha
        centerPosX + halfSideLength, centerPosY - halfSideLength, centerPosZ + halfSideLength, // Abajo Izquierda
        
        // Cara Superior
        centerPosX - halfSideLength, centerPosY + halfSideLength, centerPosZ + halfSideLength, // Arriba Izquierda
        centerPosX - halfSideLength, centerPosY + halfSideLength, centerPosZ - halfSideLength, // Arriba Derecha
        centerPosX + halfSideLength, centerPosY + halfSideLength, centerPosZ - halfSideLength, // Abajo Derecha
        centerPosX + halfSideLength, centerPosY + halfSideLength, centerPosZ + halfSideLength, // Abajo Izquierda
        
        // Cara Inferior
        centerPosX - halfSideLength, centerPosY - halfSideLength, centerPosZ + halfSideLength, // Arriba Izquierda
        centerPosX - halfSideLength, centerPosY - halfSideLength, centerPosZ - halfSideLength, // Arriba Derecha
        centerPosX + halfSideLength, centerPosY - halfSideLength, centerPosZ - halfSideLength, // Abajo Derecha
        centerPosX + halfSideLength, centerPosY - halfSideLength, centerPosZ + halfSideLength  // Abajo Izquierda
    };
    
    glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
    glEnableClientState( GL_VERTEX_ARRAY );
    glVertexPointer( 3, GL_FLOAT, 0, vertices );

    glDrawArrays( GL_QUADS, 0, 24 );
    
    glDisableClientState( GL_VERTEX_ARRAY );
}