'use strict';


var events = {
  30: "(1)", // Ubuntu and apt-get installations
  156: "(2)", // start Boost
  335: "(3)", // Pythia, HepMC and XercesC compilation
  428: "(4)", // start Geant4
  1700: "(5)", // downloading Geant4 Data
  1870: "(6)", // end Geant4, start Root
  2230: "(7)", // start Pluto
  2410: "(8)", // start Geant 3
  2620: "(9)" // start mpdroot

};

var ticks = Object.keys(events);
var labels = [];
for(var k in events){
  labels.push(events[k])
}

class SystemProfile {
  constructor (options) {
    var default_options = {
      first_data_row_index: 7,

      time_column_index: 134,
      total_cpu_column_index: 120,
      mem_column_index: 126,
      disk_column_index: 130,
      net_column_index: 132,

      cpus_columns: {
        start: 0,
        step: 6,
        count: 20
      },

      ready: function(){
        console.log("Profile ready");
      }
    };

    this.options = $.extend({}, default_options, options);

    if(!this._check_options()){
      return;
    }

    this._init();
  }

  _init(){
    var _this = this;
    console.log("SystemProfile initialization");
    this._parse_data(this.options.csv_file, function(){
      // all set and ready to render
      console.log("Ready to render");
      _this.options.ready();
    });
  }

  render(){
    var _this = this;
    if(this.time == undefined){
      console.error("cant render without time axis defined");
      return;
    }

    var container = this.options.container;

    var profile = $("<div>")
    profile.addClass("profile");


    // clear container
    profile.html("");

    // add title
    var title = $("<h2>");
    var start_time = _this.time[0];
    var end_time = _this.time[_this.time.length-1];
    var sec = end_time-start_time;
    var minutes = Math.floor(sec/60);
    var seconds = Math.floor(sec - minutes*60);
    title.html(this.options.name+" ("+minutes+":"+pad(seconds, 2)+") - "+Math.floor(sec)+"s");
    profile.append(title);

    var graphs_container = $("<div>");
    graphs_container.addClass("system_profile");

    // render graphs
    var common_options = {
      id_postfix: this.options.name,
      container: graphs_container,
      width: 500,
      from_date: this.time[0]*1000,
      to_date: this.time[this.time.length-1]*1000,
      show_ruler: false,
      mode: "mirror"
    };

    //console.log(this.total_cpu);

  //  console.log(new Date(this.time[0]*1000));

  var color_schemes = [
    {
      cpu: "#CD5334",
      net: "#30BCED",
      mem: "#574D68",
      disk: "#EDAE49"
    }, { // red blue gray purple
      cpu: "#CD5334",
      net: "#30BCED",
      mem: "#222222",
      disk: "#67597A"
    }, { // orange
      cpu: "#813405",
      net: "#D45113",
      mem: "#F9A03F",
      disk: "#F8DDA4"
    }, { // green
      cpu: "#16DB65",
      net: "#058C42",
      mem: "#04471C",
      disk: "#0D2818"
    }, { // good
      cpu: "#D66853",
      net: "#7D4E57",
      mem: "#364156",
      disk: "#212D40"
    }, {
      cpu: "#F55D3E",
      net: "#76BED0",
      mem: "#F7CB15",
      disk: "#878E88"
    }, { // good
      cpu: "#EA3546",
      net: "#33658A",
      mem: "#2F4858",
      disk: "#F6AE2D"
    }, {
      cpu: "#662E9B",
      net: "#43BCCD",
      mem: "#EA3546",
      disk: "#F86624"
    }, {
      cpu: "#1C110A",
      net: "#43AA8B",
      mem: "#E9B44C",
      disk: "#9B2915"
    }, {
      cpu: "#EF3E36",
      net: "#2E282A",
      mem: "#43AA8B",
      disk: "#EDB88B"
    }, {
      cpu: "#061826",
      net: "#0471A6",
      mem: "#43AA8B",
      disk: "#89AAE6"
    }, {
      cpu: "#43AA8B",
      net: "#254441",
      mem: "#FF6F59",
      disk: "#EF3054"
    }, {
      cpu: "#FAFF00",
      net: "#02A9EA",
      mem: "#FF01FB",
      disk: "#000300"
    }, {
      cpu: "#2C2A4A",
      net: "#7FDEFF",
      mem: "#4F518C",
      disk: "#907AD6"
    }
  ];

    this.total_cpu_graph = new Graph($.extend({}, common_options, {
      name: "CPU",
      min_value: 0,
      max_value: 100,
      data_function: _this._get_data_function(_this.time, _this.total_cpu),
      positive_color: color_schemes[0].cpu,
      show_ruler: true,
      padding_top: 50,
      ticks_format_y: function(d){
        return d+"%";
      },
      x_ticks_values: ticks_values(),
      ticks_format_x: label
    }));

    function label(d){
      var start_time = _this.time[0];
      var sec = d/1000 - start_time;

      return label_for_tick(sec);
    }


    function label_for_tick(sec){
      console.log(sec);
      console.log(ticks.indexOf(sec.toString()));
      var minutes = Math.floor(sec/60);
      var seconds = Math.floor(sec - minutes*60);
      var add = "";
      var tick_num = ticks.indexOf(sec.toString())+1;
      if(tick_num == 2 ||tick_num == 4 || tick_num == 6|| tick_num == 9){
        add = (minutes>0?minutes:"")+":"+pad(seconds, 2)+" ";
      }
      return add+labels[ticks.indexOf(sec.toString())];
    }

    function ticks_values(){
      var start_time = _this.time[0];
      var new_ticks = []
      for(var k in ticks){
        new_ticks[k] = (parseInt(ticks[k])+start_time)*1000;
      }
      console.log(new_ticks);
      return new_ticks;
    }

    this.net_graph = new Graph($.extend({}, common_options, {
      name: "NET",
      min_value: this._get_array_min_value(this.net),
      max_value: this._get_array_max_value(this.net),
      data_function: _this._get_data_function(_this.time, _this.net),
      positive_color: color_schemes[0].net,
      ticks_format_y: function(d){
        return (Math.round( d/1000000*10 ) / 10)+" MB/s";
      }
    }));

    this.mem_graph = new Graph($.extend({}, common_options, {
      name: "MEM",
      min_value: this._get_array_min_value(this.mem),
      max_value: this._get_array_max_value(this.mem), // */1.369e11*0.2,
      data_function: _this._get_data_function(_this.time, _this.mem),
      positive_color: color_schemes[0].mem,
      ticks_format_y: function(d){
        return (Math.round( d/1e9 * 10 ) / 10)+"GB";
      }
    }));



    this.disk_graph = new Graph($.extend({}, common_options, {
      name: "DISK",
      min_value: this._get_array_min_value(this.disk),
      max_value: this._get_array_max_value(this.disk),
      data_function: _this._get_data_function(_this.time, _this.disk),
      positive_color: color_schemes[0].disk,
      ticks_format_y: function(d){
        return (Math.round( d/1000000*10 ) / 10)+" MB/s";
      }
    }));

    //console.log(this._get_array_max_value(this.net));

    profile.append(graphs_container);
    container.append(profile);

    this.total_cpu_graph.render();
    this.net_graph.render();
    this.mem_graph.render();
    this.disk_graph.render();
  }

  _get_array_max_value(array){
    var max = array[0];
    for(var k in array){
      if(array[k] > max && array[k] < 1e12) // fix for enormous peaks at NET graphics
        max = array[k];
    }
    return max;
  }

  _get_array_min_value(array){
    //return 0;
    var min = array[0];
    for(var k in array){
      if(array[k] < min)
        min = array[k];
    }
    return min;
  }

  _get_data_function (time_array, data_array){
    return function(start, stop, step, callback){
      start = +start; stop = +stop;


      var current_data_index = 0;
      var values = [];
      var prev_valid_value = 0;

      while(start < stop){
        while(start > time_array[current_data_index]*1000){
          current_data_index++;
        }
        var current_time = time_array[current_data_index];
        var current_val = data_array[current_data_index];
        if(current_val > 1e12){
          current_val = prev_valid_value;
        }else{
          prev_valid_value = current_val;
        }
        values.push(current_val);
      //  console.log(current_time);
        start += step;
      }
      callback(null, values);
    }
  }

  _parse_data(csv_filepath, callback){
    var _this = this;

    $.get(csv_filepath, function(data){
      Papa.parse(data, {
        dynamicTyping: true,
        complete: function(res){
          //console.log(res);

          var rows = res.data;

          _this.time = [];
          _this.total_cpu = [];
          _this.cpus = [];
          _this.mem = [];
          _this.disk = [];
          _this.net = [];

          for(var row_i in rows){
            row_i = parseInt(row_i);
            var row = rows[row_i];
            if(row[_this.options.time_column_index] == undefined){
                continue;
            }

            if(row_i >= _this.options.first_data_row_index){
              _this.time.push(row[_this.options.time_column_index]);
              _this.total_cpu.push(row[_this.options.total_cpu_column_index]);
              _this.mem.push(row[_this.options.mem_column_index]);
              _this.disk.push(row[_this.options.disk_column_index]
                              + row[_this.options.disk_column_index+1]);
              _this.net.push(row[_this.options.net_column_index]
                              + row[_this.options.net_column_index+1]);

              var cpu_i = 0;
              for(var i = _this.options.cpus_columns.start;
                 cpu_i < _this.options.cpus_columns.count;
                 i += _this.options.cpus_columns.step)
              {
                if(_this.cpus[cpu_i] == undefined){
                  _this.cpus[cpu_i] = [];
                }

                _this.cpus[cpu_i].push(row[i]);
                cpu_i++;
              }
            }
          }

          callback();

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
