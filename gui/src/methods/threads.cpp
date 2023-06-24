/*
** EPITECH PROJECT, 2023
** gui
** File description:
** threads
*/

#include "../../include/display.hpp"

void Display::setData(std::string newData)
{
    std::unique_lock<std::mutex> lock(_mtx);
    if (_thread_seen == 1)
        _data = newData;
    else
        _data += newData;
    _thread_seen = 0;
}

std::string Display::getData()
{
    std::unique_lock<std::mutex> lock(_mtx);
    _thread_seen = 1;
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
