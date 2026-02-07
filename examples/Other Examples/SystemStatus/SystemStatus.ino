/*********************************************************************************
 *  MIT License
 *  
 *  Copyright (c) 2020-2025 Gregg E. Berman
 *  
 *  https://github.com/HomeSpan/HomeSpan
 *  
 *  Permission is hereby granted, free of charge, to any person obtaining a copy
 *  of this software and associated documentation files (the "Software"), to deal
 *  in the Software without restriction, including without limitation the rights
 *  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 *  copies of the Software, and to permit persons to whom the Software is
 *  furnished to do so, subject to the following conditions:
 *  
 *  The above copyright notice and this permission notice shall be included in all
 *  copies or substantial portions of the Software.
 *  
 *  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 *  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 *  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 *  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 *  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 *  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 *  SOFTWARE.
 *  
 ********************************************************************************/

// This sketch demonstrates how to programmatically retrieve system status information:
//  - Heap memory
//  - Number of active socket connections
//  - Stack space high water marks
//
// This example uses the Utils::getSystemStatus() function to get the data
// that is normally displayed by the HomeSpan CLI 's' and 'm' commands.
//

#include "HomeSpan.h"

void setup() {
  
  Serial.begin(115200);

  // Initialize HomeSpan
  homeSpan.begin(Category::Lighting, "SystemStatus Demo");

  // Create a simple accessory with a lightbulb
  new SpanAccessory();
    new Service::AccessoryInformation();
      new Characteristic::Identify();
    
    new Service::LightBulb();
      new Characteristic::On();

}

void loop() {
  
  homeSpan.poll();
  
  // Every 10 seconds, retrieve and display system status
  static unsigned long lastCheck = 0;
  if(millis() - lastCheck > 10000) {
    lastCheck = millis();
    
    // Get system status
    Utils::ResourceMonitor status = Utils::getSystemStatus();
    
    Serial.println("\n*** System Status ***");
    Serial.println();
    Serial.println("Heap Memory:");
    Serial.printf("  Internal: %9u allocated, %9u free, %9u largest, %9u low\n",
      status.heapInternal.allocated, status.heapInternal.free, 
      status.heapInternal.largestBlock, status.heapInternal.minFree);
    Serial.printf("  PSRAM:    %9u allocated, %9u free, %9u largest, %9u low\n",
      status.heapPSRAM.allocated, status.heapPSRAM.free, 
      status.heapPSRAM.largestBlock, status.heapPSRAM.minFree);
    Serial.println();
    Serial.printf("Active Socket Connections: %d\n", status.activeConnections);
    Serial.printf("AutoPoll Task Available Stack (-1 if not used): %d bytes\n", status.pollTaskStack);
    Serial.printf("Loop Task Available Stack: %d bytes\n", status.loopTaskStack);
    Serial.println("*********************\n");
  }

}

