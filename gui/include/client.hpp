/*
** EPITECH PROJECT, 2023
** zappy
** File description:
** client
*/

#pragma once

#include <iostream>
#include <cstring>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

class Client {
private:
    int clientSocket;
    std::string serverIP;
    int serverPort;

public:
    Client(const std::string& ip, int port) : clientSocket(-1), serverIP(ip), serverPort(port) {}

    bool connectToServer() {
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

    bool sendData(const std::string& data) {
        if (send(clientSocket, data.c_str(), data.length(), 0) < 0) {
            std::cerr << "Send failed" << std::endl;
            return false;
        }
        return true;
    }

    std::string receiveData() {
        char buffer[4096] = {0};
        if (recv(clientSocket, buffer, sizeof(buffer), 0) < 0) {
            std::cerr << "Receive failed" << std::endl;
            return "";
        }
        return std::string(buffer);
    }

    void closeConnection() {
        close(clientSocket);
    }
};
