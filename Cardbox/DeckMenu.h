#pragma once
#include "ToolMenu.h"


class DeckMenu : public ToolMenu
{
public:
	DeckMenu(AssetLoader &al,sf::Vector2u windowsize);
	~DeckMenu(void);
};

