
// Main case part

case_h = 19.3;
case_d = 28.2;
case_r = case_d/2;
gap = .5;

color([.75, .75, .75])
cylinder(case_h, case_r, case_r, center=true);

translate([0, 0, -case_h/2]) {
    color([.9, .9, .9])
    cylinder(gap/10, case_r-gap*3, case_r-gap*3, center=true);
}

translate([0, 0, gap/1.25-case_h/2]) rotate([180, 0, 180]) {
    color([.5, .7, .6])
    text("28BYJ48", 3, font="Liberation Sans", halign="center");
}

// Wire connector block

wcb_w = 16.9;
wcb_d = 7.2;
wcb_h = 17.7;

translate([0, -case_r, (case_h-gap)/2]) {
  color([.75, .75, .75])
  cube([wcb_w, wcb_d, gap], center=true);
}

translate([0, -case_r, (case_h-wcb_h - gap)/2]) {
  color([0, 0, 1])
  cube([wcb_w, wcb_d, wcb_h - gap], center=true);
}

// overhang
oh_h = 1;
oh_d = 9.2;
oh_r = oh_d/2;
oh_shift = 7.25;

translate([0, oh_shift, case_h/2 + oh_h/2]) {
  color([.75, .75, .75])
  cylinder(oh_h, oh_r, oh_r, center = true);
}

// The shaft

shaft_h = 9;
shaft_d = 5;
shaft_r = shaft_d/2;

translate([0, oh_shift, 20]) {
  color([1, 1, .75])
  cylinder(shaft_h, shaft_r, shaft_r, center = true);
}