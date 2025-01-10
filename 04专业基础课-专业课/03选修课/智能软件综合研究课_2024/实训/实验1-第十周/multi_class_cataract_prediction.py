import os
import numpy as np
import pandas as pd
import cv2
import random
from tqdm import tqdm
import matplotlib.pyplot as plt
from sklearn.model_selection import train_test_split
from sklearn.utils.class_weight import compute_class_weight
from sklearn.metrics import confusion_matrix, classification_report, accuracy_score
from tensorflow.keras.preprocessing.image import ImageDataGenerator
from tensorflow.keras.applications.vgg19 import VGG19
from tensorflow.keras.models import Model
from tensorflow.keras.layers import Dense, GlobalAveragePooling2D
from tensorflow.keras.optimizers import Adam
from tensorflow.keras.callbacks import ReduceLROnPlateau, EarlyStopping
import seaborn as sns
from mlxtend.plotting import plot_confusion_matrix

# Set global parameters
image_size = 224
batch_size = 32
num_classes = 8
epochs = 50
data_dir = "archive/preprocessed_images/"  # Adjust as needed

# Load dataset
df = pd.read_csv("archive/full_df.csv")

# Function to extract labels for multi-class classification
def extract_labels(row):
    if row["C"] == 1:
        return 3  # Cataract
    elif row["N"] == 1:
        return 0  # Normal
    elif row["D"] == 1:
        return 1  # Diabetes
    elif row["G"] == 1:
        return 2  # Glaucoma
    elif row["A"] == 1:
        return 4  # Age-related Macular Degeneration
    elif row["H"] == 1:
        return 5  # Hypertension
    elif row["M"] == 1:
        return 6  # Myopia
    else:
        return 7  # Other diseases/abnormalities

df["label"] = df.apply(extract_labels, axis=1)

# Prepare image dataset
dataset = []

def create_dataset(image_ids, label):
    for img_id in tqdm(image_ids, desc=f"Processing label {label}"):
        image_path = os.path.join(data_dir, img_id)
        try:
            image = cv2.imread(image_path, cv2.IMREAD_COLOR)
            image = cv2.resize(image, (image_size, image_size))
            dataset.append([image, label])
        except:
            continue

# Process each class
for class_label in range(num_classes):
    image_ids = df[df["label"] == class_label]["Left-Fundus"].values
    create_dataset(image_ids, class_label)

# Shuffle dataset
random.shuffle(dataset)

# Split dataset into features and labels
x = np.array([item[0] for item in dataset]).reshape(-1, image_size, image_size, 3)
y = np.array([item[1] for item in dataset])

# Train-test split
x_train, x_test, y_train, y_test = train_test_split(x, y, test_size=0.2, random_state=42)

# Normalize data and one-hot encode labels
x_train = x_train / 255.0
x_test = x_test / 255.0
y_train = pd.get_dummies(y_train).values
y_test = pd.get_dummies(y_test).values

# Data augmentation
datagen = ImageDataGenerator(
    rotation_range=10,
    zoom_range=0.1,
    width_shift_range=0.1,
    height_shift_range=0.1,
    fill_mode="nearest"
)
datagen.fit(x_train)

# Compute class weights
y_train_orig = np.argmax(y_train, axis=1)
class_weights = compute_class_weight("balanced", classes=np.unique(y_train_orig), y=y_train_orig)
class_weights = dict(enumerate(class_weights))

# Model creation
base_model = VGG19(weights="imagenet", include_top=False, input_shape=(image_size, image_size, 3))
x = base_model.output
x = GlobalAveragePooling2D()(x)
x = Dense(256, activation="relu")(x)
predictions = Dense(num_classes, activation="softmax")(x)
model = Model(inputs=base_model.input, outputs=predictions)

# Freeze VGG19 layers and compile model
for layer in base_model.layers[:15]:
    layer.trainable = False
for layer in base_model.layers[15:]:
    layer.trainable = True

model.compile(optimizer=Adam(learning_rate=1e-4), loss="categorical_crossentropy", metrics=["accuracy"])

# Callbacks
reduce_lr = ReduceLROnPlateau(monitor="val_loss", factor=0.2, patience=5, min_lr=1e-5)
early_stop = EarlyStopping(monitor="val_loss", patience=5, restore_best_weights=True)

# Train model
history = model.fit(
    datagen.flow(x_train, y_train, batch_size=batch_size),
    validation_data=(x_test, y_test),
    epochs=epochs,
    callbacks=[reduce_lr, early_stop],
    class_weight=class_weights
)

# Evaluate model
loss, accuracy = model.evaluate(x_test, y_test)
print(f"Test Loss: {loss:.4f}, Test Accuracy: {accuracy:.4f}")

# Predictions and evaluation metrics
y_pred_prob = model.predict(x_test)
y_pred = np.argmax(y_pred_prob, axis=1)
y_test_orig = np.argmax(y_test, axis=1)

print("Classification Report:\n", classification_report(y_test_orig, y_pred))
cm = confusion_matrix(y_test_orig, y_pred)
sns.heatmap(cm, annot=True, fmt="d", cmap="Blues", xticklabels=range(num_classes), yticklabels=range(num_classes))
plt.ylabel("True Label")
plt.xlabel("Predicted Label")
plt.title("Confusion Matrix")
plt.show()

# Learning curves
plt.figure(figsize=(12, 6))
epochs_range = range(1, len(history.history["accuracy"]) + 1)

plt.subplot(1, 2, 1)
plt.plot(epochs_range, history.history["accuracy"], "go-", label="Train Accuracy")
plt.plot(epochs_range, history.history["val_accuracy"], "ro-", label="Val Accuracy")
plt.title("Model Accuracy")
plt.xlabel("Epochs")
plt.ylabel("Accuracy")
plt.legend()

plt.subplot(1, 2, 2)
plt.plot(epochs_range, history.history["loss"], "go-", label="Train Loss")
plt.plot(epochs_range, history.history["val_loss"], "ro-", label="Val Loss")
plt.title("Model Loss")
plt.xlabel("Epochs")
plt.ylabel("Loss")
plt.legend()

plt.tight_layout()
plt.show()
