#ifndef ASSETS_H
#define ASSETS_H

GLuint* loadTexture( char* path )
{
    GLuint texture = 0;
 
	// You should probably use CSurface::OnLoad ... ;)
	//-- and make sure the Surface pointer is good!
	SDL_Surface* surface = IMG_Load(path);
	SDL_Texture* tex = SDL_CreateTextureFromSurface(renderer, surface);
	int w, h;
	SDL_QueryTexture(tex, NULL, NULL, &w, &h);
	float wf = w;
	float hf = h;
	glGenTextures( 1, &texture );
	SDL_GL_BindTexture(tex,
                       &wf,
                       &hf);

	SDL_FreeSurface(surface);

	return texture;
}

#endif
