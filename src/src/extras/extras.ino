/*********************************************************************************
 *  MIT License
 *  
 *  Copyright (c) 2020-2024 Gregg E. Berman
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

#include "Pixel.h"

WS2801_LED *p1;
WS2801_LED *p2;

WS2801_LED::Color *red;
WS2801_LED::Color *blue;
WS2801_LED::Color *green;

void setup() {

  Serial.begin(115200);
  delay(2000);
  Serial.printf("\n\nReady %d %d\n",F14,F22);

  p1=new WS2801_LED(F14, F22);
  p2=new WS2801_LED(F27, F23);

  red=(WS2801_LED::Color *)heap_caps_calloc(25,sizeof(WS2801_LED::Color),MALLOC_CAP_DMA);   
  blue=(WS2801_LED::Color *)heap_caps_calloc(25,sizeof(WS2801_LED::Color),MALLOC_CAP_DMA);   
  green=(WS2801_LED::Color *)heap_caps_calloc(25,sizeof(WS2801_LED::Color),MALLOC_CAP_DMA);   
  for(int i=0;i<25;i++){
    red[i].RGB(255,0,0);
    blue[i].RGB(0,0,255);
    green[i].RGB(0,128,0);
  }
}

void loop() {
  p1->set(red,25);
  p2->set(green,25);
  delay(1000);
  p1->set(blue,25);
  p2->set(green,25);
  delay(1000);    
}
