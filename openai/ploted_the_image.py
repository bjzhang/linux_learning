#!/usr/bin/env python3

import matplotlib.pyplot as plt
import matplotlib.image as mpimg
import sys

def plot_object_on_image(image_path, x_min, y_min, x_max, y_max, output_path):
    # Read the image
    img = mpimg.imread(image_path)

    # Get the dimensions of the input image
    img_height, img_width, _ = img.shape

    # Calculate the width and height of the object in image space
    obj_width = img_width * (x_max - x_min)
    obj_height = img_height * (y_max - y_min)

    # Create a figure and axis
    fig, ax = plt.subplots()

    # Set the x and y limits in image space
    ax.set_xlim([0, img_width])
    ax.set_ylim([0, img_height])

    # Plot the image
    ax.imshow(img, extent=[0, img_width, 0, img_height])

    # Plot the object with unchanged aspect ratio
    rect = plt.Rectangle((x_min * img_width, y_min * img_height), obj_width, obj_height, edgecolor='r', facecolor='none')
    ax.add_patch(rect)

    # Save the plot to a file
    plt.savefig(output_path)

# Example usage: read image path, specify normalized bounds, and output file path
if len(sys.argv) != 7:
    print("Usage: python script.py image_path x_min y_min x_max y_max output_path")
    sys.exit(1)

image_path = sys.argv[1]
x_min = float(sys.argv[2])
y_min = float(sys.argv[3])
x_max = float(sys.argv[4])
y_max = float(sys.argv[5])
output_path = sys.argv[6]

# Plot the image and save to file
plot_object_on_image(image_path, x_min, y_min, x_max, y_max, output_path)

