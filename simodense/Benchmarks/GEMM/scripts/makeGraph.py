#import matplotlib.pyplot as plt
#import re

#data = '''
#Benchmarking for matrix size 2x2 size
#204
#Benchmarking for matrix size 4x4 size
#1201
#Benchmarking for matrix size 8x8 size
#8791
#Benchmarking for matrix size 16x16 size
#68108
#Benchmarking for matrix size 32x32 size
#535181
#Benchmarking for matrix size 64x64 size
#4236856
#'''

## Extract data
#pattern = re.compile(r'(\d+)x(\d+) size\n(\d+)')
#matches = pattern.findall(data)
#sizes = [int(match[0]) for match in matches]
#clocks = [int(match[2]) for match in matches]

## Plot
#plt.figure(figsize=(10, 6))
#plt.scatter(sizes, clocks, label='Benchmarking')
#plt.xlabel('Matrix Size (NxN)')
#plt.ylabel('Time (cycles)')
#plt.title('Benchmarking Results')
#plt.xticks(sizes, [f'{size}x{size}' for size in sizes])
#plt.grid(True)
#plt.legend()
#plt.show()


import matplotlib.pyplot as plt
import re

data1 = '''
Benchmarking for matrix size 2x2 size
204
Benchmarking for matrix size 4x4 size
1201
Benchmarking for matrix size 8x8 size
8791
Benchmarking for matrix size 16x16 size
68108
Benchmarking for matrix size 32x32 size
535181
Benchmarking for matrix size 64x64 size
4236856
'''

data2 = '''
Benchmarking for matrix size 8x8 size
8831
Benchmarking for matrix size 16x16 size
70568
Benchmarking for matrix size 32x32 size
563346
Benchmarking for matrix size 64x64 size
4504972
'''

# Extract data1
pattern = re.compile(r'(\d+)x(\d+) size\n(\d+)')
matches = pattern.findall(data1)
sizes1 = [int(match[0]) for match in matches]
clocks1 = [int(match[2]) for match in matches]

# Extract data2
matches = pattern.findall(data2)
sizes2 = [int(match[0]) for match in matches]
clocks2 = [int(match[2]) for match in matches]

# Plot
plt.figure(figsize=(10, 6))
plt.plot(sizes1, clocks1, marker='o', label='Data 1')
plt.plot(sizes2, clocks2, marker='x', label='Data 2')
plt.xlabel('Matrix Size (NxN)')
plt.ylabel('Time (cycles)')
plt.title('Benchmarking Results')
plt.xticks(sizes1 + sizes2, [f'{size}x{size}' for size in sizes1 + sizes2])
plt.grid(True)
plt.legend()
plt.show()
