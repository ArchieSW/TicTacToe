#pragma once
typedef enum PlayerTurn {
	TURNCROSS = 0,
	TURNZERO
} PlayerTurn;


typedef enum PlaceState {
	CROSS = 0,
	ZERO,
	EMPTY
} PlaceState;


typedef enum WinnerState {
	WINNERCROSS = 0,
	WINNERZERO,
	WINNERDRAW,
	WINNERPASS
} WinnerState;


typedef struct GameData {
	PlaceState** map;
	PlayerTurn turn;
	WinnerState winner;
} GameData;


PlaceState** CreateNewMap(int n, int m);
void FreeMap(PlaceState** map, int n, int m);
void GetPlacePosition(int* placeX, int* placeY, int mouseX, int mouseY, int WindowHeight, int WindowWidth);
void SetPlace(int placeX, int placeY, PlaceState state, GameData* game_data);
void UpdatePlace(GameData* game_data, int placeX, int placeY);
WinnerState GetWinner (GameData* game_data);