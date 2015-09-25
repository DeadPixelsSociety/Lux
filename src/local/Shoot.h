/*
 * Lux
 *
 * Copyright (c) 2015, Julien Bernard
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#ifndef LOCAL_SHOOT_H
#define LOCAL_SHOOT_H

#include <memory>

#include "Game.h"

enum class ShootType {
  CONE,
  PERIODIC,
};

class Shoot {
public:
  virtual ~Shoot();
  virtual void shoot(float dt, const sf::Vector2f& pos, sf::Vector2f& dir, EventManager& events) = 0;
};

std::unique_ptr<Shoot> makeSimpleShoot(Origin origin, sf::Color color, float delay);
std::unique_ptr<Shoot> makeBurstShoot(Origin origin, sf::Color color, float delay, float period, int count);
std::unique_ptr<Shoot> makeConeShoot(Origin origin, sf::Color color, float delay);
std::unique_ptr<Shoot> makeContinuousSimpleShoot(Origin origin, sf::Color color, float period);
std::unique_ptr<Shoot> makeSimplePlayerShoot(Origin origin, sf::Color color, int nbshoot, float shootInterval, float inactivePeriod);


class ConcreteShoot : public Shoot {
public:
  ConcreteShoot(Origin origin, sf::Color color)
  : m_origin(origin)
  , m_color(color)
  {

  }

  Origin getOrigin() const {
    return m_origin;
  }

  const sf::Color& getColor() const {
    return m_color;
  }

private:
  Origin m_origin;
  sf::Color m_color;
};

class SingleShoot : public ConcreteShoot {
public:
  SingleShoot(Origin origin, sf::Color color)
  : ConcreteShoot(origin, color)
  {

  }

  virtual void shoot(float dt, const sf::Vector2f& pos, sf::Vector2f& dir, EventManager& events) override;

};


class ConeShoot : public ConcreteShoot {
public:
  ConeShoot(Origin origin, sf::Color color)
  : ConcreteShoot(origin, color)
  {

  }

  virtual void shoot(float dt, const sf::Vector2f& pos, sf::Vector2f& dir, EventManager& events) override;

};




class ShootDecorator : public Shoot {
public:
  ShootDecorator(std::unique_ptr<Shoot> decorated)
  : m_decorated(std::move(decorated))
  {
  }

protected:
  Shoot& getDecorated() {
    return *m_decorated;
  }

private:
  std::unique_ptr<Shoot> m_decorated;
};


class PeriodicShoot : public ShootDecorator {
public:
  PeriodicShoot(std::unique_ptr<Shoot> decorated, float period)
  : ShootDecorator(std::move(decorated))
  , m_elapsedTime(0.0f)
  , m_period(period)
  {

  }

  virtual void shoot(float dt, const sf::Vector2f& pos, sf::Vector2f& dir, EventManager& events) override;

private:
  float m_elapsedTime;
  float m_period;
};

class DelayedShoot : public ShootDecorator {
public:
  DelayedShoot(std::unique_ptr<Shoot> decorated, float delay)
  : ShootDecorator(std::move(decorated))
  , m_elapsedTime(0.0f)
  , m_delay(delay)
  {

  }

  virtual void shoot(float dt, const sf::Vector2f& pos, sf::Vector2f& dir, EventManager& events) override;

private:
  float m_elapsedTime;
  float m_delay;
};

class CountedShoot : public ShootDecorator {
public:
  CountedShoot(std::unique_ptr<Shoot> decorated, int count)
  : ShootDecorator(std::move(decorated))
  , m_count(count)
  {

  }

  virtual void shoot(float dt, const sf::Vector2f& pos, sf::Vector2f& dir, EventManager& events) override;

private:
  int m_count;
};

class RegularShoot : public ShootDecorator {
public:
  RegularShoot(std::unique_ptr<Shoot> decorated, int nbShoot, float shootInterval, float inactivePeriod)
  : ShootDecorator(std::move(decorated))
  , m_nbShoot(0)
  , m_nbShootMax(nbShoot)
  , m_shootPeriod(nbShoot * shootInterval)
  , m_shootInterval(shootInterval)
  , m_inactivePeriod(inactivePeriod)
  , m_elapsedTime(0.0f)
  , m_topFront(false)
  {

  }

  virtual void shoot(float dt, const sf::Vector2f& pos, sf::Vector2f& dir, EventManager& events) override;

private:
  int m_nbShoot;
  int m_nbShootMax;
  float m_shootPeriod;
  float m_shootInterval;
  float m_inactivePeriod;
  float m_elapsedTime;
  bool m_topFront;
};


#endif // LOCAL_SHOOT_H

