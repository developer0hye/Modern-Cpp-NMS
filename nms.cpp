#include "nms.hpp"
#include <algorithm>

float iou(const std::vector<float>& boxA, const std::vector<float>& boxB)
{
    // The format of box is [top_left_x, top_left_y, bottom_right_x, bottom_right_y]
    const float eps = 1e-6;
    float iou = 0.f;
    float areaA = (boxA[2] - boxA[0]) * (boxA[3] - boxA[1]);
    float areaB = (boxB[2] - boxB[0]) * (boxB[3] - boxB[1]);
    float x1 = std::max(boxA[0], boxB[0]);
    float y1 = std::max(boxA[1], boxB[1]);
    float x2 = std::min(boxA[2], boxB[2]);
    float y2 = std::min(boxA[3], boxB[3]);
    float w = std::max(0.f, x2 - x1);
    float h = std::max(0.f, y2 - y1);
    float inter = w * h;
    iou = inter / (areaA + areaB - inter + eps);
    return iou;
}

void nms(std::vector<std::vector<float>>& boxes, const float iou_threshold)
{
    // The format of boxes is [[top_left_x, top_left_y, bottom_right_x, bottom_right_y, score, class_id], ...]
    // Sorting "score + class_id" is to ensure that the boxes with the same class_id are grouped together and sorted by score
    std::sort(boxes.begin(), boxes.end(), [](const std::vector<float>& boxA, const std::vector<float>& boxB) { return boxA[4] + boxA[5] > boxB[4] + boxB[5];});
    for (int i = 0; i < boxes.size(); ++i)
    {
        if (boxes[i][4] == 0.f)
        {
            continue;
        }
        for (int j = i + 1; j < boxes.size(); ++j)
        {
            if (boxes[i][5] != boxes[j][5])
            {
                break;
            }
            if (iou(boxes[i], boxes[j]) > iou_threshold)
            {
                boxes[j][4] = 0.f;
            }
        }
    }
    std::erase_if(boxes, [](const std::vector<float>& box) { return box[4] == 0.f; });
}
