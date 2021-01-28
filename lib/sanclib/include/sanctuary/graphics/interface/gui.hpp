#pragma once
#include <set>

#include <sanctuary/utility/identifiers.hpp>
#include <sanctuary/containers/map.hpp>
#include <sanctuary/containers/list.hpp>
#include <sanctuary/graphics/windowing/window.hpp>
#include <sanctuary/graphics/windowing/render_state.hpp>
#include <sanctuary/graphics/interface/theme.hpp>
#include <sanctuary/graphics/interface/layout.hpp>
#include <sanctuary/graphics/interface/widget.hpp>


namespace snc {

/**
 * Gui
 *
 * A class that manages the creation, state, and drawing of widgets
 */
class Gui {
public:

    /**
     * Gui::Event
     *
     * A struct that stores Gui event state and data
     */
    struct Event {
        enum Type {
            None = -1,
            WidgetAdded,
            WidgetRemoved,
            WidgetEvent,
        };

        struct Data {
            Widget::Event event;
        };

        Type type{ None }; //!< The event type
    };

    using Callback = std::function<void(Event event)>;

private:
    using WidgetMap       = std::unordered_map<size_t, Widget>;
    using TypeMap         = std::unordered_map<std::type_index, std::set<size_t>>;
    using CallbackMap     = std::unordered_map<Event::Type, std::unordered_map<size_t, Callback>>;
    using WidgetCallbacks = std::unordered_map<Widget::Event::Type, std::unordered_map<size_t, Widget::Callback>>;
    using IdSet           = std::set<size_t>;

    Theme _theme{}; //!< Theme to apply to added widgets

    WidgetMap   _widgets{};              //!< Widgets mapped to unique IDs
    TypeMap     _types{};                //!< Sets of widgets mapped to their original type ID's
    CallbackMap _callbacks{};            //!< Gui::Callback's mapped to Gui::Event::Type's
    WidgetCallbacks _widget_callbacks{}; //!< Widget::Callback's mapped to 

    IdSet _active_widgets{};  //!< Active widgets ID's
    IdSet _visible_widgets{}; //!< Visible widgets ID's
    IdSet _pressed_widgets{}; //!< Pressed widget ID's

public:
    /**
     * Updates widgets and callbacks according to a window event.
     *
     * @param The event
     */
    void update(const Window::Event&);

    /**
     * Draws widgets.
     *
     * @param The Window to draw to
     * @param The RenderState to draw with
     */
    void draw(Window*, const RenderState& = {}) const;

    /**
     * Sets Theme and updates all themed widgets.
     *
     * @param The Theme to set
     */
    void set_theme(const Theme&);

    /**
     * Adds a new widget.
     *
     * @param An object that satisfies the Widget interface
     */
    template<class T>
    Widget& add(T&& widget) {
        const auto tid = std::type_index(typeid(T));
        const auto id  = snc::unique_id();
        auto& res = _widgets.emplace(id, std::move(widget)).first->second;
        _types[tid].emplace(id);
        res.id  = id;
        res.gui = this;
        res.set_theme(_theme);
        return res;
    }

    /**
     * Removes a widget.
     *
     * @param A reference to a widget, will be invalidated on next update
     */
    bool remove(Widget&);

    /**
     * Removes a widget by ID.
     *
     * @param A valid widget ID
     */
    bool remove(size_t);

    /**
     * Hooks a Gui::Callback to a Gui::Event::Type.
     *
     * @param The event type
     * @param The callback
     */
    void hook(Event::Type, Callback&&);

    /**
     * Hooks a Widget::Callback to a Widget::Event::Type.
     *
     * @param The widget to hook
     * @param The event type
     * @param The callback
     */
    void hook(Widget&, Widget::Event::Type, Widget::Callback&&);
};

}
