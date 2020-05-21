//librerías que se utilizan
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <cstdlib>

//Se define el tamaño de la ventana
#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

//inicializar la ventana
int main( void )
{
    GLFWwindow *window;
    
  
    if ( !glfwInit( ) )
    {
        return -1;
    }
    
//Crear la ventana
    window = glfwCreateWindow( SCREEN_WIDTH, SCREEN_HEIGHT, "Practica_1", NULL, NULL );
    
    int screenWidth, screenHeight;
    glfwGetFramebufferSize( window, &screenWidth, &screenHeight );

   
    glfwMakeContextCurrent( window );
  
//

    glViewport( 0.0f, 0.0f, screenWidth, screenHeight );  // Espacio en donde se renderizara en la ventana
    glMatrixMode( GL_PROJECTION ); //Matriz de proyección
    glLoadIdentity( ); //Cración de matriz identidad
    glOrtho( 0, SCREEN_WIDTH, 0, SCREEN_HEIGHT, 0, 600 ); //Se crea el espacio de coordenadas
    glMatrixMode( GL_MODELVIEW ); //Creación de matriz de transformación
    glLoadIdentity( );
    
    // Se crea una variable para delimitar el centro de la pantalla (punto 0,0 del plano)
    GLfloat halfScreenWidth = SCREEN_WIDTH / 2;
    GLfloat halfScreenHeight = SCREEN_HEIGHT / 2;
    
    // Variable que se suma a la mitad de la pantalla (Se creó para dejar un margen)
    GLfloat halfSideLength = 200;
    
    //Arreglo con los vértices del triángulo
    GLfloat vertices[] =
    {
        halfScreenWidth, halfScreenHeight - halfSideLength, 0.0, // P1
        halfScreenWidth - halfSideLength, halfScreenHeight + halfSideLength, 0.0, // P2
        halfScreenWidth + halfSideLength, halfScreenHeight + halfSideLength, 0.0 // P3
    };
    
    //Arreglo con los colores en RGB de cada vértices del triángulo
    GLfloat colour[] =
    {
        0, 255, 0, //  Verde P1
        0, 0, 255, //  Azul  P2
        255, 0, 0  //  Rojo  P3
    };
    
    //Loop para renderizar el triángulo
    while ( !glfwWindowShouldClose( window ) )
    {
        glClear( GL_COLOR_BUFFER_BIT );
        glEnableClientState( GL_VERTEX_ARRAY ); //Definir que se está usando un arreglo de vértices)
        glEnableClientState( GL_COLOR_ARRAY );
        glVertexPointer( 3, GL_FLOAT, 0, vertices ); //Se crean los vértices
        glColorPointer( 3, GL_FLOAT, 0, colour ); //Se le asigna el color para cada vértice
        glDrawArrays( GL_TRIANGLES, 0, 3 ); //Dibujar los vértices a manera de triángulo
        glDisableClientState( GL_COLOR_ARRAY );
        glDisableClientState( GL_VERTEX_ARRAY ); //Se completa el proceso de uso de vértices
        
        glfwSwapBuffers( window );
        
        glfwPollEvents( );
    }
    
    glfwTerminate( );
    
    return 0;
}
