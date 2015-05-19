#ifndef LOCAL_BULLETS_H
#define LOCAL_BULLETS_H

#include "Entity.h"
#include "Game.h"

class Bullets : public Entity {
public:
  Bullets(EventManager& events);

  void addBullet(Origin origin, const sf::Vector2f& pos, const sf::Vector2f& velocity, const sf::Color& color);

  virtual void update(float dt) override;
  virtual void render(sf::RenderWindow& window) override;

private:
  EventStatus onPositionEvent(EventType type, Event *event);
  EventStatus onShootEvent(EventType type, Event *event);

private:
  struct Bullet {
    Origin origin;
    sf::Vector2f pos;
    sf::Vector2f velocity;
    sf::Color color;
    bool active;
  };

  std::vector<Bullet> m_bullets;
};


#endif // LOCAL_BULLETS_H
