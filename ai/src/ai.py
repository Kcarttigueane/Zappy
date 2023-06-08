from pathfinding.core.grid import Grid
from pathfinding.finder.a_star import AStarFinder
from pathfinding.core.diagonal_movement import DiagonalMovement


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
        self.map = [['O', 'O', 'O', 'O', 'O', 'O', 'O', 'X', 'O', 'O', 'O', 'O', 'O', 'O', 'O'],
                    ['O', 'O', 'O', 'O', 'O', 'O', 'X', 'X', 'X', 'O', 'O', 'O', 'O', 'O', 'O'],
                    ['O', 'O', 'O', 'O', 'O', 'X', 'X', 'X', 'X', 'X', 'O', 'O', 'O', 'O', 'O'],
                    ['O', 'O', 'O', 'O', 'X', 'X', 'X', 'X', 'X', 'X', 'X', 'O', 'O', 'O', 'O'],
                    ['O', 'O', 'O', 'X', 'X', 'X', 'X', 'X', 'X', 'X', 'X', 'X', 'O', 'O', 'O'],
                    ['O', 'O', 'X', 'X', 'X', 'X', 'X', 'X', 'X', 'X', 'X', 'X', 'X', 'O', 'O'],
                    ['O', 'X', 'X', 'X', 'X', 'X', 'X', 'X', 'X', 'X', 'X', 'X', 'X', 'X', 'O'],
                    ['X', 'X', 'X', 'X', 'X', 'X', 'X', 'X', 'X', 'X', 'X', 'X', 'X', 'X', 'X']]

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
        return str(rarest_minerals[0]) if rarest_minerals else None

    def fill_map(self, look_input: str) -> None:
        lines = look_input.split(",")
        if lines:
            row = 0
            col = 0
            for line in lines:
                while (self.map[row][col] != 'X'):
                    col += 1
                    if col >= len(self.map[row]):
                        row += 1
                        col = 0
                self.map[row][col] = line.replace("[", "").replace("]", "").replace("\n", "")
        return self.map

    def find_path_to_stone(self, stone: str) -> str:
        target_row, target_col = 0, 0
        start_row, start_col = 0, 7
        for row in range(len(self.map)):
            for col in range(len(self.map[row])):
                for item in self.map[row][col].split(" "):
                    if item == stone:
                        target_row, target_col = row, col
                        break
        if target_row == 0 and target_col == 0:
            return None
        matrix = [[0 if self.map[r][c] == 'O' else 1
                   for c in range(len(self.map[r]))] for r in range(len(self.map))]
        grid = Grid(matrix=matrix)
        start_node = grid.node(start_col, start_row)
        target_node = grid.node(target_col, target_row)
        finder = AStarFinder(diagonal_movement=DiagonalMovement.never)
        path, _ = finder.find_path(start_node, target_node, grid)
        if len(path) == 0:
            return "Path is empty"
        move_list = []
        prev_col, prev_row = start_col, start_row
        for col, row in path[1:]:
            col_diff = col - prev_col
            row_diff = row - prev_row
            if col_diff == 1:
                move_list.append("Right")
            elif col_diff == -1:
                move_list.append("Left")
            elif row_diff == 1:
                move_list.append("Forward")
            prev_col, prev_row = col, row
        return move_list