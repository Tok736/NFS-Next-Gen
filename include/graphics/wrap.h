//
// Created by margot on 17.04.2020.
//

#ifndef NFS_NEXT_GEN_WRAP_H
#define NFS_NEXT_GEN_WRAP_H

#include <SFML/Graphics.hpp>
#include <string>
#include <utility>



class FocusObject
{
public:
    virtual void setFocus () = 0 ;
    virtual void deleteFocus () = 0 ;
    virtual void event ( const sf::Event & ) = 0 ;
} ;

class FocusController
{
public:
    explicit FocusController ( FocusObject * obj = nullptr ) : m_object (obj)
    {
        if ( m_object != nullptr )
        {
            m_object->setFocus () ;
        }
    }
    void setFocusObject ( FocusObject * new_obj )
    {
        if ( m_object == new_obj )
            return ;
        if ( m_object != nullptr )
            m_object->deleteFocus() ;
        if ( new_obj != nullptr )
            new_obj->setFocus() ;
        m_object = new_obj ;
    }
    FocusObject * getFocusObject ( )
    {
        return m_object ;
    }

private:
    FocusObject * m_object ;
} ;




class TextBox : public sf::Drawable , public FocusObject /*, public sf::Transformable */
{
public:
    explicit TextBox (sf::Text text) : m_text (std::move( text ))
    {
        m_newText = m_text.getString() ;
        updateRect() ;
        m_box.setFillColor( sf::Color::Blue ) ;
    }
    void draw ( sf::RenderTarget & render , sf::RenderStates states ) const override
    {
        if ( m_textChanged )
        {
            const_cast<TextBox*>(this)->setText ( m_newText ) ;

            m_textChanged = false ;
        }
        render.draw ( m_box , states ) ;
        render.draw ( m_text , states ) ;
    }
    void setFocus () override
    {
        m_box.setFillColor( sf::Color(255,255,255,25) ) ;
    }
    void deleteFocus () override
    {
        m_box.setFillColor( sf::Color(0,0,0,0)) ;
    }
    void event ( const sf::Event & event ) override
    {
        if (event.type == sf::Event::TextEntered && (m_newText.getSize()<15 || (m_newText.getSize() ==15 && event.text.unicode == 0x8)))
        {
            //Обработка ввода
            m_textChanged = true ;
            switch ( event.text.unicode )
            {
                case 0x8://Backspace
                    if ( !m_newText.isEmpty() )
                        m_newText.erase(m_newText.getSize()-1) ;
                    break ;
                default :
                {
                    m_newText += static_cast<wchar_t>(event.text.unicode) ;
                }
            }
        }
    }
    void setText ( const sf::String & str )
    {
        m_text.setString ( str ) ;
        updateRect() ;
    }
    sf::Text getText ()
    {
        return m_text;
    }

private:
    void updateRect ()
    {
        sf::FloatRect rect = m_text.getGlobalBounds() ;
        m_box.setPosition ( rect.left-5 , rect.top-5 ) ;
        m_box.setSize( sf::Vector2f(rect.width+10 , rect.height+10) ) ;
    }
    mutable sf::RectangleShape m_box ;
    mutable sf::Text m_text ;
    mutable sf::String m_newText ;
    mutable bool m_textChanged{} ;
} ;







#endif //NFS_NEXT_GEN_WRAP_H
