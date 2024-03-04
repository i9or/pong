#include "Utils.h"

float Utils::dot(const sf::Vector2f &a, const sf::Vector2f &b) {
  return a.x * b.x + a.y * b.y;
}

float Utils::length(const sf::Vector2f &a) {
  return std::sqrt(std::pow(a.x, 2.f) + std::pow(a.y, 2.f));
}

float Utils::distance(const sf::Vector2f &a, const sf::Vector2f &b) {
  return length(b - a);
}

sf::Vector2f Utils::reflect(const sf::Vector2f &a, const sf::Vector2f &normal) {
  return a - normal * (2 * dot(a, normal));
}
