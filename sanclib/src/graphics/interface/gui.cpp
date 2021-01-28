#include <sanctuary/graphics/interface/gui.hpp>


namespace snc {

void Gui::set_theme(const Theme& theme) {
    _theme = theme;
    for (auto& [id, widget] : _widgets)
        widget.set_theme(theme);
}

void Gui::update(const Window::Event& event) {
    if (event.type == snc::Window::Event::KeyPressed) {
    }
    else if (event.type == snc::Window::Event::KeyReleased) {
    }
    else if (event.type == snc::Window::Event::MousePressed) {
        for (auto& [id, widget] : _widgets)
            if (widget.global_bounds().contains(event.button.x, event.button.y)) {
                _pressed_widgets.emplace(widget.id);
                snc::println("Pressed widget: {}", widget.id);
            }
    }
    else if (event.type == snc::Window::Event::MouseReleased) {
        auto free_list = List<size_t>{};
        for (auto id : _pressed_widgets)
            free_list.emplace_back(id);
        for (const auto id : free_list) {
            _pressed_widgets.extract(id);
            snc::println("Released widget: {}", id);
        }
    }
    else if (event.type == snc::Window::Event::MouseMoved) {
    }
    else if (event.type == snc::Window::Event::TouchBegan) {
    }
    else if (event.type == snc::Window::Event::TouchEnded) {
    }
}

void Gui::draw(Window* window, const RenderState& state) const {
    for (auto& [id, widget] : _widgets)
        widget.draw(window, state);
}

bool Gui::remove(Widget& widget) {
    return {};
}

bool Gui::remove(size_t id) {
    return {};
}

void Gui::hook(Event::Type type, Callback&& callback) {
}

void Gui::hook(Widget& widget, Widget::Event::Type event, Widget::Callback&& callback) {
}

}
