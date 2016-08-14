'use strict';

class SystemProfile {
  constructor (options) {
    var default_options = {

    };

    this.options = $.extend({}, default_options, options);

    if(!this._check_options()){
      return;
    }

    this._init();
  }

  _init(){
    console.log("SystemProfile initialization");
    this._parse_data(this.options.csv_file, function(data){
      
    });
  }


  _parse_data(csv_filepath, callback){
    $.get(csv_filepath, function(data){
      Papa.parse(data, {
        dynamicTyping: true,
        complete: function(res){
          console.log(res);
        }
      });
    });
  }

  _check_options(){
    if(this.options.name == undefined || this.options.name == ""){
      console.error("SystemProfile must have a name");
      return false;
    }

    if(this.options.container == undefined || this.options.container.length < 1){
      console.error("SystemProfile must have container option");
      console.log("Container count = "+this.options.container.length);
      return false;
    }

    if(this.options.csv_file == undefined){
      console.error("SystemProfile must have csv_file option");
      return false;
    }
    return true;
  }
}
