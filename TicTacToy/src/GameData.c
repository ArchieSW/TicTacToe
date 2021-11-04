#include "pch.h"
#include "GameData.h"

void GetPlacePosition(int* placeX, int* placeY, int mouseX, int mouseY, int WindowHeight, int WindowWidth) {
	int tmpY = WindowHeight / 3;
	int tmpX = WindowWidth / 3;
	*placeX = mouseX / tmpX;
	*placeY = mouseY / tmpY;
}


void SetPlace(int placeX, int placeY, PlaceState state, GameData* game_data) {
	game_data->map[placeY][placeX] = state;
}


PlaceState** CreateNewMap(int n, int m) {
	PlaceState** map = (PlaceState**)calloc(n, sizeof(PlaceState*));
	if (!map) {
		printf("[ERROR]: FAILED TO ALLOCATE MEMORY\n");
		return NULL;
	}
	for (int i = 0; i < n; i++)
	{
		map[i] = (PlaceState*)calloc(m, sizeof(PlaceState));
		if (!map[i]) {
			printf("[ERROR]: FAILED TO ALLOCATE MEMORY\n");
			return NULL;
		}
	}
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			map[i][j] = EMPTY;
		}
	}
	return map;
}


void UpdatePlace(GameData* game_data, int placeX, int placeY) {
	PlaceState** map = game_data->map;
	if (map[placeY][placeX] != EMPTY) {
		printf("[INFO]: PLAYER SELECTED NOT EMPTY PLACE\n");
		return;
	}
	map[placeY][placeX] = (PlaceState)((int)game_data->turn);
	game_data->turn = (PlayerTurn)(1 - (int)game_data->turn);
	game_data->winner = GetWinner(game_data);
}


void FreeMap(PlaceState** map, int n, int m) {
	for (int i = 0; i < 3; i++)
	{
		free(map[i]);
	}
	free(map);
}


WinnerState GetWinner(GameData* game_data) {
	PlaceState** map = game_data->map;
	for (int i = 0; i < 3; i++)
	{
		if (map[i][0] == map[i][1] && map[i][1] == map[i][2] && map[i][2] != EMPTY) {
			return (WinnerState)map[i][0];
		}
	}
	for (int i = 0; i < 3; i++)
	{
		if (map[0][i] == map[1][i] && map[1][i] == map[2][i] && map[2][i] != EMPTY) {
			return (WinnerState)map[0][i];
		}
	}
	if (map[0][0] == map[1][1] && map[1][1] == map[2][2] && map[2][2] != EMPTY) {
		return (WinnerState)map[0][0];
	}
	if (map[0][2] == map[1][1] && map[1][1] == map[2][0] && map[2][0] != EMPTY) {
		return (WinnerState)map[0][2];
	}
	bool allFilled = true;
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			if (map[i][j] == EMPTY)
				allFilled = false;
		}
	}
	if (allFilled) {
		return WINNERDRAW;
	}
	return WINNERPASS;
}