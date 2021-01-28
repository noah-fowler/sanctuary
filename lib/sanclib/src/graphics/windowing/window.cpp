#include <sanctuary/graphics/windowing/window.hpp>
#include <sanctuary/io/mouse.hpp>


namespace snc {

auto screen_size() -> Vec2u {
    const auto mode = sf::VideoMode::getDesktopMode();
    return { mode.width, mode.height };
}

auto fullscreen_sizes() -> List<Vec2u> {
    auto res = List<Vec2u>{};
    for (auto mode : sf::VideoMode::getFullscreenModes())
        res.emplace_back(mode.width, mode.height);
    return res;
}

Window::Window(const String& title, unsigned width, unsigned height)
    : _window({ width, height }, static_cast<std::string>(title))
    , _title(title)
{}

Window::Window(const String& title, const Vec2u& size)
    : _window({ size.x, size.y }, static_cast<std::string>(title))
    , _title(title)
{}

Window::operator sf::RenderWindow&() {
    return _window;
}

Window::operator const sf::RenderWindow&() const {
    return _window;
}

bool Window::is_open() const {
    return _window.isOpen();
}

void Window::open(const String& title, unsigned width, unsigned height) {
    _window.create({ width, height }, static_cast<std::string>(title));
    _title = title;
}

void Window::open(const String& title, const Vec2u& size) {
    _window.create({ size.x, size.y }, static_cast<std::string>(title));
    _title = title;
}

void Window::close() {
    if (is_open())
        _window.close();
}

auto Window::size() const -> Vec2u {
    const auto res = _window.getSize();
    return { res.x, res.y };
}

auto Window::position() const -> Vec2i {
    const auto res = _window.getPosition();
    return { res.x, res.y };
}

auto Window::title() const -> String {
    return _title;
}

auto Window::view() const -> View {
    return View(_window.getView());
}

auto Window::default_view() const -> View {
    return View(_window.getDefaultView());
}

auto Window::viewport(const View& view) const -> IRect {
    return IRect(_window.getViewport(static_cast<sf::View>(view)));
}

void Window::set_size(unsigned width, unsigned height) {
    _window.setSize({ width, height });
}

void Window::set_size(const Vec2u& new_size) {
    set_size(new_size.x, new_size.y);
}

void Window::set_position(int x, int y) {
    _window.setPosition({ x, y });
}

void Window::set_position(const Vec2i& new_position) {
    set_position(new_position.x, new_position.y);
}

void Window::set_title(const String& title) {
    _window.setTitle(static_cast<std::string>(title));
}

void Window::set_visible(bool visible) {
    _window.setVisible(visible);
}

void Window::set_fps(unsigned fps) {
    _window.setFramerateLimit(fps);
}

void Window::set_vsync(bool enabled) {
    _window.setVerticalSyncEnabled(enabled);
}

void Window::set_cursor_visible(bool enabled) {
    _window.setMouseCursorVisible(enabled);
}

void Window::set_cursor_grabbed(bool enabled) {
    _window.setMouseCursorGrabbed(enabled);
}

void Window::set_active(bool enabled) {
    _window.setActive(enabled);
}

void Window::request_focus() {
    _window.requestFocus();
}

bool Window::has_focus() const {
    return _window.hasFocus();
}

bool Window::poll(Event& event) {
    auto proxy     = sf::Event{};
    const auto res = _window.pollEvent(proxy);
    if (!res)
        return {};
    event.type = static_cast<Event::Type>(proxy.type);
    if (event.type == Event::MousePressed || event.type == Event::MouseReleased)
        event.button = { proxy.mouseButton.x, proxy.mouseButton.y };
    else if (event.type == Event::MouseMoved)
        event.mouse = { proxy.mouseMove.x, proxy.mouseMove.y };
    else if (event.type == Event::TouchBegan || event.type == Event::TouchEnded || event.type == Event::TouchMoved)
        event.touch = { proxy.touch.finger, proxy.touch.x, proxy.touch.y };
    return true;
}

bool Window::wait(Event& event) {
    auto proxy     = sf::Event{};
    const auto res = _window.waitEvent(proxy);
    if (!res)
        return {};
    event.type = static_cast<Event::Type>(proxy.type);
    return true;
}

void Window::clear() {
    _window.clear();
}

void Window::display() {
    _window.display();
}

void Window::draw(const Drawable& drawable, const RenderState& state) {
    drawable.draw(this, state);
}

void Window::draw(const sf::Drawable& drawable, const sf::RenderStates& states) {
    _window.draw(drawable, states);
}

}
