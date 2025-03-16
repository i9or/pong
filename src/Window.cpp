#include "Window.h"

Window::Window() {
  create("Window", sf::Vector2u(1280, 800));
}

Window::Window(const std::string &title, const sf::Vector2u &size) {
  create(title, size);
}

Window::~Window() {
  destroy();
}

void Window::create(const std::string &title, const sf::Vector2u &size) {
  m_isDone = false;
  sf::VideoMode videoMode{{size.x, size.y}};
  m_window.create(videoMode, title, sf::Style::Close);
}

void Window::destroy() {
  m_window.close();
}

void Window::update() {
  while (const std::optional event = m_window.pollEvent()) {
    if (event->is<sf::Event::Closed>()) {
      m_isDone = true;
    } else if (const auto *keyPressed = event->getIf<sf::Event::KeyPressed>()) {
      switch (keyPressed->scancode) {
      case sf::Keyboard::Scancode::Escape:
        m_isDone = true;
        break;
      default:
        break;
      }
    }
  }
}

void Window::beginDraw() {
  m_window.clear(sf::Color::White);
}

void Window::endDraw() {
  m_window.display();
}

bool Window::isDone() const {
  return m_isDone;
}

void Window::draw(const sf::Drawable &drawable) {
  m_window.draw(drawable);
}

void Window::draw(const sf::Vertex *vertices, const std::size_t vertexCount, const sf::PrimitiveType type) {
  m_window.draw(vertices, vertexCount, type);
}

void Window::setTitle(const std::string &newTitle) {
  m_window.setTitle(newTitle);
}