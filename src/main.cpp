#include "physics.hpp"
#include <SFML/Graphics.hpp>
#include <chrono>
#include <cmath>
#include <future>
// #include <imgui-SFML.h>
// #include <imgui.h>
#include <thread>
#include <vector>

#define SCREEN_WIDTH 1000
#define SCREEN_HEIGHT 550
#define PI 3.1415
#define IMGUI_WINDOW_TITLE "Trajectory Simulator"

sf::Font regularFont;
float particleX = 0;
float particleY = 0;
float InitialParticleX = 20;
float InitialParticleY = SCREEN_HEIGHT - 40;
bool reachedOriginalY = false;

float theta = 45;
float thetaInRadians = theta * PI / 180;
float initialVelocity = 100; // Pixels per second
float range = trajectory::getRange(theta, initialVelocity);
float increment = 1;

bool isMenuOpen = false;

void logPosition(sf::CircleShape &particle, sf::Text &label) {
  label.setString("X: " + std::to_string(particle.getPosition().x) +
                  "\nY: " + std::to_string(particle.getPosition().y));
}

void moveParticle(sf::CircleShape &particle) {
  particleY = -1 * trajectory::getYPosition(theta, initialVelocity, particleX);
  std::this_thread::sleep_for(std::chrono::milliseconds(5));
  if (particle.getPosition().x == std::ceil(range))
    particleX = 0;
  particleX += increment;
  particle.setPosition(
      sf::Vector2f(particleX + InitialParticleX, particleY + InitialParticleY));
}

// void ImguiRenderStuff() { ImGui::Text("Hello world"); }

void MainMenu() {}

int main() {
  sf::RenderWindow window(sf::VideoMode(1000, 550), "Trajectory Simulator");
  // ImGui::SFML::Init(window);

  sf::Clock deltaClock;

  // Heading
  sf::Font headingFont;
  headingFont.loadFromFile("assets/font/font.ttf");
  sf::Text heading("Trajectory Simulator", headingFont);
  heading.setCharacterSize(50);
  heading.setStyle(sf::Text::Regular);
  heading.setFillColor(sf::Color::Blue);
  float headingWidth = heading.getLocalBounds().width / 2;
  heading.setPosition(sf::Vector2f(SCREEN_WIDTH / 2.0 - headingWidth, 20));

  // X and Y positions logging
  regularFont.loadFromFile("assets/font/open_sans.ttf");
  sf::Text positionLog("", regularFont);
  positionLog.setCharacterSize(20);
  positionLog.setStyle(sf::Text::Regular);
  positionLog.setFillColor(sf::Color::White);
  positionLog.setPosition(sf::Vector2f(20, 80));

  // Particle
  sf::CircleShape particle;
  particle.setRadius(10);
  particle.setFillColor(sf::Color::White);
  particle.setPosition(sf::Vector2f(InitialParticleX, InitialParticleY));

  // Ground
  sf::RectangleShape ground;
  ground.setSize(sf::Vector2f(window.getSize().x, 20));
  ground.setFillColor(sf::Color::Green);
  ground.setPosition(
      sf::Vector2f(0, InitialParticleY + 2 * particle.getRadius()));

  // Main Menu Objects

  while (window.isOpen()) {
    sf::Event event;
    while (window.pollEvent(event)) {

      // ImGui::SFML::ProcessEvent(window, event);

      if (event.type == sf::Event::Closed)
        window.close();
    }
    // ImGui part starts
    // ImGui::SFML::Update(window, deltaClock.restart());
    // ImGui::Begin(IMGUI_WINDOW_TITLE);
    // ImguiRenderStuff();
    // ImGui::End();
    // ImGui part ends
    window.clear();

    std::future<void> a_MoveParticle =
        std::async(&moveParticle, std::ref(particle));

    window.draw(heading);
    window.draw(particle);
    logPosition(particle, positionLog);
    window.draw(positionLog);
    window.draw(ground);
    // ImGui::SFML::Render(window);
    window.display();
  }
  // ImGui::SFML::Shutdown();
  return 0;
}
