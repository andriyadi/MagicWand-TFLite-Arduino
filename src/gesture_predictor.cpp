/* Copyright 2019 The TensorFlow Authors. All Rights Reserved.

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
==============================================================================*/

#include "gesture_predictor.h"

#include "constants.h"
#include "Arduino.h"

// Set to 1 to display each inference results
#define DEBUG_INF_RES 1

String LABELS[3] = {"W", "O", "L"};

// How many times the most recent gesture has been matched in a row
int continuous_count = 0;
// The result of the last prediction
int last_predict = -1;

// Return the result of the last prediction
// 0: wing, 1: ring, 2: slope, 3: unknown
int PredictGesture(float* output) {
  // Find whichever output has a probability > 0.8 (they sum to 1)
  int this_predict = -1;
  for (int i = 0; i < 3; i++) {

#if DEBUG_INF_RES
    //Using percentage to visualize inference result
    //Serial.print(LABELS[i]); Serial.print(": "); Serial.print(output[i]*100); Serial.print("%,\t");

    //Using bar graph to visualize inference result
    Serial.print(LABELS[i]); Serial.print(": "); 
    int barNum = static_cast<int>(roundf(output[i]*10));
    for(int k = 0; k < barNum; k++) {
      Serial.print("█"); 
    }   
    for(int k=barNum-1; k < 10; k++) {
      Serial.print(" "); 
    } 
    Serial.print("\t");
#endif

    if (output[i] > kMinInferenceThreshold) this_predict = i;
  }

  #if DEBUG_INF_RES
  Serial.println();
  Serial.println();
  #endif
  
  // No gesture was detected above the threshold
  if (this_predict == -1) {
    continuous_count = 0;
    last_predict = 3;
    return 3;
  }
  if (last_predict == this_predict) {
    continuous_count += 1;
  } else {
    continuous_count = 0;
  }
  last_predict = this_predict;
  // If we haven't yet had enough consecutive matches for this gesture,
  // report a negative result
  if (continuous_count < kConsecutiveInferenceThresholds[this_predict]) {
    return 3;
  }
  // Otherwise, we've seen a positive result, so clear all our variables
  // and report it
  continuous_count = 0;
  last_predict = -1;
  return this_predict;
}
