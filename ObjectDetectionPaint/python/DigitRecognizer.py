import cv2
import numpy as np
from keras.models import load_model
from keras.applications.vgg16 import VGG16
from keras.applications.vgg16 import preprocess_input
from keras.applications.vgg16 import decode_predictions
import tensorflow as tf

physical_devices = tf.config.list_physical_devices('GPU')
tf.config.experimental.set_memory_growth(physical_devices[0], True)

model = load_model("resources/test_model.h5")
model2 = VGG16()


def predictDigit():
    image = cv2.imread("Predict.jpg")
    img = cv2.cvtColor(image, cv2.COLOR_BGR2GRAY)
    resized = cv2.resize(img, (28, 28), interpolation=cv2.INTER_AREA)
    img = np.vstack(resized).reshape(-1, 28, 28, 1).astype('float32')
    img /= 255
    result = model.predict(img)
    return list(result.flatten())


def predictObject():
    image = cv2.imread("Predict.jpg")
    image = cv2.resize(image, (224, 224), interpolation=cv2.INTER_AREA)
    image = np.vstack(image).reshape(1, image.shape[0], image.shape[1], image.shape[2]).astype('float32')
    image = preprocess_input(image)
    yhat = model2.predict(image)
    label = decode_predictions(yhat, top=10)
    for x in label[0]:
        print('%s (%.2f%%)' % (x[1], x[2] * 100))
    return 1
