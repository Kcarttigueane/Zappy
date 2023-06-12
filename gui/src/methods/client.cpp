/*
** EPITECH PROJECT, 2023
** gui
** File description:
** client
*/

#include "../../include/display.hpp"

bool Display::connectToServer()
{
    clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (clientSocket == -1) {
        std::cerr << "Failed to create socket" << std::endl;
        return false;
    }
    sockaddr_in serverAddress{};
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(serverPort);
    if (inet_pton(AF_INET, serverIP.c_str(), &(serverAddress.sin_addr)) <= 0) {
        std::cerr << "Invalid address/Address not supported" << std::endl;
        return false;
    }
    if (connect(clientSocket, reinterpret_cast<sockaddr*>(&serverAddress), sizeof(serverAddress)) < 0) {
        std::cerr << "Connection failed" << std::endl;
        return false;
    }
    std::cout << "Connected to the server" << std::endl;
    return true;
}

bool Display::sendData(const std::string& data)
{
    if (send(clientSocket, data.c_str(), data.length(), 0) < 0) {
        std::cerr << "Send failed" << std::endl;
        return false;
    }
    return true;
}

std::string Display::receiveData()
{
    char buffer[14096] = {0};

    int flags = fcntl(clientSocket, F_GETFL, 0);
    if (flags == -1)
        return "";
    if (fcntl(clientSocket, F_SETFL, flags | O_NONBLOCK) == -1)
        return "";

    fd_set readSet;
    FD_ZERO(&readSet);
    FD_SET(clientSocket, &readSet);

    int selectResult = select(clientSocket + 1, &readSet, NULL, NULL, NULL);

    if (selectResult == -1)
        return "";

    if (FD_ISSET(clientSocket, &readSet)) {
        int recvResult = recv(clientSocket, buffer, sizeof(buffer), 0);
        if (recvResult < 0) {
            if (errno == EWOULDBLOCK || errno == EAGAIN)
                return "";
            else
                return "";
        } else if (recvResult == 0)
            return "";
    } else
        return "";
    return std::string(buffer);
}


void Display::threadRecieveData()
{
    while (1) {
        char buffer[14096] = {0};
        int flags = fcntl(clientSocket, F_GETFL, 0);
        if (flags == -1)
            continue;
        if (fcntl(clientSocket, F_SETFL, flags | O_NONBLOCK) == -1)
            continue;

        fd_set readSet;
        FD_ZERO(&readSet);
        FD_SET(clientSocket, &readSet);

        int selectResult = select(clientSocket + 1, &readSet, NULL, NULL, NULL);

        if (selectResult == -1)
            continue;

        if (FD_ISSET(clientSocket, &readSet)) {
            int recvResult = recv(clientSocket, buffer, sizeof(buffer), 0);
            if (recvResult < 0) {
                if (errno == EWOULDBLOCK || errno == EAGAIN)
                    continue;
                else
                    continue;
            } else if (recvResult == 0)
                continue;
        } else
            continue;
        setData(buffer);
    }
}
