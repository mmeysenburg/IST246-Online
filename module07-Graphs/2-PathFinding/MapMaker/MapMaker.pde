PImage tiger = loadImage("thomasTile.png");
tiger.resize(30, 30);
PImage bell = loadImage("bellTile.png");
bell.resize(30, 30);
PImage concrete = loadImage("concreteTile.png");
concrete.resize(30, 30);
PImage sand = loadImage("sandTile.png");
sand.resize(30, 30);
PImage water = loadImage("waterTile.png");
water.resize(30, 30);
PImage bricks = loadImage("bricksTile.png");
bricks.resize(30, 30);

String[] map = loadStrings("map.txt");

size(600, 600);
background(0);

int r = 0, c = 0;
for(String line : map) {
  c = 0;
  for(int i = 0; i < line.length(); i++) {
    switch(line.charAt(i)) {
      case 'c':
        image(concrete, c, r);
        break;
      case 's':
        image(sand, c, r);
        break;
      case 'w':
        image(water, c, r);
        break;
      case 'b':
        image(tiger, c, r);
        break;
      case 'e':
        image(bell, c, r);
        break;
      case 'x':
        image(bricks, c, r);
        break;
    }
    c += 30;
  }
  r += 30;
}

save("map.png");

String[] path = loadStrings("path.txt");

stroke(255, 0, 0);
strokeWeight(2);
noFill();
for(String line : path) {
  String[] tokens = line.split(", ");
  r = Integer.parseInt(tokens[0].trim()) * 30;
  c = Integer.parseInt(tokens[1].trim()) * 30;
  rect(c, r, 30, 30);
}

save("solved.png");
