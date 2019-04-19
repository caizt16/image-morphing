import os
import requests
from collections import OrderedDict

base_dir = os.path.dirname(os.getcwd())
img_dir = os.path.join(base_dir, 'img')
feature_dir = os.path.join(base_dir, 'feature_point')

if __name__ == '__main__':
    for filename in os.listdir(img_dir):
        with open(os.path.join(img_dir, filename), 'rb') as f:
            params = OrderedDict([
            ('api_key', (None, 'JQdjDsnHtJATSOlfIg9hYMNBb72D3CGU')),
            ('api_secret', (None, '0nQJIRWPxYFPeq6xfZnwj1zSAI58deiG')),
            ('image_file', (filename, f)),
            ('return_landmark', (None, '2'))
            ])

            response = requests.post('https://api-cn.faceplusplus.com/facepp/v3/detect', files=params)
            with open(os.path.join(feature_dir, os.path.splitext(filename)[0] + '.txt'), 'w') as f:
                f.write(response.content)
