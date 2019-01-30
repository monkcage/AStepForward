#!/usr/bin/env python3.6
"""
LSTM
"""

from numpy import array
from keras.models import Sequential
from keras.layers import LSTM
from keras.layers import Dense

x = array([[10, 20, 30], [20, 30, 40], [30, 40, 50], [40, 50, 60]])
y = array([40, 50, 60, 70])

x = x.reshape((x.shape[0], x.shape[1], 1))

model.Sequential()
model.add(LSTM(50, activation='relu', input_shape=(3, 1)))
model.add(Dense(1))
model.compile(optimizer='adam', loss='mse')

model.fit(x, y, epochs=1000, verbose=0)
x_input = array([50, 60, 70])
x_input = x_input.reshape((1, 3, 1))

pre = model.predict(x_input, verbose=0)
print(pre)
