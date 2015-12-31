#ifndef ENGINE_H
#define ENGINE_H

GLuint tile = 0;

void Initialize()
{
	tile = loadTexture( "tile.png" );
}
void Update()
{
	
}

void Render()
{
	glBindTexture(GL_TEXTURE_2D, tile);
 
// For Ortho mode, of course
int X = 0;
int Y = 0;
int Width = 100;
int Height = 100;
 
glBegin(GL_QUADS);
    glTexCoord2f(0, 0); glVertex3f(X, Y, 0);
    glTexCoord2f(1, 0); glVertex3f(X + Width, Y, 0);
    glTexCoord2f(1, 1); glVertex3f(X + Width, Y + Height, 0);
    glTexCoord2f(0, 1); glVertex3f(X, Y + Height, 0);
glEnd();
}

#endif