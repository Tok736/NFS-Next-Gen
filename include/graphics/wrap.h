//
// Created by margot on 17.04.2020.
//

#ifndef NFS_NEXT_GEN_WRAP_H
#define NFS_NEXT_GEN_WRAP_H

#include <SFML/Graphics.hpp>
#include <string>

class Color{
public:
    Color() = default;
    ~Color() = default;
    sf::Color getColor() const;
    void setColor(sf::Color color_);

private:
    sf::Color color_;
};


class Image{
public:
    Image();
    ~Image();
    void create(unsigned int, unsigned int, const Color);
    bool loadFromFile(const std::string);
    bool saveToFile(const std::string);
    void setPixel(unsigned int, unsigned int, const Color);
    Color getPixel(unsigned int, unsigned int);
    sf::Image getImage();

private:
    sf::Image image_;
};


class Font : public sf::Font{
public:
    Font();
    ~Font();
    bool loadFromFile(std::string);
};

class Sprite{
public:
    Sprite();
    ~Sprite();
    void setColor(const Color);
    sf::Sprite getSprite();
    void setPosition(float, float);
    void setRotation(float);
    void setTextuteRect(const sf::IntRect);
    void draw();

private:
    sf::Sprite sprite_;
};

class Texture{
public:
    Texture();
    ~Texture();
    bool loadFromFile(std::string);
    bool create(unsigned int, unsigned int);

private:
    sf::Texture texture_;
};


#endif //NFS_NEXT_GEN_WRAP_H
