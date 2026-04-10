def print_bitmap(bitmap):
    for row in bitmap:
        print(' '.join(str(cell) for cell in row))

# Example bitmap for "J"
j_bitmap = [
    [0, 0, 0, 0, 1, 0],
    [0, 0, 0, 0, 1, 0],
    [0, 0, 0, 0, 1, 0],
    [0, 0, 0, 0, 1, 0],
    [0, 0, 0, 0, 1, 0],
    [0, 0, 0, 0, 1, 0],
    [1, 0, 0, 0, 1, 0],
    [0, 1, 1, 1, 0, 0],
    [0, 0, 0, 0, 0, 0],
    [0, 0, 0, 0, 0, 0]
]

print_bitmap(j_bitmap)

# Compression: Run-length encoding (RLE) example
def compress_bitmap(bitmap):
    compressed = []
    for row in bitmap:
        compressed_row = []
        prev = row[0]
        count = 1
        for i in range(1, len(row)):
            if row[i] == prev:
                count += 1
            else:
                compressed_row.append((prev, count))
                prev = row[i]
                count = 1
        compressed_row.append((prev, count))
        compressed.append(compressed_row)
    return compressed

# Decompression: Revert back from RLE
def decompress_bitmap(compressed_bitmap):
    decompressed = []
    for row in compressed_bitmap:
        decompressed_row = []
        for value, count in row:
            decompressed_row.extend([value] * count)
        decompressed.append(decompressed_row)
    return decompressed

compressed_j = compress_bitmap(j_bitmap)
decompressed_j = decompress_bitmap(compressed_j)

# Print decompressed bitmap to verify correctness
print_bitmap(decompressed_j)

# Flip the bitmap horizontally
def flip_bitmap_horizontally(bitmap):
    return [list(reversed(row)) for row in bitmap]

# Example: flipping the decompressed bitmap
flipped_j = flip_bitmap_horizontally(decompressed_j)

# Print the flipped bitmap
print_bitmap(flipped_j)
