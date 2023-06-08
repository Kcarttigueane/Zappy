/*
** EPITECH PROJECT, 2023
** zappy
** File description:
** isometricMath
*/

#include "../../include/display.hpp"

sf::Vector2f getGridCoordinates(float x, float y, double scale, double x_offset, double y_offset)
{
    x -= x_offset;
    y -= y_offset;
    float og_a = 0.5 * ASSET_WIDHT * scale;
    float og_b = -0.5 * ASSET_WIDHT * scale;
    float og_c = 0.25 * ASSET_HEIGHT * scale;
    float og_d = 0.25 * ASSET_HEIGHT * scale;
    float det = (-1 / (og_a * og_d - og_b * og_c));

    float a = det * og_d;
    float b = det * -og_b;
    float c = det * -og_c;
    float d = det * og_a;

    sf::Vector2f pos;
    pos.x = -(x * a + y * b) - 0.502189;
    pos.y = -(x * c + y * d) + 0.488802;
    return pos;
}

sf::Vector2f getIsometricPos(float x, float y, float scale, sf::IntRect rect, double x_offset, double y_offset)
{
    sf::Vector2f pos;

    pos.x = (x * (0.5 * rect.width) + y * (-0.5 * rect.width)) * scale;
    pos.y = (x * (0.25 * rect.height) + y * (0.25 * rect.height)) * scale;
    pos.x += x_offset;
    pos.y += y_offset;
    return pos;
}
