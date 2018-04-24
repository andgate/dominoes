#include <iostream>

#include "player.h"

Player::Player(string name)
	: hand(), m_name(name), m_isBlocked(false)
{}


Player::~Player() {}


void Player::draw(Table* table)
{
	shared_ptr<Domino> dom = table->draw();
	hand.push_back(dom);
}


void Player::draw(Table* table, int amount)
{
	for(int i = 0; i < amount; ++i)
	{
		draw(table);
	}
}


void Player::playTurn(Table* table)
{
	m_isBlocked = false;

	// Try to play every piece in the hand.
	for(size_t i = 0; i < hand.size(); ++i)
	{
		shared_ptr<Domino> dom(hand[i]); 
		if(table->playPiece(dom))
		{
			hand.erase(hand.begin()+i);
			return;
		}
	}

	// Otherwise, draw until a playable piece is found or the boneyard is empty.
	while(!table->boneyardEmpty())
	{
		shared_ptr<Domino> dom(table->draw());

		if (table->playPiece(dom))
			return;
		else
			hand.push_back(dom);
	}

	// No playable pieces, player was blocked this turn.
	m_isBlocked = true;
}


bool Player::handEmpty()
{
	return hand.empty();
}


bool Player::isBlocked()
{
	return m_isBlocked;
}


string Player::getName()
{
	return m_name;
}


void Player::printHand()
{
	for (auto& dom : hand)
		cout << "[" << dom->getTail() << "|" << dom->getHead() << "] ";
	cout << endl;
}