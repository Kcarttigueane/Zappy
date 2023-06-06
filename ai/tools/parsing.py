import argparse
from tools.teamname import random_team_name as tn


class EpitechParser(argparse.ArgumentParser):
    def error(self, message):
        self.print_help()
        exit(84)


parser = EpitechParser(description="Zappy AI - Console Client", add_help=False)

parser.add_argument("-n", "--name", type=str, default=tn(), help="name of the team - default: Random Team Name")
parser.add_argument("-h", "--host", type=str, default="localhost", help="host of the server - default: localhost")
parser.add_argument("-p", "--port", type=int, default=4242, help="port of the host - default: 4242")
parser.add_argument("--help", action="help", help="show this help message and exit")
