#pragma once


namespace GameData
{
	static sf::Vector2u _TileSize(16, 16);
	static int			_RenderRange = 12;
	static float		_DeltaTime;

	namespace Views
	{
		static sf::View _GameView; 
		static sf::View _HUDView;

		static sf::Vector2f _GameMousePosition;
		static sf::Vector2f _HUDMousePosition;
	}

	namespace Player
	{
		static int			_TotalEnemiesKilled;
		static sf::Vector2f _PlayerPosition; 
		static bool			_Enabled; 


		static const bool ValidateRendering(const sf::Sprite& otherobj)
		{
			// O...Object, P...Player, D...Difference
			int xO = otherobj.getPosition().x / GameData::_TileSize.x, yO = otherobj.getPosition().y / GameData::_TileSize.y;
			int xP = GameData::Player::_PlayerPosition.x / GameData::_TileSize.x, yP = GameData::Player::_PlayerPosition.y / GameData::_TileSize.y;
			int xD = std::abs(xP - xO), yD = std::abs(yP - yO);

			return (xD < GameData::_RenderRange && yD < GameData::_RenderRange);
		}
	}
	
}