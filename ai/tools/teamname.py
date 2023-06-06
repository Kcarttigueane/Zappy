import json
import random
import os

scrit_dir = os.path.dirname(os.path.realpath(__file__))


adjectives_file = f"{scrit_dir}/adjectives-list.json"
animals_file = f"{scrit_dir}/animals.json"

adjectives: dict = json.load(open(adjectives_file))
animals: dict = json.load(open(animals_file))


def random_adjective():
    word: str = random.choice(adjectives)
    return word.capitalize()


def random_animal():
    word: str = random.choice(animals)
    return word.capitalize()


def random_team_name():
    return f"{random_adjective()} {random_animal()}"


if __name__ == '__main__':
    print(random_team_name())
