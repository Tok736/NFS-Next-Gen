//
// Created by margot on 17.04.2020.
//

#ifndef NFS_NEXT_GEN_WRAP_H
#define NFS_NEXT_GEN_WRAP_H

#include <SFML/Graphics.hpp>
#include <string>

//class Texture;
//
//class Color{
//public:
//    Color() = default;
//    ~Color() = default;
//    sf::Color getColor() const;
//    void setColor(sf::Color color_);
//
//private:
//    sf::Color color_;
//};


//class Image{
//public:
//    Image();
//    ~Image();
//    void create(unsigned int x, unsigned int y, const Color &);
//    bool loadFromFile(const std::string &);
//    bool saveToFile(const std::string &);
//    void setPixel(unsigned int x, unsigned int y, const Color &);
//    Color getPixel(unsigned int x, unsigned int y);
//    sf::Image getImage();
//
//private:
//    sf::Image image_;
//};

//
//class Font : public sf::Font{
//public:
//    Font();
//    ~Font();
//    bool loadFromFile(std::string);
//
//private:
//    sf::Font font_;
//};

class Texture{
public:
    Texture() = default;
    explicit Texture(unsigned int width,unsigned int height);
    ~Texture() = default;
    void loadFromFile(const std::string&);
    sf::Texture getTexture();
    bool create(unsigned int, unsigned int);

private:
    sf::Texture texture_;
};



class Sprite{
public:
    Sprite() = default;
    explicit Sprite(const sf::Texture& texture);
    ~Sprite() = default;
//    void setColor(const Color);
    sf::Sprite getSprite();
    void setPosition(float x, float y);
    void setRotation(float angle);
//    void setTextuteRect(const sf::IntRect);

private:
    sf::Sprite sprite_;
};


class Event{
public:
    Event();
    ~Event();
    sf:: Event getEvent();
    friend class Window;

    sf::Event::EventType  type;
private:
    sf::Event event_;
};



#endif //NFS_NEXT_GEN_WRAP_H
