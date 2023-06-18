#include "entity.h"
#include "side.h"
#include "game_event.h"
#include "../config.h"
#include <thread>

void PacMan::move(Room::Direction direction) {
    m_location->get_side(direction).enter(*this);
}

void PacMan::draw_into(sf::RenderWindow& window) {
    auto size = config::GAME_PACMAN_SIZE / 2;
    auto pacman_circle = sf::CircleShape(size);
    pacman_circle.setFillColor(config::GAME_COLOR_PACMAN);
    pacman_circle.setOrigin(size, size);
    pacman_circle.setPosition(m_location->get_position());
    window.draw(pacman_circle);
}

std::unique_ptr<IGameEvent> PacMan::visit(Food& ptr_food) {
    return std::make_unique<DeleteStaticEntity>(ptr_food);
}

std::unique_ptr<IGameEvent> PacMan::visit(Enemy& ptr_enemy) {
    return std::make_unique<LostGame>();
}

std::unique_ptr<IGameEvent> Food::accept(IVisitor& ptr_visitor) {
    return ptr_visitor.visit(*this);
}

void Food::draw_into(sf::RenderWindow& window) {
    float size = config::GAME_FOOD_SIZE / 2;
    auto food_circle = sf::CircleShape(size);
    food_circle.setFillColor(config::GAME_FOOD_COLOR);
    food_circle.setOrigin(size, size);
    food_circle.setPosition(m_location->get_position());
    window.draw(food_circle);
}

void Enemy::draw_into(sf::RenderWindow& window) {
    float size = config::GAME_ENEMY_SIZE / 2;
    auto enemy_circle = sf::CircleShape(size);
    enemy_circle.setFillColor(config::GAME_ENEMY_COLOR);
    enemy_circle.setOrigin(size, size);
    enemy_circle.setPosition(m_location->get_position());
    window.draw(enemy_circle);
}

void Enemy::action() {
    float delte_time = 0.2;
    if (m_time_before_action.getElapsedTime() > sf::seconds(delte_time)) {
        Room::Direction direction;
        for (size_t i = 0; i < 60; ++i) {
            direction = static_cast<Room::Direction>(s_side_choice(s_generator));
            auto [is_moved, previous_location] = m_location->get_side(direction).enter(*this);
            if (is_moved) {
//                m_previous_location = &previous_location;
                break;
            } else if (m_location == m_previous_location) {
                std::cout << "m_location == m_previous_location\n";
                using namespace std::chrono_literals;
//                std::this_thread::sleep_for(2s);
            }
//            m_previous_location = &previous_location;
        }
        m_time_before_action.restart();
    }
}

std::unique_ptr<IGameEvent> Enemy::accept(IVisitor& ptr_visitor) {
    return ptr_visitor.visit(*this);
}
