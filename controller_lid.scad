wall_width = 1.5;

//outer_x = 69;
inner_x = 67.4;

//outer_y = 129;
inner_y = 127.3;

//outer_z = 2;
inner_z = 2;

inner_frame_width = 5;

//vent_width = 1;

cut_cube_width = 1000;

module top_case(){
    cube([inner_x,inner_y,inner_z],center=true);
 
    translate([0, 0, inner_z / 2 + wall_width / 2]) {
        cube([inner_x + 2 * wall_width, inner_y + 2* wall_width, wall_width],true);
    }
}

module inner_frame_cut() {
    cube([inner_x - inner_frame_width, inner_y - inner_frame_width,inner_z],center=true);


}

module controller_lid() {
    difference() {
        top_case();
        inner_frame_cut();
    }
}

difference() {   
    controller_lid();
//    translate([0,-cut_cube_width/2,-cut_cube_width/2]) cube([cut_cube_width,cut_cube_width,cut_cube_width], center=false);
}
//module top_case(){
//cube([outer_x,outer_y,outer_z],true);
// 
//translate([0, 0, outer_z]) {
//      cube([inner_x,inner_y,inner_z],true);
// }
//
//
//}

//module vents(){
//    cube([outer_x * 0.6, vent_width, 2 * (outer_z + inner_z)],true);
//    for (i = [-4 : 2 : 4]){
//          translate([0,i]){
//        cube([outer_x * 0.6, vent_width, 2 * (outer_z + inner_z)],true);
//    }   
//    }
//
//}

//difference(){
//    top_case();
//    vents();
//}