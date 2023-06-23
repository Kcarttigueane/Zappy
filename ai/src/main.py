#!/usr/bin/env python3
import random
import sys
import os
import time
import subprocess
from tools.parsing import parser as p
from tools.parsing import got_numbers
from src.ai import AI
import socket
import selectors
from tools.teamname import random_team_name as tn

COLORS = {
    "red": "\033[31m",
    "green": "\033[32m",
    "yellow": "\033[33m",
    "blue": "\033[34m",
    "purple": "\033[35m",
    "cyan": "\033[36m",
    "light_red": "\033[91m",
    "light_green": "\033[92m",
    "light_yellow": "\033[93m",
    "light_blue": "\033[94m",
    "light_purple": "\033[95m",
    "light_cyan": "\033[96m",
}

script_path = os.path.dirname(os.path.realpath(__file__))
script = os.path.basename(__file__)
call_script = f"{script_path}/{script}"


class SocketManager:
    def __init__(self, port, host, name, ident) -> None:
        self.port = port
        self.ai = AI(ident, name, self)
        self.host = host
        self.name = name
        self.sent = False
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
        global local_time
        local_time = time.time()
        try:
            if data[-1] != "\n":
                data += "\n"
            self.socket.send(data.capitalize().encode())
        except Exception as exc:
            print(f"Could not send data to {self.host} on port {self.port}")
            print(str(exc))
            return

    def receive(self):
        try:
            self.socket.settimeout(6)
            data_r = self.socket.recv(1024)
            if data_r:
                self.close() if data_r.decode() == "dead" else None
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


def receive_handler(connected_socket: SocketManager, mask, XF=False, print_data=True, ori=False):
    data = connected_socket.receive()
    if data:
        if print_data:
            output = f"Received: {data}" if not XF else f"{data}"
            connected_socket.ai.printc(output)

        if not ori:
            connected_socket.ai.loop(data)
        return data
    return 0


def input_handler(connected_socket: SocketManager, buffer: list, mask):
    connected_socket.query = sys.stdin.readline().strip()
    if "exit" in connected_socket.query or "quit" in connected_socket.query:
        connected_socket.run = False
        connected_socket.close()
    elif connected_socket.query.strip() != "":
        connected_socket.send(connected_socket.query)


def get_color(ident):  # get a color using the identifier to choose the color
    sel = ident % 12
    color_mapping = {
        0: "red",
        1: "green",
        2: "yellow",
        3: "blue",
        4: "purple",
        5: "cyan",
        6: "light_red",
        7: "light_green",
        8: "light_yellow",
        9: "light_blue",
        10: "light_purple",
        11: "light_cyan",
    }
    return COLORS[color_mapping[sel]]


def main(connected_socket: SocketManager, ident=0):
    client_name = tn()
    color = get_color(ident)
    connected_socket.ai.color = color
    connected_socket.ai.printc(f"\nZappy AI client - Version 0.1\nThis client name is {client_name} with ID {ident}\n")
    sel = selectors.DefaultSelector()
    sel.register(connected_socket.socket, selectors.EVENT_READ, receive_handler)
    sel.register(sys.stdin, selectors.EVENT_READ, input_handler)
    receive_handler(connected_socket, None, True, False, True)
    connected_socket.send(connected_socket.name)
    time.sleep(0.2)
    receive_handler(connected_socket, None, True, False, True)
    if ident == 0:
        i = 1
        connected_socket.send("Connect_nbr")
        time.sleep(0.2)
        max_client = int(receive_handler(connected_socket, None, True, False, True))
        while i <= max_client:
            connected_socket.send("Fork")
            pid = os.fork()
            if pid == 0:
                # command = f"python3 {call_script} -p {connected_socket.port} -n {connected_socket.name} -h
                # {connected_socket.host} -i {i}"
                os.execvp("python3", ["python3", call_script, "-p", str(connected_socket.port), "-n",
                                      connected_socket.name, "-h", connected_socket.host, "-i", str(i)])
            i += 1

    connected_socket.send("Look")
    while connected_socket.is_connected():
        events = sel.select(timeout=0)
        for key, mask in events:
            callback = key.data
            callback(connected_socket, mask)
        connected_socket.ai.unwind_buffer()
    return client_name


if __name__ == '__main__':
    args = p.parse_args()
    s = SocketManager(args.port, args.host, args.name, args.identifier)
    identifier = args.identifier
    try:
        s.connect()
    except Exception as e:
        print(str(e))
        exit(84)
    name = main(s, identifier)
    print(f"Terminal {identifier} terminated - Client name {name}")
    exit(0)
