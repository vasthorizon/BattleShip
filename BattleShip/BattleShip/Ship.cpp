#include "stdafx.h"
#include "Ship.h"

Ship::Ship()
{
	m_HP = 0;
	memset(m_Pos, 0, sizeof(Position)* 5);
}

Ship::~Ship()
{
}

void Ship::AddPosition(char x, char y)
{
	Position pos;
	pos.m_X = x;
	pos.m_Y = y;
	AddPosition(pos);
}

void Ship::AddPosition(Position pos)
{
	pos.m_X = (char)tolower(pos.m_X);

	for (int i = 0; i < m_HP; i++)
	{
		if (m_Pos[i].m_X == pos.m_X && m_Pos[i].m_Y == pos.m_Y)
		{
			printf_s("ERROR : Already Exist\n");
			return;
		}
	}

	for (int i = 0; i < m_HP; i++)
	{
		if (m_Pos[i].m_X == 0)
		{
			m_Pos[i].m_X = pos.m_X;
			m_Pos[i].m_Y = pos.m_Y;
			
			break;
		}
	}
}

HitResult Ship::HitCheck(Position hitPos)
{
	hitPos.m_X = (char)tolower(hitPos.m_X);

	for (int i = 0; i < m_MaxHP; i++)
	{
		if (m_Pos[i].m_X == hitPos.m_X && m_Pos[i].m_Y == hitPos.m_Y)
		{
			m_Pos[i].m_X = 0;
			m_Pos[i].m_Y = 0;
			m_HP--;

			switch (m_Type)
			{
			case AIRCRAFT:
				return DESTROY_AIRCRAFT;
			case BATTLESHIP:
				return DESTROY_BATTLESHIP;
			case CRUISER:
				return DESTROY_CRUISER;
			case DESTROYER:
				return DESTROY_DESTROYER;
			default:
				printf_s("Ship.cpp : HitCheck - MAKE NEW CASE\n");
				break;
			}

			return HIT;
		}
	}

	return MISS;
}

void Ship::Print()
{
	printf_s("%s HP : %d POS :[", m_Name.c_str(), m_HP);
	for( int i = 0; i < m_MaxHP; i++ )
	{
		printf_s( " (%c, %c) " , m_Pos[i].m_X , m_Pos[i].m_Y );
	}
	printf( "]\n" );
}

/*
Returns true if position does not already exist
returns false if position does exist already
*/
bool Ship::PositionCheck( int posX, int posY )
{

	for( int i = 0; i < m_MaxHP; i++ )
	{
		if( m_Pos[i].m_X == posX && m_Pos[i].m_Y == posY )
		{
			return false;
		}
	}

	return true;
}
