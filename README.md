# ObjectRecognitionPaint

Draw on screen either some object or digit and predict it using 

Program that let you draw things on screen. Object can be recognized used trained model. Program consist of two parts. First is simple paint application that allow to use brush to draw things on screen with different colours. It can be either some object or digit. Digit classifier is trained on MNIST dataset. Object detection is made by using VGG16 model. Model made for object detection. After drawing things, screen is copied to image, then resized to fit input layer of either digit or object classifier. Results are then presented on console. Classification is made in python using keras library. Rest is made in c++.

Controls:

- Hold R Button - Clear screen
- P - Start digit classifier
- O - Start object classifier
- Mouse Left button - draw on screen
- Mouse Right button - clear screen with brush

Brush Settings: 

- '+' - Increase brush size
- '-' - Decrease brush size
- Num1 - Blue colour
- Num2 - Green colour
- Num3 - Red colour
- Num4 - Yellow colour
- Num5 - Magneta colour
- Num6 - White colour

Example digit recognition

![Oryginal](https://github.com/SlawoStr/ObjectDetectionPaint/blob/master/number.PNG)

Example Object recognition - jellyfish

![Oryginal](https://github.com/SlawoStr/ObjectDetectionPaint/blob/master/jellyfish.PNG)

Example Object recognition - matchstick

![Oryginal](https://github.com/SlawoStr/ObjectDetectionPaint/blob/master/matchstick.PNG)
