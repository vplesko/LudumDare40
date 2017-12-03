#include "StateMidLevel.h"
#include "Consts.h"
#include <sstream>
#include "StateInGame.h"
#include "StateMainMenu.h"

StateMidLevel::StateMidLevel(Engine *engine, MidLevelInfo *info) : GameState(engine), sprites(info->soldiersDied) {
	engine->setClearColor(sf::Color::Black);

	this->info = info;

	text.setPosition(20, 50);
	text.setFont(engine->getFonts().get(Consts::MID_LEVEL_FONT));
	text.setCharacterSize(18);
	text.setFillColor(sf::Color::White);
	text.setStyle(sf::Text::Bold);

	if (info->prevLvlLost) {
		std::stringstream str;
		str << "YOU HAVE FAILED.";
		str << "\nOUR BRAVE SOLDIERS ARE READY TO TRY AGAIN.";
		str << "\n\nPRESS ENTER TO RETRY";

		text.setString(str.str());
	} else {
		if (info->levelInd + 1 >= Consts::LEVELS.size()) {
			std::stringstream str;
			str << "CONGRATULATIONS, YOU HAVE DEFEATED THE EVIL GUERILLA!";
			str << "\nSADLY, NOT ALL OF US COULD BE HERE TO CELEBRATE.";
			str << "\n" << info->soldiersDied << " BRAVE SOULS WERE LOST IN THIS FIGHT.";
			str << "\nWE WILL NOT FORGET YOU: SOLDIER01, SOLDIER02, SOLDIER03, ...";
			
			text.setString(str.str());
		} else {
			std::stringstream str;
			str << "LEVEL " << (info->levelInd + 1) << " COMPLETE!";
			str << "\n\nTOTAL SOLDIERS LOST: " << info->soldiersDied;

			text.setString(str.str());
		}
	}

	float x = 20, y = 180;
	for (unsigned i = 0; i < sprites.size(); ++i) {
		sprites[i].setTexture(getEngine()->getTextures().get(Consts::SOLDIER_TEXTURE));
		sprites[i].setPosition(x, y);

		x += sprites[i].getGlobalBounds().width + 8;
		if (x >= 600) x = 20, y += sprites[i].getGlobalBounds().height + 8;
	}
}

void StateMidLevel::onEvent(sf::Event ev) {
	if (ev.type == sf::Event::KeyPressed) {
		if (ev.key.code == sf::Keyboard::Escape) {
			getEngine()->setOver(true);
			return;
		} else {
			if (info->prevLvlLost) {
				info->prevLvlLost = false;
				getEngine()->changeState(new StateInGame(getEngine(), info));
			} else {
				if (++info->levelInd >= Consts::LEVELS.size()) {
					getEngine()->changeState(new StateMainMenu(getEngine()));
				} else {
					getEngine()->changeState(new StateInGame(getEngine(), info));
				}		
			}
		}
	}
}

void StateMidLevel::update(sf::Time delta) {
}

void StateMidLevel::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	target.draw(text, states);

	for (unsigned i = 0; i < sprites.size(); ++i) target.draw(sprites[i], states);
}