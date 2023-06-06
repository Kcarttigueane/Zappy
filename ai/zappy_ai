#!/usr/bin/env python3

from tools.parsing import parser as p
from tools.interface import InputWindow as Iw
from tools.interface import OutputWindow as Ow
import socket
import curses
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
        outputW.add_output(data)


def main(stdscr, connected_socket: SocketManager):
    stdscr.clear()
    curses.curs_set(0)
    inputW = Iw(stdscr)
    global outputW
    outputW = Ow(stdscr)

    sel = selectors.DefaultSelector()
    sel.register(connected_socket.socket, selectors.EVENT_READ, receive_handler)

    connected_socket.send(connected_socket.name)

    while connected_socket.is_connected():
        query = ""
        while True:
            c = inputW.get_char()
            if c == "\n":
                break
            elif c == "\x7f":
                query = query[:-1]
            elif c == "\x1b":
                query = ""
            else:
                query += c
            inputW.extend_query(query)

        if query == "exit" or query == "quit" or query == "exit\n" or query == "quit\n":
            connected_socket.run = False
            connected_socket.close()
            outputW.add_output("Disconnected from server - closing loop withing 6 seconds")
            break

        if query.strip():
            inputW.add_history(query)
            outputW.add_output(f"{connected_socket.name}: '{query}'")
            query += "\n"
            connected_socket.send(query)

        inputW.clear()

        events = sel.select(timeout=0)
        for key, mask in events:
            callback = key.data
            callback(connected_socket, mask)

    outputW.clear()
    curses.endwin()


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
    curses.wrapper(main, s)
    print(f"Disconnected from {args.host} on port {args.port}")
    exit(0)
