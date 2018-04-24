#include <iostream>
#include <sstream>

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
			cout << m_name << " plays " << dom->toString() << endl;
			hand.erase(hand.begin()+i);
			return;
		}
	}

	// Otherwise, draw until a playable piece is found or the boneyard is empty.
	while(!table->boneyardEmpty())
	{
		shared_ptr<Domino> dom(table->draw());
		cout << m_name << " draws " << dom->toString() << endl;

		if (table->playPiece(dom))
		{
			cout << m_name << " plays " << dom->toString() << endl;
			return;
		}
		else
			hand.push_back(dom);
	}

	// No playable pieces, player was blocked this turn.
	cout << m_name << " is blocked this turn!" << endl;
	m_isBlocked = true;
}


bool Player::handEmpty()
{
	return hand.empty();
}


int Player::handSize()
{
	return hand.size();
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
	if(hand.empty()) {
		cout << m_name << "'s hand is empty." << endl;
	} else {
		cout << m_name << "'s hand (" << hand.size() << " pieces left): " << showHand() << endl;
	}
}

string Player::showHand()
{
	stringstream out;
	for (auto& dom : hand)
		out << "[" << dom->getTail() << "|" << dom->getHead() << "] ";
	return out.str();
}