


class AI:
    def __init__(self) -> None:
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
        self.map = []

    def parse_look(self, look_input: str) -> None:
        stones = {}
        rarest_minerals = []
        min_priority = float('inf')

        for line in look_input.split(","):
            for mineral in line.split(" "):
                if mineral in stones:
                    stones[mineral] += 1
                else:
                    stones[mineral] = 1
        for mineral, count in stones.items():
            if mineral in self.priority_order:
                priority = self.priority_order[mineral]
                if count > 0 and priority < min_priority:
                    rarest_minerals = [mineral]
                    min_priority = priority
                elif count > 0 and priority == min_priority:
                    rarest_minerals.append(mineral)
        return rarest_minerals if rarest_minerals else None
    
    def create_map(self) -> None:
        rows = 8
        width_max = 15
        width = 1
        for _ in range(rows):
            if width <= width_max:
                self.map.append(["X"] * width)
                width += 2
        return self.map

    def fill_map(self, look_input: str) -> None:
        self.map = self.create_map()
        lines = look_input.split(",")
        if lines:
            row = 0
            col = 0
            for line in lines:
                if col >= len(self.map[row]):
                    row += 1
                    col = 0
                self.map[row][col] = line
                col += 1

