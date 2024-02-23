// This is used to aggregrate visual information from all objects before we display them. 
// First we populate display and then we show it to user.
// This is particularly helpful once you start outputting your game to an LED strip, of if you want to have two separate 'screens'


class Display {

    constructor(_displaySize, _pixelSize) {
  
      this.displaySize = _displaySize;
      this.pixelSize = _pixelSize;
      this.initColor = color(0, 0, 0);      // black color
      this.displayBuffer = [];
      
      this.colorDict={
        0: color(0, 255, 0),     // Green
        1: color(255, 0, 0),     // Red        
        2: color(0, 0, 255),     // Blue
        3: color(255, 255, 0),   // Yellow
        4: color(128,0,128),  //Purp
        5: color(255,165,0),  //orange
        6: color(255, 192, 203),  //pink
        7: color(165, 42, 42),  //brown
        8: color(0, 255, 255),  //cyan
        9: color(255, 0, 255),  //magenta
        10: color(0,0,0), //black
        // Add more color mappings as needed
      };

      // Assign black to all pixels. Black = off
      for(let i = 0; i < 5; i++){
        this.displayBuffer[i] = this.initColor;
      }
      for(let i = 10; i < 15; i++){
        this.displayBuffer[i] = this.initColor;
      }
  
    }
  
     // Color a specific pixel in the buffer
    setPixeld(  _index, _colorindex) {
        this.displayBuffer[_index]  = this.colorDict[_colorindex];
    }

    setPixel(  _index, _colorindex) {
      this.displayBuffer[_index]  = _colorindex;
   }
  

    // Color all pixels in the buffer
    setAllPixels( _color) {
      
      for(let i = 0; i < displaySize; i++) { 
        display.setPixel(i, _color); 
      }
    }


    // Now write it to screen
    // This is the only function in the entire software that writes something directly to the screen. I recommend you keep it this way.
    show() {
      for (let i =0; i< this.displaySize; i++) {
        //noStroke();
        fill(this.displayBuffer[i]);
        rect(i*this.pixelSize,0,this.pixelSize,this.pixelSize);
      }
    }


    
    // Let's empty the display before we start adding things to it again
    clear() {

        for(let i = 0; i < this.displaySize; i++) {    
        this.displayBuffer[i] = this.initColor; 
        }
    }
    

  }