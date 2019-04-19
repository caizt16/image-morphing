import os
import json
import numpy as np
from PIL import Image
import matplotlib.pyplot as plt

base_dir = os.path.dirname(os.getcwd())
img_dir = os.path.join(base_dir, 'img')
feature_dir = os.path.join(base_dir, 'feature_point')
data_dir = os.path.join(base_dir, 'data')

h, w = 0, 0
for filename in os.listdir(img_dir):
    img = np.array(Image.open(os.path.join(img_dir, filename)))
    h, w = img.shape[0], img.shape[1]
    plt.imshow(img)
    plt.show()
# for filename in os.listdir(feature_dir):
#     with open(os.path.join(feature_dir, filename), 'r') as f:
#         data = json.loads(f.read())
#         with open(os.path.join(data_dir, filename), 'w') as f2:
#             f2.write('%d %d\n' % (0, 0))
#             f2.write('%d %d\n' % (w, 0))
#             f2.write('%d %d\n' % (0, h / 2))
#             f2.write('%d %d\n' % (w, h / 2))
#             f2.write('%d %d\n' % (0, h))
#             f2.write('%d %d\n' % (w, h))
#             try:
#                 for value in data['faces'][0]['landmark'].values():
#                     f2.write('%d %d\n' % (value['x'], value['y']))
#             except:
#                 pass
