#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <cstdlib>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#define SCREEN_WIDTH 1024
#define SCREEN_HEIGHT 768

void keyCallback( GLFWwindow *window, int key, int scancode, int action, int mods );
void DrawCube( GLfloat centerPosX, GLfloat centerPosY, GLfloat centerPosZ, GLfloat width, GLfloat height, GLfloat length, GLfloat color[]);
void DrawRamp( GLfloat centerPosX, GLfloat centerPosY, GLfloat centerPosZ, GLfloat width, GLfloat height, GLfloat length);
void DrawWall( GLfloat centerPosX, GLfloat centerPosY, GLfloat centerPosZ, GLfloat width, GLfloat height, char plane);

GLfloat rotationX = 0.0f;
GLfloat rotationY = 0.0f;
GLfloat translationX = 0.0f;
GLfloat translationZ = 0.0f;
GLfloat scaleFactor = 1.0f;

GLfloat mapColors[] =
{
    0.71, 0.39, 0.11,   0.71, 0.39, 0.11,   0.0, 0.0, 0.0,   0.18, 0.09, 0.0,
    0.71, 0.39, 0.11,   0.71, 0.39, 0.11,   0.18, 0.09, 0.0,   0.18, 0.09, 0.0,
    0.71, 0.39, 0.11,   0.71, 0.39, 0.11,   0.18, 0.09, 0.0,   0.18, 0.09, 0.0,
    0.71, 0.39, 0.11,   0.71, 0.39, 0.11,   0.18, 0.09, 0.0,   0.0, 0.00, 0.0,
    0.71, 0.39, 0.11,   0.81, 0.59, 0.31,   0.71, 0.39, 0.11,   0.71, 0.39, 0.11,
    0, 0, 0,   0, 0, 0,   0, 0, 0,   0, 0, 0
};

GLfloat boxColors[] =
{
    0.51, 0.6, 0.51,   0.51, 0.6, 0.51,   0.0, 0.0, 0.0,   0.11, 0.15, 0.11,
    0.51, 0.6, 0.51,   0.51, 0.6, 0.51,   0.11, 0.15, 0.11,   0.11, 0.15, 0.11,
    0.51, 0.6, 0.51,   0.51, 0.6, 0.51,   0.11, 0.15, 0.11,   0.11, 0.15, 0.11,
    0.51, 0.6, 0.51,   0.51, 0.6, 0.51,   0.11, 0.15, 0.11,   0.0, 0.00, 0.0,
    0.51, 0.6, 0.51,   0.61, 0.65, 0.61,   0.51, 0.6, 0.51,   0.51, 0.6, 0.51,
    0, 0, 0,   0, 0, 0,   0, 0, 0,   0, 0, 0
};

int texWidth, texHeight, nrChannels;

int main( void )
{
    GLFWwindow *window;

    // Inicializar la librería
    if ( !glfwInit( ) )
    {
        return -1;
    }

    // Crear la ventana
    window = glfwCreateWindow( SCREEN_WIDTH, SCREEN_HEIGHT, "Dust2 A Site", NULL, NULL );

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
    glOrtho( 0, SCREEN_WIDTH, 0, SCREEN_HEIGHT, -2000, 2000 ); // Establecer el sistema de coordenadas
    glMatrixMode(GL_MODELVIEW_MATRIX); // Matriz de transformación
    

    // Se establece el sistema de coordenadas dentro de la ventana
    GLfloat halfScreenWidth = SCREEN_WIDTH / 2;
    GLfloat halfScreenHeight = SCREEN_HEIGHT / 2 - 100;
    GLfloat startingZPos = -500;
    
    
    // Loop en donde se estará dibujando la ventana
    while ( !glfwWindowShouldClose( window ) )
    {
        glClearColor(1, 1, 1, 1.0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Render (Se crea el cubo y se generan los cambios en los vectores de transformación)
        glPushMatrix();
        glTranslatef( halfScreenWidth, halfScreenHeight, -500 ); // Coloca el cubo al centro de la pantalla
        glTranslated(translationX, 0, translationZ); // Mueve el cubo con las variables de las teclas (Vector de Traslación
        glRotatef( rotationX, 1, 0, 0 ); // Rotar el cubo en X
        glRotatef( rotationY, 0, 1, 0 ); // Rotar el cubo en Y
        glScalef(scaleFactor, scaleFactor, scaleFactor);
        glTranslatef( -halfScreenWidth, -halfScreenHeight, 500 );

        //cubo
        GLfloat boxSize = 175;
        GLfloat edgeHeight = 30;
        GLfloat siteLength = 800;
        
        DrawCube( halfScreenWidth, halfScreenHeight, -500, siteLength, 400, siteLength, mapColors ); // site
        DrawCube( halfScreenWidth+siteLength/2, halfScreenHeight, -500-siteLength, 1600, 400, 800, mapColors ); // atras
        DrawCube( halfScreenWidth-siteLength-100, halfScreenHeight, -700, 1000, 400, 800, mapColors ); // short

        DrawRamp(halfScreenWidth+siteLength, halfScreenHeight, -500, siteLength, 400, siteLength);

        DrawCube( halfScreenWidth-siteLength-100, halfScreenHeight+200+edgeHeight/2, -315, 1000, edgeHeight, edgeHeight, mapColors ); //orilla de short frente

        DrawCube( halfScreenWidth, halfScreenHeight+200+edgeHeight/2, -115, siteLength, edgeHeight, edgeHeight, mapColors ); //orilla de site frente
        DrawCube( halfScreenWidth+385, halfScreenHeight+200+edgeHeight/2, -515, edgeHeight, edgeHeight, siteLength-edgeHeight, mapColors ); //orilla de site derecha
        DrawCube( halfScreenWidth-385, halfScreenHeight+200+edgeHeight/2, -230, edgeHeight, edgeHeight, 200, mapColors ); //orilla de site izquierda

        DrawCube( halfScreenWidth+200, halfScreenHeight+200+boxSize/2, -700, boxSize, boxSize, boxSize, boxColors ); //caja atras
        DrawCube( halfScreenWidth-250, halfScreenHeight+200+boxSize/2, -220, boxSize, boxSize, boxSize, boxColors ); //stack de cajas (abajo)
        DrawCube( halfScreenWidth-250, halfScreenHeight+200+boxSize*1.5, -220, boxSize, boxSize, boxSize, boxColors ); //stack de cajas (arriba)
        DrawCube( halfScreenWidth-250, halfScreenHeight+200+boxSize/2, -220-boxSize, boxSize, boxSize, boxSize, boxColors ); //caja a un ladito
        
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
                translationZ += 10;
                break;
            case GLFW_KEY_S:
                translationZ -=10;
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


void DrawCube( GLfloat centerPosX, GLfloat centerPosY, GLfloat centerPosZ, GLfloat width, GLfloat height, GLfloat length, GLfloat colors[])
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

    /*
    GLfloat colors[] =
    {
        0, 0, 0,   0, 0, 1,   0, 1, 1,   0, 1, 0,
        1, 0, 0,   1, 0, 1,   1, 1, 1,   1, 1, 0,
        0, 0, 0,   0, 0, 1,   1, 0, 1,   1, 0, 0,
        0, 1, 0,   0, 1, 1,   1, 1, 1,   1, 1, 0,
        0, 0, 0,   0, 1, 0,   1, 1, 0,   1, 0, 0,
        0, 0, 1,   0, 1, 1,   1, 1, 1,   1, 0, 1
    };
    */
   /*
    GLfloat colors[] =
    {
        0.71, 0.39, 0.11,   0.71, 0.39, 0.11,   0.0, 0.0, 0.0,   0.18, 0.09, 0.0,
        0.71, 0.39, 0.11,   0.71, 0.39, 0.11,   0.18, 0.09, 0.0,   0.18, 0.09, 0.0,
        0.71, 0.39, 0.11,   0.71, 0.39, 0.11,   0.18, 0.09, 0.0,   0.18, 0.09, 0.0,
        0.71, 0.39, 0.11,   0.71, 0.39, 0.11,   0.18, 0.09, 0.0,   0.0, 0.00, 0.0,
        0.71, 0.39, 0.11,   0.81, 0.59, 0.31,   0.71, 0.39, 0.11,   0.71, 0.39, 0.11,
        0, 0, 0,   0, 0, 0,   0, 0, 0,   0, 0, 0
    };
    */
    
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

void DrawRamp( GLfloat centerPosX, GLfloat centerPosY, GLfloat centerPosZ, GLfloat width, GLfloat height, GLfloat length)
{
    GLfloat xOffset = width * 0.5f;
    GLfloat yOffset = height * 0.5f;
    GLfloat zOffset = length * 0.5f;

    GLfloat quads[] =
    {
        // Cara Tracera
        centerPosX - xOffset, centerPosY + yOffset, centerPosZ - zOffset, // Arriba Izquierda
        centerPosX + xOffset, centerPosY + yOffset, centerPosZ - zOffset, // Arriba Derecha
        centerPosX + xOffset, centerPosY - yOffset, centerPosZ - zOffset, // Abajo Derecha
        centerPosX - xOffset, centerPosY - yOffset, centerPosZ - zOffset, // Abajo Izquierda
        
        // Cara Superior
        centerPosX - xOffset, centerPosY - yOffset, centerPosZ + zOffset, // Arriba Izquierda
        centerPosX - xOffset, centerPosY + yOffset, centerPosZ - zOffset, // Arriba Derecha
        centerPosX + xOffset, centerPosY + yOffset, centerPosZ - zOffset, // Abajo Derecha
        centerPosX + xOffset, centerPosY - yOffset, centerPosZ + zOffset, // Abajo Izquierda
        
        // Cara Inferior
        centerPosX - xOffset, centerPosY - yOffset, centerPosZ + zOffset, // Arriba Izquierda
        centerPosX - xOffset, centerPosY - yOffset, centerPosZ - zOffset, // Arriba Derecha
        centerPosX + xOffset, centerPosY - yOffset, centerPosZ - zOffset, // Abajo Derecha
        centerPosX + xOffset, centerPosY - yOffset, centerPosZ + zOffset  // Abajo Izquierda
    };

    GLfloat leftSide[] = {
         // Cara Izquierda
        centerPosX - xOffset, centerPosY + yOffset, centerPosZ - zOffset, // Arriba Dereccha
        centerPosX - xOffset, centerPosY - yOffset, centerPosZ - zOffset, // Abajo Derecha
        centerPosX - xOffset, centerPosY - yOffset, centerPosZ + zOffset, // Abajo Izquierda
        
        // Cara Derecha
        centerPosX + xOffset, centerPosY + yOffset, centerPosZ - zOffset, // Arriba Derecha
        centerPosX + xOffset, centerPosY - yOffset, centerPosZ - zOffset, // Abajo Derecha
        centerPosX + xOffset, centerPosY - yOffset, centerPosZ + zOffset, // Abajo Izquierda
    };

    GLfloat quadColors[] =
    {
        0, 0, 0,   0, 0, 1,   0, 1, 1,   0, 1, 0,
        0.71, 0.39, 0.11,   0.81, 0.59, 0.31,   0.71, 0.39, 0.11,   0.71, 0.39, 0.11,
        0, 0, 0,   0, 0, 0,   0, 0, 0,   0, 0, 0,
    };

    GLfloat triangleColors[] = {
        0.71, 0.39, 0.11,   0.0, 0.00, 0.0,   0.71, 0.39, 0.11,
        0.71, 0.39, 0.11,   0.0, 0.00, 0.0,   0.61, 0.29, 0.01,
    };
    
    glEnable(GL_DEPTH_TEST); //Agregar la proyección de profundidad
    glDepthMask(GL_TRUE);//Agregar la proyección de profundidad
    glEnableClientState( GL_VERTEX_ARRAY );
    glEnableClientState(GL_COLOR_ARRAY);
    glVertexPointer( 3, GL_FLOAT, 0, quads );
    glColorPointer(3, GL_FLOAT, 0, quadColors ); //Buffer de color
    glDrawArrays( GL_QUADS, 0, 12 );
    glVertexPointer( 3, GL_FLOAT, 0, leftSide );
    glColorPointer(3, GL_FLOAT, 0, triangleColors ); //Buffer de color
    glDrawArrays( GL_TRIANGLES, 0, 6 );
    glDisableClientState( GL_VERTEX_ARRAY );
    glDisableClientState(GL_COLOR_ARRAY);
}

void DrawWall( GLfloat centerPosX, GLfloat centerPosY, GLfloat centerPosZ, GLfloat width, GLfloat height, char plane)
{
    GLfloat wOffset = width * 0.5f;
    GLfloat hOffset = height * 0.5f;
    GLfloat wall[12];

    if (plane == 'x') {
        wall[0] = centerPosX; wall[1] = centerPosY + hOffset; wall[2] = centerPosZ - wOffset;
        wall[3] = centerPosX; wall[4] = centerPosY + hOffset; wall[5] = centerPosZ + wOffset;
        wall[6] = centerPosX; wall[7] = centerPosY - hOffset; wall[8] = centerPosZ + wOffset;
        wall[9] = centerPosX; wall[10] = centerPosY - hOffset; wall[11] = centerPosZ - wOffset;
    }
    else if (plane == 'y') {
        wall[0] = centerPosX + hOffset; wall[1] = centerPosY; wall[2] = centerPosZ - wOffset;
        wall[3] = centerPosX + hOffset; wall[4] = centerPosY; wall[5] = centerPosZ + wOffset;
        wall[6] = centerPosX - hOffset; wall[7] = centerPosY; wall[8] = centerPosZ + wOffset;
        wall[9] = centerPosX - hOffset; wall[10] = centerPosY; wall[11] = centerPosZ - wOffset;
    }
    else {
        wall[0] = centerPosX - wOffset; wall[1] = centerPosY + hOffset; wall[2] = centerPosZ;
        wall[3] = centerPosX + wOffset; wall[4] = centerPosY + hOffset; wall[5] = centerPosZ;
        wall[6] = centerPosX + wOffset; wall[7] = centerPosY - hOffset; wall[8] = centerPosZ;
        wall[9] = centerPosX - wOffset; wall[10] = centerPosY - hOffset; wall[11] = centerPosZ;
    }

    GLfloat colors[] =
    {
        0, 0, 0,   0, 0, 1,   0, 1, 1,   0, 1, 0,
    };
    
    glEnable(GL_DEPTH_TEST); //Agregar la proyección de profundidad
    glDepthMask(GL_TRUE);//Agregar la proyección de profundidad
    glEnableClientState( GL_VERTEX_ARRAY );
    glEnableClientState(GL_COLOR_ARRAY);
    glVertexPointer( 3, GL_FLOAT, 0, wall );
    glColorPointer(3, GL_FLOAT, 0, colors); //Buffer de color
    glDrawArrays( GL_QUADS, 0, 4 );
    glDisableClientState( GL_VERTEX_ARRAY );
    glDisableClientState(GL_COLOR_ARRAY);
}