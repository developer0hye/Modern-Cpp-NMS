import numpy as np
import cv2
from plotbbox import plotBBox

def draw_bboxes(img, bboxes, classes_table, color_table):
    h, w = img.shape[:2]
    for box in bboxes:
        xmin, ymin, xmax, ymax = box[:4]
        xmin *= w
        xmax *= w
        ymin *= h
        ymax *= h

        confidence = box[4]
        class_idx = int(box[5])

        plotBBox(img, 
                int(xmin), int(ymin), int(xmax), int(ymax), 
                color=color_table[class_idx], thickness=2, 
                label=classes_table[class_idx]+f"{confidence:.3f}", font_scale=40) # plot bounding box on img
    return img

# coco classes table
classes_table = {0: "person",
  1: "bicycle",
  2: "car",
  3: "motorcycle",
  4: "airplane",
  5: "bus",
  6: "train",
  7: "truck",
  8: "boat",
  9: "traffic light",
  10: "fire hydrant",
  11: "stop sign",
  12: "parking meter",
  13: "bench",
  14: "bird",
  15: "cat",
  16: "dog",
  17: "horse",
  18: "sheep",
  19: "cow",
  20: "elephant",
  21: "bear",
  22: "zebra",
  23: "giraffe",
  24: "backpack",
  25: "umbrella",
  26: "handbag",
  27: "tie",
  28: "suitcase",
  29: "frisbee",
  30: "skis",
  31: "snowboard",
  32: "sports ball",
  33: "kite",
  34: "baseball bat",
  35: "baseball glove",
  36: "skateboard",
  37: "surfboard",
  38: "tennis racket",
  39: "bottle",
  40: "wine glass",
  41: "cup",
  42: "fork",
  43: "knife",
  44: "spoon",
  45: "bowl",
  46: "banana",
  47: "apple",
  48: "sandwich",
  49: "orange",
  50: "broccoli",
  51: "carrot",
  52: "hot dog",
  53: "pizza",
  54: "donut",
  55: "cake",
  56: "chair",
  57: "couch",
  58: "potted plant",
  59: "bed",
  60: "dining table",
  61: "toilet",
  62: "tv",
  63: "laptop",
  64: "mouse",
  65: "remote",
  66: "keyboard",
  67: "cell phone",
  68: "microwave",
  69: "oven",
  70: "toaster",
  71: "sink",
  72: "refrigerator",
  73: "book",
  74: "clock",
  75: "vase",
  76: "scissors",
  77: "teddy bear",
  78: "hair drier",
  79: "toothbrush"}

color_table = {}
for cls in classes_table:
    color_table[cls] = (np.random.randint(100, 255), np.random.randint(100, 255), np.random.randint(100, 255))

img = cv2.imread('img.jpg', cv2.IMREAD_COLOR)
h, w = img.shape[:2]

boxes = np.loadtxt('boxes.txt', delimiter=' ')
boxes_nms = np.loadtxt('boxes_nms.txt', delimiter=' ')

img_with_boxes = draw_bboxes(img.copy(), boxes, classes_table, color_table)
img_with_boxes_nms = draw_bboxes(img.copy(), boxes_nms, classes_table, color_table)

cv2.imwrite('img_with_boxes.jpg', img_with_boxes)
cv2.imwrite('img_with_boxes_nms.jpg', img_with_boxes_nms)