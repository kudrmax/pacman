#include "entity.h"
#include "side.h"
#include "game_event.h"

void PacMan::move(Room::Direction direction) {
    auto side = m_location->get_side(direction);
    side->enter(this);
}

void PacMan::draw_into(sf::RenderWindow& window) {
    float r = 20;
    auto circle = sf::CircleShape(r);
    circle.setFillColor(sf::Color::Yellow);
    circle.setOrigin(r, r);
    circle.setPosition(m_location->get_position());
    window.draw(circle);
}
std::unique_ptr<IGameEvent> PacMan::visit(Food* ptr_food) {
//    return std::unique_ptr<IGameEvent>();
    return std::make_unique<DeleteStaticEntity>(ptr_food);
}
