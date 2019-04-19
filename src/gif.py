import os
from PIL import Image

base_dir = os.path.dirname(os.getcwd())
res_dir = os.path.join(base_dir, 'res/')

if __name__ == '__main__':
    im = Image.open(res_dir + "result2_0.png")
    images = []
    for i in range(1, 20):
        images.append(Image.open(res_dir + "result2_" + str(i)  + ".png"))

    for i in range(1, 20):
        images.append(Image.open(res_dir + "result2_" + str(20 - i)  + ".png"))
    im.save(res_dir + 'result2.gif', save_all=True, append_images=images,loop=2,duration=10,comment=b"result1")
