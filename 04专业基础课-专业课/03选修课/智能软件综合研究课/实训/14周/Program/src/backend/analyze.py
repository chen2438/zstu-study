from flask_socketio import SocketIO, emit
import cv2
import dlib
import numpy as np
from scipy.spatial import distance as dist
from imutils import face_utils
import base64

socketio = SocketIO()

# 加载dlib的人脸检测器和形状预测器
detector = dlib.get_frontal_face_detector()
predictor = dlib.shape_predictor("src/backend/shape_predictor_68_face_landmarks.dat")
# predictor = dlib.shape_predictor("./shape_predictor_68_face_landmarks.dat")

# 定义闭眼阈值和帧计数
EYE_AR_THRESH = 0.15
EYE_AR_CONSEC_FRAMES = 5

# 定义打哈欠阈值和帧计数
MOUTH_AR_THRESH = 0.6
MOUTH_AR_CONSEC_FRAMES = 5


def eye_aspect_ratio(eye):
    # 计算两组垂直眼标志之间的欧氏距离
    A = dist.euclidean(eye[1], eye[5])
    B = dist.euclidean(eye[2], eye[4])

    # 计算水平眼标志之间的欧氏距离
    C = dist.euclidean(eye[0], eye[3])

    # 计算眼睛的纵横比
    ear = (A + B) / (2.0 * C)
    return ear


def mouth_aspect_ratio(mouth):
    # 计算嘴巴的纵横比
    A = dist.euclidean(mouth[2], mouth[10])  # 51, 59
    B = dist.euclidean(mouth[4], mouth[8])  # 53, 57
    C = dist.euclidean(mouth[0], mouth[6])  # 49, 55
    mar = (A + B) / (2.0 * C)
    return mar


# 初始化帧计数器和闭眼、打哈欠计数器
# EYE_COUNTER = 0
# MOUTH_COUNTER = 0
# EYE_TOTAL = 0
# MOUTH_TOTAL = 0
USERS = {}


@socketio.on("frame", namespace="/ws")
def handle_frame(data):
    user_id = data["userId"]
    # 确保每个用户的数据独立
    if user_id not in USERS:
        USERS[user_id] = {
            "EYE_COUNTER": 0,
            "MOUTH_COUNTER": 0,
            "EYE_TOTAL": 0,
            "MOUTH_TOTAL": 0,
        }

    # 使用用户特定的计数器
    EYE_COUNTER = USERS[user_id]["EYE_COUNTER"]
    MOUTH_COUNTER = USERS[user_id]["MOUTH_COUNTER"]
    EYE_TOTAL = USERS[user_id]["EYE_TOTAL"]
    MOUTH_TOTAL = USERS[user_id]["MOUTH_TOTAL"]
    # 解码图像
    img_data = base64.b64decode(data["image"])
    nparr = np.frombuffer(img_data, np.uint8)
    frame = cv2.imdecode(nparr, cv2.IMREAD_COLOR)

    # 水平翻转图像
    frame = cv2.flip(frame, 1)

    # 调整帧的大小以加快处理速度
    # frame = cv2.resize(frame, (800, 600))

    # 将帧转换为灰度图像
    gray = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)

    # 检测灰度图像中的人脸
    faces = detector(gray)

    # 假设状态为正常
    eye_text = "正常"
    mouth_text = "正常"

    for face in faces:
        # 绘制人脸识别框
        (x, y, w, h) = face_utils.rect_to_bb(face)
        cv2.rectangle(frame, (x, y), (x + w, y + h), (0, 255, 0), 2)

        # 获取人脸的形状
        shape = predictor(gray, face)
        shape = face_utils.shape_to_np(shape)

        # 绘制面部特征点
        for x, y in shape:
            cv2.circle(frame, (x, y), 1, (0, 0, 255), -1)

        # 提取左眼和右眼的坐标
        left_eye = shape[42:48]
        right_eye = shape[36:42]

        # 计算左眼和右眼的纵横比
        left_ear = eye_aspect_ratio(left_eye)
        right_ear = eye_aspect_ratio(right_eye)

        # 计算双眼纵横比的平均值
        ear = (left_ear + right_ear) / 2.0

        # 检查纵横比是否低于阈值
        if ear < EYE_AR_THRESH:
            EYE_COUNTER += 1
            eye_text = "眯眼"
        else:
            # 纵横比高于阈值时，如果连续帧计数大于等于阈值，则疲劳驾驶计数加1
            if EYE_COUNTER >= EYE_AR_CONSEC_FRAMES:
                EYE_TOTAL += 1

            # 重置帧计数器
            EYE_COUNTER = 0

        # 提取嘴巴的坐标
        mouth = shape[48:68]

        # 计算嘴巴的纵横比
        mar = mouth_aspect_ratio(mouth)

        # 检查嘴巴纵横比是否大于阈值，以检测打哈欠
        if mar > MOUTH_AR_THRESH:
            MOUTH_COUNTER += 1
            mouth_text = "打哈欠"
        else:
            # 纵横比高于阈值时，如果连续帧计数大于等于阈值，则疲劳驾驶计数加1
            if MOUTH_COUNTER >= MOUTH_AR_CONSEC_FRAMES:
                MOUTH_TOTAL += 1

            # 重置帧计数器
            MOUTH_COUNTER = 0

    # 将处理后的帧编码为JPEG，然后转换为Base64字符串
    _, buffer = cv2.imencode(".jpg", frame)
    response = base64.b64encode(buffer).decode("utf-8")

    # 更新用户特定的计数器
    USERS[user_id]["EYE_COUNTER"] = EYE_COUNTER
    USERS[user_id]["MOUTH_COUNTER"] = MOUTH_COUNTER
    USERS[user_id]["EYE_TOTAL"] = EYE_TOTAL
    USERS[user_id]["MOUTH_TOTAL"] = MOUTH_TOTAL
    # 发送响应到客户端
    emit(
        "response",
        {
            "data": response,
            "eye_count": EYE_TOTAL,
            "eye_text": eye_text,
            "mouth_count": MOUTH_TOTAL,
            "mouth_text": mouth_text,
        },
    )
