#include <iostream>
#include <SDL3/SDL.h>
//#include <SDL3/SDL_ttf.h>

struct Paddle
{
	SDL_FRect rect;
	float vel;
};

struct Ball
{
	SDL_FRect rect;

	float velX;
	float velY;
};

void displayScore(int left, int right)
{
	
}

void movePaddle(Paddle &p)
{
	p.rect.y += p.vel;
}

void detectCollision(Paddle& p1, Paddle& p2, Ball& b)
{
	if (b.rect.x < (p1.rect.x + 20) && ( b.rect.y > p1.rect.y && b.rect.y < (p1.rect.y + 50)))
	{
		b.rect.x += 5;
		b.velX *= -1.1;
	}

	if ((b.rect.x + 10) > p2.rect.x && (b.rect.y > p2.rect.y && b.rect.y < (p2.rect.y + 50)))
	{
		b.rect.x -= 5;
		b.velX *= -1.1;
	}
}

void resetBall(Ball& b)
{
	b = { {390, 290, 10, 10}, 3, 3 };
}

void moveBall(Ball& b)
{
	b.rect.x += b.velX;
	b.rect.y += b.velY;
	if (b.rect.y < 0 or b.rect.y >= 590)
		b.velY *= -1;
	if (b.rect.x < 45 or b.rect.x >= 745)
		resetBall(b);
}

int main()
{
	// 1. initialization of subsystems
	SDL_Init(SDL_INIT_VIDEO);

	// 2. declaring window and renderer
	SDL_Window* window = nullptr;
	SDL_Renderer* renderer = nullptr;

	SDL_CreateWindowAndRenderer("The Game", 800, 600, SDL_WINDOW_RESIZABLE, &window, &renderer);


	// define rectangle -> x, y, w, h

	Paddle p1 = { {30, 300, 20, 50}, 0 };
	Paddle p2 = { {750, 200, 20, 50}, 0 };
	Ball b = { {390, 290, 10, 10}, 3, 3 };

	// 3. gameloop
	bool quit = false;
	while (!quit)
	{
		// 4. event handling
		SDL_Event e;
		while (SDL_PollEvent(&e))
		{
			
			SDL_Keycode key = e.key.key;
			std::cout << "Key Pressed: " << SDL_GetKeyName(key) << std::endl;
			
			if (e.type == SDL_EVENT_QUIT)
			{
				quit = true;
			}
			
			if (e.type == SDL_EVENT_KEY_DOWN && e.key.repeat == 0)
			{
				switch (key)
				{
				// exit when Q or ESC is pressed
				case SDLK_Q:
				case SDLK_ESCAPE:
					quit = true;
					break;
					
				// move left paddle on keypress
				case SDLK_W:
					p1.vel += -5;
					break;
				case SDLK_S:
					p1.vel += 5;
					break;

				// move right paddle on keypress
				case SDLK_UP:
					p2.vel += -5;
					break;
				case SDLK_DOWN:
					p2.vel += 5;
					break;
				}
			}
			else if (e.type == SDL_EVENT_KEY_UP && e.key.repeat == 0)
			{
				switch (key)
				{
				case SDLK_W:
					p1.vel += 5;
					break;
				case SDLK_S:
					p1.vel += -5;
					break;

				case SDLK_UP:
					p2.vel += 5;
					break;
				case SDLK_DOWN:
					p2.vel += -5;
					break;
				}
			}

		}

		
		p1.rect.y = SDL_clamp(p1.rect.y, 0, 550);
		p2.rect.y = SDL_clamp(p2.rect.y, 0, 550);
		

		// 5. Render Clear
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		SDL_RenderClear(renderer);

		// 6. Draw Rectangle
		movePaddle(p1);
		movePaddle(p2);
		moveBall(b);
		detectCollision(p1, p2, b);
		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
		SDL_RenderFillRect(renderer, &p1.rect);
		SDL_RenderFillRect(renderer, &p2.rect);
		SDL_RenderFillRect(renderer, &b.rect);

		// 7. Render on Display
		SDL_RenderPresent(renderer);

		SDL_Delay(16);
	}

	// 8. Clean Up
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();

	std::cout << "Program Exited succesfully!" << std::endl;

	return 0;
}