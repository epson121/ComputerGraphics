
import java.applet.Applet;
import java.awt.Graphics;
import java.awt.Color;

public class GKSElipse extends Applet {

  @Override
  public void init() { 
    setBackground(Color.yellow);   
  }

  @Override
  public void paint(Graphics g) {
    GKS gks = new GKS(g, -10, 10, -5, 5, getWidth(), getHeight());
    gks.postaviBoju(Color.black);
    double step = 0.01;
    // draw axis
    gks.postaviNa(-10, 0);
    gks.linijaDo(10, 0);
    gks.postaviNa(0, 5);
    gks.linijaDo(0, -5);
    
    MT2D mt = new MT2D();
    
    gks.postaviBoju(Color.red);
    mt.pomakni(4.0, 2.0);
    gks.trans(mt);
    elipse(gks, 4.0, 2.0, step);

    gks.postaviBoju(Color.blue);
    mt.rotiraj(30.0);
    gks.trans(mt);
    elipse(gks, 4.0, 2.0, step);

  }

  public void elipse(GKS gks, double a, double b, double step) {
    double phi;
    double x, y;
    gks.postaviNa(a * Math.cos(0), b * Math.sin(0));
    for(phi = 0; phi <= 2.0 * Math.PI + step; phi += step) {
      x = a * Math.cos(phi);
      y = b * Math.sin(phi);
      gks.linijaDo(x, y);
    }
  }
}