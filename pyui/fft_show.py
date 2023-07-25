import re
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D
import numpy as np

def read_complex_numbers_from_file(file_path):
    with open(file_path, 'r') as file:
        complex_numbers = []
        for line in file:
            line = line.strip()
            match = re.match(r'^([+-]?\d+(\.\d*)?)([+-]\d+(\.\d*)?)i$', line)
            if match:
                real = float(match.group(1))
                imag = float(match.group(3))
                complex_numbers.append((real, imag))
            else:
                print(f"Invalid complex number format in line: {line}")
    return complex_numbers

def visualize_complex_numbers(complex_numbers):
    fig = plt.figure()
    ax = fig.add_subplot(111, projection='3d')

    # Extract real and imaginary parts from complex numbers
    a_values = [a for a, _ in complex_numbers]
    b_values = [b for _, b in complex_numbers]
    mod = np.sqrt(np.array(a_values) ** 2 + np.array(b_values) ** 2)
    # Number of lines in the file (y-axis)
    y_axis = range(1, len(complex_numbers) + 1)

    # Plotting the data points on xoy and yoz planes
    ax.plot(mod, y_axis, [0] * len(complex_numbers), c='b')  # xoy plane
    ax.plot([0] * len(complex_numbers), y_axis, a_values, c='r')    # yoz plane

    # Labeling the axes
    ax.set_xlabel('b')
    ax.set_ylabel('Line Number')
    ax.set_zlabel('a')

    plt.show()

if __name__ == '__main__':
    file_path = '../build/Debug/dft.txt'  # Replace with the actual file path
    complex_numbers = read_complex_numbers_from_file(file_path)
    visualize_complex_numbers(complex_numbers)
