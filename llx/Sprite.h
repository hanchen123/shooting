#pragma once

class Sprite
{
public:
	Sprite(SDL_Renderer* pass_renderer, std::string FilePath, int rect_x, int rect_y, int rect_w, int rect_h);
	~Sprite(void);

	void Draw(int wrap_x, int wrap_y, int wrap_w, int wrap_h);
	void Setx(int x);
	void Sety(int y);
	int Getx();
	int Gety();

	SDL_Texture* Get_Sprite();

private:
	SDL_Texture* image;
	SDL_Rect rect;

	SDL_Renderer* renderer;
};

