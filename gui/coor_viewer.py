from PIL import Image
from PIL import ImageTk
import tkinter as tk

def show_image_with_coordinates(file_path):
    # Load the image
    image = Image.open(file_path)

    # Create a Tkinter window
    window = tk.Tk()
    window.title("Image Viewer")

    # Create a canvas to display the image
    canvas = tk.Canvas(window, width=image.width, height=image.height)
    canvas.pack()

    # Display the image on the canvas
    image_tk = ImageTk.PhotoImage(image)
    canvas.create_image(0, 0, anchor=tk.NW, image=image_tk)

    def mouse_click(event):
        # Get the mouse coordinates
        x = event.x
        y = event.y

        # Display the coordinates
        print("Mouse coordinates (x, y):", x, y)

    # Bind the mouse click event to the canvas
    canvas.bind("<Button-1>", mouse_click)

    # Run the Tkinter event loop
    tk.mainloop()

# Example usage: python_script.py image.png
import sys

if __name__ == "__main__":
    if len(sys.argv) == 2:
        file_path = sys.argv[1]
        show_image_with_coordinates(file_path)
    else:
        print("Please provide the path to a PNG file as a parameter.")
