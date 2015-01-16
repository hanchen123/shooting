#include "StdAfx.h"
#include "Sprite.h"

Sprite::Sprite(SDL_Renderer* pass_renderer, std::string FilePath, int rect_x, int rect_y, int rect_w, int rect_h)
{
	renderer = pass_renderer;

	image = NULL;
	image = IMG_LoadTexture(pass_renderer, FilePath.c_str());
	if (image == NULL) {
		std::cout << "image load errer" << std::endl;
	}

	rect.x = rect_x;
	rect.y = rect_y;
	rect.w = rect_w;
	rect.h = rect_h;
}


Sprite::~Sprite(void)
{
	SDL_DestroyTexture(image);
}

void Sprite::Draw(int wrap_x, int wrap_y, int wrap_w, int wrap_h)
{
	SDL_Rect wrap;
	wrap.x = wrap_x;
	wrap.y = wrap_y;
	wrap.w = wrap_w;
	wrap.h = wrap_h;

	SDL_RenderCopy(renderer, image, &wrap, &rect);
}

void Sprite::Setx(int x) 
{
	rect.x = x;
}

void Sprite::Sety(int y) 
{
	rect.y = y;
}

int Sprite::Getx()
{
	return rect.x;
}

int Sprite::Gety()
{
	return rect.y;
}

SDL_Texture* Sprite::Get_Sprite()
{
	return image;
}