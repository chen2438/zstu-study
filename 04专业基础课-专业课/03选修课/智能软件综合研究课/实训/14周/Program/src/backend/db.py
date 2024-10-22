# backend/db.py
from flask_sqlalchemy import SQLAlchemy

db = SQLAlchemy()


class Car(db.Model):
    id = db.Column(db.Integer, primary_key=True)
    plates = db.Column(db.String(80), unique=True, nullable=False)
    style = db.Column(db.String(80))
    city = db.Column(db.String(80))
    status = db.Column(db.String(80))


class User(db.Model):
    id = db.Column(db.Integer, primary_key=True)
    name = db.Column(db.String(80), nullable=False)
    phone = db.Column(db.String(20), unique=True, nullable=False)
    address = db.Column(db.String(120))
    city = db.Column(db.String(80))


class FatigueRecord(db.Model):
    id = db.Column(db.Integer, primary_key=True)
    user_id = db.Column(db.Integer, db.ForeignKey("user.id"), nullable=False)
    car_id = db.Column(db.Integer, db.ForeignKey("car.id"), nullable=False)
    record_time = db.Column(db.DateTime)
    duration = db.Column(db.Integer)


def init_and_populate_db():
    # 添加车辆数据
    car1 = Car(id=1, plates="ABC123", style="小型车", city="City1", status="Available")
    car2 = Car(id=2, plates="XYZ789", style="大型车", city="City2", status="Available")
    # ... 添加更多车辆

    # 添加用户数据
    user1 = User(name="User1", phone="1234567890", address="Address1", city="City1")
    # ... 添加更多用户

    db.session.add(car1)
    db.session.add(car2)
    db.session.add(user1)
    # ... 添加更多记录

    db.session.commit()


def setup_db(app):
    # app.config["SQLALCHEMY_DATABASE_URI"] = "sqlite:///data.db"
    db.init_app(app)
    with app.app_context():
        db.create_all()
        # init_and_populate_db()
