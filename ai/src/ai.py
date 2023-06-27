import socket
import time
from typing import List, Any
import re

from tools.parsing import got_numbers
from tools.encrypto import encrypt_message, decrypt_message
from enum import Enum
import json


class Direction(Enum):
    UP = 0
    RIGHT = 1
    BACK = 2
    LEFT = 3


def path_find(
    target: tuple[int, int]
) -> None | list[str]:  # Simple path finding algorithm
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


def is_valid_json(text):
    json_pattern = "^\s*(\{.*\}|\[.*\])\s*$"
    if re.match(json_pattern, text):
        return True
    return False


def get_position(
    i: int,
) -> tuple[int, int]:  # get the position of the player in the map from its enumeration
    level = int((-1 + (1 + 8 * i) ** 0.5) / 2)
    pos_within_level = i - level * (level + 1) // 2
    x = pos_within_level - level
    y = level
    return x, y


class AIState(Enum):
    HOARDING = 0
    SEARCHING = 1
    EVOLVING = 2
    SOON_EVOLVING = 3


class AI:
    def __init__(self, ident, name_, socket_) -> None:
        self.name = name_  # name of the team - used as key to encrypt/decrypt messages
        self.connected_socket: socket.socket = (
            socket_  # socket of the player - to communicate with the server
        )
        self.state = AIState.HOARDING  # Define how the AI will behave
        self.waiting_ids: List[
            int
        ] = []  # List of ids of team mates we wait for to evolve
        self.id = ident  # id of the player - Used to identify itself for other AIs
        self.color = "\033[0;30m"  # color of the AI - client for debug
        self.elevation_players = []  # Players id that answered to the elevation request
        self.tracking = [False, -1]  # On track of a player, id of the player

        self.priority_order = {  # Items priority order (density of items on the map)
            "food": 0.5,
            "linemate": 0.3,
            "deraumere": 0.15,
            "sibur": 0.1,
            "mendiane": 0.1,
            "phiras": 0.08,
            "thystame": 0.05,
        }
        self.rarity = {  # Items rarity
            "food": 1 / self.priority_order["food"],
            "linemate": 1 / self.priority_order["linemate"],
            "deraumere": 1 / self.priority_order["deraumere"],
            "sibur": 1 / self.priority_order["sibur"],
            "mendiane": 1 / self.priority_order["mendiane"],
            "phiras": 1 / self.priority_order["phiras"],
            "thystame": 1 / self.priority_order["thystame"],
        }

        self.w1 = 0.4  # rarity → Huge impact (from 2 to 20 * w1).
        self.w2 = 3  # level up → Medium impact (from 1 to 5 * w2).
        self.w3 = 1  # proximity → Undefined impact yet.
        self.w4 = 3  # food → Important (life or death) BUT way too challenging to decide a correct value.
        self.w5 = 1  # inventory → May be useful sometimes, but not always.

        self.items = [
            "linemate",
            "deraumere",
            "sibur",
            "mendiane",
            "phiras",
            "thystame",
            "food",
        ]

        self.lvl_dct = {  # Items needed to level up → same order as self.items.
            "2": [1, 0, 0, 0, 0, 0],
            "3": [1, 1, 1, 0, 0, 0],
            "4": [2, 0, 1, 0, 2, 0],
            "5": [1, 1, 2, 0, 1, 0],
            "6": [1, 2, 1, 3, 0, 0],
            "7": [1, 2, 3, 0, 1, 0],
            "8": [2, 2, 2, 2, 2, 1],
            "9": [0, 0, 0, 0, 0, 0],  # In case of error
        }
        self.lvl_pl = {"2": 1, "3": 2, "4": 2, "5": 4, "6": 4, "7": 6, "8": 6}
        self.inventory = {
            "food": 10,
            "linemate": 0,
            "deraumere": 0,
            "sibur": 0,
            "mendiane": 0,
            "phiras": 0,
            "thystame": 0,
        }

        self.others_inventory = {
            "food": 0,
            "linemate": 0,
            "deraumere": 0,
            "sibur": 0,
            "mendiane": 0,
            "phiras": 0,
            "thystame": 0,
        }

        self.level = 1
        self.map = [
            ["O", "O", "O", "O", "O", "O", "O", "X", "O", "O", "O", "O", "O", "O", "O"],
            ["O", "O", "O", "O", "O", "O", "X", "X", "X", "O", "O", "O", "O", "O", "O"],
            ["O", "O", "O", "O", "O", "X", "X", "X", "X", "X", "O", "O", "O", "O", "O"],
            ["O", "O", "O", "O", "X", "X", "X", "X", "X", "X", "X", "O", "O", "O", "O"],
            ["O", "O", "O", "X", "X", "X", "X", "X", "X", "X", "X", "X", "O", "O", "O"],
            ["O", "O", "X", "X", "X", "X", "X", "X", "X", "X", "X", "X", "X", "O", "O"],
            ["O", "X", "X", "X", "X", "X", "X", "X", "X", "X", "X", "X", "X", "X", "O"],
            ["X", "X", "X", "X", "X", "X", "X", "X", "X", "X", "X", "X", "X", "X", "X"],
        ]
        self.map = []
        self.formula_nofood = (
            lambda rv, luv, pv, iv: self.w1 * (rv / self.rarity["food"])
            + self.w2 * (luv / max(self.lvl_dct[str(self.level + 1)]))
            + self.w3 * (pv / 1)
            + self.w5 * (iv / 1)
        )
        self.formula_food = (
            lambda rv, pv, fv, iv: self.w1 * (rv / self.rarity["food"])
            + self.w3 * (pv / 1)
            + self.w4 * (fv / self.rarity["food"])
            + self.w5 * (1 / (iv + 1.2))
        )

        self.type_essential = {
            "found_item": "item",
            "evolve": "level",
            "need_help": "level",
            "help_coming": "target",
            "help_given": "target",
        }

        self.flood_control_buffer = []
        self.flooded = False
        self.pool = 0

    def encrypt_text(self, text):
        return encrypt_message(text, self.name)

    def decrypt_text(self, encrypted_text):
        return decrypt_message(encrypted_text, self.name)

    def message_format(self, type, essential):
        js_index = self.type_essential[type]
        msg_dict = {
            "message_type": self.encrypt_text(type),
            "ai_id": self.id,
            js_index: self.encrypt_text(essential),
        }
        json_item = json.dumps(msg_dict)
        return json_item

    def decrypt_format(self, json_item):
        msg_dict = json.loads(json_item)
        msg_type = self.decrypt_text(msg_dict["message_type"])
        js_index = self.type_essential[msg_type]
        essential = self.decrypt_text(msg_dict[js_index])
        new_dict = {
            "message_type": msg_type,
            "ai_id": msg_dict["ai_id"],
            js_index: essential,
        }
        return new_dict

    def printc(self, text: str):
        print(f"{self.color}{text}\033[0m")

    def broadcast(self, text: str):
        self.bufferize(f"Broadcast {text}\n")

    def parse_look(self, look_input: str):
        max_priority = float("-inf")
        most_important_item = None
        pos = 0, 0

        for i, line in enumerate(look_input.split(",")):
            x, y = get_position(i)
            for item in line.split(" "):
                if item in self.priority_order:
                    pv = 1 / ((x + 1) * (y + 1) + 1)
                    if item == "food":
                        fv = 10 / (self.inventory["food"] + 1)
                        iv = 1 / (self.inventory[item] + 1)
                        priority = self.formula_food(self.rarity[item], pv, fv, iv)
                    else:
                        iv = 1 / (self.inventory[item] + 1)
                        priority = self.formula_nofood(
                            self.rarity[item],
                            self.lvl_dct[str(self.level + 1)][self.items.index(item)],
                            pv,
                            iv,
                        )
                    if priority > max_priority:
                        max_priority = priority
                        most_important_item = item
                        pos = x, y

        self.printc(
            f"Most important item: {most_important_item} with priority {max_priority} at position {pos}"
        )
        return most_important_item, pos

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
                    while self.map[row][col] != "X":
                        col += 1
                        if col >= len(self.map[row]):
                            row += 1
                            col = 0
                except IndexError:
                    break
                self.map[row][col] = (
                    line.replace("[", "").replace("]", "").replace("\n", "")
                )
        return self.map

    def pick_up_stone(self, stone):
        self.bufferize("Take " + stone)
        self.printc(f"IA {self.id} is picking up {stone}")
        message = self.message_format("found_item", stone)
        self.broadcast(message)
        self.bufferize("Inventory")
        self.bufferize("Look")

    def bufferize(self, data: str):
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

    def follow_sound(self, source):
        movements = {
            1: "Forward",
            2: "Left, Forward",
            3: "Left, Forward",
            4: "Left, Forward",
            5: "Left, Left, Forward",
            6: "Right, Forward, Right, Forward",
            7: "Right, Forward",
            8: "Right, Forward, Left, Forward",
        }

        direction = movements[source]

        for move in direction.split(", "):
            self.bufferize(move)

    def followElevation(self, pos, level):
        if level == self.level:
            self.follow_sound(pos)

    def otherInv(self, data):
        item = data["item"]
        self.others_inventory[item] += 1

    def data_management(self, data: dict, pos: int):
        if data["message_type"] == "found_item" and data["item"] != "food":
            self.otherInv(data)
        elif data["message_type"] == "evolve":
            print(f"IA {data['ai_id']} is evolving - \"They grow up so fast\"")
        elif data["message_type"] == "need_help":
            if self.state == AIState.EVOLVING or self.state == AIState.SOON_EVOLVING:
                return
            self.state = AIState.SEARCHING
            if self.tracking[0] and self.tracking[1] != data["ai_id"]:
                print(
                    f'IA {self.id} is already tracking someone else: "I will not help"'
                )
            if pos == 0:
                print(
                    f'IA {self.id} found the source of the sound: "I am the best detective"'
                )
                self.state = AIState.EVOLVING
                self.bufferize(self.message_format("help_given", data["ai_id"]))
            print(f"IA {data['ai_id']} is searching for help - \"I AM COOOOMING\"")
            self.tracking = (True, data["ai_id"])
            self.follow_sound(pos)
        elif data["message_type"] == "help_given":
            if self.state == AIState.EVOLVING and data["target"] == self.id:
                if data["ai_id"] in self.elevation_players:
                    self.elevation_players.remove(data["ai_id"])
                    print(
                        f"IA {data['ai_id']} joined me to evolve - \"That's what friends are for\""
                    )
                else:
                    print(
                        f"IA {data['ai_id']} is not tracking me or is an unexpected friend. - \"What r u doing on my swamp\""
                    )
                pass
            return

    def handle_broadcast(self, broadcast: str):
        match_ = re.match(r"^message (\d+),(.*)", broadcast)
        if match_:
            pos = int(match_.group(1))
            text = match_.group(2)
            print(f"IA {self.id} received a broadcast from {pos}: {text}")
            if not is_valid_json(text):
                return
            data: dict = self.decrypt_format(text)
            self.data_management(data, pos)

    def handle_specialData(self, data):
        pattern = r"^message (\d+),(.*)"
        if re.match(pattern, data):
            self.handle_broadcast(data)
            return True
        return False

    def updateInventory(self, data):
        pattern = (
            r"\[\s*food\s+(\d+),\s*linemate\s+(\d+),\s*deraumere\s+(\d+),\s*sibur\s+(\d+),\s*mendiane\s+(\d+),"
            r"\s*phiras\s+(\d+),\s*thystame\s+(\d+)\s*\]"
        )
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

    def updateLevel(self, data):
        pattern = r"^Current level: (\d+)"
        match = re.match(pattern, data)
        if match:
            self.level = int(match.group(1))
            self.printc(f"Level: {self.level}")
            self.state = AIState.HOARDING
            self.bufferize("Inventory")
            self.bufferize("Look")
            return True
        return False

    def evolution_process(self):
        self.state = AIState.SOON_EVOLVING
        if self.lvl_pl[str(self.level + 1)] < len(self.elevation_players):
            return False
        return True

    def can_evolve(self):
        dct_lvl = self.lvl_dct[str(self.level + 1)]
        copy_inv = []
        for key, value in self.inventory.items():
            if key == "food":
                continue
            copy_inv.append(value)
        for i, unit in enumerate(dct_lvl):
            if unit > copy_inv[i]:
                return False
        return True

    def wombat(self, data):
        if "Elevation underway" in data:
            self.state = AIState.EVOLVING
            self.printc(
                f'IA {self.id} is evolving - "AM I A BUTTERFLY? BECAUSE I FEEL LIKE A BUTTERFLY"'
            )
            return True
        return False

    def dropElevationItems(self):
        dct_lvl = self.lvl_dct[str(self.level + 1)]
        for i, unit in enumerate(dct_lvl):
            for _ in range(unit):
                self.bufferize(f"Set {self.items[i]}")

    def loop(self, data):
        self.pool -= 1
        if "dead" in data:
            self.printc(f'IA {self.id} died - "Oh nooo"')
        if self.updateLevel(data):
            return
        if "ok" in data or "dead" in data or data == [] or data is None or "ko" in data:
            if self.state == AIState.EVOLVING:
                self.elevation_players = []
                self.state = AIState.HOARDING
                self.printc(
                    f'IA {self.id} had to abort evolution due to a failure - "So close yet so far"'
                )
                self.bufferize("Inventory")
                self.bufferize("Look")
            return
        if self.updateLevel(data):
            return
        if self.wombat(data):
            return
        if self.state == AIState.EVOLVING:
            return
        if self.can_evolve():
            if self.evolution_process():
                self.dropElevationItems()
                self.bufferize("Incantation")
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
