import argparse


class EpitechParser(argparse.ArgumentParser):
    def error(self, message):
        self.print_help()
        exit(84)


parser = EpitechParser(description="Zappy AI - Console Client", add_help=False)

parser.add_argument("-n", "--name", type=str, help="name of the team - default: Random Team Name", required=True)
parser.add_argument("-h", "--host", type=str, default="localhost", help="host of the server - default: localhost")
parser.add_argument("-p", "--port", type=int, default=4242, help="port of the host - default: 4242")
parser.add_argument("-i", "--identifier", type=int, default=0, help="identifier of IA in its team - default: 0")
parser.add_argument("--help", action="help", help="show this help message and exit")


def got_numbers(data):
    for char in data:
        if char.isdigit():
            return True
    return False
