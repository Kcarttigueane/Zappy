import curses


class OutputWindow:
    def __init__(self, stdscr) -> None:
        height, width = stdscr.getmaxyx()
        self.output_win = curses.newwin(height - 1, width, 0, 0)
        self.output_win.scrollok(True)
        self.output_win.idlok(True)
        self.output_win.refresh()

    def add_output(self, output):
        self.output_win.addstr(output + "\n")
        self.output_win.refresh()

    def clear(self):
        self.output_win.clear()
        self.output_win.refresh()


class InputWindow:
    def __init__(self, stdscr) -> None:
        height, width = stdscr.getmaxyx()
        self.input_win = curses.newwin(1, width, height - 1, 0)
        self.input_win.addstr(0, 0, "Enter text: ")
        self.history = []
        self.history_index = 0

    def extend_query(self, query):
        self.input_win.clear()
        self.input_win.addstr(0, 0, "Enter text: " + query)
        self.input_win.refresh()

    def get_char(self):
        return self.input_win.get_wch()

    def get_history(self):
        if self.history_index == 0:
            return ""
        self.history_index += 1
        if self.history_index >= len(self.history):
            self.history_index = 0
        return self.history[self.history_index]

    def add_history(self, query):
        self.history.append(query)
        self.history_index = 0

    def clear(self):
        self.input_win.clear()
        self.input_win.addstr(0, 0, "Enter text: ")
        self.input_win.refresh()
