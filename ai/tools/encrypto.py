from itertools import cycle
import sys


def encrypt_message(data, key):
    return ''.join(chr(ord(x) ^ ord(y)) for (x,y) in zip(data, cycle(key)))


def decrypt_message(data, key):
    return encrypt_message(data, key)


if __name__ == '__main__':
    if len(sys.argv) != 3:
        print("Usage: python3 encrypto.py <key> <message>")
        exit(84)
    key = sys.argv[1]
    message = sys.argv[2]
    encrypted = encrypt_message(message, key)
    print(f"Encrypted message: {encrypted}")
    decrypted = decrypt_message(encrypted, key)
    print(f"Decrypted message: {decrypted}")
