import hashlib
import os
import sys
import math

def calculate_collision_prob(n):
    # n = number of items in hashset, H = 2^256
    H = 2**256
    try:
        # Birthday Paradox approximation
        return 1 - math.exp(-(n**2) / (2 * H))
    except OverflowError:
        return 1.0

def generate_random_hashes(iterations=10000):
    hashset = set()
    results = []
    collisions = 0
    
    print(f"Processing {iterations:,} hashes...")

    for i in range(iterations):
        raw_data = os.urandom(16)
        sha256_hash = hashlib.sha256(raw_data).hexdigest()
        
        # Check for common occurrences (collisions)
        if sha256_hash in hashset:
            collisions += 1
        else:
            hashset.add(sha256_hash)
            
        # Store for display (first 5 and last 5)
        if i < 5 or i >= iterations - 5:
            results.append((i + 1, raw_data.hex(), sha256_hash))

    # Display Table
    print(f"\n{'No.':<6} | {'Source Data (Hex)':<35} | {'SHA-256 Hash'}")
    print("-" * 110)
    
    for idx, (num, src, hsh) in enumerate(results):
        print(f"{num:<6} | {src:<35} | {hsh}")
        if idx == 4 and iterations > 10:
            print(f"{'...':<6} | {'...':<35} | {'...'}")

    # Summary Info
    total_in_set = len(hashset)
    prob = calculate_collision_prob(total_in_set)

    print("-" * 110)
    print(f"Total Inputs Processed: {iterations:,}")
    print(f"Unique Hashes Stored:   {total_in_set:,}")
    print(f"Collisions Detected:    {collisions}")
    print(f"Theoretical Prob:       {prob:.2e}")

if __name__ == "__main__":
    num_lines = 10000
    if len(sys.argv) > 1:
        try:
            num_lines = int(sys.argv[1])
        except ValueError:
            print("Usage: python solve.py <number>")
            sys.exit(1)
    
    generate_random_hashes(num_lines)
