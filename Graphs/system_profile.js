'use strict';

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
    title.html(this.options.name);
    profile.append(title);

    var graphs_container = $("<div>");
    graphs_container.addClass("system_profile");

    // render graphs
    var common_options = {
      container: graphs_container,
      width: 500,
      from_date: this.time[0]*1000,
      to_date: this.time[this.time.length-1]*1000,
      show_ruler: false,
      mode: "mirror"
    };

    //console.log(this.total_cpu);

  //  console.log(new Date(this.time[0]*1000));

    this.total_cpu_graph = new Graph($.extend({}, common_options, {
      name: "CPU",
      min_value: 0,
      max_value: 100,
      data_function: _this._get_data_function(_this.time, _this.total_cpu),
      positive_color: "#74ff52"
    }));


    this.mem_graph = new Graph($.extend({}, common_options, {
      name: "MEM",
      min_value: this._get_array_min_value(this.mem),
      max_value: this._get_array_max_value(this.mem), // 1.369e11
      data_function: _this._get_data_function(_this.time, _this.mem),
      positive_color: "#ff9052"
    }));

    this.net_graph = new Graph($.extend({}, common_options, {
      name: "NET",
      min_value: this._get_array_min_value(this.net),
      max_value: this._get_array_max_value(this.net),
      data_function: _this._get_data_function(_this.time, _this.net),
      positive_color: "#52d0ff"
    }));

    this.disk_graph = new Graph($.extend({}, common_options, {
      name: "DISK",
      min_value: this._get_array_min_value(this.disk),
      max_value: this._get_array_max_value(this.disk),
      data_function: _this._get_data_function(_this.time, _this.disk),
      positive_color: "#ff52a0"
    }));

    //console.log(this._get_array_max_value(this.net));

    profile.append(graphs_container);
    container.append(profile);

    this.total_cpu_graph.render();
    this.mem_graph.render();
    this.net_graph.render();
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
              _this.net.push(row[_this.options.net_column_index]);

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
