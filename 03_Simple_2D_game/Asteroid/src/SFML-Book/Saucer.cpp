#include <SFML-Book/Saucer.hpp>

#include <SFML-Book/random.hpp> //random
#include <SFML-Book/World.hpp> //World
#include <SFML-Book/Shoot.hpp> //ShootSaucer
#include <SFML-Book/Collision.hpp> //Collision

namespace book
{
    bool Saucer::isCollide(const Entity& other)const
    {
        if(dynamic_cast<const ShootSaucer*>(&other) == nullptr)
        {
            return Collision::circleTest(_sprite,other._sprite);
        }
        return false;
    }

    void Saucer::update(sf::Time deltaTime)
    {
        float seconds = deltaTime.asSeconds();

        //float angle = _sprite.getRotation() / 180 * M_PI - M_PI / 2;
        //sf::Vector2f impulse = sf::Vector2f(std::cos(angle),std::sin(angle)) * 300.f;
        //_sprite.move(seconds * impulse);
        
        _sprite.move(seconds * sf::Vector2f(300,100));
    }

    void Saucer::newSaucer(World& world)
    {
        Saucer* res = nullptr;
        //if(book::random(0,1) < Configuration::score - 40000)
          res = new SmallSaucer(world);
        //else
//          res = new BigSaucer(world);
        world.add(res);
    }

    /************ BigSaucer ******************/

    BigSaucer::BigSaucer(World& world) : Saucer(Configuration::Textures::BigSaucer,world)
    {
    }

    int BigSaucer::getPoints()const
    {
        return 50;
    }

    /********** SmallSaucer *********************/

    SmallSaucer::SmallSaucer(World& world) : Saucer(Configuration::Textures::SmallSaucer,world)
    {        
            _time_since_last_shoot = sf::Time::Zero;
    }

    int SmallSaucer::getPoints()const
    {
        return 200;
    }

    void SmallSaucer::update(sf::Time deltaTime)
    {
        Saucer::update(deltaTime);
        //shoot on the Configuration::player
        _time_since_last_shoot += deltaTime;
        if(_time_since_last_shoot > sf::seconds(3))
        {
            if(Configuration::player != nullptr)
            {
                _world.add(new ShootSaucer(*this));
            }
            _time_since_last_shoot = sf::Time::Zero;
        }
    }

}
