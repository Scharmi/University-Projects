from pwn import *
from pwn import remote
import hashlib
from Crypto.Cipher import AES
from Crypto.Random import get_random_bytes, random
def pad(msg):
    byte = 16 - len(msg) % 16
    return msg + bytes([byte] * byte)

def int_to_bits(n):
    return format(n, '064b')
def last_k_bits_match(n, m, k):
    return n & (2**k-1) == m & (2**k-1)
def add_oldest_bit(n, bit, n_length):
    return n | (bit << n_length)
def mult_last_k_bits(n, m, k):
    return (n & (2**k-1)) * (m & (2**k-1)) & (2**k-1)
def xor_k_bits(n, m, k):
    return (n & (2**k-1)) ^ (m & (2**k-1))
def get_hex_from_hex_string(s):
    return bytes.fromhex(s)
def bytes_to_int(b):
    return int.from_bytes(b, "big")
def int_to_16_bytes(n):
    return n.to_bytes(16, "big")
def cut_0x(s):
    return s[2:]
def fill_string_to_16(s):
    while len(s) % 16 != 0:
        s = "0" + s
    return s

host = sys.argv[1]
port = sys.argv[2]
conn = remote(host, port)
conn.recvn(len("Welcome to the crypto task game!\n"))
conn.recvn(len("\n"))
conn.recvn(len("Which challenge do you want to solve?\n"))
conn.recvn(len(" 1) NCG\n"))
conn.recvn(len(" 2) Block cipher (two flags here)\n"))
conn.sendline(b"2")
conn.recvn(len("> "))
iv = conn.recvn(32).strip().decode()
encrypted_hello = conn.recvn(32).strip().decode()
int_hello_enc = int(encrypted_hello, 16)
hello = b'Hello'
hello = pad(hello)
int_hello = int(hello.hex(), 16)
flag_request = b'flag?aaaaaaaaaa'
flag_request = pad(flag_request)
int_flag_request = int(flag_request.hex(), 16)
conn.sendline(fill_string_to_16(cut_0x(hex(int(iv, 16) ^ int_flag_request ^ int_hello))) + fill_string_to_16(cut_0x(hex(int_hello_enc))))
conn.interactive()
