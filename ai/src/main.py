#!/usr/bin/env python3
import time

from tools.parsing import parser as p
import socket
import selectors


class SocketManager:
    def __init__(self, port, host, name) -> None:
        self.port = port
        self.host = host
        self.name = name
        self.socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        self.connected = False
        self.run = False
        self.reader, self.writer = None, None
        self.query = ""

    def connect(self):
        try:
            self.socket.connect((self.host, self.port))
            self.connected = True
            self.run = True
        except Exception as ext:
            print(f"Could not connect to {self.host} on port {self.port}")
            print(str(ext))
            exit(84)

    def send(self, data):
        try:
            if data[-1] != "\n":
                data += "\n"
            self.socket.send(data.encode())
            time.sleep(0.2)
        except Exception as exc:
            print(f"Could not send data to {self.host} on port {self.port}")
            print(str(exc))
            return

    def receive(self):
        try:
            self.socket.settimeout(6)
            data_r = self.socket.recv(1024)
            if data_r:
                return data_r.decode()
        except socket.timeout:
            pass
        except Exception as exc:
            print(f"Error while listening to {self.host} on port {self.port}")
            print(str(exc))
            return

    def close(self):
        self.connected = False
        self.socket.close()

    def is_connected(self):
        return self.connected


def receive_handler(connected_socket: SocketManager, mask):
    data = connected_socket.receive()
    if data:
        print(data)


def main(connected_socket: SocketManager):
    sel = selectors.DefaultSelector()
    sel.register(connected_socket.socket, selectors.EVENT_READ, receive_handler)
    receive_handler(connected_socket, None)
    connected_socket.send(connected_socket.name)
    time.sleep(0.2)
    receive_handler(connected_socket, None)

    while connected_socket.is_connected():
        connected_socket.query = input("Enter command: ")
        if "exit" in connected_socket.query or "quit" in connected_socket.query:
            connected_socket.run = False
            connected_socket.close()
            print("Exiting...")
            break

        if connected_socket.query.strip() != "":
            connected_socket.send(connected_socket.query)

        events = sel.select(timeout=0)
        for key, mask in events:
            callback = key.data
            callback(connected_socket, mask)


if __name__ == '__main__':
    args = p.parse_args()
    print(f"Connecting to {args.host} on port {args.port} with team name {args.name}")
    s = SocketManager(args.port, args.host, args.name)
    try:
        s.connect()
    except Exception as e:
        print(str(e))
        exit(84)
    print(f"Connected to {args.host} on port {args.port}")
    main(s)
    print(f"Disconnected from {args.host} on port {args.port}")
    exit(0)
