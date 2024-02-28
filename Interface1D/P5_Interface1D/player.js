
// This holds some player information, like color and position.
// It also has some player methods for managing how a player moves.


class Player {
    //put levels here

    constructor(_num, _level, _displaySize) {
        //this.colordict = _colordict;
        let p0leveldict={
            0:[10,10,3,10,10],
            1:[10,2,3,2,10],
            2:[0,1,2,3,0],
            3:[0,0,0,0,0],
            4:[6,1,1,6,6],
            5:[1,0,0,0,1],
            6:[1,1,1,1,1],
            7:[1,1,1,1,0],
            8:[0,2,3,2,0],
            9:[1,1,1,1,0],
            10:[3,3,0,0,0],
            11:[1,1,1,0,0],
        }

        let p1leveldict={
            0:[10,10,0,10,10],
            1:[10,1,0,1,10],
            2:[3,2,3,2,1],
            3:[0,0,5,0,0],
            4:[0,0,5,5,5],
            5:[2,0,0,0,0],
            6:[0,0,0,0,0],
            7:[1,1,2,1,1],
            8:[1,2,3,2,1],
            9:[1,1,2,1,1],
            10:[1,1,0,0,0],
            11:[1,0,1,1,0],
        }

        let p0actdict = {
            0:['x','x','a','x','x'],
            1:['x','a','a','a','x'],
            2:['a','a','a','a','a'],
            3:['x','x','a','x','x'],
            4:['a','a','a','a1','a1'],
            5:['d','a','a','a','a'],
            6:['e','e','e','e','e'],
            7:['d','d','d','d','a'],
            8:['d','d','d','d','a'],
            9:['d','d','d','d','e'],
            10:['f','f','f','a','a'],
            11:['f','f','f','e','a2'],
        }
        
        let p1actdict = {
            0:['x','x','a','x','x'],
            1:['x','a','a','a','x'],
            2:['a','a','a','a','a'],
            3:['x','x','a1','x','x'],
            4:['a','a','a1','a1','a1'],
            5:['d','a','a','a','a'],
            6:['e','e','e','e','e'],
            7:['d','d','d','d','a'],
            8:['d','d','d','d','a'],
            9:['d','d','d','d','e'],
            10:['f','f','f','a','a'],
            11:['f','f','f','e','a2'],
        }

        let leveldict={
            0: p0leveldict,
            1: p1leveldict,
        }

        let actdict={
            0: p0actdict,
            1: p1actdict,
        }

        this.levelcount=Object.keys(p0leveldict).length;
        this.level=_level;
        this.num=_num;
        this.arr = Array.from(leveldict[_num][_level]);
        this.act = Array.from(actdict[_num][_level]);
        this.displaySize = _displaySize;
        this.leveldict=leveldict;
        this.actdict=actdict;
        this.oldarr=[0,0,0,0,0];
    }

    levelup(){
        this.level=(this.level+1)%this.levelcount;
        this.arr = Array.from(this.leveldict[this.num][this.level]);
        this.act = Array.from(this.actdict[this.num][this.level]);
    }
    resetlevel(){
        this.arr = Array.from(this.leveldict[this.num][this.level]);
    }
    restart(){
        this.level=0;
        this.arr = Array.from(this.leveldict[this.num][this.level]);
        this.act = Array.from(this.actdict[this.num][this.level]);
    }
  }