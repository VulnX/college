import sys
from Crypto.Cipher import AES
from Crypto.Random import get_random_bytes
from Crypto.Util.Padding import pad, unpad

def encrypt(data, key):
        cipher = AES.new(key, AES.MODE_CBC)
        ct = cipher.encrypt(pad(data, AES.block_size))
        return cipher.iv + ct

def decrypt(data, key):
        iv = data[:16]
        ct = data[16:]
        cipher = AES.new(key, AES.MODE_CBC, iv=iv)
        return unpad(cipher.decrypt(ct), AES.block_size)

def usage():
        print("usage: python aes.py <enc|dec>")

if len(sys.argv) != 2:
        usage()
        sys.exit(1)

mode = sys.argv[1]


if mode == "enc":
        data = input('Message: ')
        key = get_random_bytes(32)
        out = encrypt(data.encode(), key)
        print('Ciphertext:', out.hex())
        print('Key:', key.hex())
elif mode == "dec":
        data = input('Ciphertext: ')
        key = bytes.fromhex(input('Key: ').strip())
        out = decrypt(bytes.fromhex(data), key)
        print('Plaintext:', out)
else:
        usage()
