#ifndef LOCAL_BULLETS_H
#define LOCAL_BULLETS_H

#include "Entity.h"
#include "Game.h"
#include "Resources.h"

class Bullets : public Entity {
public:
  Bullets(EventManager& events, ResourceManager &manager);

  void addBullet(Origin origin, const sf::Vector2f& pos, const sf::Vector2f& velocity);

  virtual void update(float dt) override;
  virtual void render(sf::RenderWindow& window) override;

private:
  EventStatus onLocationEvent(EventType type, Event *event);
  EventStatus onShootEvent(EventType type, Event *event);

private:
  struct Bullet {
    Origin origin;
    sf::Vector2f pos;
    sf::Vector2f velocity;
    sf::Texture *texture;
    bool active;
  };

  std::vector<Bullet> m_bullets;
  sf::Texture *m_bulletBlueTexture;
  sf::Texture *m_bulletGreenTexture;
};


#endif // LOCAL_BULLETS_H
