from pwn import *
from pwn import remote
import sys

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

def suffix_match(a_suffix, xor_suffix, numbers, length):
    result = True
    for i in range(4):
        if not last_k_bits_match(xor_k_bits(mult_last_k_bits(a_suffix, numbers[i], length), xor_suffix, length), numbers[i+1], length):
            result = False
    return result

def find_matching_a(length, a_suffix, xor_suffix, new_oldest_bit, numbers):
    new_a_suffix = add_oldest_bit(a_suffix, new_oldest_bit, length)
    prod = mult_last_k_bits(new_a_suffix, numbers[0], length + 1)
    new_xor_oldest_bit = int(int_to_bits(prod)[64 - length - 1]) ^ int(int_to_bits(numbers[1])[64 - length - 1])
    new_xor_suffix = add_oldest_bit(xor_suffix, new_xor_oldest_bit, length)
    if not suffix_match(new_a_suffix, new_xor_suffix, numbers, length + 1):
        return (False, "", "")
    else:
        if length == 63:
            return (True, new_a_suffix, new_xor_suffix)
    (result, a, x) = find_matching_a(length + 1, new_a_suffix, new_xor_suffix, 1, numbers)
    if result:
        return (True, a, x)
    (result, a, x) = find_matching_a(length + 1, new_a_suffix, new_xor_suffix, 0, numbers)
    if result:
        return (True, a, x)
    return (False, "", "")
        

    



end = False
while not end:
    number = []
    host = sys.argv[1]
    port = sys.argv[2]
    conn = remote(host, port)
    #conn = remote("cryptotask2023.tailcall.net", 30007)
    conn.recvn(len("Welcome to the crypto task game!\n"))
    conn.recvn(len("\n"))
    conn.recvn(len("Which challenge do you want to solve?\n"))
    conn.recvn(len(" 1) NCG\n"))
    conn.recvn(len(" 2) Block cipher (two flags here)\n"))
    conn.sendline(b"1")
    conn.recvn(len("> "))

    for i in range(5):
        response = conn.recvline().decode().strip()
        number.append(int(response))
    (res, a, x) = find_matching_a(0, 0, 0, 1, number)
    if not res:
        (res, a, x) = find_matching_a(0, 0, 0, 0, number)
    conn.recvn(len("What's next?\n"))
    conn.sendline(str((number[4] * a ^ x) % 2**64).encode())
    flag = conn.recvline()
    if(flag  != b'nope\n'):
        end = True
print(flag.decode())
