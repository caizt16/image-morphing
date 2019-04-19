import os, json

base_dir = os.path.dirname(os.getcwd())
feature_dir = os.path.join(base_dir, 'feature_point')
data_dir = os.path.join(base_dir, 'data')

with open(os.path.join(feature_dir, 'target2_unique.txt'), 'r') as f1:
    with open(os.path.join(feature_dir, 'source2.txt'), 'r') as f2:
        with open(os.path.join(data_dir, 'target2.txt'), 'w') as f3:
            data1 = [ x.split() for x in f1.readlines() ]
            data2 = json.loads(f2.read())
            cnt = 0
            cnt2 = 0
            for key in data2['faces'][0]['landmark'].keys():
                if key == "left_eye_pupil":
                    key = "left_eye_center"
                if key == "right_eye_pupil":
                    key = "right_eye_center"
                cnt += 1
                for data in data1:
                    if data[0] == key:
                        cnt2 += 1
                        f3.write('%s %s\n' % (data[2], data[1]))
            print cnt, cnt2
