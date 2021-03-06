#pragma once

enum PACKET_ID
{
	EMPTY,
	CONTINUE,
	START,
	REQUEST_UPLOAD,
	ACCEPT_REQUEST,
	DECLINE_REQUEST,
	UPLOAD,
	UPLOAD_DONE,
	TURN_CARD,
	ROTATE_CARD,
	PICK_UP_CARD,
	RELEASE_CARD,
	DRAW_FROM_DECK,
	AREA,
	SHUFFLE,
	MOVE_SHIT,
	MESSAGE,
};

enum PHASE
{
	CONNECTIONS,
	DOWNLOADS,
	GAME,
};