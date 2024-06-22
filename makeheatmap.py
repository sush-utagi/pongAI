import numpy as np
import matplotlib.pyplot as plt

# Generate a black and white heatmap
size = 128  # size of the heatmap
heatmap = np.random.rand(size, size)  # random values for the heatmap

# Plot the heatmap
plt.imshow(heatmap, cmap='gray')
plt.axis('off')
plt.savefig('example.png', bbox_inches='tight', pad_inches=0)
plt.show()
