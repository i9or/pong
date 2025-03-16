#pragma once

#include <SFML/System.hpp>

const float PI = 3.14159f;

struct Utils {
  static float dot(const sf::Vector2f &a, const sf::Vector2f &b);
  static float length(const sf::Vector2f &a);
  static float distance(const sf::Vector2f &a, const sf::Vector2f &b);
  static sf::Vector2f reflect(const sf::Vector2f &a, const sf::Vector2f &normal);
};