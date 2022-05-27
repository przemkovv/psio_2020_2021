#pragma once
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>

#include <iostream>
#include <vector>


class AnimatedSprite : public sf::Sprite
{
private:
	std::vector<sf::IntRect> frames_;
	float frameDurationMs_;

	std::size_t indexFrame_ = 0;
	std::int64_t sinceLastChange = 0;

	sf::Vector2f speed_{0, 0}; // Speed is in pixels per second
public:
	AnimatedSprite(
		const sf::Texture& texture,
		float fps
	) :
		frameDurationMs_((1.0f / fps) * 1'000),
		frames_({
			sf::IntRect{
				{0, 0},
				sf::Vector2i{texture.getSize()}
			}
		}) {

		setTexture(texture);
		setTextureRect(frames_[indexFrame_]);

	}

	void setFrames(const std::vector<sf::IntRect>& frames) {
		indexFrame_ = 0;
		frames_ = frames;
		setTextureRect(frames_[indexFrame_]);
	}

	void setSpeed(const sf::Vector2f& speed) {
		speed_ = speed;
	}

	void Step(std::int64_t millisecondsElapsed, const sf::Vector2f& windowSize) {
		sinceLastChange += millisecondsElapsed;
		if (sinceLastChange > frameDurationMs_)
		{
			indexFrame_ = (indexFrame_ + 1) % frames_.size();
			setTextureRect(frames_[indexFrame_]);
			sinceLastChange = 0;
		}

		if (speed_ != sf::Vector2f{0, 0})
		{
			move(frameDurationMs_ / 1'000.0f * speed_);
		}
		auto position = getPosition();
		if (position.x > windowSize.x)
		{
			position.x -= windowSize.x;
		}
		else if (position.x < 0)
		{
			position.x += windowSize.x;
		}
		if (position.y > windowSize.y)
		{
			position.y -= windowSize.y;
		}
		else if (position.y < 0)
		{
			position.y += windowSize.y;
		}
		setPosition(position);
	}
};
