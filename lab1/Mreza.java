
import java.applet.Applet;
import java.awt.Graphics;
import java.awt.Color;

public class Mreza extends Applet {

  @Override
  public void init() {
    setBackground(Color.yellow);
  }

  @Override
  public void paint(Graphics g) {
    int w = getWidth();  // sirina appleta u pikselima
    int h = getHeight(); // visina appleta u pikselima
    
    g.setColor(Color.RED);

    for (int i = 1; i <= w; i+=40) {
            g.drawLine(i, 0, i, w);
    }
    
    for (int i = 1; i <= h; i+=40) {
            g.drawLine(0, i, w, i);
    }
    
  }
}