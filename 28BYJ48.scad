
// Main case part

case_h = 19.3;
case_d = 28.2;
case_r = case_d/2;

cylinder(case_h, case_r, case_r, center=true);

// Wire connector block

wcb_w = 16.9;
wcb_d = 7.2;
wcb_h = 17.7;

translate([0, -case_r, (case_h-wcb_h)/2])
  cube([wcb_w, wcb_d, wcb_h], center=true);

// overhang
oh_h = 1;
oh_d = 9.2;
oh_r = oh_d/2;

oh_shift = 7.25;

translate([0, oh_shift, case_h/2 + oh_h/2])
  cylinder(oh_h, oh_r, oh_r, center = true);

// The shaft

shaft_h = 9;
shaft_d = 5;
shaft_r = shaft_d/2;

#translate([0, oh_shift, 20])
  cylinder(shaft_h, shaft_r, shaft_r, center = true);
