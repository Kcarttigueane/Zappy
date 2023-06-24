/*
** EPITECH PROJECT, 2023
** gui
** File description:
** threads
*/

#include "../../include/display.hpp"

void Display::setData(std::string newData)
{
    std::lock_guard<std::mutex> lock(_mtx);
    _data = newData;
}

std::string Display::getData()
{
    std::lock_guard<std::mutex> lock(_mtx);
    return _data;
}

void Display::startClientThread()
{
    _clientThread = std::thread(&Display::threadRecieveData, this);
}

void Display::stopClientThread()
{
    // if (_clientThread.joinable())
    _clientThread.join();
}
