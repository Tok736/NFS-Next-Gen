//
// Created by margot on 02.05.2020.
//

#include "graphics/wrap.h"


/////////////////////                    SPRITE            //////////////////////////////////////////

Sprite::Sprite(const sf::Texture& texture) {
    sprite_.setTexture(texture, false);
}


sf::Sprite Sprite::getSprite() {
    return sprite_;
}

void Sprite::setPosition(float x, float y) {
    sprite_.setPosition(x, y);
}

void Sprite::setRotation(float angle) {
    sprite_.setRotation(angle);
}

/////////////////////                    TEXTURE             //////////////////////////////////////////


void Texture::loadFromFile(const std::string& src) {
    texture_.loadFromFile(src);
}

sf::Texture Texture::getTexture() {
    return texture_;
}

Texture::Texture(unsigned int width,unsigned int height) {
    texture_.create(width, height);
}


/////////////////////                    COLOR             //////////////////////////////////////////

//sf::Color Color::getColor() const {
//    return color_;
//}


