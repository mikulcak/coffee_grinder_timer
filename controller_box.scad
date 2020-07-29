switch_hole_diameter = 16;

cable_hole_diameter = 15;

overall_box_width = 25;

overall_box_height = 70;

overall_box_depth = 130;

box_wall_width = 2.5;

// offset the switch hole so that it is positioned in the 
// center of the box even with the lid on
switch_hole_offset = box_wall_width / 2;

screw_diameter = 4.5;

screw_column_height = 8;

screw_column_wall_width = 1.5;


module box() {
// cut away switch hole
difference(){
    
    // cut away inner part of main box
    difference() {
        // main box
        cube([overall_box_width,overall_box_depth,overall_box_height],true);

        // inner part
        translate([box_wall_width / 2, 0, 0]){
            cube([
                overall_box_width,
                overall_box_depth - box_wall_width,
                overall_box_height - box_wall_width
                ],
                true);
            }
        }
        
        // cylinder describing the switch hole
        translate([switch_hole_offset,overall_box_depth/2 * 0.7, overall_box_height / 2]) {
            cylinder(h = box_wall_width * 2, r=switch_hole_diameter / 2, center=true, $fn=60);
        }


    
    // cut out cable hole
    translate([0,-overall_box_depth / 2,overall_box_height / 2 * 0.45]){
    rotate(90,[1,0,0]){
        cylinder(h = box_wall_width * 2, r=cable_hole_diameter / 2, center=true, $fn=60);
        }
    }
    
    // create union of four screw holes and cut them out 
    union(){
        translate([
            -(overall_box_width / 2),
            -overall_box_depth / 2 * 0.7,
            overall_box_height / 2 * 0.7]){
            screw_inner();
        }

        translate([
            -(overall_box_width / 2),
            -overall_box_depth / 2 * 0.7 + 64,
            overall_box_height / 2 * 0.7]){
            screw_inner();
        }


        translate([
            -(overall_box_width / 2),
            -overall_box_depth / 2 * 0.7 + 64,
            overall_box_height / 2 * 0.7 - 40]){
            screw_inner();
        }

        translate([
            -(overall_box_width / 2),
            -overall_box_depth / 2 * 0.7,
            overall_box_height / 2 * 0.7 - 40]){
            screw_inner();
        }
    }
}


translate([
    -(overall_box_width / 2 - screw_column_height/2),
    -overall_box_depth / 2 * 0.7,
    overall_box_height / 2 * 0.7]){
    screw_column();
}

translate([
    -(overall_box_width / 2 - screw_column_height/2),
    -overall_box_depth / 2 * 0.7 + 64,
    overall_box_height / 2 * 0.7]){
    screw_column();
}


translate([
    -(overall_box_width / 2 - screw_column_height/2 ),
    -overall_box_depth / 2 * 0.7 + 64,
    overall_box_height / 2 * 0.7 - 40]){
    screw_column();
}

translate([
    -(overall_box_width / 2 - screw_column_height/2  ),
    -overall_box_depth / 2 * 0.7,
    overall_box_height / 2 * 0.7 - 40]){
    screw_column();
}
}

module screw_column() {
    rotate(90,[0,1,0]) {
        difference(){
            cylinder(h = screw_column_height, r=screw_diameter / 2 + screw_column_wall_width, center=true, $fn=60);
            cylinder(h = screw_column_height, r=screw_diameter / 2, center=true, $fn=60);

        }
    }
}

module screw_inner(){
    rotate(90,[0,1,0]) {
        cylinder(h = screw_column_height * 2, r=screw_diameter / 2, center=true, $fn=60);
    }
}

intersection(){
//    translate([0,-500,0]) cube([1000,1000,1000], center=true);
    box();
    // translate([0,0,0])box();
}

