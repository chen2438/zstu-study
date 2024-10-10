import cv2
import dlib
from scipy.spatial import distance as dist
from imutils import face_utils

# 加载dlib的人脸检测器和形状预测器
detector = dlib.get_frontal_face_detector()
predictor = dlib.shape_predictor("shape_predictor_68_face_landmarks.dat")

# 定义闭眼阈值和帧计数
EYE_AR_THRESH = 0.15
EYE_AR_CONSEC_FRAMES = 15

# 初始化帧计数器和闭眼计数器
COUNTER = 0
TOTAL = 0


# 定义计算眼睛纵横比的函数
def eye_aspect_ratio(eye):
    # 计算两组垂直眼标志之间的欧氏距离
    A = dist.euclidean(eye[1], eye[5])
    B = dist.euclidean(eye[2], eye[4])

    # 计算水平眼标志之间的欧氏距离
    C = dist.euclidean(eye[0], eye[3])

    # 计算眼睛的纵横比
    ear = (A + B) / (2.0 * C)
    return ear


# 打开摄像头
cap = cv2.VideoCapture(0)

while True:
    # 读取视频流的帧
    ret, frame = cap.read()
    if not ret:
        break

    # 水平翻转图像
    frame = cv2.flip(frame, 1)

    # 调整帧的大小以加快处理速度
    frame = cv2.resize(frame, (960, 540))

    # 将帧转换为灰度图像 保持字体和识别框颜色
    gray = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)
    frame = cv2.cvtColor(gray, cv2.COLOR_GRAY2BGR)

    # 检测灰度图像中的人脸
    faces = detector(gray)

    for face in faces:
        # 获取人脸的形状
        shape = predictor(gray, face)
        shape = face_utils.shape_to_np(shape)

        # 提取左眼和右眼的坐标
        left_eye = shape[42:48]
        right_eye = shape[36:42]

        # 计算左眼和右眼的纵横比
        left_ear = eye_aspect_ratio(left_eye)
        right_ear = eye_aspect_ratio(right_eye)

        # 计算双眼纵横比的平均值
        ear = (left_ear + right_ear) / 2.0

        # 绘制眼睛区域
        cv2.drawContours(frame, [cv2.convexHull(left_eye)], -1, (0, 255, 0), 1)
        cv2.drawContours(frame, [cv2.convexHull(right_eye)], -1, (0, 255, 0), 1)

        text = "Normal"
        # 检查纵横比是否低于阈值
        if ear < EYE_AR_THRESH:
            COUNTER += 1
            text = "Fatigue"
        else:
            # 纵横比高于阈值时，如果连续帧计数大于等于阈值，则疲劳驾驶计数加1
            if COUNTER >= EYE_AR_CONSEC_FRAMES:
                TOTAL += 1

            # 重置帧计数器
            COUNTER = 0

        # 显示疲劳驾驶状态
        cv2.putText(
            frame,
            "Fatigue Count: {}".format(TOTAL),
            (240, 30),
            cv2.FONT_HERSHEY_SIMPLEX,
            1,
            (0, 0, 255),
            2,
        )

        cv2.putText(
            frame,
            text,
            (240, 60),
            cv2.FONT_HERSHEY_SIMPLEX,
            1,
            (0, 0, 255),
            2,
        )

    # 显示视频帧
    cv2.imshow("Fatigue Detection", frame)
    key = cv2.waitKey(1) & 0xFF

    # q退出循环
    if key == ord("q"):
        break

# 清理资源
cap.release()
cv2.destroyAllWindows()
