#pragma once

#include <SFML/Window/Keyboard.hpp>
#include <string_view>
#include <unordered_map>

#include "../tomlplusplus/toml.hpp"

// For whatever reason SFML doesn't have any string->key converter, so one has
// made on the spot. And there is this guy who replies to like every thread
// asking for this feature saying he has a lib that solves the issue as if c++
// dependencies aren't a flaming trash heap
std::unordered_map<std::string_view, sf::Keyboard::Key> const getKeyByName = {
    {"unknown",   sf::Keyboard::Key::Unknown},
    {"a",         sf::Keyboard::Key::A},
    {"b",         sf::Keyboard::Key::B},
    {"c",         sf::Keyboard::Key::C},
    {"d",         sf::Keyboard::Key::D},
    {"e",         sf::Keyboard::Key::E},
    {"f",         sf::Keyboard::Key::F},
    {"g",         sf::Keyboard::Key::G},
    {"h",         sf::Keyboard::Key::H},
    {"i",         sf::Keyboard::Key::I},
    {"j",         sf::Keyboard::Key::J},
    {"k",         sf::Keyboard::Key::K},
    {"l",         sf::Keyboard::Key::L},
    {"m",         sf::Keyboard::Key::M},
    {"n",         sf::Keyboard::Key::N},
    {"o",         sf::Keyboard::Key::O},
    {"p",         sf::Keyboard::Key::P},
    {"q",         sf::Keyboard::Key::Q},
    {"r",         sf::Keyboard::Key::R},
    {"s",         sf::Keyboard::Key::S},
    {"t",         sf::Keyboard::Key::T},
    {"u",         sf::Keyboard::Key::U},
    {"v",         sf::Keyboard::Key::V},
    {"w",         sf::Keyboard::Key::W},
    {"x",         sf::Keyboard::Key::X},
    {"y",         sf::Keyboard::Key::Y},
    {"z",         sf::Keyboard::Key::Z},
    {"num0",      sf::Keyboard::Key::Num0},
    {"num1",      sf::Keyboard::Key::Num1},
    {"num2",      sf::Keyboard::Key::Num2},
    {"num3",      sf::Keyboard::Key::Num3},
    {"num4",      sf::Keyboard::Key::Num4},
    {"num5",      sf::Keyboard::Key::Num5},
    {"num6",      sf::Keyboard::Key::Num6},
    {"num7",      sf::Keyboard::Key::Num7},
    {"num8",      sf::Keyboard::Key::Num8},
    {"num9",      sf::Keyboard::Key::Num9},
    {"lcontrol",  sf::Keyboard::Key::LControl},
    {"lshift",    sf::Keyboard::Key::LShift},
    {"lalt",      sf::Keyboard::Key::LAlt},
    {"lsystem",   sf::Keyboard::Key::LSystem},
    {"rcontrol",  sf::Keyboard::Key::RControl},
    {"rshift",    sf::Keyboard::Key::RShift},
    {"ralt",      sf::Keyboard::Key::RAlt},
    {"rsystem",   sf::Keyboard::Key::RSystem},
    {"menu",      sf::Keyboard::Key::Menu},
    {"[",         sf::Keyboard::Key::LBracket},
    {"]",         sf::Keyboard::Key::RBracket},
    {";",         sf::Keyboard::Key::SemiColon},
    {",",         sf::Keyboard::Key::Comma},
    {".",         sf::Keyboard::Key::Period},
    {"'",         sf::Keyboard::Key::Quote},
    {"/",         sf::Keyboard::Key::Slash},
    {"\\",        sf::Keyboard::Key::BackSlash},
    {"`",         sf::Keyboard::Key::Tilde},
    {"=",         sf::Keyboard::Key::Equal},
    {"-",         sf::Keyboard::Key::Hyphen},
    {" ",         sf::Keyboard::Key::Space},
    {"enter",     sf::Keyboard::Key::Enter},
    {"backspace", sf::Keyboard::Key::Backspace},
    {"tab",       sf::Keyboard::Key::Tab},
    {"pageup",    sf::Keyboard::Key::PageUp},
    {"pagedown",  sf::Keyboard::Key::PageDown},
    {"end",       sf::Keyboard::Key::End},
    {"home",      sf::Keyboard::Key::Home},
    {"insert",    sf::Keyboard::Key::Insert},
    {"delete",    sf::Keyboard::Key::Delete},
    {"left",      sf::Keyboard::Key::Left},
    {"right",     sf::Keyboard::Key::Right},
    {"up",        sf::Keyboard::Key::Up},
    {"down",      sf::Keyboard::Key::Down},
    {"numpad0",   sf::Keyboard::Key::Numpad0},
    {"numpad1",   sf::Keyboard::Key::Numpad1},
    {"numpad2",   sf::Keyboard::Key::Numpad2},
    {"numpad3",   sf::Keyboard::Key::Numpad3},
    {"numpad4",   sf::Keyboard::Key::Numpad4},
    {"numpad5",   sf::Keyboard::Key::Numpad5},
    {"numpad6",   sf::Keyboard::Key::Numpad6},
    {"numpad7",   sf::Keyboard::Key::Numpad7},
    {"numpad8",   sf::Keyboard::Key::Numpad8},
    {"numpad9",   sf::Keyboard::Key::Numpad9},
    {"f1",        sf::Keyboard::Key::F1},
    {"f2",        sf::Keyboard::Key::F2},
    {"f3",        sf::Keyboard::Key::F3},
    {"f4",        sf::Keyboard::Key::F4},
    {"f5",        sf::Keyboard::Key::F5},
    {"f6",        sf::Keyboard::Key::F6},
    {"f7",        sf::Keyboard::Key::F7},
    {"f8",        sf::Keyboard::Key::F8},
    {"f9",        sf::Keyboard::Key::F9},
    {"f10",       sf::Keyboard::Key::F10},
    {"f11",       sf::Keyboard::Key::F11},
    {"f12",       sf::Keyboard::Key::F12},
    {"f13",       sf::Keyboard::Key::F13},
    {"f14",       sf::Keyboard::Key::F14},
    {"f15",       sf::Keyboard::Key::F15},
    {"pause",     sf::Keyboard::Key::Pause},
};

struct Settings
{
    Settings(toml::parse_result config)
    {
        filmgrainEnabled = config
            ["Graphics"]
            ["PostProcesing"]
            ["filmgrainEnabled"]
            .value_or(false);
        filmgrainIntensity = config
            ["Graphics"]
            ["PostProcesing"]
            ["filmgrainIntensity"]
            .value_or(0.0);

        controls.up = getKeyByName.at(config
            ["Controls"]
            ["up"]
            .value_or("unknown")
        );

        controls.down = getKeyByName.at(config
            ["Controls"]
            ["down"]
            .value_or("unknown")
        );

        controls.left = getKeyByName.at(config
            ["Controls"]
            ["left"]
            .value_or("unknown")
        );

        controls.right = getKeyByName.at(config
            ["Controls"]
            ["right"]
            .value_or("unknown")
        );
    }

    bool filmgrainEnabled;
    float filmgrainIntensity;

    struct {
        sf::Keyboard::Key up;
        sf::Keyboard::Key down;
        sf::Keyboard::Key left;
        sf::Keyboard::Key right;
    } controls;
};
