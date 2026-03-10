import sys
from Crypto.PublicKey import RSA
from Crypto.Cipher import PKCS1_OAEP

def encrypt(data, pub):
        cipher = PKCS1_OAEP.new(pub)
        return cipher.encrypt(data)

def decrypt(data, priv):
        cipher = PKCS1_OAEP.new(priv)
        return cipher.decrypt(data)

def usage():
        print("usage: python rsa.py <enc|dec>")

if len(sys.argv) != 2:
        usage()
        sys.exit(1)

mode = sys.argv[1]

if mode == "enc":
        data = input('Message: ')
        key = RSA.generate(1024)
        pub = key.publickey()
        out = encrypt(data.encode(), pub)
        print('Ciphertext:', out.hex())
        print('PrivateKey:', key.export_key().hex())
elif mode == "dec":
        data = input('Ciphertext: ')
        key = RSA.import_key(bytes.fromhex(input('PrivateKey: ').strip()))
        out = decrypt(bytes.fromhex(data), key)
        print('Plaintext:', out)
else:
        usage()
