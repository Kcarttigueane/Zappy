import socket
import time
from typing import List, Any
import re

from tools.parsing import got_numbers
from enum import Enum


def go_to_sound_source(source, connected_socket):
    movements = {
        1: "Forward",
        2: "Left, Forward",
        3: "Left, Forward",
        4: "Left, Forward",
        5: "Backward",
        6: "Right, Backward",
        7: "Right, Backward",
        8: "Right, Forward",
    }

    direction = movements[source]

    for move in direction.split(", "):
        connected_socket.send(move)


class Direction(Enum):
    UP = 0
    RIGHT = 1
    BACK = 2
    LEFT = 3


def path_find(target: tuple[int, int]) -> None | list[str]:
    direction = Direction.UP
    x, y = 0, 0
    move_list = []
    while target[1] > y:
        move_list.append("Forward")
        y += 1

    while target[0] != x:
        if target[0] > x:
            if direction == Direction.UP:
                move_list.append("Right")
                direction = Direction.RIGHT
            elif direction == Direction.RIGHT:
                move_list.append("Forward")
                x += 1
            elif direction == Direction.BACK:
                move_list.append("Left")
                direction = Direction.RIGHT
            elif direction == Direction.LEFT:
                move_list.append("Right")
                direction = Direction.UP
        elif target[0] < x:
            if direction == Direction.UP:
                move_list.append("Left")
                direction = Direction.LEFT
            elif direction == Direction.RIGHT:
                move_list.append("Left")
                direction = Direction.UP
            elif direction == Direction.BACK:
                move_list.append("Right")
                direction = Direction.LEFT
            elif direction == Direction.LEFT:
                move_list.append("Forward")
                x -= 1
    return move_list


def parse_target(target_str: str) -> tuple[int, int]:
    split_target = target_str.split('-TARGET:')
    from_level = int(split_target[0][1:])
    to_level = int(split_target[1][1:])

    return from_level, to_level


def get_position(i: int) -> tuple[int, int]:
    level = int((-1 + (1 + 8 * i) ** 0.5) / 2)
    pos_within_level = i - level * (level + 1) // 2
    x = pos_within_level - level
    y = level
    return x, y


class ElevationState(Enum):
    NOT_STARTED = 0,
    IN_PROGRESS = 1,
    WAITING_PLAYERS = 2,
    WAITING_RESOURCES = 3,
    FINISHED = 4


class AI:
    def __init__(self, ident, name_, socket_) -> None:
        self.name = name_
        self.connected_socket: socket.socket = socket_
        self.leveling_up = False
        self.id = ident
        self.color = "\033[0;30m"
        self.elevation_state = ElevationState.NOT_STARTED
        self.elevation_players = 0
        self.slot_available = 0
        self.priority_order = {
            "food": 0.5,
            "linemate": 0.3,
            "deraumere": 0.15,
            "sibur": 0.1,
            "mendiane": 0.1,
            "phiras": 0.08,
            "thystame": 0.05
        }
        self.rarity = {
            "food": 1 / self.priority_order["food"],
            "linemate": 1 / self.priority_order["linemate"],
            "deraumere": 1 / self.priority_order["deraumere"],
            "sibur": 1 / self.priority_order["sibur"],
            "mendiane": 1 / self.priority_order["mendiane"],
            "phiras": 1 / self.priority_order["phiras"],
            "thystame": 1 / self.priority_order["thystame"]
        }

        self.w1 = 0.4  # rarity → Huge impact (from 2 to 20 * w1).
        self.w2 = 3.5  # level up → Medium impact (from 1 to 5 * w2).
        self.w3 = 0.75  # proximity → Undefined impact yet.
        self.w4 = 3  # food → Important (life or death) BUT way too challenging to decide a correct value.
        self.w5 = 1  # inventory → May be useful sometimes, but not always.

        self.items = ["linemate", "deraumere", "sibur", "mendiane", "phiras", "thystame", "food"]
        self.head_level = False
        self.missing_items = [0, 0, 0, 0, 0, 0, 0]
        # lvl_dct represents the number of items needed to level up. They are in the same order as self.items.
        self.lvl_dct = {
            "2": [1, 0, 0, 0, 0, 0],
            "3": [1, 1, 1, 0, 0, 0],
            "4": [2, 0, 1, 0, 2, 0],
            "5": [1, 1, 2, 0, 1, 0],
            "6": [1, 2, 1, 3, 0, 0],
            "7": [1, 2, 3, 0, 1, 0],
            "8": [2, 2, 2, 2, 2, 1],
            "9": [0, 0, 0, 0, 0, 0]  # In case of error
        }
        # lvl_pl represents the number of players needed to level up.
        self.lvl_pl = {
            "2": 1,
            "3": 2,
            "4": 2,
            "5": 4,
            "6": 4,
            "7": 6,
            "8": 6
        }
        self.inventory = {
            "food": 10,
            "linemate": 0,
            "deraumere": 0,
            "sibur": 0,
            "mendiane": 0,
            "phiras": 0,
            "thystame": 0
        }
        self.level = 1
        self.map = [['O', 'O', 'O', 'O', 'O', 'O', 'O', 'X', 'O', 'O', 'O', 'O', 'O', 'O', 'O'],
                    ['O', 'O', 'O', 'O', 'O', 'O', 'X', 'X', 'X', 'O', 'O', 'O', 'O', 'O', 'O'],
                    ['O', 'O', 'O', 'O', 'O', 'X', 'X', 'X', 'X', 'X', 'O', 'O', 'O', 'O', 'O'],
                    ['O', 'O', 'O', 'O', 'X', 'X', 'X', 'X', 'X', 'X', 'X', 'O', 'O', 'O', 'O'],
                    ['O', 'O', 'O', 'X', 'X', 'X', 'X', 'X', 'X', 'X', 'X', 'X', 'O', 'O', 'O'],
                    ['O', 'O', 'X', 'X', 'X', 'X', 'X', 'X', 'X', 'X', 'X', 'X', 'X', 'O', 'O'],
                    ['O', 'X', 'X', 'X', 'X', 'X', 'X', 'X', 'X', 'X', 'X', 'X', 'X', 'X', 'O'],
                    ['X', 'X', 'X', 'X', 'X', 'X', 'X', 'X', 'X', 'X', 'X', 'X', 'X', 'X', 'X']]
        self.map = []
        self.formula_nofood = lambda rv, luv, pv, iv: self.w1 * (rv / self.rarity["food"]) + self.w2 * \
                                                      (luv / max(self.lvl_dct[str(self.level + 1)])) + self.w3 * (
                                                              pv / 1) + self.w5 * (iv / 1)
        self.formula_food = lambda rv, pv, fv, iv: self.w1 * (rv / self.rarity["food"]) + self.w3 * (pv / 1) + self.w4 * \
                                                   (fv / self.rarity["food"]) + self.w5 * (1 / (iv + 1.2))

        self.flood_control_buffer = []
        self.flooded = False
        self.pool = 0

    def level_and_id(self, connected_socket: socket.socket):
        connected_socket.send(f"Broadcast id-{self.id} level-{self.level}\n".encode())

    def printc(self, text: str):
        print(f"{self.color}{text}\033[0m")

    def encrypt_text(self, text):
        key = self.name
        encrypted_text = ''
        key_length = len(key)

        for i in range(len(text)):
            char = text[i]
            key_char = key[i % key_length]
            encrypted_char = chr(ord(char) ^ ord(key_char))
            encrypted_text += encrypted_char

        return encrypted_text

    def decrypt_text(self, encrypted_text):
        return self.encrypt_text(encrypted_text)

    def broadcast(self, text: str):
        encrypted_text = self.encrypt_text(text)
        self.bufferize(f"Broadcast {encrypted_text}\n".encode())

    def parse_look(self, look_input: str):
        max_priority = float('-inf')
        most_important_item = None
        pos = 0, 0

        for i, line in enumerate(look_input.split(",")):
            x, y = get_position(i)
            for item in line.split(" "):
                if item in self.priority_order:
                    pv = 1 / ((x + 1) * (y + 1) + 1)
                    if item == 'food':
                        fv = 10 / (self.inventory['food'] + 1)
                        priority = self.formula_food(self.rarity[item], pv, fv, self.inventory[item])
                    else:
                        priority = self.formula_nofood(self.rarity[item], self.lvl_dct[str(self.level + 1)]
                                                       [self.items.index(item)], pv, self.inventory[item])
                    if priority > max_priority:
                        max_priority = priority
                        most_important_item = item
                        pos = x, y

        self.printc(f"Most important item: {most_important_item} with priority {max_priority} at position {pos}")
        return most_important_item, pos

    def check_elevation_items(self, look_input: str):
        case_0 = look_input.split(',')[0]
        here_items = [0, 0, 0, 0, 0, 0, 0]
        for item in case_0.split(' '):
            if item in self.items:
                here_items[self.items.index(item)] += 1
        for i, item in enumerate(here_items):
            if item < self.lvl_dct[str(self.level + 1)][i]:
                return False
        return True

    def find_level_head(self, message: str):
        if not self.head_level:
            return
        split_broadcast = message.split(' ')
        id_str = split_broadcast[0]
        level_str = split_broadcast[1]

        id_num = int(id_str.split('-')[1])
        level_num = int(level_str.split('-')[1])
        if level_num == self.level and id_num < self.id:
            self.head_level = False

    def create_map(self) -> list[Any]:
        rows = 8
        width_max = 15
        width = 1
        for _ in range(rows):
            if width <= width_max:
                self.map.append(["X"] * width)
                width += 2
        return self.map

    def fill_map(self, look_input: str) -> list[Any]:
        lines = look_input.split(",")
        if lines:
            row = 0
            col = 0
            for line in lines:
                try:
                    while self.map[row][col] != 'X':
                        col += 1
                        if col >= len(self.map[row]):
                            row += 1
                            col = 0
                except IndexError:
                    break
                self.map[row][col] = line.replace("[", "").replace("]", "").replace("\n", "")
        return self.map

    def init_missing_items(self):
        self.missing_items = [0, 0, 0, 0, 0, 0, 0]

        for item in self.lvl_dct[str(self.level + 1)]:
            if self.inventory[self.items[item]] < self.lvl_dct[str(self.level + 1)][item]:
                self.missing_items[item] = self.lvl_dct[str(self.level + 1)][item] - self.inventory[self.items[item]]

    def checkRequiredLvlChange(self):
        if self.inventory["linemate"] >= self.lvl_dct[str(self.level + 1)][0] and \
                self.inventory["deraumere"] >= self.lvl_dct[str(self.level + 1)][1] and \
                self.inventory["sibur"] >= self.lvl_dct[str(self.level + 1)][2] and \
                self.inventory["mendiane"] >= self.lvl_dct[str(self.level + 1)][3] and \
                self.inventory["phiras"] >= self.lvl_dct[str(self.level + 1)][4] and \
                self.inventory["thystame"] >= self.lvl_dct[str(self.level + 1)][5]:
            return True
        return False

    def dropElevationItems(self):
        for items in self.lvl_dct[str(self.level)]:
            for _ in range(items):
                self.bufferize("Set " + self.items[self.lvl_dct[str(self.level)].index(items)])
                self.inventory[self.items[self.lvl_dct[str(self.level)].index(items)]] -= 1

    def Elevate(self, connected_socket):
        if self.checkRequiredLvlChange():
            self.dropElevationItems()
            connected_socket.send("Incantation")
            self.leveling_up = True
            self.elevation_state = ElevationState.WAITING_RESOURCES

    def followElevation(self, data):
        pos = data[0]
        level = data[1]
        if level == self.level:
            go_to_sound_source(pos, self.connected_socket)

    def handle_level_up(self, data, connected_socket):
        if not self.leveling_up:
            return False
        if data == "Current level: " + str(self.level):
            self.leveling_up = False
            self.level += 1
            return True
        if data == "ko":
            self.leveling_up = False
            self.printc("Leveling up failed")
            return True
        self.broadcast(f"E{self.level}-TARGET:E{self.level + 1}")
        return True

    def broadcast_missing_items(self):
        self.broadcast(f"E{self.level}-MISSING: {self.missing_items}")

    def pick_up_stone(self, stone):
        stone_index = self.items.index(stone)
        is_missing = self.missing_items[stone_index] > 0
        self.bufferize("Take " + stone)
        self.printc(f"IA {self.id} is picking up {stone}")
        if is_missing:
            message = f"E{self.level}-MISSING: {self.missing_items}" if self.head_level else \
                f"E{self.level}-FOUND: {stone}"
            self.broadcast(message)
        self.bufferize("Inventory")
        time.sleep(0.1)
        self.bufferize("Look")

    def parse_missing_items(self, data):
        dt = data.split(": ")[1]
        current_missing_items = dt.split(", ")
        for i in range(len(current_missing_items)):
            self.missing_items[i] = int(current_missing_items[i])

    def refresh_missing_items(self, data):  # when "FOUND" is received
        if not self.head_level:
            return
        dt = data.split(": ")[1]
        index = self.items.index(dt)
        self.missing_items[index] -= 1
        self.broadcast_missing_items()

    def bufferize(self, data):
        self.flood_control_buffer.append(data)
        self.printc(f"Buffed: {data}")

    def unwind_buffer(self):
        if self.pool >= 8:
            return
        if len(self.flood_control_buffer) > 0:
            unwinded = self.flood_control_buffer.pop(0)
            self.connected_socket.send(unwinded)
            self.pool += 1
            self.printc(f"Sent: {unwinded}")

    def handle_broadcast(self, broadcast: str):
        broadcast = broadcast.split(", ")[1]
        decrypted_broadcast = self.decrypt_text(broadcast)
        if re.match(r"^E\d+-TARGET:E\d+$", decrypted_broadcast):
            pos = int(broadcast.split(", ")[0].split(" ")[1])
            level = int(decrypted_broadcast.split(":")[1][1])
            self.followElevation([pos, level])
        if re.match(r"^E\d+-MISSING: \d+, \d+, \d+, \d+, \d+, \d+, \d+$", decrypted_broadcast):
            self.parse_missing_items(decrypted_broadcast)
        if re.match(r"^E\d+-FOUND: \w+$", decrypted_broadcast):
            self.refresh_missing_items(decrypted_broadcast)

    def handle_specialData(self, data):
        pattern = r"^message \d+,"
        if re.match(pattern, data):
            self.handle_broadcast(data)
            return True
        return False

    def updateInventory(self, data):
        pattern = r"\[\s*food\s+(\d+),\s*linemate\s+(\d+),\s*deraumere\s+(\d+),\s*sibur\s+(\d+),\s*mendiane\s+(\d+)," \
                  r"\s*phiras\s+(\d+),\s*thystame\s+(\d+)\s*\]"
        match = re.match(pattern, data)
        if match:
            self.inventory["food"] = int(match.group(1))
            self.inventory["linemate"] = int(match.group(2))
            self.inventory["deraumere"] = int(match.group(3))
            self.inventory["sibur"] = int(match.group(4))
            self.inventory["mendiane"] = int(match.group(5))
            self.inventory["phiras"] = int(match.group(6))
            self.inventory["thystame"] = int(match.group(7))
            return True
        return False

    def loop(self, data):
        self.pool -= 1
        if "ok" in data or "dead" in data or data == [] or data is None or "ko" in data:
            return
        if self.updateInventory(data):
            return
        if self.handle_specialData(data):
            return
        rare_stones, pos = self.parse_look(data)
        if rare_stones:
            self.fill_map(data)
            moves = path_find(pos)
            if moves is not None:
                for move in moves:
                    self.printc(f"IA {self.id} is moving: {move}")
                    self.bufferize(move)
            self.pick_up_stone(rare_stones)
