#include "allegro5/allegro.h"
#include "allegro5/allegro_primitives.h"

#include <iostream>
#include <vector>

#include "Engine/SnakePart.h"

using namespace etsai::snake;
using std::cerr;
using std::endl;
using std::vector;

int main(int argc, char **argv) {
    if(!al_init()) {
        cerr << "failed to initialize allegro!" << endl;
        return -1;
    }
    if(!al_install_keyboard()) {
        cerr << "failed to initialize the keyboard!" << endl;
        return -1;
    }
    if(!al_install_mouse()) {
        cerr << "failed to initialize the mouse!" << endl;
        return -1;
    }
    if (!al_init_primitives_addon()) {
        cerr << "failed to initialize the drawing primitives" << endl;
        return -1;
    }

    ALLEGRO_DISPLAY *display= al_create_display(1680, 1050);
    ALLEGRO_EVENT_QUEUE *event_queue= al_create_event_queue();
    ALLEGRO_TIMER *timer= al_create_timer(1.0/30.0);
    ALLEGRO_EVENT ev;

    al_register_event_source(event_queue, al_get_display_event_source(display));
    al_register_event_source(event_queue, al_get_timer_event_source(timer));
    al_register_event_source(event_queue, al_get_keyboard_event_source());
    al_register_event_source(event_queue, al_get_mouse_event_source());
    al_start_timer(timer);

    vector<engine::SnakePart> parts;
    for(int i= 0; i < 10; i++) {
        parts.push_back(engine::SnakePart(840 - (10 * i), 525));
    }

    do {
        al_wait_for_event(event_queue, &ev);

        switch(ev.type) {
            case ALLEGRO_EVENT_TIMER:
                for(auto &part: parts) {
                    part.tick(1.0/30.0);
                }
                break;
            case ALLEGRO_EVENT_KEY_DOWN:
                if (ev.keyboard.keycode == ALLEGRO_KEY_W) {
                    auto top= parts.begin();
                    top->changeDirection(engine::SnakePart::Direction::UP);
                    for(auto &part: parts) {
                        part.addPivot(top->getXPos(), top->getYPos(), engine::SnakePart::Direction::UP);
                    }
                } else if (ev.keyboard.keycode == ALLEGRO_KEY_A) {
                    auto top= parts.begin();
                    top->changeDirection(engine::SnakePart::Direction::LEFT);
                    for(auto &part: parts) {
                        part.addPivot(top->getXPos(), top->getYPos(), engine::SnakePart::Direction::LEFT);
                    }
                } else if (ev.keyboard.keycode == ALLEGRO_KEY_S) {
                    auto top= parts.begin();
                    top->changeDirection(engine::SnakePart::Direction::DOWN);
                    for(auto &part: parts) {
                        part.addPivot(top->getXPos(), top->getYPos(), engine::SnakePart::Direction::DOWN);
                    }
                } else if (ev.keyboard.keycode == ALLEGRO_KEY_D) {
                    auto top= parts.begin();
                    top->changeDirection(engine::SnakePart::Direction::RIGHT);
                    for(auto &part: parts) {
                        part.addPivot(top->getXPos(), top->getYPos(), engine::SnakePart::Direction::RIGHT);
                    }
                }
                break;
        }
        al_clear_to_color(al_map_rgb(0,0,0));
        for(auto &part: parts) {
            part.draw();
        }
        al_flip_display();
    } while(ev.type != ALLEGRO_EVENT_DISPLAY_CLOSE);

    al_destroy_display(display);
    return 0;
}