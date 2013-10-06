
import java.applet.Applet;
import java.awt.Graphics;
import java.awt.Color;

public class Sinus extends Applet {

  @Override
  public void init() {
    setBackground(Color.yellow);
  }
  
  @Override
  public void paint(Graphics g) {
    int w = getWidth();  // sirina appleta u pikselima
    int h = getHeight(); // visina appleta u pikselima
    
    int sx = w/6;
    int sy = h/2;
    
    //xmin
    int px = -sx * 0;
    //ymax
    int py = sy * 1;
    
    g.drawLine(0, h/2, w, h/2);
    //g.drawLine(w/2, 0, w/2, h);

    g.setColor(Color.RED);

    double i = 0;
    double jump = 0.1;
    do {
      double y1 = Math.sin(i);
      double y2 = Math.sin(i+jump);
      g.drawLine((int) (sx * i) + px, (int) (-sy * y1) + py, (int) (sx * (i+jump)) + px, (int) (-sy * y2) + py);
      i += jump;
    } while (i <= 6);

  }
  
}