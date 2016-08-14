$(function(){

  var data_path = "experimental_data/20cores_azure";

  $.get("./experiments_config.json", function(data){
    // edit paths and names
    for(var k in data){
      var ex = data[k];
      ex.name = ex.path.replace(/.*\/([0-9A-Za-z_]*)\.csv/, "$1");
      ex.path = data_path+ex.path;
    }

    var ready_count = 0;

    // create sys profiles
    var system_profiles = [];
    for(var k in data){
      var ex = data[k];
      system_profiles.push(
        new SystemProfile({
          name: ex.name,
          csv_file: ex.path,
          container: $("#profiles_container"),
          ready: function(){
            ready_count++;
            if(ready_count == system_profiles.length){
              console.log("All ready");
              // render all
              for(var k in system_profiles){
                var profile = system_profiles[k];
                profile.render();
              }
            }
          }
        })
      );
    }




  });

});
