import numpy as np
from numpy.lib.stride_tricks import sliding_window_view
import matplotlib.pyplot as plt
from matplotlib.colors import ListedColormap

def rotate_kernel(k):
    pos = [(0,0),(0,1),(0,2),(1,2),(2,2),(2,1),(2,0),(1,0)]

    vals = [k[i,j] for i,j in pos]
    vals = np.roll(vals, 1)   # clockwise shift

    out = k.copy()
    for (i,j),v in zip(pos, vals):
        out[i,j] = v

    return out


def plot_thinning_steps(res):

    n = len(res)

    # custom colormap
    cmap = ListedColormap([
        "black",   # 0
        "white",   # 1
        "grey"     # 2
    ])

    fig, axes = plt.subplots(n, 3, figsize=(9, 3*n))

    if n == 1:
        axes = np.array([axes])

    for i, (title, img, kernel) in enumerate(res):

        ax_img = axes[i, 0]
        ax_text = axes[i, 1]
        ax_kernel = axes[i, 2]

        # --- IMAGE ---
        ax_img.imshow(img, cmap=cmap, vmin=0, vmax=2, interpolation="nearest")

        h, w = img.shape
        ax_img.set_xticks(np.arange(-.5, w, 1), minor=True)
        ax_img.set_yticks(np.arange(-.5, h, 1), minor=True)
        ax_img.grid(which="minor", color="black", linewidth=0.5)

        ax_img.set_xticks([])
        ax_img.set_yticks([])

        # --- CENTER LABEL ---
        ax_text.axis("off")
        ax_text.text(
            0.5,
            0.5,
            title,
            ha="center",
            va="center",
            fontsize=12,
            fontweight="bold"
        )

        # --- KERNEL ---
        ax_kernel.imshow(kernel, cmap=cmap, vmin=0, vmax=2, interpolation="nearest")

        h, w = kernel.shape
        ax_kernel.set_xticks(np.arange(-.5, w, 1), minor=True)
        ax_kernel.set_yticks(np.arange(-.5, h, 1), minor=True)
        ax_kernel.grid(which="minor", color="black", linewidth=0.5)

        ax_kernel.set_xticks([])
        ax_kernel.set_yticks([])

    plt.tight_layout()
    plt.show()

img = np.array([
    [1, 1, 1, 0],
    [0, 1, 1, 1],
    [0, 1, 1, 1],
    [0, 1, 1, 1]
], dtype=np.uint8)

kernel = np.array([
    [0, 0, 0],
    [2, 1, 2],
    [1, 1, 1]
], dtype=np.uint8)

mask = kernel != 2

res = []

for i in range(8):
    padded = np.pad(img, pad_width=1, mode='constant', constant_values=0)
    windows = sliding_window_view(padded, (3,3))
    hits = np.all(windows[..., mask] == kernel[mask], axis=-1).astype(np.uint8)
    img = img - hits
    res.append((f'Iteration {i + 1}', img.copy(), kernel.copy()))
    kernel = rotate_kernel(kernel)

plot_thinning_steps(res)

