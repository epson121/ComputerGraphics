
import java.applet.Applet;
import java.awt.Graphics;
import java.awt.Color;

public class Elipse extends Applet {

  @Override
  public void init() { 
    setBackground(Color.yellow);   
  }

  @Override
  public void paint(Graphics g) {
    GKS gks = new GKS(g, -5, 5, -5, 5, getWidth(), getHeight());
    gks.postaviBoju(Color.black);
    int a = 4, b = 2;
    double phi;
    double x, y;
    double step = 0.01;
    // draw axis
    gks.postaviNa(-5, 0);
    gks.linijaDo(5, 0);
    gks.postaviNa(0, 5);
    gks.linijaDo(0, -5);
 
    gks.postaviBoju(Color.red);
    gks.postaviNa(a * Math.cos(0), b * Math.sin(0));
    for(phi = 0; phi <= 2.0 * Math.PI + step; phi += step) {
      x = a * Math.cos(phi);
      y = b * Math.sin(phi);
      gks.linijaDo(x, y);
    }
  }
}