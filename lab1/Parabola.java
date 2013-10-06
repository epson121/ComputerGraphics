
import java.applet.Applet;
import java.awt.Graphics;
import java.awt.Color;

public class Parabola extends Applet {

  @Override
  public void init() {
    setBackground(Color.yellow);
  }
  
  @Override
  public void paint(Graphics g) {
    int w = getWidth();  // sirina appleta u pikselima
    int h = getHeight(); // visina appleta u pikselima
    
    int sx = w/10;
    int sy = h/10;
    
    int px = -sx * -5;
    int py = sy * 5;
    
    g.drawLine(0, h/2, w, h/2);
    g.drawLine(w/2, 0, w/2, h);

    g.setColor(Color.RED);

    double i = -5;
    double jump = 0.1;
    do {
      double y1 = 0.5 * i*i - 3;
      double y2 = 0.5 * (i+jump)*(i+jump) - 3;
      g.drawLine((int) (sx * i) + px, (int) (-sy * y1) + py, (int) (sx * (i+jump)) + px, (int) (-sy * y2) + py);
      i += jump;
    } while (i <= 5);

  }
  
}