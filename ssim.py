# Usage:
#
# python3 script.py --input original.png --output modified.png
# Based on: https://github.com/mostafaGwely/Structural-Similarity-Index-SSIM-

# Import the necessary packages
from skimage.measure import compare_ssim
import argparse
import imutils
import cv2

import os
from sklearn.metrics import mean_squared_error
from math import sqrt

# Incicate the path for the two folders
groundTruthPath = "metrics/eye/left/"
testPath = "metrics/eye/left/"

"""
The way to do the 1-to-1 comparison
"""
# Get the lists of the files
groundTruthList = os.listdir(groundTruthPath)
testList = os.listdir(testPath)

# A list to store the SSIM values and a list of perfect values
SSIM = []
perfectValue = [1] * len(testList)

# Start getting the SSIM values
for i in range(0, len(testList)):
    # Load the test input images
    imageB = cv2.imread(testPath + testList[i])
    # Retrieve the time of the test image
    numberB = []
    for word in range(0, len(testList[i])):
        if testList[0][word].isdigit():
            numberB.append(int(testList[0][word]))
    stringsB = [str(k) for k in numberB]
    bString = "".join(stringsB)
    bInt = int(bString)

    deltaT = 100000000.0
    gtImage = groundTruthList[0]
    # Find the proper file to compare from the ground-truth images
    for j in range(0, len(groundTruthList)):
        numberA = []
        for word in range(0, len(groundTruthList[i])):
            if groundTruthList[i][word].isdigit():
                numberA.append(int(groundTruthList[i][word]))
        stringsA = [str(k) for k in numberA]
        aString = "".join(stringsA)
        aInt = int(aString)

        if (abs(bInt - aInt) < deltaT):
            deltaT = abs(bInt - aInt)
            gtImage = groundTruthList[i]

    imageA = cv2.imread(groundTruthPath + gtImage)

    # For debugging purpose
    print(testList[i] + ' ' + gtImage + '\n')
    # print(groundTruthPath + gtImage + '\n')
    # print(testPath + testList[i] + '\n')

    # Convert the images to grayscale
    grayA = cv2.cvtColor(imageA, cv2.COLOR_BGR2GRAY)
    grayB = cv2.cvtColor(imageB, cv2.COLOR_BGR2GRAY)

    # Compute the Structural Similarity Index (SSIM) between the two
    # images, ensuring that the difference image is returned
    (score, diff) = compare_ssim(grayA, grayB, full=True)
    diff = (diff * 255).astype("uint8")

    # Append the results
    SSIM.append(score)

# Calculate the RMSE
mse = mean_squared_error(SSIM, perfectValue)
rmse = sqrt(mse)

# Print out the result
print("RMSE: {}".format(rmse))
