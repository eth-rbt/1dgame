
// This holds some player information, like color and position.
// It also has some player methods for managing how a player moves.


class Player {
    //put levels here

    constructor(_num, _level, _displaySize) {
        //this.colordict = _colordict;
        let p0leveldict={
            0:[0,0,3,0,0],
            1:[0,1,1,1,0],
            2:[0,0,0,0,0],
            3:[1,0,0,0,1],
            4:[1,1,1,1,1],
        }
        let p1leveldict={
            0:[0,0,1,0,0],
            1:[0,1,0,1,0],
            2:[0,0,5,0,0],
            3:[2,0,0,0,0],
            4:[0,0,0,0,0],
        }
        let leveldict={
            0: p0leveldict,
            1: p1leveldict,
        }

        let p0actdict = {
            0:['x','x','a','x','x'],
            1:['a','a','a','a','a'],
            2:['x','x','a','x','x'],
            3:['d','a','a','a','a'],
            4:['e','e','e','e','e'],
        }
        let p1actdict = {
            0:['x','x','a','x','x'],
            1:['a','a','a','a','a'],
            2:['x','x','a1','x','x'],
            3:['d','a','a','a','a'],
            4:['e','e','e','e','e'],
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