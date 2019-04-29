#ifndef SFMLWIDGET_H_INCLUDED
#define SFMLWIDGET_H_INCLUDED

#include <SFML/Graphics.hpp>
#include <gtkmm/widget.h>

class SFMLWidget : public Gtk::Widget
{
protected:
    sf::VideoMode m_vMode;

    virtual void on_size_allocate(Gtk::Allocation& allocation);
    
    virtual void on_unrealize();

    Glib::RefPtr<Gdk::Window> m_refGdkWindow;
public:
    sf::RenderWindow renderWindow;
	virtual void on_realize();
    SFMLWidget(sf::VideoMode mode, int size_request=-1);
    virtual ~SFMLWidget();

    void invalidate();
    void display();
};

#endif