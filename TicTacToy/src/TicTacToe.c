#include "pch.h"
#include "Window.h"
#include "Color.h"
#include "Image.h"
#include "GameData.h"

#define SCREEN_WIDTH 720	
#define SCREEN_HEIGHT 720

SDL_Window* window = NULL; // окно
SDL_Surface* screen_surface = NULL; // оболочка дл€ окна


int init();
void update();
void render();


bool isRunning = true;

int main(int argc, char** args) {
	if (init()) {
		printf("[ERROR]: FAILED TO INIT PROGRAM\n");
		return 1;
	}
	Window* window = create_new_window("TicTacToe!", 720, 720, (Color) { 0, 0, 0 });
	GameData* game_data = (GameData*)malloc(sizeof(GameData));

	if (!game_data) {
		printf("[ERROR]: FAILED TO ALLOCATE MEMORY\n");
		return 1;
	}
	
	game_data->map = CreateNewMap(3, 3);
	game_data->turn = TURNCROSS;
	game_data->winner = WINNERPASS;
	
	Image*** map = (Image***)calloc(3, sizeof(Image**));
	if (!map) {
		printf("[ERROR]: FAILED TO ALLOCATE MEMORY\n");
		return 1;
	}
	for (int i = 0; i < 3; i++)
	{
		map[i] = (Image**)calloc(3, sizeof(Image*));
		if (!map[i]) {
			printf("[ERROR]: FAILED TO ALLOCATE MEMORY\n");
			return 1;
		}
	}

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			map[i][j] = create_new_image(j * (SCREEN_WIDTH / 3), i * (SCREEN_HEIGHT / 3), "assets/clear_space.bmp");
			map[i][j]->state = EMPTY;
			glue_image(map[i][j], window);
		}
	}

	Image* CrossesLayer = create_new_image(0,0,"assets/crosses_won.bmp");
	Image* ZeroesLayer = create_new_image(0,0,"assets/zeroes_won.bmp");
	Image* DrawLayer = create_new_image(0,0,"assets/draw_screen.bmp");
	Image* WinnersLayer = NULL;
	bool WinnerFound = false;

	while (isRunning) {

		update(game_data);
		if (!WinnerFound)
			render(game_data, map, window);
		if (game_data->winner != WINNERPASS && !WinnerFound) {
			switch (game_data->winner)
			{
			case WINNERCROSS:
				WinnersLayer = CrossesLayer;
				break;
			case WINNERDRAW:
				WinnersLayer = DrawLayer;
				break;
			case WINNERZERO:
				WinnersLayer = ZeroesLayer;
				break;
			default:
				break;
			}
			glue_image(WinnersLayer, window);
			SDL_UpdateWindowSurface(window->window);
			printf(SDL_GetError());
			WinnerFound = true;
		}
	}


	free_image(CrossesLayer);
	free_image(ZeroesLayer);
	free_image(DrawLayer);
	free_window(window);

	FreeMap(game_data->map, 3, 3);
	free(game_data);

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			free_image(map[i][j]);
		}
		free(map[i]);
	}
	free(map);
	SDL_Quit();

	return 0;
}


void update(GameData* game_data) {
	static bool forMotion;
	SDL_Event event;
	int x, y;
	int posX, posY;
	while (SDL_PollEvent(&event)) {
		switch (event.type)
		{
		case SDL_QUIT:
			isRunning = false;
			break;
		case SDL_MOUSEMOTION:
			if (forMotion) {
				printf("[INFO]: SDL_MOUSEMOTION\n");
				forMotion = false;
			}
			break;
		case SDL_MOUSEBUTTONDOWN:
			printf("[INFO]: SDL_MOUSEBUTTONDOWN\n");
			forMotion = true;
			break;
		case SDL_MOUSEBUTTONUP:
			printf("[INFO]: SDL_MOUSEBUTTONUP\n");
			forMotion = true;
			SDL_GetMouseState(&x, &y);
			printf("[INFO]: MOUSE POSITION: X = %d Y = %d\n", x, y);
			GetPlacePosition(&posX, &posY, x, y, SCREEN_HEIGHT, SCREEN_WIDTH);
			printf("[INFO]: SELECTED SPACE: X = %d Y = %d\n", posX, posY);
			UpdatePlace(game_data, posX, posY);
			break;
		default:
			break;
		}
	}
	static bool stop_loging_winner;
	switch (game_data->winner)
	{
	case WINNERCROSS:
		if (!stop_loging_winner) {
			printf("[INFO]: CROSSES WON\n");
			stop_loging_winner = true;
		}
		break;
	case WINNERZERO:
		if (!stop_loging_winner) {
			printf("[INFO]: ZEROES WON\n");
			stop_loging_winner = true;
		}
		break;
	default:
		break;
	}
}


void render(GameData* game_data, Image*** map, Window* window) {
	
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			if (game_data->map[i][j] != map[i][j]->state) {
				Image* new_image = NULL;
				switch (game_data->map[i][j])
				{
				case EMPTY:
					new_image = create_new_image(j * (SCREEN_WIDTH / 3), i * (SCREEN_HEIGHT / 3), "assets/clear_space.bmp");
					break;
				case CROSS:
					new_image = create_new_image(j * (SCREEN_WIDTH / 3), i * (SCREEN_HEIGHT / 3), "assets/cross_space.bmp");
					break;
				case ZERO:
					new_image = create_new_image(j * (SCREEN_WIDTH / 3), i * (SCREEN_HEIGHT / 3), "assets/zero_space.bmp");
					break;
				default:
					break;
				}
				if (!new_image) {
					printf("[ERROR]: FAILED TO ALLOCATE MEMORY\n");
					return;
				}
				new_image->state = game_data->map[i][j];
				free_image(map[i][j]);
				map[i][j] = new_image;
				glue_image(map[i][j], window);
			}
		}
	}

	SDL_UpdateWindowSurface(window->window);
	SDL_Delay(10);
}


int init() {
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) { // »нициализируем библиотеку SDL
		printf("[ERROR]: FAILED TO INIT SDL\n");
		printf(SDL_GetError());
		return 1;
	}

	return 0;
}