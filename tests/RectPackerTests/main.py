from PIL import Image, ImageDraw
import os
import random

def generate_random_color_image(width, height, border_size = 3):
    # Create a new image with a transparent background
    image = Image.new("RGBA", (width, height), (0, 0, 0, 0))
    draw = ImageDraw.Draw(image)

    # Define the border color
    border_color = (random.randint(0, 255), random.randint(0, 255), random.randint(0, 255), 255)

    # Draw the border
    draw.rectangle([0, 0, width - 1, height - 1], outline=border_color, width=border_size)

    return image

def save_image(image, folder, filename):
    # Ensure the folder exists
    os.makedirs(folder, exist_ok=True)

    # Save the image as a PNG file
    image.save(os.path.join(folder, filename), "PNG")

def generate_and_save_images(num_images, folder):
    for i in range(num_images):
        # Generate random width and height for each image
        width = random.randint(80, 500)
        height = random.randint(80, 500)

        # Generate a random color image
        random_image = generate_random_color_image(width, height)

        # Save the image to the specified folder with a unique filename
        filename = f"random_image_{i + 1}.png"
        save_image(random_image, folder, filename)

if __name__ == "__main__":
    num_images_to_generate = 15  # Change this to the desired number of images
    output_folder = "output_images"

    generate_and_save_images(num_images_to_generate, output_folder)
