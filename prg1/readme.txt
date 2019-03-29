This is a game about beacons.
The basic structure of one beacon is with properties: id, coordinates, color(x,y), brightness, name, master and vassal.
Because the relation between the beacons are quite simple, I do not choose any nonlinear structure or other complicated structure to store or search them.
If two beacons are connected with lightbeam, the source beacon's vassal will be the targetid and verse visa.
Basic operations of the beacons are: beacon_count, clear_beacons, all_beacons, find_beacons, add_beacon, remove_beacon, get_name, get_cordinates, get_color, sorting beacon ID with name alphebetically or brightness increasingly.
More detail information, for instances, minimum brightness and maximum brightness.
To change beacon's name or color can also be done easily. 
More advanced operations include add_lightbeam, get_lightsource, path_outbeam and path_inbeam_longest.
The complex of every function are also estimated and explained in the .hh file.
Please do as the instruction suggest on the GUI.