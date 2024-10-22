import math

from flask_socketio import SocketIO, emit
from flask import Flask, jsonify, request
from flask_cors import CORS
import random
from datetime import datetime
import os

app = Flask(__name__)
CORS(app)

# analyze.py
from analyze import socketio

app.config["SECRET_KEY"] = "secret!"
socketio.init_app(app, cors_allowed_origins="*")

# db.py
from db import setup_db

basedir = os.path.abspath(os.path.dirname(__file__))
app.config["SQLALCHEMY_DATABASE_URI"] = f"sqlite:///{os.path.join(basedir, 'data.db')}"
setup_db(app)

cars = [
    {
        "carId": 1,
        "carState": 0,  # 0未启动，1启动
        "carPlates": "ABC123",
        "carStyle": "小型车",
        "userName": "张三",
        "userId": 1,
        "userPhone": "1234567890",
        "carTude": "120.1,30.2",
        "userAddress": "Address1",
    },
    {
        "carId": 2,
        "carState": 1,  # 0未启动，1启动
        "carPlates": "DEF123",
        "carStyle": "大型车",
        "userName": "李四",
        "userId": 2,
        "userPhone": "12322227890",
        "carTude": "120.2,30.3",
        "userAddress": "Address2",
    },
]
users = [
    {
        "userId": 1,
        "userName": "张三",
        "userPhone": "1234567890",
        "userTime": "2023-01-01",
        "userScore": 10,  # 司机驾驶分
        "userAddress": "Address1",
        "userAccount": "driver",
        "userPassword": "driver123456",
        "type": 1,  # 司机
    },
    {
        "userId": 2,
        "userName": "李四",
        "userPhone": "12322227890",
        "userTime": "2023-01-01",
        "userScore": 12,  # 司机驾驶分
        "userAddress": "Address2",
        "userAccount": "driver2",
        "userPassword": "driver123666",
        "type": 1,  # 司机
    },
    {
        "userId": 1,
        "userName": "交管中心",
        "userPhone": "1231117890",
        "userTime": "2013-11-11",
        "userScore": 12,  # 初始化驾驶分数都是12，虽然对管理员没用
        "userAddress": "Address0",
        "userAccount": "admin",
        "userPassword": "admin123456",
        "type": 0,  # 管理员
    }
    # ... 其他用户数据
]
# 疲劳的表中userName和carPlates需要将tired表和cars表通过userId连接得到
tired = [
    {
        "userId": 1,
        "userName": "张三",
        "carPlates": "ABC123",
        "tiredSituation": "眯眼3次，打哈欠5次",
        "times": 2,
        "reminded": 38,
        "curtimes": "2023-12-16 18:18",
    },
    {
        "userId": 2,
        "userName": "李四",
        "carPlates": "DEF123",
        "tiredSituation": "眯眼10次，打哈欠20次",
        "times": 1,
        "reminded": 2,
        "curtimes": "2023-12-16 28:28",
    },
]
events = [
    {"eventTime": "2011-1-1 20:46", "event": "过度疲劳，被警示，扣2分", "userId": "1"},
    {"eventTime": "2022-2-2 20:46", "event": "过度疲劳，被警示，扣2分", "userId": "2"},
    {"eventTime": "2011-1-1 18:45", "event": "过度疲劳，被警示，扣2分", "userId": "1"},
    {"eventTime": "2022-2-2 18:45", "event": "过度疲劳，被警示，扣2分", "userId": "2"},
]


@app.route("/Account/AccountLogin", methods=["POST"])
def account_login():
    # 从请求中提取管理员用户名和密码
    name = request.json.get("Name")
    pwd = request.json.get("Pwd")
    print(f"{name}, {pwd}")
    # 遍历登录信息列表，检查用户名和密码是否匹配
    for login in users:
        if login["userAccount"] == name and login["userPassword"] == pwd:
            carPlates = (
                [
                    car["carPlates"]
                    for car in cars
                    if car["userId"] == login["userId"] and login["type"] == 1
                ],
            )
            # 登录成功，返回对应的用户类型
            response = {
                "code": 20000,
                "message": "登录成功",
                "data": {
                    "token": "fake-jwt-token-for-demo",  # 示例用的假JWT令牌
                    "type": login["type"],  # 返回用户类型
                    "sessionid": login["userId"],
                    "userName": login["userName"],
                    "userAccount": login["userAccount"],
                    "carPlates": carPlates[0],
                },
            }
            return jsonify(response)
        if login["userAccount"] == name and login["userPassword"] != pwd:
            # 密码不匹配
            response = {"code": 4002, "message": "管理员用户名对应密码错误"}
            return jsonify(response)
    # 管理员用户名不存在
    response = {"code": 4001, "message": "本管理员用户名不存在"}
    return jsonify(response)


# 注册
@app.route("/Account/AccountRegister", methods=["POST"])
def admin_register():
    data = request.get_json()
    print("data", data)
    name = data.get("admin")
    password = data.get("password")
    type = 1  # 这里新增用户默认是司机
    try:
        if name != "" and password != "":
            userId = len(users)  # 默认只有一个管理员
            new_user = {
                "userId": userId,
                "userName": "",
                "userPhone": "",
                "userTime": datetime.now().date().strftime("%Y-%-m-%-d"),
                "userScore": 12,
                "userAddress": "",
                "userAccount": name,
                "userPassword": password,
                "type": 1,
            }
            users.append(new_user)
            response = {
                "code": 20000,
                "message": "register success",
                "data": {
                    "token": "fake-jwt-token-for-demo",  # 示例用的假JWT令牌
                },
            }
            return jsonify(response)
    except Exception as e:
        print("register failed: ", e)
        response = {"code": 4001, "message": "register failed"}
        return jsonify(response)


@app.route("/Car/findCarCityAndCount", methods=["GET"])
def find_car_city_and_count():
    data = [{"carTude": "City1", "cityCount": 5}, {"carTude": "City2", "cityCount": 3}]
    return jsonify({"code": 20000, "data": {"carCityAndCount": data}})


@app.route("/Car/queryCarList", methods=["GET"])
def query_car_list():
    city = request.args.get("carTude")
    plates = request.args.get("carPlates")
    style = request.args.get("carStyle")
    filtered_car = cars
    if city:
        filtered_car = [item for item in filtered_car if item["carTude"] == city]
    if plates:
        filtered_car = [
            item for item in filtered_car if item["carPlates"].find(plates) != -1
        ]
    if style:
        filtered_car = [item for item in filtered_car if item["carStyle"] == style]
    print("filtered_car", filtered_car)
    return jsonify(
        {"code": 20000, "data": {"records": filtered_car, "total": len(cars)}}
    )


@app.route("/User/common/findUserList", methods=["GET"])
def find_user_list():
    # 添加分页和过滤逻辑
    return jsonify({"code": 20000, "data": {"records": users, "total": len(users)}})


@app.route("/Head/findUserTired", methods=["GET"])
def find_user_tired():
    # 添加分页和过滤逻辑
    return jsonify({"code": 20000, "data": {"UserAll": tired, "total": len(tired)}})


@app.route("/User/common/getUserById", methods=["GET"])
def get_user_by_id():
    user_id = request.args.get("userId")
    user = next((u for u in users if u["userId"] == int(user_id)), None)
    return jsonify({"code": 20000, "data": {"user": user}})


@app.route("/User/common/editUser", methods=["GET"])
def edit_user():
    userId = request.args.get("userId")
    userScore = request.args.get("userScore")
    reason = request.args.get("reason")
    eventTime = datetime.now().strftime("%Y-%m-%d %H:%M")
    event = {"eventTime": eventTime, "event": reason + userScore, "userId": userId}
    events.append(event)

    # emit("response", {"events": events})
    return jsonify({"code": 20000, "message": "用户信息更新成功"})


@app.route("/User/common/deleteUser", methods=["GET"])
def delete_user():
    global users  # 引入全局变量
    userId_to_delete = request.json.get("userId")
    # 使用列表推导式创建一个新的列表，仅保留 userId 不等于要删除的值的数据项
    users = [user for user in users if user["userId"] != userId_to_delete]
    return jsonify({"code": 20000, "message": "用户删除成功"})


@app.route("/User/common/findCarsAndUser", methods=["GET"])
def find_cars_and_user():
    data = {
        "startedCarNum": random.randint(1, 5),
        "stoppedCarNum": random.randint(1, 5),
        "userNum": len([user for user in users if user["type"] == 1]),
    }
    return jsonify({"code": 20000, "data": data})


@app.route("/User/common/warningAllTiredUser", methods=["POST"])
def warning_all_tired_user():
    # 生成警告信息
    for item in tired:
        item["reminded"] += 1
    # res=[{"flag":'all'}]
    # emit("response", {"flag": res})
    # emit("response", res)
    return jsonify({"code": 20000, "message": "所有疲劳驾驶用户已警告"})


@app.route("/User/common/warningtiredUserById", methods=["POST"])
def warning_tired_user_by_id():
    # 根据用户ID生成警告
    user_id = request.args.get("userId")
    for item in tired:
        if item["userId"] == user_id:
            item["reminded"] += 1
    # res = [{"flag":user_id}]
    # emit("response", {"flag": res})
    # emit("response", res)
    # 在这里只返回成功信息
    return jsonify({"code": 20000, "message": f"用户 {user_id} 已被警告"})


@app.route("/Car/findStoppedCars", methods=["GET"])
def find_stopped_cars():
    # 模拟未启动车辆数据
    stopped_cars = [car for car in cars if car["carState"] == 0]
    return jsonify({"code": 20000, "data": {"stoppedCarList": stopped_cars}})


def generate_random_coordinates():
    longitude = round(random.uniform(120.1, 120.2), 10)
    latitude = round(random.uniform(30.1, 30.2), 10)
    return f"{longitude},{latitude}"


@app.route("/Car/findStartedCars", methods=["GET"])
def find_started_cars():
    # 模拟已启动车辆数据
    # 如果要求实现实时更新与服务区距离，已启动车的坐标不能写死，每5000ms：前端通过该请求获取车辆坐标
    # 然后再每5000ms：当前司机车辆该坐标传参通过updateDist请求，计算服务区距离，返回数据
    started_cars = [car for car in cars if car["carState"] == 1]
    # 优化应该根据人脸识别存储的数据设置状态
    for car in started_cars:
        car["userNow"] = random.randint(0, 1)
    for car in started_cars:
        car["carTude"] = generate_random_coordinates()
    return jsonify({"code": 20000, "data": {"startedCarList": started_cars}})


@app.route("/User/userInfo", methods=["GET"])
def userInfo():
    target = int(request.args.get("userId"))
    print(target)
    res_user = [
        user for user in users if user["userId"] == target and user["type"] == 1
    ]
    return jsonify({"code": 20000, "res": res_user[0], "events": events})


@app.route("/User/updateuser", methods=["GET"])
def updateUser():
    temp_user = request.args.get("userId")
    return jsonify({"code": 20000, "message": "用户修改成功"})


@app.route("/User/updatevideo", methods=["GET"])
def updateVideo():
    status = request.args.get("status")
    temp = {}
    temp["userName"] = status["userName"]
    temp["carPlates"] = status["carPlates"]
    temp["tiredSituation"] = (status["situation"],)
    temp["times"] = (status["fatigue"],)
    temp["reminded"] = (status["reminded"],)
    temp["curtimes"] = (status["time"],)
    tired.append(temp)
    if temp:
        # emit("response", {"tired": tired})
        return jsonify({"code": 20000, "message": "视频数据更新成功"})
    else:
        return jsonify({"code": 4001, "message": "视频数据更新失败"})


@app.route("/Userhost/updatedist", methods=["GET"])
def updateDist():
    x = request.args.get("curlocat_x")
    y = request.args.get("curlocat_y")
    print(x, y)
    # 假设服务区地址["0","0"]
    serve = ["0", "0"]
    if x != None and y != None:
        dist = math.sqrt(
            (float(x) - float(serve[0])) ** 2 + (float(y) - float(serve[1])) ** 2
        )
        return jsonify({"code": 20000, "curdist": dist})
    else:
        return jsonify({"code": 20000, "curdist": "XXXXXX"})


from gevent import pywsgi


if __name__ == "__main__":
    # socketio.run(app, debug=True, port=8000)
    # socketio.run(app, debug=True, port=8000, allow_unsafe_werkzeug=True)
    server = pywsgi.WSGIServer(("0.0.0.0", 8000), app)
    server.serve_forever()
