#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <cstdlib>

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
        DrawCube( halfScreenWidth, halfScreenHeight+200+edgeHeight/2, -115, edgeLength, edgeHeight, edgeHeight ); //orilla del site
        DrawCube( halfScreenWidth+385, halfScreenHeight+200+edgeHeight/2, -515, edgeHeight, edgeHeight, edgeLength-edgeHeight ); //orilla del site
        DrawCube( halfScreenWidth-385, halfScreenHeight+200+edgeHeight/2, -515, edgeHeight, edgeHeight, edgeLength-edgeHeight ); //orilla del site

        DrawCube( halfScreenWidth+200, halfScreenHeight+200+boxSize/2, -700, boxSize, boxSize, boxSize ); //caja por goose
        DrawCube( halfScreenWidth-250, halfScreenHeight+200+boxSize/2, -220, boxSize, boxSize, boxSize ); //stack de cajas (abajo)
        DrawCube( halfScreenWidth-250, halfScreenHeight+200+boxSize*1.5, -220, boxSize, boxSize, boxSize ); //stack de cajas (arriba)
        DrawCube( halfScreenWidth-250, halfScreenHeight+200+boxSize/2, -220-boxSize, boxSize, boxSize, boxSize ); //caja a un ladito
        
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

    GLfloat vertices[] =
    {
        // Cara frontal
        centerPosX - xOffset, centerPosY + yOffset, centerPosZ + zOffset, // Arriba Izquierda
        centerPosX + xOffset, centerPosY + yOffset, centerPosZ + zOffset, // Arriba Derecha
        centerPosX + xOffset, centerPosY - yOffset, centerPosZ + zOffset, // Abajo Derecha
        centerPosX - xOffset, centerPosY - yOffset, centerPosZ + zOffset, // Abajo Izquierda
        
        // Cara Tracera
        centerPosX - xOffset, centerPosY + yOffset, centerPosZ - zOffset, // Arriba Izquierda
        centerPosX + xOffset, centerPosY + yOffset, centerPosZ - zOffset, // Arriba Derecha
        centerPosX + xOffset, centerPosY - yOffset, centerPosZ - zOffset, // Abajo Derecha
        centerPosX - xOffset, centerPosY - yOffset, centerPosZ - zOffset, // Abajo Izquierda
        
        // Cara Izquierda
        centerPosX - xOffset, centerPosY + yOffset, centerPosZ + zOffset, // Arriba Izquierda
        centerPosX - xOffset, centerPosY + yOffset, centerPosZ - zOffset, // Arriba Dereccha
        centerPosX - xOffset, centerPosY - yOffset, centerPosZ - zOffset, // Abajo Derecha
        centerPosX - xOffset, centerPosY - yOffset, centerPosZ + zOffset, // Abajo Izquierda
        
        // Cara Derecha
        centerPosX + xOffset, centerPosY + yOffset, centerPosZ + zOffset, // Arriba Izquierda
        centerPosX + xOffset, centerPosY + yOffset, centerPosZ - zOffset, // Arriba Derecha
        centerPosX + xOffset, centerPosY - yOffset, centerPosZ - zOffset, // Abajo Derecha
        centerPosX + xOffset, centerPosY - yOffset, centerPosZ + zOffset, // Abajo Izquierda
        
        // Cara Superior
        centerPosX - xOffset, centerPosY + yOffset, centerPosZ + zOffset, // Arriba Izquierda
        centerPosX - xOffset, centerPosY + yOffset, centerPosZ - zOffset, // Arriba Derecha
        centerPosX + xOffset, centerPosY + yOffset, centerPosZ - zOffset, // Abajo Derecha
        centerPosX + xOffset, centerPosY + yOffset, centerPosZ + zOffset, // Abajo Izquierda
        
        // Cara Inferior
        centerPosX - xOffset, centerPosY - yOffset, centerPosZ + zOffset, // Arriba Izquierda
        centerPosX - xOffset, centerPosY - yOffset, centerPosZ - zOffset, // Arriba Derecha
        centerPosX + xOffset, centerPosY - yOffset, centerPosZ - zOffset, // Abajo Derecha
        centerPosX + xOffset, centerPosY - yOffset, centerPosZ + zOffset  // Abajo Izquierda
    };

    GLfloat colors[] =
    {
        0, 0, 0,   0, 0, 1,   0, 1, 1,   0, 1, 0,
        1, 0, 0,   1, 0, 1,   1, 1, 1,   1, 1, 0,
        0, 0, 0,   0, 0, 1,   1, 0, 1,   1, 0, 0,
        0, 1, 0,   0, 1, 1,   1, 1, 1,   1, 1, 0,
        0, 0, 0,   0, 1, 0,   1, 1, 0,   1, 0, 0,
        0, 0, 1,   0, 1, 1,   1, 1, 1,   1, 0, 1
    };

    glEnable(GL_DEPTH_TEST); //Agregar la proyección de profundidad
    glDepthMask(GL_TRUE);//Agregar la proyección de profundidad
    glEnableClientState( GL_VERTEX_ARRAY );
    glEnableClientState(GL_COLOR_ARRAY);
    glVertexPointer( 3, GL_FLOAT, 0, vertices );
    glColorPointer(3, GL_FLOAT, 0, colors); //Buffer de color
    glDrawArrays( GL_QUADS, 0, 24 );
    glDisableClientState( GL_VERTEX_ARRAY );
    glDisableClientState(GL_COLOR_ARRAY);
}
